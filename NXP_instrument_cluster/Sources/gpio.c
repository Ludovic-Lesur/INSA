/*
 * gpio.c
 *
 *  Created on: Nov 12, 2016
 *      Author: Benjamin
 */

#include "gpio.h"
#include "MPC5645S.h"
#include "ext_global.h"
#include "port.h"

//functions

//Configuration of PORT as an intput GPIO (no alternate function)
int Config_port_input(unsigned int port) 
{
	int error=-1;
	SIU.PCR[port].B.WPE = 0;
	SIU.PCR[port].B.WPS = 0;
	SIU.PCR[port].B.ODE= 0;
	SIU.PCR[port].B.PA = 0;
	SIU.PCR[port].B.OBE = 0;
	SIU.PCR[port].B.IBE = 1;
	error = 0;
	return error;
}

//Configuration of PORT as an output GPIO (no alternate function)
int Config_port_output(unsigned int port) 
{
    int error =-1;
    SIU.PCR[port].B.WPE = 1;
	SIU.PCR[port].B.WPS = 0;
	SIU.PCR[port].B.ODE= 0;
    SIU.PCR[port].B.SRC = 1;  //1.8 V low-power DDR full speed
	SIU.PCR[port].B.PA = 0;
	SIU.PCR[port].B.OBE = 1;
	SIU.PCR[port].B.IBE = 0;
	error = 0;
	return error;
}

//Configuration of PORT as an output GPIO, with inverted logic (no alternate function)
int Config_port_output_logical_inverted(unsigned int port)
{
	int error=-1;
	SIU.PCR[port].B.WPE = 1;
	SIU.PCR[port].B.WPS = 0;
	SIU.PCR[port].B.ODE= 1; 
	SIU.PCR[port].B.SRC = 1;  //1.8 V low-power DDR full speed
	SIU.PCR[port].B.PA = 0;
	SIU.PCR[port].B.OBE = 0;
	SIU.PCR[port].B.IBE = 0;
	error = 0;
	return error;
}

//Configuration of PORT in alternate function number AF_num
int Config_port_AF(unsigned int port, unsigned int AF_num) 
{
    int error =-1;
	if (1 <= AF_num && 3 >= AF_num)
	{
		SIU.PCR[port].B.PA = AF_num;
		error = 0;
	}
	else
	{
		error = 1;
	}
	return error;
}

// Set an output PORT
int Set_GPIO(unsigned int port)
{
	int error=-1;
	SIU.GPDO[port].B.PDO = 1;
	error = 0;
	return error;
}

// Reset an output PORT
int Reset_GPIO(unsigned int port)
{
	int error=-1;
	SIU.GPDO[port].B.PDO = 0;
	error = 0;
	return error;
}

// Invert the state of an output PORT
int Invert_GPIO(unsigned int port)
{
	int error=-1;
	SIU.GPDO[port].B.PDO = ~SIU.GPDO[port].B.PDO;
	error = 0;
	return error;
}

// Read the content of an input PORT
uint8_t Read_GPIO(unsigned int port)
{
	return SIU.GPDI[port].B.PDI;	
}
