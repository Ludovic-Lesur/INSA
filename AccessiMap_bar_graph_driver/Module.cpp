/*
 * Module.cpp
 *
 * Created: 02/06/2016
 * Author: Ludovic Lesur
 */ 


#include "Module.h"


/**
	CONSTRUCTOR FOR CLASS MODULE.
	@param pListOfBars		<NUMBER_OF_BARS>-array containing DynamicBar objects.
	@param pCalib			Digital input pin attached to the calibration button.
	@param pLedCalib		Digital output pin attached to the calibration LED.
	@param pLedUpdating		Digital output pin attached to the update LED.
	@return 				None.
*/
Module::Module(DynamicBar* pListOfBars, uint32_t pCalib, uint32_t pLedCalib, uint32_t pLedUpdating) {
	listOfBars = pListOfBars ;
	currentByte = -1 ;
	previousByte = -1 ;
	currentNumber = -1 ;
	currentPourcent = -1 ;
	previousNumber = -1 ;
	calib = pCalib ;
	ledCalib = pLedCalib ;
	ledUpdating = pLedUpdating ;
}


/**
	MODULE INITIALISATION.
	@param		None.
	@return 	None.
*/
void Module::init() {
	// Set pins mode and initial tension for outputs.
	pinMode(calib, INPUT_PULLUP) ;
	pinMode(ledCalib, OUTPUT) ;
	digitalWrite(ledCalib, LOW) ;
	pinMode(ledUpdating, OUTPUT) ;
	digitalWrite(ledUpdating, LOW) ;
	// Initialisation of each bar
	int i = 0 ;
	for (i=0 ; i<NUMBER_OF_BARS ; i++) {
		listOfBars[i].init() ;
	}
	boolean ready = false ;
	// Auto-calibration
	digitalWrite(ledCalib, HIGH) ;
	while (ready == false) {
		ready = true ;
		for (i=0 ; i<NUMBER_OF_BARS ; i++) {
			if (listOfBars[i].calibrate() == false) {
				ready = false ;
			}
		}
	}
	// Calibration is done
	digitalWrite(ledCalib, LOW) ;
}


/**
	SETS 'currentByte' AND 'currentPOURCENT' WHEN SERIAL PORT EVENT OCCURS.
	@param		None.
	@return 	None.
*/
void Module::readBarData() {
	
	// If a byte is available on serial port...
	if (Serial.available() > 0) {
		currentByte = Serial.read() ;
		
		// If data is different from previous...
		if (currentByte != previousByte) {
			
			// If it's a bar number -> ensure it exists
			if ((currentByte >= 0) && (currentByte < NUMBER_OF_BARS)) {
				currentNumber = currentByte ;
			}
			
			// If it's a pourcentage or an instruction -> ensure is known
			if ((currentByte >= OFFSET) && (currentByte <= OFFSET+INSTRUCTION_IMMOBILE)) {
				currentPourcent = currentByte-OFFSET ;
			}
			
			// If it's the calibration instruction -> we call the init() function
			if (currentByte == INSTRUCTION_CALIBRATION) {
				init() ;
			}
		}
	}
	previousByte = currentByte ;
}


/**
	MAIN UPDATING FUNCTION.
	@param		None.
	@return 	None.
*/
void Module::update() {
	// Set height order if new number occurs
	if (currentNumber != previousNumber) {
		listOfBars[currentNumber].setHeightOrder(currentPourcent) ;
	}
	// Update all bars of the module
	int i = 0 ;
	boolean updating = false ;
	for (i=0 ;  i<NUMBER_OF_BARS ; i++) {
		if (listOfBars[i].update()) {
			updating = true ;
		}
	}
	// Turns on the update LED if one bar (at least) is currently moving
	if (updating == true) {
		digitalWrite(ledUpdating, HIGH) ;
	}
	else {
		digitalWrite(ledUpdating, LOW) ;
	}
	previousNumber = currentNumber ;
}