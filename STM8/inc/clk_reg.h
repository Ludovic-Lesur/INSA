/*
 * clk_reg.h
 *
 *  Created on: 10 mars 2018
 *      Author: Ludovic
 */

#ifndef CLK_REG_H_
#define CLK_REG_H_

/*** CLK registers ***/

typedef struct {
	volatile unsigned char CKDIVR;		// System clock divided register.
	volatile unsigned char CRTCR;		// RTC register.
	volatile unsigned char ICKCR;		// Internal clock register.
	volatile unsigned char PCKENR1;		// Peripheral clock gating register 1.
	volatile unsigned char PCKENR2;		// Peripheral clock gating register 2.
	volatile unsigned char CCOR;		// Configurable clock output register.
	volatile unsigned char ECKCR;		// External clock register.
	volatile unsigned char SCSR;		// System clock status register.
	volatile unsigned char SWR;		// System clock switch register.
	volatile unsigned char SWCR;		// Switch control register.
	volatile unsigned char CSSR;		// Clock security system register.
	volatile unsigned char CBEEPR;		// Clock BEEP register.
	volatile unsigned char HSICALR;		// HSI calibration register.
	volatile unsigned char HSITRIMR;	// HSI clock calibration trimming register.
	volatile unsigned char HSIUNLCKR;	// HSI unlock register.
	volatile unsigned char REGCSR;		// Main regulator control status register.
	volatile unsigned char PCKENR3;		// Peripheral clock gating register 3.
} CLK_BaseAddress;

/*** CLK base address ***/

#define CLK		((CLK_BaseAddress*) ((unsigned int) 0x0050C0))

#endif /* CLK_REG_H_ */