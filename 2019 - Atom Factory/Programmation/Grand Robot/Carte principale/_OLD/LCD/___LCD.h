/*
* \file ___LCD.h
* \brief Gère l'afficheur LCD I2C (defs.)
* \ EMVs Eurobot - Driver Moteur
* \author Amand Axel
* \version 2.0
* \date 20.11.2015
* \copyright GNU Public License
*/

#ifndef ___LCD_H
#define ___LCD_H

void __Init_LCD(void); // Init LCD
void __ClearLCD(void);	// Efface l'écran
void __WriteLCD(unsigned int8 _Command);	// Ecrit la commande 
void __WriteCount(float64 _Value, int1 _Mode);	// Ecrit une valeur, int32 si mode = 0, float si mode = 1
void __SautLig(unsigned int8 _Lig);	// Saute d'une ligne sur l'écran

#include "LCD/___LCD.c"

#endif