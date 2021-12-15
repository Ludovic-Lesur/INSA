/*
 * ShapeChanging.ino
 *
 * Created: 01/06/2016
 * Author: Ludovic Lesur
 */


#include "Netlist.h"
#include "Module.h"


// Declaration of each bar (step motor + dynamic bar)
StepMotor mpp1(NB_STEPS, BAR1_CMDE1, BAR1_CMDE2) ;
DynamicBar bar1(0, mpp1, NORMAL, BAR1_BPBB, BAR1_BPBH, BAR1_SWITCH, BAR1_BPSV) ;	// Module A = NORMAL
																					// Module B = INVERTED

StepMotor mpp2(NB_STEPS, BAR2_CMDE1, BAR2_CMDE2) ;
DynamicBar bar2(1, mpp2, INVERTED, BAR2_BPBB, BAR2_BPBH, BAR2_SWITCH, BAR2_BPSV) ;	// Module A = INVERTED
																					// Module B = NORMAL

StepMotor mpp3(NB_STEPS, BAR3_CMDE1, BAR3_CMDE2) ;
DynamicBar bar3(2, mpp3, INVERTED, BAR3_BPBB, BAR3_BPBH, BAR3_SWITCH, BAR3_BPSV) ;	// Module A = INVERTED
																					// Module B = INVERTED

StepMotor mpp4(NB_STEPS, BAR4_CMDE1, BAR4_CMDE2) ;
DynamicBar bar4(3, mpp4, INVERTED, BAR4_BPBB, BAR4_BPBH, BAR4_SWITCH, BAR4_BPSV) ;	// Module A = INVERTED
																					// Module B = NORMAL

// This line needs to be modified manually if NUMBER_OF_BARS (defined in DynamicModule.h) changes.
// Bars are inverted because they are inverted from the front view
DynamicBar listOfBars[NUMBER_OF_BARS] = {bar4, bar3, bar2, bar1} ;
	
// Dynamic module
Module module(listOfBars, BP_CALIB, LED_CALIB, LED_UPDATE) ;


/**
	ARDUINO BOARD INITIALISATION (CALLED 1 TIME WHEN THE BOARD TURNS ON).
	@param		None.
	@return 	None.
*/
void setup() {
	Serial.begin(9600) ; // Serial port initialisation
	analogWriteResolution(8) ;
	module.init() ; // Initialisation of module (includes auto-calibration of each bar)
}


/**
	MAIN LOOP FUNCTION (POLLING) 
	@param		None.
	@return 	None.
*/
void loop() {
	
	// If the calibration button is pressed...
	if (digitalRead(BP_CALIB) == LOW) {
		module.init() ;
	}
	else {
		module.update() ;
	}
}


/**
	EVENT FUNCTION CALLED WHEN BYTES ARE AVAILABLE ON SERIAL PORT.
	@param		None.
	@return 	None.
*/
void serialEvent() {
	module.readBarData() ;
}