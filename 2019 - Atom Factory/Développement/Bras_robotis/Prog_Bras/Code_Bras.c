/*==========================================================================
====               EMVs - Ecole des métiers du Valais
============================================================================
====                     Programmation MPLAB IDE
====                     ---------------------------
====------------------------------------------------------------------------
==== Nom du projet de programme        	: Prog_Bras
==== Langage de programmation utilisé  	: c
==== Version							: 1.0
====------------------------------------------------------------------------
==== Créateur (Nom, Prénom)            	: Thurre Florian
==== Classe                            	: EMVs-EL 3B
==== Date de création                  	: 21.01.2015
====------------------------------------------------------------------------
==== Description succincte du programme:
==== ----------------------------------
==== Ce programme gère la programmation du bras à servomoteurs série
==== Il contrôle:
====  			- en entrée, les trois dip switchs sur RC1 à RC3
====			- en sortie, les trois LEDs RD0 à RD2
====			- en entrées et sorties, la communication aux servomoteurs
===========================================================================*/

#include <18F45K22.h>
#include "18FK_register.h"
#include <math.h>

#device ICD=TRUE
#DEVICE HIGH_INTS=TRUE
#use delay(clock=20000000)
#fuses NOWDT, WDT128, HSH, NOPLLEN, NOBROWNOUT, WDT_SW, NOLVP, NOXINST, DEBUG	// fuses valable pour le PIC18F45K22
#use rs232(baud=115200,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=SERVOS)
#use rs232(baud=9600,parity=N,xmit=PIN_B6,rcv=PIN_B7,bits=8,stream=ARDUINO)

#bit LED1 = PORTD.0	// Les trois LEDs de signalisation de mon circuit
#bit LED2 = PORTD.1
#bit LED3 = PORTD.2
#bit Direction = PORTC.4	// Permet de choisir si l'on veut transmettre ou recevoir

//---------------------------------------------------------------------------
//BRAS ROBOTIS
#define ARM_INTERAXIS_LENGTH 70
#define ARM_ANGLE_MAX 50
#define PI 3.14159265359

int8 tab_id[5] = {1,2,9,3,14};


int16 arm_length_max = 0;
int16 arm_length_min = 0;

int16 angle_to_aim = 0;
float dist_to_atom = 0;
float angle_pos = 0;
int16 servo_pos_1 = 512;
int16 servo_pos_2 = 512;
int16 servo_pos_3 = 512;
float x_powed;
float y_powed;
float x_and_y;


enum{id, angle, wait};

//--------------------------------------------------------------------------



 /*==========================================================================
==== Fonction:	Init_uC				                                   	====
==== by FLOTHU 	21.01.2015                                       		====
====--------------------------------------------------------------------====
==== Fonction d'initialisation des ports du uC							====
==== Pas de paramètres													====
==== Ne retourne rien													====
============================================================================*/
void Init_uC(void)
{
	TRISC= 0b10001110;	// RX input, TX output, Direction output, 3 switchs input
	TRISD= 0b10000000;	// RX input, TX output, 3 LEDs output
	TRISB= 0b10000000;	// RX input, TX output, 3 LEDs output
	LED1 = LED2 = LED3 = 0;		// On éteint les LEDs
	
	enable_interrupts(INT_RDA);
	enable_interrupts(INT_RDA2);

	enable_interrupts(GLOBAL);
	
}

/*==========================================================================
==== Fonction:	Init_Servos			                                   	====
==== by FLOTHU 	22.01.2015                                       		====
====--------------------------------------------------------------------====
==== Fonction d'initialisation de la position des servos				====
==== Pas de paramètres													====
==== Ne retourne rien													====
============================================================================*/
void Init_Servos(void)
{
		// d'éviter d'envoyer des instructions inutiles aux servos
		Move_speed(100);	// Vitesse très faible
		
		Envoyer_instruction(0xFE,0x02,0x18,0x01,0x00);
	 
		position_servos[0] = 512;	// Moteur 1 à 150 degrés
		position_servos[1] = 200;	// Moteur 2 à 120 degrés
		position_servos[2] = 220;	// Moteur 3 à 120 degrés
		position_servos[3] = 810;	// Moteur 4 à 150 degrés
		position_servos[4] = 512;	// Moteur 5 à 120 degrés
		
		for(i=0;i<=4;i=i+1)	// Boucle permettant d'envoyer 
		{					// les 6 instructions aux 6 servos
			Servo_goal_position(tab_id[i], position_servos[i]);	// Envoi de l'instruction
			delay_us(100);	
		}
		
}

/*==========================================================================
==== Fonction:	Init_Arm			                                   	====
==== by FLOTHU 	22.01.2015                                       		====
====--------------------------------------------------------------------====
==== Fonction d'initialisation du bras									====
==== Pas de paramètres													====
==== Ne retourne rien													====
============================================================================*/
void Init_Arm(void)
{
	arm_length_min = ARM_INTERAXIS_LENGTH+(2*ARM_INTERAXIS_LENGTH*cos(ARM_ANGLE_MAX*PI/180));
	arm_length_max = 3 * ARM_INTERAXIS_LENGTH; 
}	

/*==========================================================================
==== Fonction:	Servo_goal_position           							====
==== by FLOTHU	21.01.2015                                 				====
====--------------------------------------------------------------------====
==== Fonction qui permet de bouger un servo à un angle désiré     		====
==== Paramètres:	- ID: ID du servomoteur (numéro écrit sur le servo)	====
====				- deg: angle désiré en degré						====
====				  min = 0° ; middle = 150° ; max = 300°				====
==== Ne retourne rien													====
============================================================================*/
void Servo_goal_position(int ID, int16 deg)
{
	//position = deg * 3.41;	// conversion angle en degré(0 à 300) --> valeur de 0 à 1023 pour le servo
	position = deg;	// conversion angle en degré(0 à 300) --> valeur de 0 à 1023 pour le servo
	int position_1 = position & 0b0000000011111111;	// Position pour les low bits
	int position_2 = (position & 0b1111111100000000) >> 8;	// Position pour les high bits

	Envoyer_instruction(ID,0x03,0x1E,position_1,position_2);	//Envoie des instructions
	delay_us(100);	// Ce delay est nécessaire sinon certains servos ne réagissent pas
}	


/*==========================================================================
==== Fonction:	Move_speed                                            	====
==== by FLOTHU 	21.01.2015                                       		====
====--------------------------------------------------------------------====
==== Fonction qui permet de définir la vitesse de tous les servos      	====
==== Paramètres:	- speed: valeur entre 0 et 1023 réglant la vitesse	====
====				  du servo. 0 = max, 1023 = 114 rpm, 300 = 33.3 rpm ====	
==== Ne retourne rien													====
============================================================================*/
void Move_speed(int16 speed)
{							
	int speed_1 = speed & 0b0000000011111111;			// position pour les low bits
	int speed_2 = (speed & 0b1111111100000000) >> 8;	// position pour les high bits
						
	Envoyer_instruction(0XFE,0x03,0x20,speed_1,speed_2);	// Envoie des instructions																				
	delay_us(100);	// Ce delay est nécessaire sinon certains servos ne réagissent pas						
	
}	

/*==========================================================================
==== Fonction:	Move_speed                                            	====
==== by FLOTHU 	21.01.2015                                       		====
====--------------------------------------------------------------------====
==== Fonction qui permet de définir la vitesse d'un seul servo         	====
==== Paramètres:	- ID: ID du servomoteur (numéro écrit sur le servo)	====
====				- speed: valeur entre 0 et 1023 réglant la vitesse	====
====				  du servo. 0 = max, 1023 = 114 rpm, 300 = 33.3 rpm ====	
==== Ne retourne rien													====
============================================================================*/
void Move_speed(int ID, int16 speed)
{
	int speed_1 = speed & 0b0000000011111111;			// position pour les low bits
	int speed_2 = (speed & 0b1111111100000000) >> 8;	// position pour les high bits					

	Envoyer_instruction(ID,0x03,0x20,speed_1,speed_2);	// Envoi de l'instruction																				
	delay_us(100);	// Ce delay est nécessaire sinon certains servos ne réagissent pas						
}	

/*==========================================================================
==== Fonction:	Envoyer_instruction	                                   	====
==== by FLOTHU 	21.01.2015                                       		====
====--------------------------------------------------------------------====
==== Fonction qui permet d'envoyer une instruction au servomoteurs		====
==== Paramètres: 	- ID: correspond à l'ID du servomoteur				====
====				- nbr_param: nombre de paramètre que l'on passe		====
====				- instruction: instruction désirée (bouger le servo,====
====				  changer la vitesse, limite de couple,...)			====
====				- param1: premier paramètre				 			====
====				- param2: deuxième paramètre						====
==== Ne retourne rien													====
============================================================================*/
void Envoyer_instruction(int ID,int nbr_param,int instruction,int param1,int param2)
{
	checksum = 0xFF;		// Reset du checksum

	Direction = 1;			// Direction à 1 pour pouvoir envoyer
	//disable_interrupts(INT_RDA);
	putc(0xFF, SERVOS);				// 0xFF pour le start
	putc(0xFF, SERVOS);				// Deuxième 0xFF pour le start
	putc(ID, SERVOS);				// Envoie de l'id
	putc(nbr_param + 2, SERVOS);	// Envoie du nombre de paramètre
	putc(0x03, SERVOS);				// Envoie de l'instruction Write_data
	putc(instruction, SERVOS);		// Envoie de l'instruction voulu
	putc(param1, SERVOS);			// Envoie du premier paramètre
	if(nbr_param == 3)		// Si un deuxième paramètre est nécessaire
	{
		putc(param2);		// Envoie du deuxième paramètre
		checksum = checksum - param2;	// Calcul du checksum avec deuxième paramètre
	}
	checksum = checksum - ID - nbr_param - 2 - 3 - instruction - param1;	// Calcul du checksum final
	putc(checksum, SERVOS);			// Envoie du checksum
	delay_us(200);			// Delay pour laisser finir l'envoie de la trame
	//enable_interrupts(INT_RDA);
	Direction = 0;			// Direction à 0 pour pouvoir recevoir
}	

void Get_Atome(float x_atom, float y_atom, int1 x_right)
{
	
	x_powed = 2 + 3;//pow(10.0, 2);
	y_powed = pow(10.0, 2);
	
	x_and_y = x_powed + y_powed;
	
	dist_to_atom = sqrt(x_and_y);
	
	if(dist_to_atom > arm_length_min && dist_to_atom < arm_length_min)
	{
		if(!x_right)
		{
			angle_to_aim = (atan(y_atom/x_atom)*57.2958*3.316666) + 215;
		}
		else
		{
			angle_to_aim = ((180-(atan(y_atom/x_atom))*57.2958)*3.316666) + 215;
		}
		
		angle_pos = acos((dist_to_atom-ARM_INTERAXIS_LENGTH)/2*ARM_INTERAXIS_LENGTH);
		
		servo_pos_1 = 512-(angle_pos*3.41);
		servo_pos_2 = 512-(2*angle_pos*3.41);//-((180-angle_pos)*3.41);
		servo_pos_3 = 809-(angle_pos*3.41);
		
		Servo_goal_position(tab_id[0], angle_to_aim);
		Servo_goal_position(tab_id[1], servo_pos_1);
		Servo_goal_position(tab_id[2], servo_pos_2);
		Servo_goal_position(tab_id[3], servo_pos_3);
	
	}	

	
}	




void main(void)
{
	Init_uC();	// Initialisation des ports utilisés du microcontrôleur
	delay_ms(1000);
	
	Move_speed(100);	
	Init_Servos();
	Init_Arm();
	Move_speed(500);
	delay_ms(1000);
	
	
	
	
	while(1)	// une boucle infinie
	{
				
		Get_Atome(1, 1, 1);
		
	}
}