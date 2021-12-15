/*
 * dcu.c
 *
 *  Created on: Nov 14, 2016
 *      Author: Benjamin
 */

#include "MPC5645S.h"
#include "dcu.h"
#include "ext_global.h"
#include "port.h"
#include "gpio.h"
#include "lcd.h"


//activation du DCU test
void activ_DCU_Test()
{
	//DCU_mode : mode normal
	DCU.DCU_MODE.B.DCU_MODE = 3; //mode test
	DCU.DCU_MODE.B.RASTER_EN = 1; //démarrage du balayage de pixel

}

//activation du DCU normal
void activ_DCU_Normal()
{
	//DCU_mode : mode normal
	DCU.DCU_MODE.B.DCU_MODE = 1; //mode normal
	DCU.DCU_MODE.B.RASTER_EN = 1; //démarrage du balayage de pixel
}

//configuration des I/O du DCU
void CONFIG_DCU_IO()
{
	//signaux à configurer en sortie:
	//DCU_PCLK: PG11 (OBE à activer), Fast Pad
	//DCU_VSYNC et DCU_HSYNC: PG8 et PG9
	//DCU_TAG: non utilisé
	//DCU_DE: PG10
	//DCU_R[7:2]: PA[7:2]
	//DCU_G[7:0]: PA[15:10]
	//DCU_B[7:2]: PG[7:2]
	//pour tous, fonction alternative 1 PA[1:0] = 1 dans les registres PCR
	
	//il faut aussi configurer le port PH5 en sortie et le mettre à  1 car elle commande la pin Reset de l'afficheur
	//On met aussi à '1' PG0 qui commande PWM_BL (commande du backlight)
	
	//config du port A (2 à 7):
	Config_port_AF(PA2,1);
	Config_port_AF(PA3,1);
	Config_port_AF(PA4,1);
	Config_port_AF(PA5,1);
	Config_port_AF(PA6,1);
	Config_port_AF(PA7,1);
	
	//config du port A (10 à 15):
	Config_port_AF(PA10,1);
	Config_port_AF(PA11,1);
	Config_port_AF(PA12,1);
	Config_port_AF(PA13,1);
	Config_port_AF(PA14,1);
	Config_port_AF(PA15,1);
	
	
	//config du port G (2 à 10), hormis PG[11] = PCLK
	Config_port_AF(PG2,1);
	Config_port_AF(PG3,1);
	Config_port_AF(PG4,1);
	Config_port_AF(PG5,1);
	Config_port_AF(PG6,1);
	Config_port_AF(PG7,1);
	Config_port_AF(PG8,1);
	Config_port_AF(PG9,1);
	Config_port_AF(PG10,1);

	//PG[11} = PCLK, fonction alternative 1 + OBE = 1
	//Config_port_AF(PG11,1);
	//Config_port_output(PG11);
	SIU.PCR[97].R = 0x600; //fonction alternative 1 + OBE = 1
	
	//PH[5] = reset afficheur, en mode sortie et à '1'
	Config_port_output(PH5);
	Set_GPIO(PH5);

	
	//PG0 = Backlight, en mode sortie et à '1'
	Config_port_output(PG0);
	Set_GPIO(PG0);
	
	//PG12 = alim 3.3 V du LCD, en mode sortie et à '1'
	Config_port_output(PG12);
	Set_GPIO(PG12);
}

//configuration du DCU3 en mode de test
void CONFIG_DCU()
{
	//activation du TCON
	//To enable TTL mode, set TCON_CTRL1[RSDS_MODE]=’0’, TCON_CTRL1[TCON_BYPASS]=’0’ and TCON_CTRL1[TCON_EN]=’1’.
	TCON.CTRL1.B.RSDS_MODE = 0; 
	TCON.CTRL1.B.TCON_BYPASS = 1; //En fait, si on met Bypass à 0, on n'arrive pas à sortir les signaux HSYN, VSYN et DE !!!
	TCON.CTRL1.B.TCON_EN = 0;  //pour l'instant, on désactive le TCON, qui semble inutile. 
	
	
	//config taille de l'écran (480 x 272 px) --> DISP_SIZE
	DCU.DISP_SIZE.B.DELTA_Y = RESO_VERT; //résolution verticale en nombre de pixels
	DCU.DISP_SIZE.B.DELTA_X = RESO_HOR; //résolution horizontale en multiple de 16 pixels
	
	//configuration des paramètres temporels
	//DIV_RATIO --> pour fixer la clock pixel. Horloge système = 100 MHz. Horloge pixel à 10 MHz --> facteur de division = 9 
	//--> DIV_RATIO = 9
	DCU.DIV_RATIO.R = 0x00000009;
	//paramètres de synchro horizontale : HSYN_PARA (FP_H, BP_H, and PW_H)
	DCU.HSYN_PARA.B.PW_H = 5; //l'impulsion sur DCU_HSYNC dure 5 pixel clocks (on a mesure une impulsion nég de 500 ns).
	//Impulsion nég sur DCU_HSYNC toutes les 58.1 µs. Il reste donc 58.1-0.5-480*0.1 = 9.6 µs pour BP_H et FP_H.
	//On prend BP_H = FP_H = 4.8 µs soit 48 pixel clocks.
	DCU.HSYN_PARA.B.BP_H = 48;
	DCU.HSYN_PARA.B.FP_H = 48;
	//paramètres de synchro verticale : VSYN_PARA (FP_V, BP_V, and PW_V)
	DCU.VSYN_PARA.B.PW_V = 2; //l'impulsion sur DCU_HSYNC dure 116.2 µs soit 2 cycles horizontaux.
	//Impulsion nég sur DCU_VSYNC toutes les 20 ms. Il reste donc 20e3-2*58.1-272*58.11 = 4080.6 µs, soit 70 cycles horiz pour BP_V et FP_V.
	//On prend BP_V = FP_V = 11 cyncles horizontaux.
	DCU.VSYN_PARA.B.BP_V = 39;
	DCU.VSYN_PARA.B.FP_V = 31;
	//Polarité des signaux de synchro : négative pour tous les signaux (HSYNC, VSYNC, DE)
	DCU.SYN_POL.B.INV_PXCK = 0; //display samples on falling edges
	DCU.SYN_POL.B.NEG = 0; //pas de négation des données pixels
	DCU.SYN_POL.B.BP_VS = 0; //do not bypass VSYNC
	DCU.SYN_POL.B.BP_HS = 0; //do not bypass HSYNC
	DCU.SYN_POL.B.INV_VS = 1; //VSYNC active low
	DCU.SYN_POL.B.INV_HS = 1; //HSYNC active low
	
	//Rq : les tests montrent en mode test que cela fonctionne queque soit INV_VS, INV_HS,INV_PXCK.
	
	//Background color : fond de couleur blanc-gris
	DCU.BGND.B.BGND_R = 0xAA;
	DCU.BGND.B.BGND_G = 0xAA;
	DCU.BGND.B.BGND_B = 0xAA;
}

//initialisation des paramètres des layers graphiques, ici le layer 1 seulement
void InitLayers()
{
	//Initialisation du layer1
	DCU.LAYER[0].CTRLDESCL1.B.HEIGHT = Layer1_H;
	DCU.LAYER[0].CTRLDESCL1.B.WIDTH = Layer1_W;
	DCU.LAYER[0].CTRLDESCL2.B.POSX = Layer1_posX;
	DCU.LAYER[0].CTRLDESCL2.B.POSY = Layer1_posY;
	DCU.LAYER[0].CTRLDESCL3.R = Adress1;
		
	DCU.LAYER[0].CTRLDESCL4.B.EN = 1;
	DCU.LAYER[0].CTRLDESCL4.B.DATA_SEL = 0; //données en mémoire
	DCU.LAYER[0].CTRLDESCL4.B.TRANS = 0xFF; //pas de selction de pixels où sera gérée la transparence. 
	DCU.LAYER[0].CTRLDESCL4.B.BPP = 0; //format 1 bpp. Couleur défini dans la CLUT (noir ou blanc)
	DCU.LAYER[0].CTRLDESCL4.B.LUOFFS = 0; //valeurs situées au début de la CLUT
	DCU.LAYER[0].CTRLDESCL4.B.AB = 2; //blend the whole frame  
}
