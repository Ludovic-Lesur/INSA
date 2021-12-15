/*
 * Module.h
 *
 * Created: 02/06/2016
 * Author: Ludovic Lesur
 */ 


#ifndef MODULE_H
#define MODULE_H


#include "DynamicBar.h"


// Communication
#define OFFSET 128


class Module {

	private :
	
	// List of bars of the module
	DynamicBar* listOfBars ;
	
	// Current bar the program is working on
	byte currentByte ;
	byte previousByte ;
	int currentNumber ;
	int previousNumber ;
	int currentPourcent ; // Between 0 and 100% if it's pourcentage, or = 101, 102 and 103 for movement
	
	// Calbration button
	uint32_t calib ;
	// State LEDs
	uint32_t ledCalib ;
	uint32_t ledUpdating ;
	
	
	public :
	
	/* Constructor */
	
	Module(DynamicBar* pListOfBars, uint32_t pCalib, uint32_t pLedCalib, uint32_t pLedUpdating) ;
	
	/* Méthods */
	
	void init() ;
	void readBarData() ;
	void update() ;
	void vibrate() ;
	
} ;

#endif