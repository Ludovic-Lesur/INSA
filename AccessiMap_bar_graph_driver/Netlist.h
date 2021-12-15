/*
 * Netlist.h (pin configuration of the Arduino Due board driving the module)
 *
 * Created: 01/06/2016
 * Author: Ludovic Lesur
 */ 


#ifndef NETLIST_H
#define NETLIST_H


// Bar 1
#define BAR1_CMDE1 22 // Step motor drivers (digital output pins)
#define BAR1_CMDE2 23
#define BAR1_SWITCH 2 // General transistor of ULN2003A (analog PWM output pin)
#define BAR1_BPBB 24 // Detection of bottom stop (digital input-pullup pin).
#define BAR1_BPBH 25 // Detection of top stop (digital input-pullup pin).
#define BAR1_BPSV 26 // Button which activates voice synthesis (digital input-pullup pin)

// Bar 2
#define BAR2_CMDE1 27
#define BAR2_CMDE2 28
#define BAR2_SWITCH 3
#define BAR2_BPBB 29
#define BAR2_BPBH 30
#define BAR2_BPSV 31

// Bar 3
#define BAR3_CMDE1 32
#define BAR3_CMDE2 33
#define BAR3_SWITCH 4
#define BAR3_BPBB 34
#define BAR3_BPBH 35
#define BAR3_BPSV 36

// Bar 4
#define BAR4_CMDE1 37
#define BAR4_CMDE2 38
#define BAR4_SWITCH 5
#define BAR4_BPBB 39
#define BAR4_BPBH 40
#define BAR4_BPSV 41

// Update LED
#define LED_UPDATE 51

// Calibration button and LED.
#define LED_CALIB 52
#define BP_CALIB 53


#endi /* NETLIST_H */