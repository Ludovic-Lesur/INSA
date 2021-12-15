/*
 * DynamicBar.h
 *
 * Created: 01/06/2016
 * Author: Ludovic Lesur
 */


#ifndef DYNAMICBAR_H
#define DYNAMICBAR_H


#include "StepMotor.h"


// Number of bars for each module
#define NUMBER_OF_BARS 4

// Direction of the step motor revolution
#define NORMAL false
#define INVERTED true

// Swing speed (period in ms)
#define PERIOD_SWING 200

// Instructions coding
#define INSTRUCTION_SWING 101
#define INSTRUCTION_VIBRATION 102
#define INSTRUCTION_IMMOBILE 103
#define INSTRUCTION_CALIBRATION 255


class DynamicBar {
	
private :
	
	// Bar number
	int barNumber ;
	
	// Step motor associated to the bar
	StepMotor motor ;
	
	// Sometimes motor wiring is inverted, so that step(+1) makes the bar go down.
	// 'direction' is here to correct this inversion, assigning it 'NORMAL' or 'INVERTED' value.
	boolean direction ;
	
	// Digital INPUT_PULLUP pins detecting top and bottom stops
	uint32_t bottom ;
	uint32_t top ;
	
	// Output pin controling the main switch of the ULN2003A
	uint32_t switchBar ;
	
	// Digital INPUT_PULLUP pin detecting the voice synthesis button
	uint32_t voiceButton ;
	boolean voicePressed ;
	
	// Calibration
	boolean bottomCalib ;
	boolean topCalib ;
	boolean ready ;
	
	// Height of the bar
	int stepsToTop ; // Number of steps to attain maximum height (calculated by calibrate() function)
	int currentStep ; // Current number of step(s)
	int heightOrder ; // Objective in %
	int currentHeight ; // Current in %
	
	// Vibration
	boolean vibration ;
	boolean swinging ;
	uint32_t offsetTime ;
	boolean directionVibration ;
	
	// Intern methods
	void positiveStep() ;
	void negativeStep() ;
	
	
public :
	
	/* Constructors */
	
	DynamicBar() ;
	DynamicBar(int pBarNumber, StepMotor pMotor, boolean pDirection, uint32_t pBottom, uint32_t pTop, uint32_t pSwitchBar, uint32_t pVoice) ;
	
	/* Methods */
	
	void init() ;
	boolean calibrate() ;
	void calculateHeight() ;
	void setHeightOrder(int newPourcent) ;
	void up() ;
	void down() ;
	boolean update() ;
	void swing() ;
	void vibrate() ;
	void switchOn() ;
	void switchOff() ;
	
} ;

#endif