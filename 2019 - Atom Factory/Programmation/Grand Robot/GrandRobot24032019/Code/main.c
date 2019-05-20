/*====================================================================================================
=											EMVs - EUROBOT	  										==
===											--------------											==
======================================================================================================
===	 Auteur				: Borgeat Remy				  												==
===  Date				: 8.6.2017																	==
===  Nom du programme 	: InterfaceRoboteQ.mcp (fichier main.c)										==
===  Version 			: V2.0.0.0.0																==
=====================================================================================================*/

#include <30F6014A.h>
#include "DSPIC30F_registers.h"

// Fuses
#fuses NOWDT, HS2_PLL8, NOPUT, NOPROTECT, DEBUG, NOBROWNOUT, NOWRTÂ 
#device ICD=TRUE
// DÃ©finit la vitesse du quartz (prendre en compte si PLL employÃ©e)
#use delay(clock=80000000)
// Config IIC
#use i2c(master,force_hw,slow,I2C1)
#build(stack=2048)
#use rs232(baud=115200,parity=N,xmit=PIN_F5,rcv=PIN_F4,bits=8,STREAM=ROBOTEQ) // Pour pouvoir utiliser le RS232/2
//#use rs232(baud=115200,parity=N,xmit=PIN_F3,rcv=PIN_F2,bits=8,stream=ROBOTEQ/*UART*/) // Pour pouvoir utiliser le RS232/1
#use spi (MASTER, MODE=0, BAUD=100000, SPI1, FORCE_HW)

// Variables utiles (globales)
int1 flagGameEnd=0,flagTimeOut=0;	// DÃ©finit si le temps est dÃ©passÃ©
int1 flagBaliseCheck=0;				// DÃ©finit si adversaire dÃ©tectÃ©
int1 flagError=0; 					// Si une erreur doit Ãªtre affichÃ©e
int1 flag_started = 0;
int1 ToDisplay=0;
int1 IsPassedTimeOut=0;
int1 flag_depl_ok = 0;
int1 flag_end = 0;
int1 _Detected = 0; 
int1 balise_on = 0;
int1 flag_error = 0; 
int1 Team=0;

signed int32 ActualPosition = 0;
unsigned int32 RealTimeMS=0,BeginTimeMS=0,GameTimeMS=0;
unsigned int8 value_balise=0;	// Valeur de la balise en dÃ©tection
unsigned int8 GameTimeS=0;	// Temps de jeu
unsigned int8 Time_detected = 0;
unsigned int8 TIME_tempo_dectected = 4;
unsigned int8 No_erreur = 0; 
unsigned int8 Value_bal = 0; 
unsigned int8 Tempo_bal = 0 ; 


unsigned int8 NoObj = 1;
unsigned int8 NoPts = 1;
unsigned int32 last_obj = 0;

int1 Check = 1;
unsigned int8 points = 0;
unsigned int8 solution = 0;

unsigned int8 Write_cmd_arduino(unsigned int8 cmd,unsigned int8 taille, unsigned int8 *data ) ;


// DÃ©finit les constantes ASCII, comme il n'a pas l'air de les prendre ...
enum{NUL,SOH,STX,ETX,EOT,ENQ,ACK,BEL,BS,TAB,LF,VT,FF,CR,SO,SI,DLE,DC1,DC2,DC3,DC4,NAK,SYN,ETB,CAN,EM,SUB,ESC,FS,GS,RS,US,SPACE};
enum{Init, Choose_objectif, Check_ZI, Send_depl_action, Send_depl_action_ZI, Depl_action_process, Depl_action_process_ZI,Switch_end_obj,Wait_end} Etat_rob = Init;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define BalSensitivity 3
#define MARGE 360
#define SIZE_TABLE_X 3000
#define SIZE_TABLE_Y 2000
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Inclusion des fichiers sources
#include "driver_moteur.c"
#include "Com_balises.c"
#include "Init.h"
#include "data/___data.h"
#include <math.h>
#include <stdlib.h>
#include "servomoteur/servomoteur.h"
#include "LCD/___LCD.h"
#include "Deplacement/___Depl.h"
#include "Functions.h"
#include "PC/___PC.h"
#include "zonesinterdites/__ZonesInterdites.h"



//********************************************************************************
//*  Mains
//****************************************************************************************************
void main(void)
{
	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////	INITIALISATION DE TOUS LES MODULES	////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
		// Initialisation du dsPIC
	__Init_dsPIC();	
	__Init_UART();
	//__Init_pos();
					
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			// Configuration de la balise
	Balise_config_plage(0, 12, 14);	// En avanÃ§ant
	delay_ms(100);
	Balise_config_plage(1, 4, 6); // En reculant
	delay_ms(100);

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Set la base
		// On n'affiche pas l'erreur ici car si on dÃ©branche le driver de dÃ©placement
		// pour envoyer les objectifs, cela bloquerait le systÃ¨me
//	unsigned int8 ToSetBase=0;

	LED3 = 1;
	
	if(_TEAM==0)
	{
		//_LDT1=0;
		//_LDT2=1;
		Team=0;
		LED3 = 0;
		
	}
	else if(_TEAM==1)
	{
		//_LDT2=0;
		//_LDT1=1;
		Team=1;
		LED3 = 1;
	}	
	
	delay_ms(500);
	
	fprintf(ROBOTEQ,"!MG\r");
	////////////////////////////////////////////////////////////////////////////////////////
			
	////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////	PROGRAMME PRINCIPAL	////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
	int1 action_ok1 = 0;
	int1 action_ok2 = 0;
	int1 action_ok3 = 0;
	int1 Module_inplace = 0;
	
	LED1 = 1;
	delay_ms(200);
	LED1 = 0;
	LED2 = 1;
	delay_ms(200);
	LED2 = 0;
	LED3 = 1;
	delay_ms(200);
	LED3 = 0;
	delay_ms(200);
	LED3 = 1;
	delay_ms(200);
	LED3 = 0;
	LED2 = 1;
	delay_ms(200);
	LED2 = 0;
	LED1 = 1;
	delay_ms(200);
	LED1 = 0;
	delay_ms(180);
 	
  		
	while(1)
	{		
		switch(Etat_rob)
		{
			case Init:
			
				if(!_DEMA && flag_started == 0)
				{
					LED3 = 1;
					LED2 = 0;
					LED1 = 0;
					flag_started = 1;
				}
					
				else if(_DEMA && flag_started == 0)
				{
					LED1 = 1;
					LED2 = 1;
					LED3 = 1;
					
					delay_ms(200);
					
					LED1 = 0;
					LED2 = 0;
					LED3 = 0;
					
					delay_ms(200);
				}
				
				else if(NbreObjectifs > 0 && _DEMA  && !flag_end && flag_started == 1)//si on a des objectifs et qu'il sont charger
				{
					LED3 = 0;
					LED2 = 0;
					LED1 = 1;
					
					if(BeginTimeMS==0) 
					{
						BeginTimeMS = RealTimeMS;
						//delay_ms(1000); 
					}
					__LoadObj(NoObj,NoPts);//on mets l'objectifs dans des variables
					Etat_rob = Check_ZI;//on change d'etat
					Depl_send = 0;			
				}
				else if(NbreObjectifs == 0 && !_DEMA  && !flag_end && flag_started == 1)
				{
					LED3 = 0;
					LED2 = 1;
					LED1 = 0;
					__ReadObjectifs();	
					__ReadZones_Interdites();
				}
				else if(!_DEMA && NbreObjectifs != 0 && flag_started == 1)
				{		
					LED3 = 0;
					LED2 = 1;
					LED1 = 1;		
					__Init_pos();	

					//Envoi de l'initialisation �l'arduino pour lui indiquer de quel c�t� on joue
					
					//data_to_transmit[0] = Team;
					//Write_cmd_arduino(100,1, &data_to_transmit );				
				}
						
					
					
				break;


			
			case Choose_objectif:

				/*
				static int obj_todo = 0; //L'objectif qu'on regarde si on peut le faire

				obj_todo++; //On passe � l'objectif suivant
				__LoadObj(obj_todo, 1); //On r�cup�re les donn�es de l'objectif dans les variables

				if(oTime < (TimeLimit - GameTimeS) && !obj_done && !obj_notcontinuable)
				{
					Etat_rob = Check_ZI;
				}

				if (obj_todo >= (NbreObjectifs)) 
				{
					obj_todo = 0;
					Etat_rob = Wait_end;
				}
				*/
				break;
				

			case Check_ZI:

				if(checkPath())
				{
					Etat_rob = Send_depl_action;
				}
				else
				{
					//On met le point de d�part dans la premi�re case du tableau
					i_rel = 0;
					PtsRelai[i_rel][X] = Pos_x; 
					PtsRelai[i_rel][Y] = Pos_y; 
					i_rel++;
					
					findPath();
					
					i_rel++;
					PtsRelai[i_rel-1][X] = oXp; 
					PtsRelai[i_rel-1][Y] = oYp; 
					i_depl = 1;
					
					if(path_impossible == 1)
			        {
				        __Stop();
				    } 
				    else
				    {
					    Etat_rob = Send_depl_action_ZI;
					} 
					
				}

				break;

			case Send_depl_action:

				if(!Depl_send && !flag_end)//si le deplacement n'as pas ete envoye
				{
					__DeplToDo(oType);//envoie le d�placment
				}
				if(!Action_send && !flag_end)//si l'action n'a pas ete envoyee
				{
					flag_action_done = 0;
					__Action_Writting(obj_Action);//envoie l'action
				}
				if(/*flag_action_done &&*/ Depl_send && Action_send && !flag_end)//si tout a ete envoye
				{
					Depl_send = 0;
					Action_send = 0;
					Etat_rob = Depl_action_process;
				}
				break;


			case Send_depl_action_ZI:

				//__Check_commande_atteint();
				
				if(!Action_send)//si l'action n'a pas ete envoyee
				{
					flag_action_done = 0;
					__Action_Writting(obj_Action);//envoie l'action
				}

				//Si le déplacement n'a pas encore été envoyé
				if(!Depl_send)
				{
					//On l'envoie
					__PaP(PtsRelai[i_depl][X], PtsRelai[i_depl][Y]);
				}

				//Si tout a été envoyé
				if(Depl_send && Action_send && !flag_end)//si tout a ete envoye
				{
					Depl_send = 0;
					Action_send = 0;
					Etat_rob = Depl_action_process_ZI;
				}

				break;

			case Depl_action_process :

				__Check_commande_atteint();
				Check_action_done();
				
				if(flag_depl_ok/* && flag_action_done*/ && Check && !flag_end && !_Detected)//on attend que tout soit fini
				{
					if(NoObj==1&&NoPts==1) delay_ms(1000);
					//actualisation position xy 
					Pos_x += Dist_x; 
					Pos_y += Dist_y;
					
	
					Dist_x=0;
					Dist_y=0;
					Dorient = 0;
					balise_on = 0;
					flag_depl_ok = 0;
					action_ok1 = 0;
					action_ok2 = 0;
					action_ok3 = 0;
					Etat_rob = Switch_end_obj;
				}
				break;

			case Depl_action_process_ZI:

				__Check_commande_atteint();
				Check_action_done();
				
				if(flag_depl_ok && flag_action_done && Check && !flag_end && !_Detected)//on attend que tout soit fini
				{
					if(NoObj==1&&NoPts==1) delay_ms(1000);
					//actualisation position xy 
					Pos_x += Dist_x; 
					Pos_y += Dist_y;
					
	
					Dist_x=0;
					Dist_y=0;
					Dorient = 0;
					balise_on = 0;
					flag_depl_ok = 0;
					action_ok1 = 0;
					action_ok2 = 0;
					action_ok3 = 0;
					
					i_depl++;
					
					if(i_depl >= i_rel)//si tout a ete envoye
					{
						Depl_send = 0;
						Action_send = 0;
						int i;
						for(i = 0; i < 10; i++)
						{
							PtsRelai[i][0] = 0;
							PtsRelai[i][1] = 0;
						}	
						path_opposite = 0;
						Etat_rob = Switch_end_obj;
					}
					else
					{
					 Etat_rob = Send_depl_action_ZI;
					}	
					
				}
				break;	

			
			case Switch_end_obj:
			
				if(keep_obj==0) 
				{
					TabObjectifs[NoObj][1][8] = 0; // mise de la ponderation a 0 --> on le remploie plus
				}
			 	if(Obj_end)//si fini l'objectifs,passe a l'obj suivant
				{
					if(Next_obj!=0) // 0--> passe a l'obj suivant, sinon va a l'obj marquer
					{
						last_obj = NoObj;
						NoObj = Next_Obj;
						NoPts = 1;
						__LoadObj(NoObj,NoPts);//charge le nouveau pts						
					}
					else
					{
						last_obj = NoObj;
						do //prochain objectifs avec pondÃ©ration de 10
						{
							//__Afficheur_7segments(4);
							NoObj++; // on passe a l'objectifs suivant
							NoPts=1; // on reprend au premier pts
							if(NoObj == 10)
							{
								Flag_end = 1;
								Ponderation = 10;
							}
							else __LoadObj(NoObj,NoPts);//charge le nouveau pts
	
						}while(Ponderation!=10);

					}
				}
				else
				{
					if(Pt_commun==1) NoPts+=2; // skip le pts droite
					else NoPts++; // passe au pt suivant suivant																
					__LoadObj(NoObj,NoPts);//charge le nouveau pts
				}	
				if(Pt_commun!=0)//si point pas symetrique
				{
					if(Team)//pt droite
					{
						if(Pt_commun==1) NoPts++; // passe Ã  l'obj suivant (pt droite)
					}
				}
				
				if(!Flag_end) Etat_rob = Init;
				break;

			case Wait_end: //case wait
				if(flag_error) //erreur --> clignotement 7 segments
				{
					LED1 = 1;
					
					delay_ms(200);
					
					LED1 = 0;
					
					delay_ms(200);
				}
				if(flagGameEnd)
				{
					LED1 = 1;
					delay_ms(200);
					LED1 = 0;
					LED2 = 1;
					delay_ms(200);
					LED2 = 0;
					LED3 = 1;
					delay_ms(200);
					LED3 = 0;
					delay_ms(200);
					LED3 = 1;
					delay_ms(200);
					LED3 = 0;
					LED2 = 1;
					delay_ms(200);
					LED2 = 0;
					LED1 = 1;
					delay_ms(200);
					LED1 = 0;
					delay_ms(180);
					
					// Desactive tout le reste
					disable_interrupts(INTR_GLOBAL);
					flagGameEnd=0;			
				}				
				break;			
			default:
			
				break;
		}
		////////////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////////////////
		////////////////////////	ACTION PARALLELES	////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		
		/////////////////////////////////////////////////////////////////////////////////////
		///////////////////////        BALISE          //////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////
		if(flagBaliseCheck && !flag_end && balise_on && !flag_error)
      	{
        	Value_bal = Check_balise(); 			//Recuperation de la valeur de la bailse
        	tempo_bal++; 							//temporisation de la balise, d'une fois detecte, il faut passer 4  tempo bal = 4 pour continuer
	        if(Value_bal>=MAX_VALUE_DETECT_BALISE) 	//si adversaire trop proche
	        {   
	       		tempo_bal = 0;						//remise a 0 de la tempo
           		////__Afficheur_7segments(44);
	           	LED1,LED2,LED3 = 1;
	           	_Detected = 1;						//indique que l'on a detecte l'adversaire
	        
	            /////////////////// Arret du robot ///////////////////////////////////////
	            fprintf(ROBOTEQ,"^MDEC 1 9000_^MDEC 2 9000\r");	//rampe de dec. plus raide 
	            delay_ms(20);
	            fprintf(ROBOTEQ,"!S 1 0_!S 2 0\r");				//vitesse du robot a 0 --> il va freiner

	            if(Time_detected==0) // recuperation du temps de la detection
	            {
	               Time_detected = GameTimeS;
	            }
	            else if(((GameTimeS - Time_detected) >= TIME_tempo_dectected))//on attend 6s
	            { 
	            	
	            	__actual_pos();// actualisation de la Pos xy 
    				
    				/////////////////// effacer l'ordre en cours  /////////////////// 
                  	fprintf(ROBOTEQ,"^MMOD 1 0_^MMOD 2 0\r"); //passage en open loop speed
                  	delay_ms(10);
                  	fprintf(ROBOTEQ,"^MMOD 1 3_^MMOD 2 3\r"); //passage en closed loop count postion
	                  	
					if(checkPath())
					{
						////__Afficheur_7segments(0);
						__Stop();
					}
					else
					{
						
	                  	
	                  	_Detected = 0;
		                balise_on = 0;
		                Dist_x = 0;
		                Dist_y = 0;
		                Dorient = 0; 
		                Time_detected=0;
		                
		                Depl_send = 0;
						Action_send = 0;
						int i;
						for(i = 0; i < 10; i++)
						{
							PtsRelai[i][0] = 0;
							PtsRelai[i][1] = 0;
						}
	                  	
	                  	path_impossible = 1;
	                  	
	                  	Etat_rob = Check_ZI;
	                  	
	                  	
					}
     
	            	/*
	                if(TabObjectifs[(NoObj+1)][1][8]!=10 && TabObjectifs[(NoObj+1)][1][8]!=0)//si obj suivant pond entre 1 et 9 --> on switch l'obj
	                {
	                   /////////////////// actualisation position x,y ///////////////////
	                  __actual_pos();// actualisation de la Pos xy 

	                   /////////////////// effacer l'ordre en cours  /////////////////// 
	                  fprintf(ROBOTEQ,"^MMOD 1 0_^MMOD 2 0\r"); //passage en open loop speed
	                  delay_ms(10);
	                  fprintf(ROBOTEQ,"^MMOD 1 3_^MMOD 2 3\r"); //passage en closed loop count postion

	                   /////////////////// Passage a l'obj suivant  ///////////////////
	                  NoObj++; // passage a l'objectif suivant
	                  NoPts = 1; // on demarre par le premier pts
	                  __LoadObj(NoObj,NoPts);//charge le nouveau pts
	               
	                  if(Pt_commun!=0)//si point pas symetrique
	                  {
	                  if(Team)//pt droite
	                  {
	                     if(Pt_commun==1) NoPts++; // passe Ã  l'obj suivant (pt droite)
	                  }
	                  }
	                  Etat_rob = Init; // on recommence le programme
	                  _Detected = 0;
	                  balise_on = 0;
	                  Dist_x = 0;
	                  Dist_y = 0;
	                  Dorient = 0; 
	                  _LED2,_LED3,_LED4 = 0;
	                  Time_detected=0;
	                }
	                */

	            }
	        }
	        else if(_Detected && tempo_bal == 4) // si detecte et que l'adv n'est plus la 
	        {
	             /////////////////// Reprise de l'ordre  ///////////////////         
	            fprintf(ROBOTEQ,"^MDEC 1 6000_^MDEC 2 6000\r");//on reprend le dernier ordre   
	            fprintf(ROBOTEQ,"!S 1 %u_!S 2 %u\r",oVitMax,oVitMax);

	            Time_detected = 0; 
	            LED1=0;
	            _Detected = 0;
            
	        }
	        LED1=!LED1; 
	        flagBaliseCheck = 0;
	    }   

		/////////////////////////////////////////////////////////////////////////////////////
		///////////////////////        UART            //////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////
		if(PCh_flagUARTReadyToDecode) __UART_Decode(TabDecoded);


		/////////////////////////////////////////////////////////////////////////////////////
		///////////////////////        Fin du prog.    //////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////
		if((Flag_end || flagTimeOut || flag_error) && !IsPassedTimeOut)
		{
			////__Afficheur_7segments(points);

			IsPassedTimeOut=1;
			// arret moteurs
			fprintf(ROBOTEQ, "!EX \r"); 
			
			Etat_rob = Wait_end;
		}
		
	}
}





/**
* \fn void TIMER1_isr(void)
* \author Amand Axel
* \version 2.0
* \date 19.10.2015
*
* \brief Met Ã  jour la pose, gÃ¨re le profil trapÃ©zoÃ¯dal et le PID
*		 S'active chaque 1 [ms]
*
*/
#INT_TIMER1 HIGH
void TIMER1_isr(void)
{
	// Compte le temps rÃ©el
	RealTimeMS ++;
	// Temps de jeu
	if(BeginTimeMS!=0)
	{
		GameTimeMS=RealTimeMS-BeginTimeMS;
		if(GameTimeMS%1000==0)GameTimeS++;
	}	
	
	////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////	TASK GIVER	////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////
	// Balise Ã  checker
	if(GameTimeS == 92) FlagGameEnd = 1; 
	if(BeginTimeMS!=0 && GameTimeMS%TIME_TO_CHECK_BAL==0)
	{
		// Check Balise
		flagBaliseCheck=1;
	}
	if(BeginTimeMS!=0 && GameTimeMS%500==0)ToDisplay=!ToDisplay;
	////////////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////	WATCHDOG INTERRUPTS	////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////
	// WD Times
	static unsigned int16 UART_WD_TIME=0;
	
	// Watchdog UART, rÃ©initialise la capture
	if(PCh_flagUARTWatchdog==1)
	{
		UART_WD_TIME++;
		if(UART_WD_TIME>=UART_WD_DELAY)
		{
			// Reset UART
			ToDoUART = 0;
			PosTabToDecode=0;
			UARTToSendBack=0;
			UARTWaitResp=0;
			// Desactive le watchdog UART
			PCh_flagUARTWatchdog = 0;
		}
	}
	else UART_WD_TIME=0;
	////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////		PROGRAM END		////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////
	// AprÃ¨s 1min30, on arrÃªte les Ã©lÃ©ments essentiels
	if(BeginTimeMS!=0 && GameTimeS>=98)
	{
		flagTimeOut=1;
	}
	// AprÃ¨s la fin de jeu, on ouvre le parasol 
	if(BeginTimeMS!=0 && GameTimeS>=92)
	{
		//flagGameEnd=1;
	}	
}

////////////////////////////////////////
//// Timer de clignotement d'erreur. ////
////////////////////////////////////////
#INT_TIMER3
void TIMER3_isr(void)
{
	static int1 On_Off_Error = 0;
	
	// Si doit afficher une erreur
	if(flagError)
	{
	//	//__Afficheur_7segments(NO_ERROR,On_Off_Error);
		On_Off_Error =! On_Off_Error;
	}	
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    