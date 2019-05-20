 /*====================================================================================================
=											EMVs - EUROBOT	  						==
===											--------------							==
======================================================================================
===	 Auteur				: Borgwat RÃ©my				  								==
===  Date				: 26.2.16													==
===  Nom du programme 	: InterfaceRoboteQ.mcp (fichier main.c)						==
===  Version 			: V2.0.0.0.0												==

======================================================================================
=== Description :																
	=== 																			==
	==============================================================*/	

#include "30F6014A.h"


#device ICD=TRUE
#device ADC=10

// Fuses
#fuses NOWDT, HS2_PLL8, NOPUT, NOPROTECT, DEBUG, NOBROWNOUT, NOWRT

// DÃ©finit la vitesse du quartz (prendre en compte si PLL employÃ©e)

#use delay(clock=80000000)

#build(stack=1024)
// Config IIC

#use i2c(master,force_hw,SLOW,I2C1)
// Config RS232
#use rs232(baud=115200,parity=N,xmit=PIN_F3,rcv=PIN_F2,bits=8,stream=ROBOTEQ/*UART*/) // Pour pouvoir utiliser le RS232/1
//#use rs232(baud=115200,parity=N,xmit=PIN_F5,rcv=PIN_F4,bits=8,stream=ROBOTEQ) // Pour pouvoir utiliser le RS232/2

#define BalSensitivity 3
#define Entraxe_roue 167
#define diametre_roue 9 // 72 /8 pour pas d�passer int32
#define impulsion_tour 11008 //nbre impulse encoder * reducteur * 4 = 88064 /8 pour pas d�passer int32
#define distance_1 50
#define d_capteur 670
#define pi 3.1416



// Variables utiles (globales)
int1 flag_servo = 0;
int1 flagTimeOut=0;   // dit que le temps est écouler
int1 flagBaliseCheck=0;   // permet le check d'adversaire
unsigned int value_balise;
unsigned int8 toto;

int1 Flag_check_cratere=0; //MODIFIE

int nbreEssai = 0;
int Score = 0;
int8 debug1 =0;

int1 flag_depl_ok = 0;
unsigned int16 Time = 0;
//unsigned int8 Erreur_surchage_d1,Erreur_surchauffe_d1,Erreur_noconnect_d1,Erreur_surchage_d2,Erreur_surchauffe_d2,Erreur_noconnect_d2 = 0;
unsigned int8 Arret_Cratere = 0;

enum{stop, action1_avance1, action1_pince20, action1_pince21, action1_pince22, action1_pince23, action1_pince24, action1_pince25, action1_pince26, action1_pince27, action1_pince28, action1_pince29, action2_extension3, action2_avance4, action2_repli5, action3_recule6, action3_tourne7, action3_avance8, action3_tourne9, action3_avance10, action3_tourne11, action3_tourne12, action3_avance13, action3_tourne14, action3_avance15, action3_pince16, x14, fin_gauche}

Etat_prog_gauche = stop;

// Inclusion des fichiers sources

#include "DSPIC30F_registers.h"
#include <math.h>
#include "stdlib.h"
#include "Functions.h"
#include "driver_moteur.c"



//********************************************************************************
//*  Main
//****************************************************************************************************
void main(void)
{

	__Init_dsPIC();
	
	delay_ms(1000);
	
	__Avance(50000,500);                     //Fonction pour faire avancer le robot 

	while(1)
	{
		

			/*
//==============================================================================================================================
//==============================================================================================================================	      
//										PROG COTE DROIT
//==============================================================================================================================
//==============================================================================================================================
			if(_Dig6==0)
			{
				_LED4 = 1;

				_LED1=1;
			switch(Etat_prog_gauche)//côte gauche (violet)
			{
				case stop :                                                          
                  if(_Dig1==0)
				{ 
                  	_Tim1On= 1;									// Activation du décompte du temps

					//delay_ms(20000);
					
                     flag_depl_ok=0;//???
                     __Afficheur_7segments(0);               // incrémentation de l'afficheur 7 segements
					 Score = 10;
				     Affichage_Score(0x70, Score);
                     Etat_prog_gauche = action1_avance1;         // permet de passer au mouvement suivant    
                 }
                 break; 

             	case action1_avance1 :

					_Tim3On= 1;									// permet le check d'adversaire

					driver_Servo_Angle(0xC4, 180, 1, 5); //Initialisation en position ferm�

                  __Avance(291500,1500);                     //Fonction pour faire avancer le robot     

                  __Afficheur_7segments(1);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action1_pince20;            //permet de passer au mouvement suivant   
                  break;


                  case action1_pince20 :
            	  __Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {

	              	_Tim3On=0;
	                flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

	          		__Afficheur_7segments(20);                  //incrémentation de l'afficheur 7 segements

	          		Score = Score + 10;
					Affichage_Score(0x70, Score);
	          		
	          		__Recule(3000,1500);

	          		Etat_prog_gauche = action1_pince21;            //permet de passer au mouvement suivant 
	          		
	          	  }
	          	  else
		          	{
		          		set_adc_channel(3);
		          		int value = read_adc();
		          		if(value > 515)
		          		{
		          			_LED3 =1;
		          			fprintf(ROBOTEQ,"!S 2 450_!S 1 350 \r");
		          		}	
		          		else if(value < 510)
		          		{
		          			_LED3 =0;
		          			fprintf(ROBOTEQ,"!S 2 1350_!S 1 1500 \r");
		          		}
		          		else
		          		{
		          			fprintf(ROBOTEQ,"!S 2 1500_!S 1 1500 \r");
		          		} 
		          	}   
	          	    
                  break;

                  //==========================================================================
                  // 								BALLE 1
                  //==========================================================================

                  case action1_pince21 :

                  	__Afficheur_7segments(21);                  //incrémentation de l'afficheur 7 segements

                  	Int32 waiting = 0;
                  	int tooLong = 0;
	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut

					delay_ms(500);

                  	driver_Servo_Angle(0xC4, 180, 1, 1); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 179, 3); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 10, 3); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut
		          		
						
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
          				__Recule(3000, 1500);
          				while(flag_depl_ok == 0)
          				{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

          				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);
	          			while(_Dig2==0)
						{
							//on attend
						}
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action1_pince22;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
                  
                	break;

                	//==========================================================================
                  // 								BALLE 2
                  //==========================================================================

                  case action1_pince22 :

                  	__Afficheur_7segments(22);                  //incrémentation de l'afficheur 7 segements
                  	waiting = 0;
                  	tooLong = 0;
	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut

					delay_ms(500);

                  	driver_Servo_Angle(0xC4, 180, 1, 1); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 179, 3); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 10, 3); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut
		          	
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
          				__Recule(3000, 1500);
          				while(flag_depl_ok == 0)
          				{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
          				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);
	          			while(_Dig2==0)
						{
							//on attend
						}
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action1_pince23;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
                  
                  break;

                  //==========================================================================
                  // 								BALLE 3
                  //==========================================================================

                  case action1_pince23 :

                  	__Afficheur_7segments(23);                  //incrémentation de l'afficheur 7 segements

                  	waiting = 0;
                  	tooLong = 0;
	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut

					delay_ms(500);

                  	driver_Servo_Angle(0xC4, 180, 1, 1); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 179, 3); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 10, 3); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
          				__Recule(3000, 1500);
          				while(flag_depl_ok == 0)
          				{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
          				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);
	          			while(_Dig2==0)
						{
							//on attend
						}
						
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action1_pince24;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
                  
                  break;


				  //==========================================================================
                  // 								BALLE 4
                  //==========================================================================

                  case action1_pince24 :

                  	__Afficheur_7segments(24);                  //incrémentation de l'afficheur 7 segements

                  	waiting = 0;
                  	tooLong = 0;
	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut

					delay_ms(500);

                  	driver_Servo_Angle(0xC4, 180, 1, 1); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 179, 3); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 10, 3); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
          				__Recule(3000, 1500);
          				while(flag_depl_ok == 0)
          				{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
          				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);
	          			while(_Dig2==0)
						{
							//on attend
						}
						
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action1_pince25;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
                  
                  break;

                  //==========================================================================
                  // 								BALLE 5
                  //==========================================================================

                  case action1_pince25 :

                  	__Afficheur_7segments(25);                  //incrémentation de l'afficheur 7 segements

                  	waiting = 0;
                  	tooLong = 0;
	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut

					delay_ms(500);

                  	driver_Servo_Angle(0xC4, 180, 1, 1); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 179, 3); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 10, 3); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
          				__Recule(3000, 1500);
          				while(flag_depl_ok == 0)
          				{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
          				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);
	          			while(_Dig2==0)
						{
							//on attend
						}
						
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action1_pince26;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
                  
                  break;

                  //==========================================================================
                  // 								BALLE 6
                  //==========================================================================

                  case action1_pince26 :

                  	__Afficheur_7segments(26);                  //incrémentation de l'afficheur 7 segements

                  	waiting = 0;
                  	tooLong = 0;
	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut

					delay_ms(500);

                  	driver_Servo_Angle(0xC4, 180, 1, 1); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 179, 3); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 10, 3); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
          				__Recule(3000, 1500);
          				while(flag_depl_ok == 0)
          				{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

          				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);
	          			while(_Dig2==0)
						{
							//on attend
						}
						
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action1_pince27;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
                  
                  break;

                  //==========================================================================
                  // 								BALLE 7
                  //==========================================================================

                  case action1_pince27 :

                  	__Afficheur_7segments(27);                  //incrémentation de l'afficheur 7 segements

                  	waiting = 0;
                  	tooLong = 0;
	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut

					delay_ms(500);

                  	driver_Servo_Angle(0xC4, 180, 1, 1); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 179, 3); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 10, 3); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
          				__Recule(3000, 1500);
          				while(flag_depl_ok == 0)
          				{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
          				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);
	          			while(_Dig2==0)
						{
							//on attend
						}
						
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action1_pince28;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
                  
                  break;

                  //==========================================================================
                  // 								BALLE 8
                  //==========================================================================

                  case action1_pince28 :

                  	__Afficheur_7segments(28);                  //incrémentation de l'afficheur 7 segements

                  	waiting = 0;
                  	tooLong = 0;
	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut

					delay_ms(500);

                  	driver_Servo_Angle(0xC4, 180, 1, 1); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 179, 3); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 10, 3); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
          				__Recule(3000, 1500);
          				while(flag_depl_ok == 0)
          				{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

          				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);
	          			while(_Dig2==0)
						{
							//on attend
						}
						
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
                  
                  break;


                  //==========================================================================
                  // 								BALLE (9)
                  //==========================================================================

                  case action1_pince29 :

                  	__Afficheur_7segments(29);                  //incrémentation de l'afficheur 7 segements

                  	waiting = 0;
                  	tooLong = 0;
	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut

					delay_ms(500);

                  	driver_Servo_Angle(0xC4, 180, 1, 1); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 179, 3); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 10, 3); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
          				__Recule(3000, 1500);
          				while(flag_depl_ok == 0)
          				{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
          				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

          				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);
	          			while(_Dig2==0)
						{
							//on attend
						}
						
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
                  
                  break;
                  
	          	case action2_extension3 :
					
					delay_ms(1000);
					
					if(_Dig2==1)
					{
						Etat_prog_gauche = action1_pince29;            //permet de passer au mouvement suivant   	
					}
					else
					{
						
                  		driver_Servo_Angle(0xC4, 180, 1, 5); //Initialisation en position ferm�
						_Tim3On=1;     

                  		__Afficheur_7segments(3);                  //incrémentation de l'afficheur 7 segements
                 		 Etat_prog_gauche = action2_avance4;            //permet de passer au mouvement suivant
     				}            		    
                  break;

                  case action2_avance4 :

					
		            __Avance(400000, 1500);                  //Fonction pour faire avancer le robot     


		            
	                flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
	          		__Afficheur_7segments(4);                  //incrémentation de l'afficheur 7 segements

	          		Etat_prog_gauche = action2_repli5;            //permet de passer au mouvement suivant                  

	          		break;

	          		case action2_repli5 :
            	__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {
		            driver_Servo_Angle(0xC4, 180, 160, 5); //Initialisation en position ferm�   

		            _Tim3On=0;
	                flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
	          		__Afficheur_7segments(5);                  //incrémentation de l'afficheur 7 segements

	          		Score = Score + 50;
					Affichage_Score(0x70, Score);

	          		Etat_prog_gauche = action3_recule6;            //permet de passer au mouvement suivant                  
	          	} 
	          	else
	          	{
	          		set_adc_channel(3);
	          		int value = read_adc();
	          		if(value > 450)
	          		{
	          			_LED3 =1;
	          			fprintf(ROBOTEQ,"!S 2 400_!S 1 250 \r");
	          		}	
	          		else if(value < 430)
	          		{
	          			_LED3 =0;
	          			fprintf(ROBOTEQ,"!S 2 1400_!S 1 1500 \r");	                  	
	                  	//delay_ms(1000);
	                  	//fprintf(ROBOTEQ,"!S 2 1500_!S 1 1500 \r");
	          		}
	          		else
	          		{
	          			fprintf(ROBOTEQ,"!S 2 1500_!S 1 1500 \r");
	          		} 
	          	}   
	          	break;

	          	case action3_recule6 :
				  _Tim3On= 1;									// permet le check d'adversaire
                  __Recule(300000,2000);                     //Fonction pour faire avancer le robot     

                  __Afficheur_7segments(6);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_tourne7;            //permet de passer au mouvement suivant   
                  break;

                  case action3_tourne7 :
				__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {
                  __Tourne_sur_place(-91,5000);                     //Fonction pour faire avancer le robot     

                  
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(7);                  //incrémentation de l'afficheur 7 segements
                  //Etat_prog_gauche = action3_avance8;            //permet de passer au mouvement suivant   
				  Etat_prog_gauche = 999;
              }
              else
              {
              	set_adc_channel(3);
              	int value = read_adc();
              	if(value > 450)
              	{
              		_LED3 =1;
              		fprintf(ROBOTEQ,"!S 2 600_!S 1 500 \r");
              	}
/*	

              	else if(value < 350)
              	{
              		_LED3 =0;
              		fprintf(ROBOTEQ,"!S 2 1300_!S 1 1500 \r");
              	}
*/


/*
              	else
              	{
              		fprintf(ROBOTEQ,"!S 2 1500_!S 1 1500 \r");
              	} 
              }    
              break;

              case action3_avance8 :
				__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {
					_Tim3On=1;
                  __Recule(1500000,5000);                     //Fonction pour faire avancer le robot
                  
                  
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(8);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_tourne9;            //permet de passer au mouvement suivant  
              }    
              break;

              case action3_tourne9 :

              set_adc_channel(5);
              int value = read_adc();
              if(value > 350)
              {
	              if(value > 440)                     //si le déplacement est fini
	              {

					fprintf(ROBOTEQ, "^mmod 1 0_^mmod 2 0 \r");		              
	              	fprintf(ROBOTEQ, "!G 1 0_!G 2 0 \r");
					delay_ms(2000);
	              	fprintf(ROBOTEQ, "^mmod 1 3_^mmod 2 3 \r");

					_Tim3On=1;

					__Avance(20000,2000);                     //Fonction pour faire avancer le robot
					
					while(flag_depl_ok == 0)
						{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
					flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
					
                  __Tourne_sur_place(-90,2000);                     //Fonction pour faire avancer le robot  
                  
                  
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(9);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_avance10;            //permet de passer au mouvement suivant 
              }     
              else
              {
              	fprintf(ROBOTEQ,"!S 2 200_!S 1 200 \r"); 	  
              }
          }           
          break;

          case action3_avance10 :
				__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {
                  __Recule(650000,2000);                     //Fonction pour faire avancer le robot    
                  
                  
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(10);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_tourne11;            //permet de passer au mouvement suivant   
              }   
              break;

              case action3_tourne11 :
              set_adc_channel(5);
              int value2 = read_adc();

	              if(value2 > 380)                     //si le déplacement est fini
	              {
	              	fprintf(ROBOTEQ, "^mmod 1 0_^mmod 2 0 \r");		              
	              	fprintf(ROBOTEQ, "!G 1 0_!G 2 0 \r");
	              	fprintf(ROBOTEQ, "^mmod 1 3_^mmod 2 3 \r");

	              	delay_ms(500);
                  __Tourne_sur_place(90,3000);                     //Fonction pour faire avancer le robot     
                  
                  
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(11);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_tourne12;            //permet de passer au mouvement suivant   
                  }
			   
              break;

              case action3_tourne12 :
				__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {
		             __Tourne_sur_place(15,3000);                     //Fonction pour faire avancer le robot
		             

		             
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(12);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_avance13;            //permet de passer au mouvement suivant   
              }   
              break;

              case action3_avance13 :
				__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {

		             __Avance(30000,2000);                     //Fonction pour faire avancer le robot 

		             
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(13);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_tourne14;            //permet de passer au mouvement suivant   
              }   
              break;

              case action3_tourne14 :
				__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {
		             __Tourne_sur_place(-15,3000);                     //Fonction pour faire avancer le robot

		             
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(14);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_avance15;            //permet de passer au mouvement suivant   
              }   
              break;


              case action3_avance15 :
				__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {
                  __Avance(178000,3000);                     //Fonction pour faire avancer le robot 
                  
                  
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(15);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_pince16;            //permet de passer au mouvement suivant   
              }   
              break;  
              
              case action3_pince16 :
            	__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {

					driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut

					driver_Servo_Angle(0xC4, 180, 1, 4); //Ouvre pince du bas

	              	_Tim3On=0;
	                flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
	          		__Afficheur_7segments(16);                  //incrémentation de l'afficheur 7 segements

					delay_ms(2000);
					
					if(_Dig2 == 1)
					{
						Score = Score + 10;
						Affichage_Score(0x70, Score);
					}

	          		Etat_prog_gauche = 999;            //permet de passer au mouvement suivant                  
	          	} 
	          	else
	          	{
	          		set_adc_channel(4);
	          		int value = read_adc();
	          		if(value > 500)
	          		{
	          			_LED3 =1;
	          			fprintf(ROBOTEQ,"!S 2 200_!S 1 380 \r");
	          		}	
	          		else if(value < 485)
	          		{
	          			_LED3 =0;
	          			fprintf(ROBOTEQ,"!S 2 1100_!S 1 1000 \r");
	          		}
	          		else
	          		{
	          			fprintf(ROBOTEQ,"!S 2 1500_!S 1 1500 \r");
	          		} 
	          	}   
	          	break;
	          }

	      }
//==============================================================================================================================
//==============================================================================================================================	      
//										PROG COTE DROIT
//==============================================================================================================================
//==============================================================================================================================	      
	      else
	      {
	      	_LED4 = 0;
	      	
	      	_LED1=1;
			switch(Etat_prog_gauche)//côte gauche (violet)
			{
				case stop :                                                               
                  if(_Dig1==0)
				{
                  	_Tim1On= 1;
					_Tim3On= 1;									// permet le check d'adversaire
                     flag_depl_ok=0;//???
                     __Afficheur_7segments(0);               // incrémentation de l'afficheur 7 segements

					//delay_ms(20000);

					 Score = 10;
					 Affichage_Score(0x70, Score);
                     Etat_prog_gauche = action1_avance1;         // permet de passer au mouvement suivant    
                 }
                 break; 

                 case action1_avance1 :

                  __Avance(291500,1500);                     //Fonction pour faire avancer le robot 

					driver_Servo_Angle(0xC4, 180, 1, 5); //Initialisation en position ferm�    

                  __Afficheur_7segments(1);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action1_pince20;            //permet de passer au mouvement suivant   
                  break;

	          	case action1_pince20 :
            	  __Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {

	              	_Tim3On=0;
	                flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

	          		__Afficheur_7segments(20);                  //incrémentation de l'afficheur 7 segements
	          		
	          		__Recule(3000,1500);

					Score = Score + 10;
					Affichage_Score(0x70, Score);

	          		Etat_prog_gauche = action1_pince21;            //permet de passer au mouvement suivant 
	          		
	          	  }
	          	  else
		          	{
		          		set_adc_channel(4);
		          		int value = read_adc();
		          		if(value > 510)
		          		{
		          			_LED3 =1;
		          			fprintf(ROBOTEQ,"!S 1 450_!S 2 350 \r");
		          		}	
		          		else if(value < 505)
		          		{
		          			_LED3 =0;
		          			fprintf(ROBOTEQ,"!S 1 1350_!S 2 1500 \r");
		          		}
		          		else
		          		{
		          			fprintf(ROBOTEQ,"!S 1 1500_!S 2 1500 \r");
		          		} 
		          	}   
	          	    
                  break;


		          //==========================================================================
	              // 								BALLE 1
	              //==========================================================================

	              case action1_pince21 :

	              	__Afficheur_7segments(21);                  //incrémentation de l'afficheur 7 segements

	              	Int32 waiting = 0;
	              	int tooLong = 0;
	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut

					delay_ms(500);

	              	driver_Servo_Angle(0xC4, 180, 50, 2); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 1, 4); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 150, 4); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
	      				__Recule(3000, 1500);
	      				while(flag_depl_ok == 0)
	      				{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

	      				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);
	          			
						while(_Dig2==0)
						{
							//on attend	
						}
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						delay_ms(600);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action1_pince22;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}

						driver_moteur(0xC0, 0);
	          		}
	              
	            	break;


		          //==========================================================================
	              // 								BALLE 2
	              //==========================================================================

	              case action1_pince22 :

	              	__Afficheur_7segments(22);                  //incrémentation de l'afficheur 7 segements
	              	
	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut

					delay_ms(500);

	              	driver_Servo_Angle(0xC4, 180, 50, 2); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 1, 4); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 150, 4); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
	      				__Recule(3000, 1500);
	      				while(flag_depl_ok == 0)
	      				{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

	      				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);

						while(_Dig2==0)
						{
							//on attend	
						}
	          			
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						delay_ms(600);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action1_pince23;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
	              
	            	break;


		          //==========================================================================
	              // 								BALLE 3
	              //==========================================================================

	              case action1_pince23 :

	              	__Afficheur_7segments(23);                  //incrémentation de l'afficheur 7 segements

	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut

					delay_ms(500);

	              	driver_Servo_Angle(0xC4, 180, 50, 2); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 1, 4); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 150, 4); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
	      				__Recule(3000, 1500);
	      				while(flag_depl_ok == 0)
	      				{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

	      				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);

						while(_Dig2==0)
						{
							//on attend	
						}
	          			
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						delay_ms(600);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action1_pince24;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
	              
	            	break;


		          //==========================================================================
	              // 								BALLE 4
	              //==========================================================================

	              case action1_pince24 :

	              	__Afficheur_7segments(24);                  //incrémentation de l'afficheur 7 segements

	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut

					delay_ms(500);

	              	driver_Servo_Angle(0xC4, 180, 50, 2); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 1, 4); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 150, 4); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
	      				__Recule(3000, 1500);
	      				while(flag_depl_ok == 0)
	      				{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

	      				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);

						while(_Dig2==0)
						{
							//on attend	
						}
	          			
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						delay_ms(600);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action1_pince25;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
	              
	            	break;


		          //==========================================================================
	              // 								BALLE 5
	              //==========================================================================

	              case action1_pince25 :

	              	__Afficheur_7segments(25);                  //incrémentation de l'afficheur 7 segements

	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut

					delay_ms(500);

	              	driver_Servo_Angle(0xC4, 180, 50, 2); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 1, 4); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 150, 4); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
	      				__Recule(3000, 1500);
	      				while(flag_depl_ok == 0)
	      				{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

	      				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);

						while(_Dig2==0)
						{
							//on attend	
						}
	          			
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						delay_ms(600);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action1_pince26;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
	              
	            	break;




		          //==========================================================================
	              // 								BALLE 6
	              //==========================================================================

	              case action1_pince26 :

	              	__Afficheur_7segments(26);                  //incrémentation de l'afficheur 7 segements

	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut

					delay_ms(500);

	              	driver_Servo_Angle(0xC4, 180, 50, 2); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 1, 4); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 150, 4); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
	      				__Recule(3000, 1500);
	      				while(flag_depl_ok == 0)
	      				{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

	      				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);

						while(_Dig2==0)
						{
							//on attend	
						}
	          			
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						delay_ms(600);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action1_pince27;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
	              
	            	break;


		          //==========================================================================
	              // 								BALLE 7
	              //==========================================================================

	              case action1_pince27 :

	              	__Afficheur_7segments(27);                  //incrémentation de l'afficheur 7 segements

	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut

					delay_ms(500);

	              	driver_Servo_Angle(0xC4, 180, 50, 2); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 1, 4); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 150, 4); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
	      				__Recule(3000, 1500);
	      				while(flag_depl_ok == 0)
	      				{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

	      				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);

						while(_Dig2==0)
						{
							//on attend	
						}
	          			
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						delay_ms(600);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action1_pince28;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
	              
	            	break;



		          //==========================================================================
	              // 								BALLE 8
	              //==========================================================================

	              case action1_pince28 :

	              	__Afficheur_7segments(28);                  //incrémentation de l'afficheur 7 segements

	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut

					delay_ms(500);

	              	driver_Servo_Angle(0xC4, 180, 50, 2); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 1, 4); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 150, 4); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
	      				__Recule(3000, 1500);
	      				while(flag_depl_ok == 0)
	      				{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

	      				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);

						while(_Dig2==0)
						{
							//on attend	
						}
	          			
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);
						
						delay_ms(600);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Score = Score + 5;
							Affichage_Score(0x70, Score);
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
	              
	            	break;


		          //==========================================================================
	              // 								BALLE 9
	              //==========================================================================

	              case action1_pince29 :

	              	__Afficheur_7segments(29);                  //incrémentation de l'afficheur 7 segements

	                //Ouvertures et fermetures des pinces pour qu'une balle passe
	                //============================================================
	                driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut

					delay_ms(500);

	              	driver_Servo_Angle(0xC4, 180, 50, 2); //Ferme pince du haut
						
					delay_ms(300);

					driver_Servo_Angle(0xC4, 180, 1, 4); //Ouvre pince du bas
					
					delay_ms(500);
					
					driver_Servo_Angle(0xC4, 180, 150, 4); //Ferme pince du bas

					//Envoi de la balle
	                //============================================================

	                //On attend que la balle soit en position
					while(_Dig2==0 && waiting < 3000)
					{
						delay_ms(1);
	          			waiting++;

	          			//Si on attend plus que 3s on "secoue" le robot
						if (waiting >= 3000)
						{
							      				
	          				nbreEssai++;

	          			}
	          			

	          		}
	          		if (nbreEssai > 2)
	          		{
	          			Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
	          		}
	          		else if (waiting >= 3000)
	          		{
		          		driver_Servo_Angle(0xC4, 180, 140, 2); //Ouvre pince du haut
		          		
	          			__Avance(3000, 1500);
						while(flag_depl_ok == 0)
						{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
	      				__Recule(3000, 1500);
	      				while(flag_depl_ok == 0)
	      				{
	      					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	      				}
	      				_Tim3On=0;
	                 	flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

	      				waiting = 0;
	          		}
	          		else
	          		{
		          		delay_ms(300);

						while(_Dig2==0)
						{
							//on attend	
						}
	          			
						int	etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,85,DRV_ARRET_COURANT,3000);

						delay_ms(600);

						while (_Dig2==1 && tooLong == 0)
						{
							delay_ms(1);
							waiting++;

		          			//Si on attend plus que 1s on "seccoue" le robot
							if (waiting > 3000)
							{
								tooLong = 1;
								
							}
							
						}

						if (tooLong == 1)
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant   
						}
						else
						{
							Etat_prog_gauche = action2_extension3;            //permet de passer au mouvement suivant
							nbreEssai  = 0;   
						}
						driver_moteur(0xC0, 0);
	          		}
	              
	            	break;



	          	case action2_extension3 :

                  delay_ms(1000);
					
					if(_Dig2==1)
					{
						Etat_prog_gauche = action1_pince29;            //permet de passer au mouvement suivant   	
					}
					else
					{
						
                  		driver_Servo_Angle(0xC4, 180, 1, 5); //Initialisation en position ferm�
						_Tim3On=1;   

                  		__Afficheur_7segments(3);                  //incrémentation de l'afficheur 7 segements
                 		 Etat_prog_gauche = action2_avance4;            //permet de passer au mouvement suivant
     				}            		    
                  break;

                  case action2_avance4 :

					

					
		            __Avance(400000, 1500);                  //Fonction pour faire avancer le robot     


		            
	                flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
	          		__Afficheur_7segments(4);                  //incrémentation de l'afficheur 7 segements

	          		Etat_prog_gauche = action2_repli5;            //permet de passer au mouvement suivant                  

	          		break;

	          		case action2_repli5 :
            	__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {
		            driver_Servo_Angle(0xC4, 180, 160, 5); //Initialisation en position ferm�   

		            
	                flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
	          		__Afficheur_7segments(5);                  //incrémentation de l'afficheur 7 segements

	          		Score = Score + 50;
					Affichage_Score(0x70, Score);

	          		Etat_prog_gauche = action3_recule6;            //permet de passer au mouvement suivant                  
	          	} 
	          	else
	          	{
	          		set_adc_channel(4);
	          		int value = read_adc();
	          		if(value > 490)
	          		{
	          			_LED3 =1;
	          			fprintf(ROBOTEQ,"!S 1 400_!S 2 250 \r");
	          		}	
	          		else if(value < 480)
	          		{
	          			_LED3 =0;
	          			fprintf(ROBOTEQ,"!S 1 1400_!S 2 1500 \r");	                  	
	                  	//delay_ms(1000);
	                  	//fprintf(ROBOTEQ,"!S 2 1500_!S 1 1500 \r");
	          		}
	          		else
	          		{
	          			fprintf(ROBOTEQ,"!S 1 1500_!S 2 1500 \r");
	          		} 
	          	}   
	          	break;

	          	case action3_recule6 :

                  __Recule(300000,2000);                     //Fonction pour faire avancer le robot     

                  __Afficheur_7segments(6);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_tourne7;            //permet de passer au mouvement suivant   
                  break;

                  case action3_tourne7 :
				__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {
                  __Tourne_sur_place(91,5000);                     //Fonction pour faire avancer le robot     

                  
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(7);                  //incrémentation de l'afficheur 7 segements
                  //Etat_prog_gauche = action3_avance8;            //permet de passer au mouvement suivant
					Etat_prog_gauche = 999;				  
              }
              else
              {
              	set_adc_channel(4);
              	int value = read_adc();
              	if(value > 450)
              	{
              		_LED3 =1;
              		fprintf(ROBOTEQ,"!S 1 600_!S 2 500 \r");
              	}	
              	else if(value < 350)
              	{
              		_LED3 =0;
              		fprintf(ROBOTEQ,"!S 1 1300_!S 2 1500 \r");	                  	
	                  	//delay_ms(1000);
	                  	//fprintf(ROBOTEQ,"!S 2 1500_!S 1 1500 \r");
              	}
              	else
              	{
              		fprintf(ROBOTEQ,"!S 1 1500_!S 2 1500 \r");
              	} 
              }    
              break;

              case action3_avance8 :
				__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {
					
                  __Recule(1500000,5000);                     //Fonction pour faire avancer le robot
                  
                  
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(8);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_tourne9;            //permet de passer au mouvement suivant  
              }    
              break;

              case action3_tourne9 :

              set_adc_channel(5);
              int value = read_adc();
              if(value > 350)
              {
	              if(value > 440)                     //si le déplacement est fini
	              {

	              	fprintf(ROBOTEQ, "^mmod 1 0_^mmod 2 0 \r");		              
	              	fprintf(ROBOTEQ, "!G 1 0_!G 2 0 \r");
					delay_ms(2000);
	              	fprintf(ROBOTEQ, "^mmod 1 3_^mmod 2 3 \r");
					
					_Tim3On=1;

					__Avance(20000,2000);                     //Fonction pour faire avancer le robot
					
					while(flag_depl_ok == 0)
						{
          					__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
          				}
					flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser

                  __Tourne_sur_place(89,2000);                     //Fonction pour faire avancer le robot  
                  
                  
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(9);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_avance10;            //permet de passer au mouvement suivant 
              }     
              else
              {
              	fprintf(ROBOTEQ,"!S 2 200_!S 1 200 \r"); 	  
              }
          }           
          break;

          case action3_avance10 :
				__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {
                  __Recule(650000,2000);                     //Fonction pour faire avancer le robot    
                  
                  
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(10);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_tourne11;            //permet de passer au mouvement suivant   
              }   
              break;

              case action3_tourne11 :
              set_adc_channel(5);
              int value2 = read_adc();

	              if(value2 > 380)                     //si le déplacement est fini
	              {
	              	fprintf(ROBOTEQ, "^mmod 1 0_^mmod 2 0 \r");		              
	              	fprintf(ROBOTEQ, "!G 1 0_!G 2 0 \r");
	              	fprintf(ROBOTEQ, "^mmod 1 3_^mmod 2 3 \r");

	              	delay_ms(500);
                  __Tourne_sur_place(-90,3000);                     //Fonction pour faire avancer le robot     
                  
                  
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(11);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_tourne12;            //permet de passer au mouvement suivant   
              		}
				   
              break;

              case action3_tourne12 :
				__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {
		             __Tourne_sur_place(-15,3000);                     //Fonction pour faire avancer le robot
		             

		             
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(12);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_avance13;            //permet de passer au mouvement suivant   
              }   
              break;

              case action3_avance13 :
				__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {

		             __Avance(30000,2000);                     //Fonction pour faire avancer le robot 

		             
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(13);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_tourne14;            //permet de passer au mouvement suivant   
              }   
              break;

              case action3_tourne14 :
				__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {
		             __Tourne_sur_place(15,3000);                     //Fonction pour faire avancer le robot

		             
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(14);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_avance15;            //permet de passer au mouvement suivant   
              }   
              break;


              case action3_avance15 :
				__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {
                  __Avance(180000,3000);                     //Fonction pour faire avancer le robot 
                  
                  
	              flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
                  __Afficheur_7segments(15);                  //incrémentation de l'afficheur 7 segements
                  Etat_prog_gauche = action3_pince16;            //permet de passer au mouvement suivant   
              }   
              break;  
              
              case action3_pince16 :
            	__Check_commande_atteint();                  //fonction qui check si le déplacement à été effectué
	              if(flag_depl_ok == 1)                     //si le déplacement est fini
	              {

					

					driver_Servo_Angle(0xC4, 180, 90, 1); //Ouvre pince du haut
					driver_Servo_Angle(0xC4, 180, 179, 3); //Ouvre pince du bas

	              	_Tim3On=0;
	                flag_depl_ok = 0;                     //remise à  0 de la variable pour pouvoir la réutiliser
	          		__Afficheur_7segments(16);                  //incrémentation de l'afficheur 7 segements

					delay_ms(2000);
					
					if(_Dig2 == 1)
					{
						Score = Score + 10;
						Affichage_Score(0x70, Score);
					}

	          		Etat_prog_gauche = 999;            //permet de passer au mouvement suivant                  
	          	} 
	          	else
	          	{
	          		set_adc_channel(3);
	          		int value = read_adc();
	          		if(value > 500)
	          		{
	          			_LED3 =1;
	          			fprintf(ROBOTEQ,"!S 1 200_!S 2 380 \r");
	          		}	
	          		else if(value < 485)
	          		{
	          			_LED3 =0;
	          			fprintf(ROBOTEQ,"!S 1 1100_!S 2 1000 \r");	                  	
						//delay_ms(1000);
						//fprintf(ROBOTEQ,"!S 2 1500_!S 1 1500 \r");
	          		}
	          		else
	          		{
	          			fprintf(ROBOTEQ,"!S 1 1500_!S 2 1500 \r");
	          		} 
	          	}   
	          	break;
	          } 
	      }    
	      	
		if(flagTimeOUt == 1)//fin du temps
		{		
			__TimeOut();	//fct qui arrête le robot
		}

		if(flagBaliseCheck == 1)//on check la balise
		{
			__Detected(); 		// check si un adversaire est vers nous	
		}
	  */
	}
	

}
//----------------------------------------------------------------------------------------------------
//  Nom: 	    RDA_isr
//	Auteur :	AMANAX
//	Date:	    27.03.2015
//  Statut :    OK
//----------------------------------------------------------------------------------------------------
//  Description : Interruption pour la réception RS232. 
#INT_RDA
void RDA_isr(void)
{
	_LED3=!_LED3;
	// Pour la lecture du caractère reçu
	char myChar;
	// Réception
	myChar = fgetc(ROBOTEQ);
	// Ajout au buffer et incrémentation de la longeur du buffer
	RoboteQ_receiveBuffer[RoboteQ_receiveLenght] = myChar;
	RoboteQ_receiveLenght++;

	// Si on trouve la fin de la commande
	if(myChar == '\r')
	{
		// On dit qu'on peut lire le buffer de réception
		RoboteQ_receiveToProceed = RoboteQ_receiveLenght;
		RoboteQ_receiveLenght=0;
	}

}

/*
////////////////////////////////////////
//// Timer temps de jeu////
////////////////////////////////////////
#INT_TIMER1
void TIMER1_isr(void)
{
	if(Flag_Arret_Moteur)			//MODIFIE
	{								//MODIFIE
		Timer_Arret_Moteur++;		//MODIFIE
		if(Timer_Arret_Moteur>25)	//MODIFIE
			Timer_Arret_Moteur=25;	//MODIFIE
	}								//MODIFIE
	else							//MODIFIE
	{								//MODIFIE
		Timer_Arret_Moteur=0;		//MODIFIE
	}								//MODIFIE
	//12 secondes pour poser poisson sans se recaler environ
	//3 eme passage on ne se recal pas si pas 12 secondes alors o n fait allez retour
	_LED2=!_LED2;
	// Variable contenant le temps restant (90*5 (<=200[m]) = 450)
	set_timer1(0);
	// Incr�mente le temps 
	Time++;
	// Si temps terminee
	if(Time>=490)//apr�s 88secondes
	{
		// Dit que temps dépasser
		flagTimeOut = 1;
		//__Afficheur_7segments(99); //MODIFIE		
	}	
	if(Time>=510)
	{
		flag_servo =1;		
		disable_interrupts(INTR_GLOBAL);
		//__Afficheur_7segments(00); //MODIFIE
	}

}
////////////////////////////////////////////////////////////////
//// Timer qui sert à la capture de la balise ////
///////////////////////////////////////////////////////////////
#INT_TIMER3
void TIMER3_isr(void)
{
	_LED4=!_LED4;
	flagBaliseCheck=1;
}
*/