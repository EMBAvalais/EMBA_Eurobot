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

#bit _Dig1 = PORTA.10		//--|
#bit _Dig2 = PORTA.12		//	|
#bit _Dig3 = PORTA.13		//	|- Digital Inputs
#bit _Dig4 = PORTA.6		//	|
#bit _Dig5 = PORTA.7		//  |
#bit _Dig6 = PORTA.9		//	|

#bit _Out1 = LATD.0 		//--|
#bit _Out2 = LATD.1	    //	|
#bit _Out3 = LATD.2 	 	//	|
#bit _Out4 = LATD.3 		//	|- Outputs
#bit _Out5 = LATD.4		//	|
#bit _Out6 = LATD.5 		//	|
#bit _Out7 = LATD.6		//  |
#bit _Out8 = LATD.7		//	|

#bit _Tim1On = T1CON.15
#bit _Tim2On = T2CON.15
#bit _Tim3On = T3CON.15

#bit _I2CEN = I2CCON.15
#bit _GCEN = I2CCON.7


#bit _En_Diz = PORTB.10
#bit _EN_Uni = PORTB.11

//----------------------------------------------------------------------------------------------------
//  Nom: 	    __Init_dsPIC
//	Auteur :		BORREM
//	Date:	    	23.3.2016
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
	//PORTA=0; //MODIFIE
	TRISB = 0b0000000000111100;		// RB2-5: Analog Input
	//PORTB=0; //MODIFIE
	TRISC = 0b0000000000000000;		// RC1-4: LEDs
	//PORTC=0; //MODIFIE
	TRISD = 0b0000000000000000;		// RD0-7: Outputs
	//PORTD=0; //MODIFIE
	TRISF = 0b0000000000010100;		// RF2-5: Rx1, Tx1, Rx2, Tx2
	//PORTF=0; //MODIFIE
	TRISG = 0b0000000000000000;		// RG2-3: SCL-SDA
	//PORTG=0; //MODIFIE



	
	// Activation de l'ADC selon vitesse interne
	setup_adc(ADC_CLOCK_INTERNAL);
	// Set les entrées en analogique
	setup_adc_ports(sAN2 | sAN3 | sAN4 | sAN5);



	// Temps de jeu
	// Autorise le timer1
	enable_interrupts(INT_TIMER1);
	// Set le timer1 avec la fréquence interne, incrément chaque 64 instructions, jusque 62500 => 200 [ms]
	setup_timer1(TMR_INTERNAL | TMR_DIV_BY_64, 62500);
	// Désactive le timer1
	_Tim1On=0;

	// Capture balise
	// Autorise le timer3
	enable_interrupts(INT_TIMER3);
	// Set le timer3 avec la fréquence interne, incrément chaque 64 instructions, jusque 31250 =>  [ms]
	setup_timer3(TMR_INTERNAL | TMR_DIV_BY_64, 62500);
	// Désactive le timer3
	_Tim3On=0;

		// Interruptions RS232
	enable_interrupts(INT_RDA);	// Réception RS232/1
	
	
	// Autorise les interruptions globalement
	enable_interrupts(INTR_GLOBAL);

	// Configuration de la balise
	Balise_config_plage(1, 4, 6);
	delay_ms(100);
	Balise_config_plage(2, 12, 14);
	delay_ms(100);
		
	// Quitte la fonction
	return;
}

#endif