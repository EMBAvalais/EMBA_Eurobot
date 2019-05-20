//*************************************************************************
//*  EMVS
//*  Ce code doit permettre de pouvoir contrôler quatre servomoteurs en même 
//*	 temps, grâce à une interruption de 100us.
//*  Auteur: FAVLEN
//*  Date: 23.03.2017
//*************************************************************************
// Carte servomoteurs
//*************************************************************************

   
#include <18F2520.h>
#include "18F_register.h"


#device ICD=TRUE
#device HIGH_INTS=TRUE	   //to use save the mininal contexte18.

#define I2C_ADDRESS 0xC4

#use delay(crystal=10000000,clock=40000000)
#use i2c(slave,slow,ADDRESS=I2C_ADDRESS,SDA=PIN_C4,SCL=PIN_C3,force_hw)
#fuses NOWDT, NOPUT, NOPROTECT, DEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT, NOXINST, NOPBADEN//, HS

#BIT Servo1=LATA.0		// Servomoteurs
#BIT Servo2=LATA.1
#BIT Servo3=LATA.2
#BIT Servo4=LATA.3
#BIT Servo5=LATB.0		// Servomoteurs
#BIT Servo6=LATB.1
#BIT Servo7=LATB.2
#BIT Servo8=LATB.3

#BIT LED1=LATC.0		// Leds
#BIT LED2=LATC.1

unsigned int16 TempsServo1 = 100;
unsigned int16 TempsServo2 = 100;
unsigned int16 TempsServo3 = 100;
unsigned int16 TempsServo4 = 100;
unsigned int16 TempsServo5 = 100;
unsigned int16 TempsServo6 = 100;
unsigned int16 TempsServo7 = 100;
unsigned int16 TempsServo8 = 100;
unsigned int16 n_fois = 0;
unsigned int8 ServoNumber = 0;
unsigned int16 Temps = 0;
unsigned int flagReception = 0;
//-----------------------------------------------------------------------------------
// Routine d'initialisation des ports du microcontrôleur
void Init_uC(void)
{
	T0CON =0b10001000;
                                       //bit0,1,2   :xxx	
                                       //bit3   	:1 	PS non-utilisé (PS=1)
                                       //bit4		:0 	Counting on clock low-to-high
                                       //bit5   	:0	Clock interne (CLKO)
                                       //bit6		:0	Timer 16 bits   
									   //bit7		:1	Timer0 on					   

	TRISC=0xFC;
	TRISA=0x00;			//0xFFA4 = 10us				   

	TRISC=0xFC;
	TRISA=0x00;
	PORTA=0x00;
	TRISB=0x00;
	PORTB=0x00;
	LED1=1;
	LED1=0;
	enable_interrupts(INT_TIMER0);      // autorise l'interruption timer0
	enable_interrupts(INT_SSP);      // autorise l'interruption I2C
	enable_interrupts(GLOBAL);          // autorise globalement les interruptions
}
//------------------------------------------------------------------------------------
// Routine d'interruption qui s'exécute chaque 5us, 
#INT_TIMER0 FAST			//Quick save -> minimal contexte saving
void TIMER0_isr(void)
{
	TMR0L=0xA4;				//0xFFD6 = 5us, PS=1
	TMR0H=0xFF;				//0xFFA4 = 10us
	LED2=1;

	if(n_fois<1999)		 	// Pour avoir une pulse toute les 20ms
	{
		if(n_fois==TempsServo1)
		{
			Servo1 = 0;
		}
		if(n_fois==TempsServo2)
		{
			Servo2 = 0;	
		}
		if(n_fois==TempsServo3)
		{
			Servo3 = 0;
		}
		if(n_fois==TempsServo4)
		{
			Servo4 = 0;	
		}
		if(n_fois==TempsServo5)
		{
			Servo5 = 0;
		}
		if(n_fois==TempsServo6)
		{
			Servo6 = 0;	
		}
		if(n_fois==TempsServo7)
		{
			Servo7 = 0;
		}
		if(n_fois==TempsServo8)
		{
			Servo8 = 0;	
		}
		n_fois++;	
	}
	else
	{
		Servo1 = 1;
		Servo2 = 1;
		Servo3 = 1;
		Servo4 = 1;
		Servo5 = 1;
		Servo6 = 1;
		Servo7 = 1;
		Servo8 = 1;
		n_fois = 0;
	}
	LED2 = 0;
}

void main(void)
{
	Init_uC();
	while(1)
	{
		if(flagReception == 1)
		{
			LED1 = 1;
			switch(ServoNumber)
			{
				case 1	:	TempsServo1 = Temps + 100;
							break;
				case 2	:	TempsServo2 = Temps + 100;
							break;
				case 3	:	TempsServo3 = Temps + 100;
							break;
				case 4	:	TempsServo4 = Temps + 100;
							break;
				case 5  :	TempsServo5 = Temps + 100;
							break;
				case 6  :	TempsServo6 = Temps + 100;
							break;
				case 7  :	TempsServo7 = Temps + 100;
							break;
				case 8  :	TempsServo8 = Temps + 100;
							break;
				default	:	break;
			}
			flagReception = 0;
			LED1 = 0;
		}
	}
}
//------------------------------------------------------------------------------------
// Routine d'interruption qui s'exécute lors d'un réception par I2C
#INT_SSP
void I2C_isr(void)
{
	int state = i2c_isr_state();			// Fonction qui retourne l'état de la communication i2c
	switch(state)
	{
		case 0	:	i2c_read();
					break;
		case 1	:	ServoNumber = i2c_read();
					break;
		case 2	:	Temps = i2c_read();
					flagReception = 1;
					break;
		default	:	i2c_read();
					break;
	}
}