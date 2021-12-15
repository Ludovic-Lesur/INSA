/*
 * StepMotor.h (adapted from Stepper.h of Arduino Library, only for step motors using ULN2803 circuit with two control pins)
 *
 * Created: 01/06/2016
 * Author: Ludovic Lesur
 */ 


#ifndef STEPMOTOR_H
#define STEPMOTOR_H


#include "Arduino.h"


// Maximum speed of the motor in revolutions per minute (RPM)
#define SPEED_MAX 400
// Number of steps of the motor 28BYJ-48
#define NB_STEPS 64


class StepMotor {
	
	private :
	
	int direction ; // Direction of rotation
	int speed ; // Speed in revolutions per minute (RPM)
	unsigned long stepDelay ; // Delay between two consecutive steps in ms, based on 'speed'
	int numberOfSteps ; // Number of steps of the motor
	int stepNumber ; // Which step the motor is on
	int motorPin1 ;
	int motorPin2 ;
	unsigned long lastStepTime ; // Time stamp (in µs) of when the last step was taken
	void coilStep(int thisStep) ;
	
	public :
	
	/* Constructors */

	StepMotor() ;
	StepMotor(int pNumberOfSteps, int pMotorPin1, int pMotorPin2) ;
	
	/* Methods */
	
	void init() ;
	void setSpeed(long newSpeed) ;
	void step(int stepsToMove) ;
	
} ;

#endif