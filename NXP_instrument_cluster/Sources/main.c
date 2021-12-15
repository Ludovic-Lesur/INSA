#include "MPC5645S.h"
#include "ext_global.h"
#include "init_watchd_pll.h"
#include "gpio.h"
#include "port.h"
#include "can.h"
#include "step_motors.h"
#include "dcu.h"
#include "lcd.h"
#include "pit.h"
#include "IntcInterrupts.h"


// Function prototypes.
void enableIrq(void) ;
void PIT_CH0_ISR(void) ;
void PIT_CH1_ISR(void) ;

// Step motors structures.
struct StepMotor speedIndicator ;
struct StepMotor rpmIndicator ;
struct StepMotor oilIndicator ;
struct StepMotor temperatureIndicator ;

// Step motors pointers.
struct StepMotor* ptrSpeedIndicator = &speedIndicator ;
struct StepMotor* ptrRpmIndicator = &rpmIndicator ;
struct StepMotor* ptrOilIndicator = &oilIndicator ;
struct StepMotor* ptrTemperatureIndicator = &temperatureIndicator ;

// Indicates if cluster initialisation is done.
int init = 0 ;

// Test code
int valSpeed = 0 ;
int sensSpeed = 0 ;
int valRPM = 0 ;
int sensRPM = 0 ;
int valOil = 0 ;
int sensOil = 0 ;
int valTemperature = 0 ;
int sensTemperature = 0 ;


/** 
 * MAIN FUNCTION. 
 *
 * @param 	None.	
 * @return	None.
 */
int main(void) {
	
	DISABLE_WATCHDOG() ;
	MC_MODE_INIT_PLL() ; // Run0 mode: fClk = 100 MHz.
	enableIrq() ;
	
	// SMC initialisation.
	initSMC() ;
	
	// PIT initialisation.
	Init_PIT() ;
	
	// Initialisation timer
	Set_Counter_Value_PIT(0, 0x1DCD6500) ;
	Autorize_IT_PIT(0) ;
	Start_PIT(0) ;
	
	// Microstep timer
	Set_Counter_Value_PIT(TIMER_SMC, MICROSTEP_TIME) ;
	Autorize_IT_PIT(TIMER_SMC) ;
	Start_PIT(TIMER_SMC) ;
	
	// Step motors creation
	setParameters(ptrSpeedIndicator, PD0, PD1, PD2, PD3, 0, 1,
				  MIN_SPEED_INDICATOR, MAX_SPEED_INDICATOR,
				  OFFSET_SPEED_INDICATOR, FULL_SCALE_SPEED_INDICATOR, LOGIC_SPEED_INDICATOR) ;
	setParameters(ptrRpmIndicator, PD4, PD5, PD6, PD7, 2, 3,
				  MIN_RPM_INDICATOR, MAX_RPM_INDICATOR,
				  OFFSET_RPM_INDICATOR, FULL_SCALE_RPM_INDICATOR, LOGIC_RPM_INDICATOR) ;
	setParameters(ptrOilIndicator, PD8, PD9, PD10, PD11, 4, 5,
				  MIN_OIL_INDICATOR, MAX_OIL_INDICATOR,
				  OFFSET_OIL_INDICATOR, FULL_SCALE_OIL_INDICATOR, LOGIC_OIL_INDICATOR) ;
	setParameters(ptrTemperatureIndicator, PD12, PD13, PD14, PD15, 6, 7,
				  MIN_TEMPERATURE_INDICATOR, MAX_TEMPERATURE_INDICATOR,
				  OFFSET_TEMPERATURE_INDICATOR, FULL_SCALE_TEMPERATURE_INDICATOR, LOGIC_TEMPERATURE_INDICATOR) ;
	
	// Step motors initialisation
	initStepMotor(ptrSpeedIndicator) ;
	initStepMotor(ptrRpmIndicator) ;
	initStepMotor(ptrOilIndicator) ;
	initStepMotor(ptrTemperatureIndicator) ;

	// Loop forever
	while(1) {
	}
}


/** 
 * ENABLES INTERRUPTS.
 *
 * @param 	None.	
 * @return	None.
 */
void enableIrq(void) {
  INTC.CPR.B.PRI = 0 ;
  asm("wrteei 1") ; // Enable external interrupts
  INTC_InstallINTCInterruptHandler(PIT_CH0_ISR, 59, 3) ; // Enable TIMER 0 interrupt and set priority
  INTC_InstallINTCInterruptHandler(PIT_CH1_ISR, 60, 2) ; // Enable TIMER 1 interrupt and set priority
}


/** 
 * TIMER 0 HANDLER. USED FOR CLUSTER INITIALISATION (5s). 
 *
 * @param 	None.	
 * @return	None.
 */
void PIT_CH0_ISR(void) {
	
	Clear_Flag_PIT(0) ;
	
	if (init == 0) {
		resetCurrentStep(ptrSpeedIndicator) ;
		resetCurrentStep(ptrRpmIndicator) ;
		resetCurrentStep(ptrOilIndicator) ;
		resetCurrentStep(ptrTemperatureIndicator) ;
		init = 1 ;
	}
}


/** 
 * TIMER 1 HANDLER. USED TO CONTROL ALL THE STEP MOTORS.
 *
 * @param 	None.	
 * @return	None.
 */
void PIT_CH1_ISR(void) {
	
	Clear_Flag_PIT(TIMER_SMC) ;
	
	if (init == 0) {
		// During initialisation, the 4 needles are reseted.
		calibrate(ptrSpeedIndicator) ;
		calibrate(ptrRpmIndicator) ;
		calibrate(ptrOilIndicator) ;
		calibrate(ptrTemperatureIndicator) ;
	}
	else {
		// After initialisation, all step motors are continuously updated.
		update(ptrSpeedIndicator) ;
		update(ptrRpmIndicator) ;
		update(ptrOilIndicator) ;
		update(ptrTemperatureIndicator) ;
		
		/*** TEST CODE ***/
		
		// Update test values
		if (sensSpeed == 1) {
			valSpeed++ ;
		}
		else {
			valSpeed-- ;
		}
		
		if (sensRPM == 1) {
			valRPM = valRPM + 100 ;
		}
		else {
			valRPM = valRPM - 100 ;
		}
		
		if (sensOil == 1) {
			valOil++ ;
		}
		else {
			valOil-- ;
		}
		
		if (sensTemperature == 1) {
			valTemperature++ ;
		}
		else {
			valTemperature-- ;
		}
		
		// Update direction
		if (isAtMinimum(ptrSpeedIndicator)) {
			sensSpeed = 1 ;
		}
		if (isAtMaximum(ptrSpeedIndicator)) {
			sensSpeed = 0 ;
		}
		
		if (isAtMinimum(ptrRpmIndicator)) {
			sensRPM = 1 ;
		}
		if (isAtMaximum(ptrRpmIndicator)) {
			sensRPM = 0 ;
		}
		
		if (isAtMinimum(ptrOilIndicator)) {
			sensOil = 1 ;
		}
		if (isAtMaximum(ptrOilIndicator)) {
			sensOil = 0 ;
		}
		
		if (isAtMinimum(ptrTemperatureIndicator)) {
			sensTemperature = 1 ;
		}
		if (isAtMaximum(ptrTemperatureIndicator)) {
			sensTemperature = 0 ;
		}
		
		setOrder(ptrSpeedIndicator, valSpeed) ;
		setOrder(ptrRpmIndicator, valRPM) ;
		setOrder(ptrOilIndicator, valOil) ;
		setOrder(ptrTemperatureIndicator, valTemperature) ;
	}
}


/* MISE A JOUR DES VALEURS CONSIGNES
 * 
 * Dans l'interruption liée au bus CAN, on reçoit la valeur 'v' à afficher sur le cadran géré par le moteur 'm'.
 * Après décodage du message CAN, on appelle la fonction setOrder(m, v) ;
 */
