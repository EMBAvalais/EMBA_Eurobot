/*()_()
  (o.o)
  (.)(.)*/
/*====================================================================================================
===																									==
===											EMVs - EUROBOT	  										==
===											--------------											==
======================================================================================================
===	 Auteur				: Amand Axel     					  										==
===  Date				: 05.03.2015																==
===  Nom du programme 	: InterfaceRoboteQuC.mcp													==
===  Version 			: V1.0																		==
======================================================================================================
=== Description :																					==
=== Fonctions d'initialisation du dsPIC30F6014A.				    								==
====================================================================================================*/

#ifndef ___Init
#define ___Init

//****************************************************************************************************
//*  Défintion des bits
//*  ! Utiliser LATx pour des sorties et PORTx pour des entrées lorsque commandes succintes rapides. !
//****************************************************************************************************
#bit _LED1 = LATC.1			//--|
#bit _LED2 = LATC.2			//	|
#bit _LED3 = LATC.3			//	|- LEDs
#bit _LED4 = LATC.4			//	|

#bit _DEMA = PORTA.10		//--|
#bit _TEAM = PORTA.12		//	|
#bit _Dig3 = PORTA.13		//	|- Digital Inputs
#bit _Dig4 = PORTA.6		//	|
#bit _ZeroPoint = PORTA.7		//  |
#bit _Dig6 = PORTA.9		//	|

#bit _Out1 = LATD.0 		//--|
#bit _Out2 = LATD.1	    //	|
#bit _Out3 = LATD.2 	 	//	|
#bit _Out4 = LATD.3 		//	|- Outputs
#bit _SERV = LATD.4		//	|
#bit _LDT1 = LATD.5 		//	|
#bit _LDT2 = LATD.6		//  |
#bit _Out8 = LATD.7		//	|

#bit _Tim1On = T1CON.15
#bit _Tim2On = T2CON.15
#bit _Tim3On = T3CON.15

#bit _I2CEN = I2CCON.15
#bit _GCEN = I2CCON.7

#bit _En_Diz = PORTB.10
#bit _EN_Uni = PORTB.11


enum{STOP,CHARGE_OBJ,DRIVER_GO,OBJ_PERSO,DRIVER_DONE,OBJ_DONE,WAIT}State=STOP;

//----------------------------------------------------------------------------------------------------
//  Nom: 	    __Init_dsPIC
//	Auteur :	AMANAX
//	Date:	    30.01.2015
//  Statut :    Fonctionnel
//----------------------------------------------------------------------------------------------------
//  Description : Config. et initialisation du dsPIC30F6014A.
//	Paramètre(s): /
//  Résultat :    / 
//----------------------------------------------------------------------------------------------------
void __Init_dsPIC(void)
{
	//------------------------------------------------------------------------------
	// Configuration des I/O
	TRISA = 0b0011011011000000;		// RA6,7,9,10,12,13 : Digital Input
	PORTA=0;
	TRISB = 0b0000000000111100;		// RB2-5: Analog Input
	PORTB=0;
	TRISC = 0b0000000000000000;		// RC1-4: LEDs
	PORTC=0;
	TRISD = 0b0000000000000000;		// RD0-7: Outputs
	PORTD=0;
	TRISF = 0b0000000000010100;		// RF2-5: Rx1, Tx1, Rx2, Tx2
	PORTF=0;
	TRISG = 0b0000000000001100;		// RG2-3: SCL-SDA
	PORTG=0; 


// configuration de l'I2C
	I2CCON = 0x800f;//LAISSER, SINON L'I2C PLANTE
//	_GCEN=0;
//	_I2CEN=1;
	
	// Temps de jeu
	// Set le timer1 à 1 [ms]
	setup_timer1(TMR_INTERNAL,0x4E20);	

	// Capture balise
	// Set le timer3 avec la fréquence interne, incrément chaque 64 instructions, jusque 31250 => 100 [ms]
	setup_timer3(TMR_INTERNAL | TMR_DIV_BY_64, 31250);
	
	// Autorise le timer1
	enable_interrupts(INT_TIMER1);
	// Autorise le timer3
	enable_interrupts(INT_TIMER3);
	// Interruptions RS232
	enable_interrupts(INT_RDA2);	// Réception RS232/1
	// Autorise les interruptions globalement
	enable_interrupts(INTR_GLOBAL);
	
	config_driver_moteur_pid(0xC0, 200, 1, 0);
	config_driver_moteur_pid(0xC2, 200, 1, 0);
	delay_ms(10);
	
	config_driver_moteur(0xC0, 5000, 5000, 1000,4556);//moteur barillet
	config_driver_moteur(0xC2, 5000, 5000, 2000,0);//moteur éjection
	config_driver_moteur(0xC4, 5000, 5000, 1000,0);//moteur poussage
	delay_ms(10);
	
	return;
	
}
	
#endif