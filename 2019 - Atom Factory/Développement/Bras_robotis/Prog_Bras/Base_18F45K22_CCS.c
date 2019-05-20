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

#device ICD=TRUE
#DEVICE HIGH_INTS=TRUE
#use delay(clock=20000000)
#fuses NOWDT, WDT128, HSH, NOPLLEN, NOBROWNOUT, WDT_SW, NOLVP, NOXINST, DEBUG	// fuses valable pour le PIC18F45K22
#use rs232(baud=115200,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1)
//#use rs232(baud=1000000,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1)

#bit LED1 = PORTD.0	// Les trois LEDs de signalisation de mon circuit
#bit LED2 = PORTD.1
#bit LED3 = PORTD.2
#bit Direction = PORTC.4	// Permet de choisir si l'on veut transmettre ou
							// recevoir des données des servometeurs (1=TX, 0=RX)
// Prototypes des fonctions
void Init_uC(void);
void Init_Servos(void);
void Desactiver_status_return(void);
void Servo_goal_position(int ID, int16 deg);
void Move_speed(int16 speed);
void Move_speed(int ID, int16 speed);
void Envoyer_instruction(int ID,int nbr_param,int instruction,int param1,int param2);
void set_pos_servos(int number);
int1 Send_Sequence(void);
void Receive_data();
void Read_data(int ID,int instruction,int param1,int param2);
void Reset_motor(int id);
void Ask_Positions();

// Variables globales
int16 present_pos[5] = {0, 0, 50, 0, 0};
int16 present_pos2[5] = {0, 0, 50, 0, 0};


int i = 0;	// Variable qui permet de faire des incrémentations dans des boucles for
int16 position=0;	// Variable qui contient la valeur de la position désirée de servo
int16 position_servos[6] = {0};	// Variable qui garde les valeurs des positions des servos
int8 ID_servos[6] = {1, 17, 9, 3, 14,0};
int checksum = 0xFF;	// Variable qui contient 0xFF - les valeurs envoyées au servomoteur
int16 dataReceived[] = {0};
int16 new_data[8] = {0};
int1 receive_done = 0;
int8 i_data;


int index;
int8 Etat_Ask_Positions = 0;
int8 Etat_Send_Sequence = 0;
int1 ready_to_ask = 1;
int8 i_id = 0;


enum{id, angle, wait};

int8 tab_id[5] = {1,2,9,3,14};
int16 tab_pos[][5] = {{100,80,0,150,120}, {200,150,150,150,150}, {150,80,200,150,120}, {120,80,200,90,120}, {180,80,200,210,120}, {225,80,0,150,120}, {225,150,150,150,150}, {225,80,0,150,120}, {180,90,200,210,120}, {150,80,200,150,120}, {150,80,0,150,120}};
int16 tab_sequence[][3] = {{14,400,0},{2,514,1},{9,250,2}};

void main(void)
{
	Init_uC();	// Initialisation des ports utilisés du microcontrôleur
	delay_ms(1000);
	
	Move_speed(50);
	
	
	while(1)	// une boucle infinie
	{
		Read_data(0x01, 0x02, 0x24, 0x02);
		delay_ms(20);
		
		/*
		Send_Sequence();
		delay_ms(20);
 		
		
		//Envoyer_instruction(0xFE,0x02,0x04,16,0);
		set_pos_servos(1);
		delay_ms(2000);
		set_pos_servos(0);
		delay_ms(2000);
		
		
		
		
		
		
		
		
		checksum = 0xFF;		// Reset du checksum
		Direction = 1;			// Direction à 1 pour pouvoir envoyer
		putc(0xFF);				// 0xFF pour le start
		putc(0xFF);				// Deuxième 0xFF pour le start
		putc(0x02);				// Envoie de l'id
		putc(0x02);				// Envoie de l'id
		putc(0x01);				// Envoie du nombre de paramètre
		putc(0xFA);				// Envoie du checksum
		delay_us(200);
		Direction = 0;			// Direction à 1 pour pouvoir envoyer
		
		delay_ms(50);
			
		*/
		
	}
}

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
	LED1 = LED2 = LED3 = 0;		// On éteint les LEDs
	
	enable_interrupts(INT_RDA);

	enable_interrupts(GLOBAL);
	
}

void set_pos_servos(int number)
{
		for(i=0;i<5;i++)	// Boucle permettant d'envoyer 
		{	
			// les 6 instructions aux 6 servos
			Servo_goal_position(tab_id[i], tab_pos[number][i]);	// Envoi de l'instruction
			delay_us(100);	
		}		
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
		Move_speed(50);	// Vitesse très faible
		
		Envoyer_instruction(0xFE,0x02,0x18,0x01,0x00);
	 
		position_servos[0] = 180;	// Moteur 1 à 150 degrés
		position_servos[1] = 180;	// Moteur 2 à 120 degrés
		position_servos[2] = 180;	// Moteur 3 à 120 degrés
		position_servos[3] = 180;	// Moteur 4 à 150 degrés
		position_servos[4] = 180;	// Moteur 5 à 120 degrés
		position_servos[5] = 0;	// Moteur 6 à 150 degrés
		
		for(i=0;i<=4;i=i+1)	// Boucle permettant d'envoyer 
		{					// les 6 instructions aux 6 servos
			Servo_goal_position(ID_servos[i], position_servos[i-1]);	// Envoi de l'instruction
			delay_us(100);	
		}
		
}

void Ask_Positions()
{
	enum{SEND, WAIT};
	
	switch(Etat_Ask_Positions)
	{
		case SEND :
			ready_to_ask = 0;
			Read_data(tab_id[i_id], 0x02, 0x24, 0x02);
			Etat_Ask_Positions = WAIT;
			break;
			
		case WAIT :
			if(ready_to_ask == 1);
			{
				Etat_Ask_Positions = SEND;
				i_id++;
				
				if(i_id > 4)
				{
					i_id = 0;
				}
			}		
			break;
	}		
		
}	

/*==========================================================================
==== Fonction:	Send_Sequence		                                   	====
==== by AURRIT 	03.12.2018                                       		====
====--------------------------------------------------------------------====
==== Fonction d'initialisation de la position des servos				====
==== Pas de paramètres													====
==== Ne retourne rien													====
============================================================================*/
int1 Send_Sequence(void)
{
	enum{Send, Ask_Position, Wait, Check_Value};
	
	switch(Etat_Send_Sequence)
	{
		case Send :
			Servo_goal_position(tab_sequence[index][id], tab_sequence[index][angle]);	// Envoi de l'instruction
			if(tab_sequence[index][wait] == 1)
			{
				Etat_Send_Sequence = Ask_Position;
			}
			else if(tab_sequence[index][wait] == 2)
			{
				index = 0;
				return 1;
			}	
				
			else
			{
				index++;
			}		
				
			break;
		
		case Ask_Position :
			
			Read_data(tab_sequence[index][id], 0x02, 0x24, 0x02);
			Etat_Send_Sequence = Check_value;
		
			break;
			
		case Wait :
			
			//Read_data(tab_sequence[index][id], 0x02, 0x24, 0x02);
			//delay_ms(5);
			
			if(receive_done > 0)
			{
				receive_done = 0;
				Etat_Send_Sequence = Check_value;
			}	

			break;
			
		case Check_value :
			
			
			int16 position_error = tab_sequence[index][1]-present_pos[tab_sequence[index][0]];
			if(position_error < 20)
			{
				index++;
				Etat_Send_Sequence = Send;
			}
			else
			{
				Etat_Send_Sequence = Ask_Position;
			}	
				
				
	}	
		
}

//------------------------------------------------------------------------------
// Chaque caractrère reçu via le RS232, la routine suivante est exécutée
//------------------------------------------------------------------------------
// Cette fonction permet de lire les données reçues via le RS232. Si on n'attend
//------------------------------------------------------------------------------
// Aucun paramètre
//------------------------------------------------------------------------------
#INT_RDA
void RX_isr(void)
{
	LED1= 1;
	int data = getc();	
	new_data[i_data] = data;
	
	switch(i_data)
	{
		case 0:
			if(data == 0xFF)
				i_data = 1;
			break;
		
		case 1:
			if(data == 0xFF)
				i_data = 2;
			else
				i_data = 0;
				
			break;
			
		case 7:
			i_data = 0;
			Receive_data();
			ready_to_ask = 1;
			break;
		
		default:
			i_data++;
			break;
	}		
	

	
	
	LED1= 0;
	
}

/* =========================================================================
==== Fonction:	Desactiver_status_return                              	====
==== by FLOTHU	23.01.2015                                             	====
====--------------------------------------------------------------------====
==== Fonction qui permet de désactiver tous les status return des servos====
==== Pas de paramètres													====
==== Ne retourne rien													====
============================================================================*/
void Desactiver_status_return(void)
{								
	for(i=1;i<=18;i++)							//Boucle de 1 à 18
	{
		Envoyer_instruction(i,0x02,0x10,0,0);	//Envoie des instructions
												//0x10 -> status return
		delay_ms(1);	//Delay pour laisser les moteurs envoyer un status return
	} 											
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
==== Fonction:	Receive_data                                           	====
==== by FLOTHU 	21.01.2015                                       		====
====--------------------------------------------------------------------====
==== Fonction qui permet de définir la vitesse d'un seul servo         	====
==== Paramètres:	- ID: ID du servomoteur (numéro écrit sur le servo)	====
====				- speed: valeur entre 0 et 1023 réglant la vitesse	====
====				  du servo. 0 = max, 1023 = 114 rpm, 300 = 33.3 rpm ====	
==== Ne retourne rien													====
============================================================================*/
void Receive_data()
{
	int16 checksum = 0xFF - new_data[2] - new_data[3] - new_data[4] - new_data[5] - new_data[6];
	
	if(checksum == new_data[7])
	{
		int16 pos_temp = (new_data[6]<< 8)+new_data[5];
		present_pos[new_data[2]] = pos_temp;
	}	
	
	
}

/*==========================================================================
==== Fonction:	Envoyer_instruction	                                   	====
==== by FLOTHU 	21.01.2015                                       		====
====--------------------------------------------------------------------====
==== Fonction qui permet d'envoyer une instruction au servomoteurs		====
==== Paramètres: 	- ID: correspond à l'ID du servomoteur				====
====				- instruction: pour lire 0x02						====
====				- param1: adresse de la valeur qu'on veut lire		====
====				- param2: longueur de la donnée à lire				====
==== Ne retourne rien													====
============================================================================*/
void Read_data(int ID,int instruction,int param1,int param2)
{
	checksum = 0xFF;		// Reset du checksum
	//disable_interrupts(INT_RDA);
	Direction = 1;			// Direction à 1 pour pouvoir envoyer
	putc(0xFF);				// 0xFF pour le start
	putc(0xFF);				// Deuxième 0xFF pour le start
	putc(ID);				// Envoie de l'id
	putc(0x04);	// Envoie du nombre de paramètre
	putc(instruction);		// Envoie de l'instruction voulu
	putc(param1);			// Envoie du premier paramètre
	putc(param2);		// Envoie du deuxième paramètre
	checksum = checksum - ID - 0x04 - instruction - param1 - param2;	// Calcul du checksum final
	
	putc(checksum);			// Envoie du checksum
	delay_us(200);			// Delay pour laisser finir l'envoie de la trame
	//enable_interrupts(INT_RDA);
	Direction = 0;			// Direction à 0 pour pouvoir recevoir
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
	putc(0xFF);				// 0xFF pour le start
	putc(0xFF);				// Deuxième 0xFF pour le start
	putc(ID);				// Envoie de l'id
	putc(nbr_param + 2);	// Envoie du nombre de paramètre
	putc(0x03);				// Envoie de l'instruction Write_data
	putc(instruction);		// Envoie de l'instruction voulu
	putc(param1);			// Envoie du premier paramètre
	if(nbr_param == 3)		// Si un deuxième paramètre est nécessaire
	{
		putc(param2);		// Envoie du deuxième paramètre
		checksum = checksum - param2;	// Calcul du checksum avec deuxième paramètre
	}
	checksum = checksum - ID - nbr_param - 2 - 3 - instruction - param1;	// Calcul du checksum final
	putc(checksum);			// Envoie du checksum
	delay_us(200);			// Delay pour laisser finir l'envoie de la trame
	//enable_interrupts(INT_RDA);
	Direction = 0;			// Direction à 0 pour pouvoir recevoir
}	


/*==========================================================================
==== Fonction:	Reset_motor 											====
==== by FLOTHU 	12.02.2015                                       		====
====--------------------------------------------------------------------====
==== Fonction qui reset des moteurs s'ils sont beugés     				====
==== Pas de paramètres													====
==== Ne retourne rien													====
============================================================================*/

// IMPORTANT: Pour utiliser cette fonction, il faut déconnecter tous 
// les moteurs et laisser seulement le servo que l'on désire reset
void Reset_motor(int id)
{
	Direction = 1;				//Direction à 1 pour pouvoir envoyer
	putc(0xFF);					//Envoie de 0xFF pour le start
	putc(0xFF);					//Deuxième 0xFF pour le start
	putc(id);					//Envoie de l'adresse
	putc(0x02);					//Envoie de la longueur des paramètres + 2 (0+2) donc 0x02
	putc(0x06);					//Envoie de l'instruction Reset
	putc(0xF7 - id);			//Envoir du checksum (0xF7 - adress)
	Direction = 0;				//Direction à 0 pour pouvoir recevoir
	delay_ms(20);				//Delay de 20 ms pour laisser le temps de reset
	
	

	Direction = 1;				//Direction à 1 pour pouvoir envoyer
	putc(0xFF);					//Envoie de 0xFF pour le start
	putc(0xFF);					//Deuxième 0xFF pour le start
	putc(0x01);					//Envoie de l'adress (0x01), un servo reset prend toujours l'adress 1
	putc(0x04);					//Envoie de la longeur des paramètres + 2 (2+2) donc 0x04
	putc(0x03);					//Envoie de l'instruction Write_data
	putc(0x03);					//Envoie de l'adresse de l'eeprom du servo -> 0x03
	putc(2);					//Envoie de l'adresse que l'on désire avoir
	putc(0xF4 - id);			//Envoie du checksum (0xF4 - adress)
	Direction = 0;				//Direction à 0 pour pouvoir recevoir
	delay_ms(1);				//Delay pour laisser passer le temps de la réception d'une trame
	
	
}
