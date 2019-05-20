/*==========================================================================
====               EMVs - Ecole des m�tiers du Valais
============================================================================
====                     Programmation MPLAB IDE
====                     ---------------------------
====------------------------------------------------------------------------
==== Nom du projet de programme        	: Prog_Bras
==== Langage de programmation utilis�  	: c
==== Version							: 1.0
====------------------------------------------------------------------------
==== Cr�ateur (Nom, Pr�nom)            	: Thurre Florian
==== Classe                            	: EMVs-EL 3B
==== Date de cr�ation                  	: 21.01.2015
====------------------------------------------------------------------------
==== Description succincte du programme:
==== ----------------------------------
==== Ce programme g�re la programmation du bras � servomoteurs s�rie
==== Il contr�le:
====  			- en entr�e, les trois dip switchs sur RC1 � RC3
====			- en sortie, les trois LEDs RD0 � RD2
====			- en entr�es et sorties, la communication aux servomoteurs
===========================================================================*/

#include <18F45K22.h>
#include "18FK_register.h"


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

#include <math.h>

void Init_uC(void);
void Init_Servos(void);
void Servo_goal_position(int ID, int16 deg);
void Move_speed(int16 speed);
void Move_speed(int ID, int16 speed);
void Envoyer_instruction(int ID,int nbr_param,int instruction,int param1,int param2);

int16 position_servos[5] = {0};	// Variable qui garde les valeurs des positions des servos

//---------------------------------------------------------------------------
//BRAS ROBOTIS
#define ARM_INTERAXIS_LENGTH 70
#define ARM_ANGLE_MAX 50

int8 tab_id[5] = {1,2,9,3,14};


int16 arm_length_max = 0;
int16 arm_length_min = 0;

int16 angle_to_aim = 0;
int16 dist_to_atom = 0;
float angle_pos = 0;
int16 servo_pos_1 = 512;
int16 servo_pos_2 = 512;
int16 servo_pos_3 = 512;

int16 x_powed;
int16 y_powed;
int16 x_and_y;


enum{id, angle, wait};

//--------------------------------------------------------------------------



 /*==========================================================================
==== Fonction:	Init_uC				                                   	====
==== by FLOTHU 	21.01.2015                                       		====
====--------------------------------------------------------------------====
==== Fonction d'initialisation des ports du uC							====
==== Pas de param�tres													====
==== Ne retourne rien													====
============================================================================*/
void Init_uC(void)
{
	TRISC= 0b10001110;	// RX input, TX output, Direction output, 3 switchs input
	TRISD= 0b10000000;	// RX input, TX output, 3 LEDs output
	TRISB= 0b10000000;	// RX input, TX output, 3 LEDs output
	LED1 = LED2 = LED3 = 0;		// On �teint les LEDs
	enable_interrupts(INT_RDA);
	enable_interrupts(INT_RDA2);

	enable_interrupts(GLOBAL);
	
}

/*==========================================================================
==== Fonction:	Init_Servos			                                   	====
==== by FLOTHU 	22.01.2015                                       		====
====--------------------------------------------------------------------====
==== Fonction d'initialisation de la position des servos				====
==== Pas de param�tres													====
==== Ne retourne rien													====
============================================================================*/
void Init_Servos(void)
{
		// d'�viter d'envoyer des instructions inutiles aux servos
		Move_speed(100);	// Vitesse tr�s faible
		
		Envoyer_instruction(0xFE,0x02,0x18,0x01,0x00);
	 
		position_servos[0] = 512;	// Moteur 1 � 150 degr�s
		position_servos[1] = 200;	// Moteur 2 � 120 degr�s
		position_servos[2] = 220;	// Moteur 3 � 120 degr�s
		position_servos[3] = 810;	// Moteur 4 � 150 degr�s
		position_servos[4] = 512;	// Moteur 5 � 120 degr�s
		
		int i;
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
==== Pas de param�tres													====
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
==== Fonction qui permet de bouger un servo � un angle d�sir�     		====
==== Param�tres:	- ID: ID du servomoteur (num�ro �crit sur le servo)	====
====				- deg: angle d�sir� en degr�						====
====				  min = 0� ; middle = 150� ; max = 300�				====
==== Ne retourne rien													====
============================================================================*/
void Servo_goal_position(int ID, int16 deg)
{
	//position = deg * 3.41;	// conversion angle en degr�(0 � 300) --> valeur de 0 � 1023 pour le servo
	int16 position = 0;
	position = deg;	// conversion angle en degr�(0 � 300) --> valeur de 0 � 1023 pour le servo
	int position_1 = position & 0b0000000011111111;	// Position pour les low bits
	int position_2 = (position & 0b1111111100000000) >> 8;	// Position pour les high bits

	Envoyer_instruction(ID,0x03,0x1E,position_1,position_2);	//Envoie des instructions
	delay_us(100);	// Ce delay est n�cessaire sinon certains servos ne r�agissent pas
}	


/*==========================================================================
==== Fonction:	Move_speed                                            	====
==== by FLOTHU 	21.01.2015                                       		====
====--------------------------------------------------------------------====
==== Fonction qui permet de d�finir la vitesse de tous les servos      	====
==== Param�tres:	- speed: valeur entre 0 et 1023 r�glant la vitesse	====
====				  du servo. 0 = max, 1023 = 114 rpm, 300 = 33.3 rpm ====	
==== Ne retourne rien													====
============================================================================*/
void Move_speed(int16 speed)
{							
	int speed_1 = speed & 0b0000000011111111;			// position pour les low bits
	int speed_2 = (speed & 0b1111111100000000) >> 8;	// position pour les high bits
						
	Envoyer_instruction(0XFE,0x03,0x20,speed_1,speed_2);	// Envoie des instructions																				
	delay_us(100);	// Ce delay est n�cessaire sinon certains servos ne r�agissent pas						
	
}	

/*==========================================================================
==== Fonction:	Move_speed                                            	====
==== by FLOTHU 	21.01.2015                                       		====
====--------------------------------------------------------------------====
==== Fonction qui permet de d�finir la vitesse d'un seul servo         	====
==== Param�tres:	- ID: ID du servomoteur (num�ro �crit sur le servo)	====
====				- speed: valeur entre 0 et 1023 r�glant la vitesse	====
====				  du servo. 0 = max, 1023 = 114 rpm, 300 = 33.3 rpm ====	
==== Ne retourne rien													====
============================================================================*/
void Move_speed(int ID, int16 speed)
{
	int speed_1 = speed & 0b0000000011111111;			// position pour les low bits
	int speed_2 = (speed & 0b1111111100000000) >> 8;	// position pour les high bits					

	Envoyer_instruction(ID,0x03,0x20,speed_1,speed_2);	// Envoi de l'instruction																				
	delay_us(100);	// Ce delay est n�cessaire sinon certains servos ne r�agissent pas						
}	

/*==========================================================================
==== Fonction:	Envoyer_instruction	                                   	====
==== by FLOTHU 	21.01.2015                                       		====
====--------------------------------------------------------------------====
==== Fonction qui permet d'envoyer une instruction au servomoteurs		====
==== Param�tres: 	- ID: correspond � l'ID du servomoteur				====
====				- nbr_param: nombre de param�tre que l'on passe		====
====				- instruction: instruction d�sir�e (bouger le servo,====
====				  changer la vitesse, limite de couple,...)			====
====				- param1: premier param�tre				 			====
====				- param2: deuxi�me param�tre						====
==== Ne retourne rien													====
============================================================================*/
void Envoyer_instruction(int ID,int nbr_param,int instruction,int param1,int param2)
{
	int16 checksum = 0xFF;		// Reset du checksum

	Direction = 1;			// Direction � 1 pour pouvoir envoyer
	//disable_interrupts(INT_RDA);
	putc(0xFF, SERVOS);				// 0xFF pour le start
	putc(0xFF, SERVOS);				// Deuxi�me 0xFF pour le start
	putc(ID, SERVOS);				// Envoie de l'id
	putc(nbr_param + 2, SERVOS);	// Envoie du nombre de param�tre
	putc(0x03, SERVOS);				// Envoie de l'instruction Write_data
	putc(instruction, SERVOS);		// Envoie de l'instruction voulu
	putc(param1, SERVOS);			// Envoie du premier param�tre
	if(nbr_param == 3)		// Si un deuxi�me param�tre est n�cessaire
	{
		putc(param2);		// Envoie du deuxi�me param�tre
		checksum = checksum - param2;	// Calcul du checksum avec deuxi�me param�tre
	}
	checksum = checksum - ID - nbr_param - 2 - 3 - instruction - param1;	// Calcul du checksum final
	putc(checksum, SERVOS);			// Envoie du checksum
	delay_us(200);			// Delay pour laisser finir l'envoie de la trame
	//enable_interrupts(INT_RDA);
	Direction = 0;			// Direction � 0 pour pouvoir recevoir
}	

void Get_Atome(float x_atom, float y_atom, int1 x_right)
{
	
	x_powed = pow(x_atom, 2);
	y_powed = pow(y_atom, 2);
	
	x_and_y = x_powed + y_powed;
	
	dist_to_atom = sqrt(x_and_y);
	
	if(dist_to_atom > arm_length_min && dist_to_atom < arm_length_max)
	{
		if(!x_right)
		{
			angle_to_aim = (atan(y_atom/x_atom)*57.2958*3.316666) + 215;
		}
		else
		{
			angle_to_aim = ((180-(atan(y_atom/x_atom))*57.2958)*3.316666) + 215;
		}
		
		float tmp1 = dist_to_atom-ARM_INTERAXIS_LENGTH;
		float tmp2 = tmp1/2;
		float tmp3 = tmp2/ARM_INTERAXIS_LENGTH;
		
		angle_pos = acos(tmp3)*180/PI;
		int8 current_angle = 90;
		
		servo_pos_1 = 512-(angle_pos*3.41);
		servo_pos_2 = 525-(2*angle_pos*3.41);//-((180-angle_pos)*3.41);
		servo_pos_3 = 809-(angle_pos*3.41);
		
		Servo_goal_position(tab_id[0], angle_to_aim);
		Servo_goal_position(tab_id[1], servo_pos_1);
		Servo_goal_position(tab_id[2], servo_pos_2);
		Servo_goal_position(tab_id[3], servo_pos_3);	
		delay_ms(20);
	
	}	

	
}	




void main(void)
{
	Init_uC();	// Initialisation des ports utilis�s du microcontr�leur
	delay_ms(1000);
	
	Move_speed(100);	
	Init_Servos();
	Init_Arm();
	Move_speed(500);
	delay_ms(1000);
	
	
	
	while(1)	// une boucle infinie
	{
				
		Get_Atome(160, 80, 0);				
		
	}
}