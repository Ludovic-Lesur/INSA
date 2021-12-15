/*
* StepMotor.cpp (adapted from Stepper.h of Arduino library)
*
* Created: 01/06/2016
* Author: Ludovic Lesur
*/


#include "StepMotor.h"


/**
	CONSTRUCTOR WITHOUT ARGUMENT FOR CLASS STEPMOTOR.
	@param		None.
	@return 	None.
*/
StepMotor::StepMotor() {
	speed = 0 ;
	direction = 0 ;
	stepNumber = 0 ;
	motorPin1 = 0 ;
	motorPin2 = 0 ;
	numberOfSteps = 0 ;
	lastStepTime = 0 ;
}


/**
	CONSTRUCTOR FOR CLASS STEPMOTOR.
	@param pNumberOfSteps :		The number of steps of the used motor.
	@param pMotorPin1 :			The pin driving the first control signal.
	@param pMotorPin2 :			The pin driving the second control signal.
	@return 	None.
*/
StepMotor::StepMotor(int pNumberOfSteps, int pMotorPin1, int pMotorPin2) {
	speed = 0 ;
	direction = 0 ;
	stepNumber = 0 ;
	numberOfSteps = pNumberOfSteps ;
	motorPin1 = pMotorPin1 ;
	motorPin2 = pMotorPin2 ;
	lastStepTime = 0 ;
}


/**
	DEFINES THE CONTROL SEQUENCE OFF THE STEP MOTOR.
	@param thisStep :		The current step's number.
	@return 				None.
*/
void StepMotor::coilStep(int thisStep) {
	switch (thisStep) {
	case 0 : // 01
		digitalWrite(motorPin1, LOW) ;
		digitalWrite(motorPin2, HIGH) ;
		break ;
	case 1 : // 11
		digitalWrite(motorPin1, HIGH) ;
		digitalWrite(motorPin2, HIGH) ;
		break ;
	case 2 : // 10
		digitalWrite(motorPin1, HIGH) ;
		digitalWrite(motorPin2, LOW) ;
		break ;
	case 3 : // 00
		digitalWrite(motorPin1, LOW) ;
		digitalWrite(motorPin2, LOW) ;
		break ;
	}
}


/**
	PINS AND SPEED INITIALISATION.
	@param		None.
	@return 	None.
*/
void StepMotor::init() {
	pinMode(motorPin1, OUTPUT) ;
	pinMode(motorPin2, OUTPUT) ;
	setSpeed(SPEED_MAX) ;
}


/**
	CHANGES THE REVOLTION SPEED OF THE STEP MOTOR.
	@param newSpeed		The new speed to apply.
	@return 			None.
*/
void StepMotor::setSpeed(long newSpeed) {
	int realSpeed = newSpeed ;
	// Ensure newSpeed <= SPEED_MAX
	if (realSpeed > SPEED_MAX) {
		realSpeed = SPEED_MAX ;
	}
	stepDelay = 60L * 1000L * 1000L / numberOfSteps / realSpeed ;
}


/**
	MOVER METHOD.
	@param stepsToMove		The number of steps the motor have to do.
	@return 				None.
*/
void StepMotor::step(int stepsToMove) {
	// How many steps to take
	int stepsLeft = abs(stepsToMove) ;
	
	// Determine direction based on whether 'stepsToMove' is + or -
	if (stepsToMove > 0) {
		direction = 1 ;
	}
	if (stepsToMove < 0) {
		direction = 0 ;
	}

	// Decrement the number of steps, moving one step each time
	while (stepsLeft > 0) {
		unsigned long now = micros() ;
		// Move only if the appropriate delay has passed
		if (now - lastStepTime >= stepDelay) {
			// Get the timeStamp of when you stepped
			lastStepTime = now ;
			// Increment or decrement the step number, depending on direction
			if (direction == 1) {
				stepNumber ++ ;
				if (stepNumber == numberOfSteps) {
					stepNumber = 0 ;
				}
			}
			else {
				if (stepNumber == 0) {
					stepNumber = numberOfSteps ;
				}
				stepNumber -- ;
			}
			// Decrement the steps left
			stepsLeft -- ;
			coilStep(stepNumber % 4) ;
		}
	}
}