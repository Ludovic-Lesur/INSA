/*
 * main.c
 *
 *  Created on: 10 mars 2018
 *      Author: Ludovic
 */

#include "../inc/registers/clk_reg.h"
#include "../inc/registers/gpio_reg.h"

int main(void) {
    // Configure clock.
    CLK -> ICKCR |= 0x01; // Enable HSI.
    while (((CLK -> ICKCR) & 0x02) == 0); // Wait for HSI to be stable.
    
    // Configure PD1 pin.
    GPIOD -> DDR |= 0x02; // Output.
    GPIOD -> CR1 |= 0x02; // Push-pull.
    
    unsigned char i = 0;
    unsigned char j = 0;
    unsigned char k = 0;
    
    while(1) {
        // Toggle LED on PD1.
        GPIOD -> ODR |= 0x02;
        for (k=0 ; k<2 ; k++) {
            for (i=0 ; i<255 ; i++) {
                for (j=0 ; j<255 ; j++);
            }
        }
        GPIOD -> ODR &= ~(0x02);
        for (k=0 ; k<2 ; k++) {
            for (i=0 ; i<255 ; i++) {
                for (j=0 ; j<255 ; j++);
            }
        }
    }
    
    return 0;
}
