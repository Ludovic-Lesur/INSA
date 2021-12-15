/*
 * DynamicBar.cpp
 *
 * Created: 01/06/2016
 * Author: Ludovic Lesur
 */


#include "DynamicBar.h"


/**
	CONSTRUCTOR WITHOUT ARGUMENT FOR CLASS DYNAMICBAR.
	@param		None.
	@return 	None.
*/
DynamicBar::DynamicBar() {
	barNumber = 0 ;
	direction = false ;
	stepsToTop = 0 ;
	currentStep = 0 ;
	heightOrder = 0 ;
	currentHeight = 0 ;
	bottomCalib = false ;
	topCalib = false ;
	ready = false ;
	swinging = false ;
	directionVibration = false ;
}


/**
	CONSTRUCTOR WITH ARGUMENTS FOR CLASS DynamicBar.
	@param pMotor :			StepMotor object attached to the bar.
	@param pDirection :		Direction of motor revolution (NORMAL or INVERTED).
	@param pBottom :		Digital input pin attached to the bottom-stop button.
	@param pTop :			Digital input pin attached to the top-stop button.
	@param pSwitchBar :		Analog output pin attached to the general transistor.
	@param pVoiceButton :	Digital input pin attached to the voice synthesis button.
	@return 				None.
*/
DynamicBar::DynamicBar(int pBarNumber, StepMotor pMotor, boolean pDirection, uint32_t pBottom, uint32_t pTop, uint32_t pSwitchBar, uint32_t pVoiceButton) {
	barNumber = pBarNumber ;
	motor = pMotor ;
	direction = pDirection ;
	bottom = pBottom ;
	top = pTop ;
	switchBar = pSwitchBar ;
	voiceButton = pVoiceButton ;
	currentStep = 0 ;
	heightOrder = 0 ;
	currentHeight = 0 ;
	bottomCalib = false ;
	topCalib = false ;
	ready = false ;
	swinging = false ;
	directionVibration = false ;
}


/**
	PINS INITIALISATION.
	@param		None.
	@return 	None.
*/
void DynamicBar::init() {
	motor.init() ;
	stepsToTop = 0 ;
	bottomCalib = false ;
	topCalib = false ;
	ready = false ;
	// Pin modes
	pinMode(bottom, INPUT_PULLUP) ;
	pinMode(top, INPUT_PULLUP) ;
	pinMode(voiceButton, INPUT_PULLUP) ;
	switchOn() ;
}


/**
	CALIBRATES THE STEP MOTOR CALCULATING 'stepsToTop' VALUE.
	@param				None.
	@return ready		Boolean indicating if calibration is done.
*/
boolean DynamicBar::calibrate() {
	// Find bottom position
	if (bottomCalib == false) {
		down() ;
		if (digitalRead(bottom) == LOW) {
			bottomCalib = true ;
		}
	}
	else {
		// Find top position and calculate stepsToTop
		if (topCalib == false) {
			up() ;
			// Save the number of steps to attain maximum height
			stepsToTop ++ ;
			if (digitalRead(top) == LOW) {
				topCalib = true ;
			}
		}
		else {
			// Return to bottom position
			if (ready == false) {
				down() ;
				if (digitalRead(bottom) == LOW) {
					ready = true ;
					currentStep = 0 ;
					calculateHeight() ;
					switchOff() ;
				}
			}
		}
	}
	return ready ;
}


/**
	CONVERTS CURRENT NUMBER OF STEPS INTO HEIGHT IN %.
	@param		None.
	@return		None.
*/
void DynamicBar::calculateHeight() {
	currentHeight = (int) 100.0*((float)currentStep / (float)stepsToTop) ;
}


/**
	SET HEIGHT ORDER (MOVEMENT INSTRUCTION OR POURCENTAGE)
	@param newPourcent		New order in %.
	@return					None.
*/
void DynamicBar::setHeightOrder(int newPourcent) {
	// Ensure heightOrder is known
	switch (newPourcent) {
	// Movement instructions
	case INSTRUCTION_SWING :
		heightOrder = INSTRUCTION_SWING ;
		break ;
	case INSTRUCTION_VIBRATION :
		heightOrder = INSTRUCTION_VIBRATION ;
		break ;
	case INSTRUCTION_IMMOBILE :
		heightOrder = INSTRUCTION_IMMOBILE ;
		break ;
	default :
		// It's pourcentage...
		if (newPourcent > 100) {
			heightOrder = 100 ;
		}
		else {
			if (heightOrder < 0) {
				heightOrder = 0 ;
			}
			else {
				heightOrder = newPourcent ;
			}
		}
	}
}


/**
	POSITIVE STEP ON THE MOTOR.
	@param		None.
	@return		None.
*/
void DynamicBar::positiveStep() {
	motor.step(1) ;
}


/**
	NEGATIVE STEP ON THE MOTOR.
	@param		None.
	@return		None.
*/
void DynamicBar::negativeStep() {
	motor.step(-1) ;
}


/**
	ONE STEP UP TAKING TO ACCOUNT 'direction'.
	@param		None.
	@return		None.
*/
void DynamicBar::up() {
	if (direction == false) {
		positiveStep() ;
	}
	else {
		negativeStep() ;
	}
	currentStep++ ;
}


/**
	ONE STEP DOWN TAKING TO ACCOUNT 'direction'.
	@param		None.
	@return		None.
*/
void DynamicBar::down() {
	if (direction == false) {
		negativeStep() ;
	}
	else {
		positiveStep() ;
	}
	currentStep-- ;
}


/**
	MAKES THE BAR SWING.
	@param		None.
	@return		None.
*/
void DynamicBar::swing() {
	if (swinging == false) {
		swinging = true ;
		offsetTime = millis() ;
	}
	switchOn() ;
	if (directionVibration == false) {
		up() ;
	}
	else {
		down() ;
	}
	// Invert direction every <PERIOD_SWING> ms.
	if (millis() > offsetTime+PERIOD_SWING) {
		offsetTime = millis() ;
		directionVibration = !directionVibration ;
	}
}


/**
	MAKES THE BAR VIBRATE.
	@param		None.
	@return		None.
*/
void DynamicBar::vibrate() {
	switchOn() ;
	if (directionVibration == false) {
		up() ;
	}
	else {
		down() ;
	}
	// Invert direction every times the function is called.
	directionVibration = !directionVibration ;
}


/**
	SWITCH ON THE PCB WITH ULN2003A.
	@param		None.
	@return		None.
*/
void DynamicBar::switchOn() {
	analogWrite(switchBar, 255) ;
}


/**
	SWITCH OFF THE PCB WITH ULN2003A.
	@param		None.
	@return		None.
*/
void DynamicBar::switchOff() {
	analogWrite(switchBar, 0) ;
}


/**
	MAIN REGULATION FUNCTION.
	@param				None.
	@return	updating	Boolean indicating if one bar (at least) is currently moving.
*/
boolean DynamicBar::update() {
	boolean updating = false ;
	calculateHeight() ;
	// Decode instruction...
	switch (heightOrder) {
	case INSTRUCTION_SWING :
		swing() ;
		break ;
	case INSTRUCTION_VIBRATION :
		vibrate() ;
		swinging = false ;
		break ;
	case INSTRUCTION_IMMOBILE :
		switchOff() ;
		swinging = false ;
		break ;
	// Launches regulation loop if height Order is pourcentage
	default :
		// Bar is too low...
		if ((currentHeight > heightOrder) && (digitalRead(bottom) == HIGH)) {
			switchOn() ;
			down() ;
			updating = true ;
		}
		else {
			// Bar is too high...
			if ((currentHeight < heightOrder) && (digitalRead(top) == HIGH)) {
				switchOn() ;
				up() ;
				updating = true ;
			}
			else {
				// If position is correct -> switch off motor
				switchOff() ;
			}
		}
	}
	// If voice button is pressed -> send the barNumber to the Java program
	if (digitalRead(voiceButton) == LOW) {
		if (voicePressed == false) {
			voicePressed = true ;
			// We send the opposed number because bar numbers are inverted from the front view
			Serial.write(NUMBER_OF_BARS-barNumber-1) ;
		}
	}
	else {
		voicePressed = false ;
	}
	return updating ;
}