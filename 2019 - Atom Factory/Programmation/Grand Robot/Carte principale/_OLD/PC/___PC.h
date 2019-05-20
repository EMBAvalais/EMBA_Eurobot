/*
* \file ___PC.h
* \brief Gère la communication PC (defs.)
* \ EMVs Eurobot - Driver Moteur
* \author Amand Axel
* \version 2.0
* \date 20.11.2015
* \copyright GNU Public License
*/

#ifndef ___PC_H
#define ___PC_H



// Config RS232
#use rs232(baud=115200,parity=N,xmit=PIN_F3,rcv=PIN_F2,bits=8,stream=RS232)
// Config UART
//#use rs232(baud=9600,parity=N,xmit=PIN_F5,rcv=PIN_F4,bits=8,stream=UARTi)

// Définit quand un tableau est à décoder
int1 PCh_flagUARTReadyToDecode = 0;
// Watchdog pour éviter un blocage UART
int1 PCh_flagUARTWatchdog = 0;


void __Init_UART(void);	// Initialise
void __UART_Decode(unsigned int32* _Tab);	// Décode une trame
void __SendBackUART(void); // Renvoi la dernière commande envoyée
void __CommDecode(unsigned int8* _TabToDec,unsigned int32* _TabDec); // Décode un tableau
#include "PC/___PC.c"

#endif