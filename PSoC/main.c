/* ========================================
 *
 * B.E. Systèmes Embarqués Autonomes.
 * INSA 5ESE 2016-2017.
 *
 * Author: Taha BENAICHA, Ludovic LESUR, Benjamin ROQUES and Anas RCHI.
 * Since: 15/12/2016
 *
 * ========================================
 */


/* INCLUDES */

#include "project.h"
#include <stdio.h>
#include <math.h>


/* MACRO DECLARATION */

#define SOUND_SPEED 0.34 // Sound speed (in mm/µs).
#define SPACE_RX_TX 48 // Space between transmitter and receiver on PCB (in mm).
#define DISTANCE_MIN 200 // Minimum distance before disabling front movement.

// According to experimental data, a corrective ax+b equation has been found with MATLAB.
// Linear regression : correctDistance = a*measure+b.
#define coef_a 1.1723
#define coef_b -48.0862

/* INSTRUCTIONS */

// Vitesse
#define I_LOW_SPEED 0x6B // k
#define I_MEDIUM_SPEED 0x6C // l
#define I_HIGH_SPEED 0x6D // m

// Movement
#define I_FORWARD 0x7A // z
#define I_STOP 0x73 // s
#define I_BACK 0x77 // w
#define I_LEFT 0x71 // q
#define I_RIGHT 0x64 // d
#define I_FORWARD_RIGHT 0x65 // e
#define I_FORWARD_LEFT 0x61 // a


/* GLOBAL VARIABLES */

char response ; // Indicate if the feedback is detected by the comparator.
double chrono ; // Time between the sending and the 
double distance ; // Raw distance computed with d = v*t.
double realDistance ; // Real distance taking to account 'SPACE_RX_TX'.
double calibratedDistance ;
char8 str[10] ; // Result displayed on the LCD screen.
uint8 vitesse = 0 ;
char instruction = 0 ;


/* COMPUTES DISTANCE ACCORDING TO THE TELEMETER.
 *
 * @param :     None.
 * @return :    None.
 */
void computeDistance() {
    distance = SOUND_SPEED*chrono ;
    realDistance = 0.5*sqrt(pow(distance,2)-pow(SPACE_RX_TX,2)) ;
    calibratedDistance = coef_a*realDistance+coef_b ;
}


/* UPDATES DUTY CYCLE WITH THE SELECTED SPEED.
 *
 * @param :     None.
 * @return :    None.
 */
void update_vitesse(void) {
    PWM_Front_WriteCompare1(vitesse) ;
    PWM_Front_WriteCompare2(vitesse) ;
    PWM_Back_WriteCompare1(vitesse) ;
    PWM_Back_WriteCompare2(vitesse) ;
}


/* HANDLER CALLED EVERY 10ms (TX INTERRUPT).
 *
 * @param :     None.
 * @return :    None.
 */
CY_ISR(Interrupt_TX_Handler) {
    if (response == 0) {
        // No feedback
        sprintf(str, "D = Infinie") ;
    }
    else {
        // Distance successfully computed
        sprintf(str, "D = %d mm", (int)calibratedDistance) ;
    }
    // Displays result on LCD screen.
    LCD_Position(1u, 0u) ;
	LCD_PrintString("              ") ;
    LCD_Position(1u, 0u) ;
    LCD_PrintString(str) ;
    
    // Start new measure.
    response = 0 ;
}


/* HANDLER CALLED IF A FEEDBACK IS DETECTED BY THE COMPARATOR.
 *
 * @param :     None.
 * @return :    None.
 */
CY_ISR(Interrupt_RX_Handler) {
    // If the handler wasn't called yet... (= It's the first peak detected).
    if (response == 0) {
        response = 1 ;
        // Update chrono.
        chrono = ((double)Chronometer_ReadCounter())/(6.0) ; // (Clk = 6 MHz).
        computeDistance() ;
    }
}


/* HANDLER CALLED IF A CHAR IS RECEIVED BY THE XBEE MODULE
 *
 * @param :     None.
 * @return :    None.
 */
CY_ISR(Interrupt_Xbee_Handler) {
    
    instruction = XBee_GetChar() ;
        
    sprintf(str, "I = %c", instruction) ;
    LCD_Position(0u, 0u) ;
	LCD_PrintString("              ") ;
    LCD_Position(0u, 0u) ;
    LCD_PrintString(str) ;
}


/* STOP.
 *
 * @param :     None.
 * @return :    None.
 */
void stop() {
    Rotation_Register_Write(0x00) ; // '00000000'
}


/* GO FORWARD.
 *
 * @param :     None.
 * @return :    None.
 */
void forward() {
    if ((response == 0) || (calibratedDistance >= DISTANCE_MIN)) {
        Rotation_Register_Write(0xAA) ; // '10100110'
    }
    else {
        stop() ;
    }
}


/* GO BACKWARD.
 *
 * @param :     None.
 * @return :    None.
 */
void backward() {
    Rotation_Register_Write(0x55) ; // '01011001'
}

/* MAIN FUNCTION
 *
 * @param :     None.
 * @return :    None.
 */
int main(void) {

    // Initialisations
    Clk_Start() ;
    Clock_1_Start() ;
    Clock_2_Start() ;
    
    LCD_Start() ;
    LCD_ClearDisplay() ;
    
    Chronometer_Start() ;
    Comparator_Start() ;
    Counter_Pulses_Start() ;
    Out_MAX232_Start() ;
    Pre_Ampli_Start() ;
    Threshold_Start() ;
    Timer_TX_Start() ;
    
     // Enables global interrupts.
    CyGlobalIntEnable ;
    
    // Links interrupts and corresponding handlers.
    Interrupt_TX_StartEx(Interrupt_TX_Handler) ;
    Interrupt_RX_StartEx(Interrupt_RX_Handler) ;
    Interrupt_Xbee_StartEx(Interrupt_Xbee_Handler) ;
    
    XBee_Init() ;
    XBee_Start() ;
    PWM_Front_Start() ;
    PWM_Back_Start() ;
    
    uint8 c = 0 ; // Variable à 3 états (obliger passage par tout droit avanat de tourner
    stop() ; // Arret au debut
    
    // Application code.
    while (1) {
        
        // Choix vitesse
        switch (instruction) {
        case (I_LOW_SPEED) :
            vitesse = 127 ;
            break ;
        case (I_MEDIUM_SPEED) : 
            vitesse = 191 ;  
            break ;
        case (I_HIGH_SPEED) : 
            vitesse = 220u ;
            break ; 
        }
        
        // Mouvements
        
        // Avancer vers l'avant
        if (instruction == I_FORWARD) {  
            forward() ;
            update_vitesse() ;
            c = 0 ;
        }
        // Reculer
        if (instruction == I_BACK) {  
            backward() ;
            update_vitesse() ;
            c = 0 ;
        }
        // Tourner à droite
        if (instruction == I_RIGHT) {
            Rotation_Register_Write(0xA5) ; // '10100101'
            update_vitesse() ;
            c = 0 ;
        }
        // Tourner à gauche
        if (instruction == I_LEFT) { 
            Rotation_Register_Write(0x5A) ; // '01011010'
            update_vitesse() ;
            c = 0 ;
        }
        // Arret
        if (instruction == I_STOP) { 
            stop() ;
            update_vitesse() ;
            c = 0 ;
        }
        // Tourner à gauche en avançant  
        if ((instruction == I_FORWARD_LEFT) && (c != 2) && (c != 1)) {                  
            PWM_Front_WriteCompare2(PWM_Front_ReadCompare1()+30) ;
            PWM_Back_WriteCompare2(PWM_Back_ReadCompare1()+30) ;
            forward() ;
            c = 1 ;
        }
        // Tourner à droite en avançant
        if ((instruction == I_FORWARD_RIGHT) && (c != 1) &&( c != 2)) { 
            PWM_Front_WriteCompare1(PWM_Front_ReadCompare1()+30) ;
            PWM_Back_WriteCompare1(PWM_Back_ReadCompare1()+30) ;
            forward() ;
            c = 2 ;
        }
    }
}