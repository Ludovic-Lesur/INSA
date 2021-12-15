/*
 * lcd.h
 *
 *  Created on: Nov 12, 2016
 *      Author: Benjamin
 */
/*Pour l'instant, juste affichage de l'image FORD de bienvenu*/

#ifndef LCD_H_
#define LCD_H_

#include "MPC5645S.h"

//global naming

	//paramètres écran LCD
#define RESO_VERT 272
#define RESO_HOR 30; // 480/16

	//Image FORD (taille en pixels)
#define W_Image_FORD 480
#define H_Image_FORD 272
#define PixelPerWord_Image_FORD 8 //8 pixels par mot de 32 bits --> 4 bpp

#define PixelPerWord_2bpp 16 //16 pixels par mot de 32 bits --> 2 bpp
#define PixelPerWord_Cadre 32 //32 pixels par mot de 32 bits --> 1 bpp

//Définition des espaces mémoires des différentes couches graphiques. Attention à bien déterminer l'espace mémoire occupée 
//par une couche pour éviter toute erreur d'affichage. Veiller à ce que le début des adresses des layers soient des multiples de 64!
//mémoire graphique SRAM : de 0x60000000 à 0x600FFFFF
//On range dans l'ordre
//- Image FORD seulement pour l'instant

//adresse de l'image FORD (480*272 pixels encodés en 4 bpp = 65.28ko = 522.24kb)
#define Adr_Image_FORD 0x60000000

//On met l'image FORD sur Layer1. Elle couvre tout l'écran.
//Format 4 bpp --> (160*32 px /8 (1bpp) = 640 octets)
//attention, le contenu de la mémoire doit démarrer à une adresse multiple de 64 !
#define Layer1_W 472  //multiple de 32 car format 1 bpp
#define Layer1_H 280
#define Layer1_posX 0 
#define Layer1_posY 0  
#define Adress1 0x60000000

//CLUT
#define Start_CLUT 0xFFE5E000
#define Adress_Start_CLUT *(uint32_t *) Start_CLUT

//macro declaration

//functions prototypes
void InitLayerMemory(void);

#endif /* LCD_H_ */
