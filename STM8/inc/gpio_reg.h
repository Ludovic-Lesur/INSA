/*
 * gpio_reg.h
 *
 *  Created on: 10 mars 2018
 *      Author: Ludovic
 */

#ifndef REGISTERS_GPIO_REG_H_
#define REGISTERS_GPIO_REG_H_

/*** GPIO registers ***/

typedef struct {
    volatile unsigned char ODR;	// Output data register.
    volatile unsigned char IDR;	// Input data register.
    volatile unsigned char DDR;	// Data direction register.
    volatile unsigned char CR1;	// Control register 1.
    volatile unsigned char CR2;	// Control register 2.
} GPIO_BaseAddress;

#define GPIOA	((GPIO_BaseAddress*) ((unsigned int) 0x005000))
#define GPIOB	((GPIO_BaseAddress*) ((unsigned int) 0x005005))
#define GPIOC	((GPIO_BaseAddress*) ((unsigned int) 0x00500A))
#define GPIOD	((GPIO_BaseAddress*) ((unsigned int) 0x00500F))
#define GPIOE	((GPIO_BaseAddress*) ((unsigned int) 0x005015))
#define GPIOF	((GPIO_BaseAddress*) ((unsigned int) 0x00501A))

#endif /* REGISTERS_GPIO_REG_H_ */
