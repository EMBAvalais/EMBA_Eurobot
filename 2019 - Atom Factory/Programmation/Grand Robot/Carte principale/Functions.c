
/*====================================================================================================
===																									==
===											EMVs - EUROBOT	  										==
===											--------------											==
======================================================================================================
===	 Auteur				: Amand Axel
						: Borgeat Rémy     					  										==
===  Date				: 30.04.2015    															==
===  Nom du programme 	: Function.c														==
===  Version 			: V1.0																		==
======================================================================================================
=== Description :																					==
=== Contient des fonctions pour le robot																==
====================================================================================================*/

#ifndef ___Functions_c
#define ___Functions_c

//TEMP////////////////////////////////////////////////////////////////////////////////////////////////////////////
#DEFINE vitesse_roboteq 300/////////////////////////////////////////////////////////////////////////////////////////////////
#DEFINE vitesse_cour 200/////////////////////////////////////////////////////////////////////////////////////////////////
#DEFINE vitesse_crem 200/////////////////////////////////////////////////////////////////////////////////////////////////
#DEFINE impulse -10672/////////////////////////////////////////////////////////////////////////////////////////////////
#DEFINE distance 52000////////////////////////////////////////////////////////////////////////////////////////////////
#DEFINE START 30
//unsigned int8 points = 0;//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------------------------------
//  Nom: 	    Afficheur 7 segments
//	Auteur :	BORR
//	Date:	    6.1.16
//  Statut :    Fonctionnel
//  Futur :     n.a.
//----------------------------------------------------------------------------------------------------
//  Description : Gère 2 afficheur 7 segments
//	Paramètre(s): int8 nombre -> nombre<=99
//  Résultat :    / 
//----------------------------------------------------------------------------------------------------
void __Afficheur_7segments(int8 nombre,int1 ToBlank=0)
{
	_EN_Uni = _En_Diz = 1;
	
	if(ToBlank)
	{
		PORTB |= 0b1111<<12;
		// charge sur les latchs
		_EN_Uni = _En_Diz = 0;
		_EN_Uni = _En_Diz = 1;
	}
	else
	{		
		static unsigned int16 dizaine = 0; // variable qui va récupérer le chiffre des dizaine 
		static unsigned int16 unite = 0; // variable qui va récupérer le chiffre des unité
	
		dizaine = nombre/10; //récupération du nombre des dizaine
		unite   = nombre%10; //récupération du nombre des unités
	
		dizaine = dizaine * 4096; //décalage vers la droite car sortie sur RB12 à RB15
		unite = unite * 4096; //décalage vers la droite car sortie sur RB12 à RB15
		
		_En_Diz = 0; // possibilité d'afficher sur l'afficheur des dizaine	
		PORTB = dizaine; //affichage de la valeur sur l'afficheur
		_En_Diz = 1; // Afficheur dizaine allumé, mais on ne peux plus changer la valeur
	
		_EN_Uni = 0; // possibilité d'afficher sur afficheur unité 
		PORTB = unite; // affichage des unité sur l'afficheur des unité 
		_EN_Uni = 1; // Afficheur unité allumé, mais on ne peux plus changer la valeur
	}
	
	// Quitte la fonction
	return;
}

/*
	Fct qui reset une partie de l'eeprom en
	remettant les valeurs à 0xffff
	
	Auteur : Borgeat Rémy
	Date   : 9.2.2017
*/
void __resetEEPROM(void)
{
	unsigned int16 adresse = 0;
	for(adresse = 0; adresse <= 820; adresse +=  2)
	{
		write_eeprom(adresse, 0xFFFF);//on écrase l'eeprom
	}
}
void __reset_roboteq(void)
{
	fputc('%',ROBOTEQ);
	fprintf(ROBOTEQ,"RESET 321654987 \r");
}
/*=======================================================================================
	Fct qui va recuperer les pid du roboteq et les mettre dans un tableau
=========================================================================================	
	Auteur : Borgeat Rémy
	Date : 16.2.2017
=========================================================================================	
	! on doit faire passer 6x dans la fct.
	On doit mettre une boucle exeterieur, car avec dans la fct,
	on resete la dedans, et donc on ne peut pas recuperer des caractere
	
	Trame envoyer : Tab{2,0,:,10,...\r)
					Tab{kp1 : ki1 : ...)
	Les : separe les donnes, le \r annonce la fin du tableau
	
	!on peut pas chainer les commande, car il ecrase a chaque fois la reponse de l'ordre precdent
==========================================================================================*/
void __GetRoboteqPID(unsigned int8 valeur)
{
	static int8 i = 3; // car on recoit KP=110 -> on veut que la valeur --> on saute les 3 premiers caractere
	static int8 y = 0;
	
	switch(valeur) // on demande au roboteq es valeur
	{
		case 0:
			fprintf(ROBOTEQ,"~KP 1 \r");			
			delay_ms(10);			
			break;
		case 1:
			fprintf(ROBOTEQ,"~KI 1 \r");
			delay_ms(10);
			break;
		case 2:
			fprintf(ROBOTEQ,"~KD 1 \r");
			delay_ms(10);
			break;
		case 3:
			fprintf(ROBOTEQ,"~KP 2 \r");
			delay_ms(10);
			break;
		case 4:
			fprintf(ROBOTEQ,"~KI 2 \r");
			delay_ms(10);
			break;
		case 5:
			fprintf(ROBOTEQ,"~KD 2 \r");
			delay_ms(10);
			break;	
		case 6:
			fprintf(ROBOTEQ,"~MAC 1 \r");
			delay_ms(10);
			i = 4;
			break;	
		case 7:
			fprintf(ROBOTEQ,"~MDEC 1 \r");
			delay_ms(10);
			i = 5;
			break;	
		case 8:
			fprintf(ROBOTEQ,"~MAC 2 \r");
			delay_ms(10);
			i = 4;
			break;	
		case 9:
			fprintf(ROBOTEQ,"~MDEC 2 \r");
			delay_ms(10);
			i = 5;
			break;	
	}	

	if(RoboteQ_receiveBuffer[0] == 'K' || RoboteQ_receiveBuffer[0] == 'M')
	{
		while(RoboteQ_receiveBuffer[i] != 0x0D) // On commence du [2] pour sauter le 'C='. Le +3 est pour le C,= et : (C=xxx:xxx).
		{ 
			TabSentRS232[y] = RoboteQ_receiveBuffer[i];				
			i++;
			y++;
		}
		if(valeur<9)
		{	
			TabSentRS232[y] = ':';//seperation des valeur	
			y++;
		}
		else
		{
			TabSentRS232[y] = '\r'; // fin de transmssion
			y = 0 ;	
		}
		i = 3;
	}	

}
/*
	Fct qui va changer les paramètre PID du roboteq.
	Les parametre ont ete recu du pc et ont les save en
	dans l'eeprom du roboteq
	
	Auteur : Borgeat Rémy
	Date   : 16.2.2017
*/
void __SetRoboteqPID(unsigned int8 P1,I1,D1,P2,I2,D2,ac1,dc1,ac2,dc2)
{
	//envoi des paramètres PID au ROBOTEQ
	fprintf(ROBOTEQ,"^KP 1 %u_^KI 1 %u_^KD 1 %u_^KP 2 %u_^KI 2 %u_^KD 2 %u \r",P1,I1,D1,P2,I2,D2);
	fprintf(ROBOTEQ,"^MAC 1 %u_^MDEC 1 %u_^MAC 2 %u_^MDEC 2 %u \r",ac1,dc1,ac2,dc2);// envoie au Roboteq

	write_eeprom(300,P1);
	write_eeprom(302,I1);
	write_eeprom(304,D1);
	write_eeprom(306,P2);
	write_eeprom(308,I2);
	write_eeprom(310,D2);
	
	//Sauvegarde en eeprom
	fputc('%',ROBOTEQ);//pas le choix de faire un putc, car le % est un caractère réservé pour le pritnf
	fprintf(ROBOTEQ,"EESAV \r");//envoie du reste de la commande

}

// Récupère tous les objectifs et les stock en eeprom
void __ReadObjectifs(void)
{
	// Lit les objectifs stockés en EEPROM
	// Les éléments d'objectifs sont stockés chaque deux dans l'EEPROM
	unsigned int16 i = 0;
	unsigned int16 y = 0;
	static int16 offset;
	unsigned int16 NumObj = 0;
	unsigned int16 Obj = 0;

	while(y==0)
	{
		Obj = read_eeprom(offset);//on check si il reste des objectifs
		NumObj = read_eeprom(offset+2);
		if(Obj!=0xFFFF)//Si il en reste
		{
			for( i = 0 ; i < 24; i += 2)
			{			
				TabObjectifs[Obj][NumObj][(i/2)] = read_eeprom(i+4+offset);//remplir le tableau avec les objectifs
			}	
			offset += 28;// offset de +24,afin de lire les objectifs suivant	
			NbreObjectifs=Obj;	
		}
		else//si il n'y a plus d'objectis
		{
			y=1;//on sort de la boucle
		}
	}

}
// Récupère tous les objectifs et les stock en eeprom
void __ReadZones_Interdites(void)
{
	// Lit les objectifs stockés en EEPROM
	// Les éléments d'objectifs sont stockés chaque deux dans l'EEPROM
	unsigned int16 i = 0;
	unsigned int16 y = 0;
	static int16 offset = 200;
	unsigned int16 NumZone = 0;

	while(y==0)
	{
		NumZone = read_eeprom(offset);//on check si il reste des objectifs
		if(NumZone!=0xFFFF)//Si il en reste
		{
			for( i = 0 ; i < 16; i += 2)
			{
				TabZones[NumZone][(i/2)] = read_eeprom(i+2+offset);//remplir le tableau avec les objectifs
			}	
			offset += 18;// offset de +24,afin de lire les objectifs suivant	
			NbreZone_check++;
		}
		else//si il n'y a plus d'objectis
		{
			y=1;//on sort de la boucle
		}
			
	}
//	NbreZone = read_eeprom(512);	
}

// Actions à effectuer
void __Action_Writting(unsigned int8 ActionToDo)
{
//	unsigned int8 StateDriver = 0;
	switch(ActionToDo)
	{
		// Ne fait rien
		case 0 :
			Action_send=1;
			break;		
		case 1 :
			Ramassage(0);
			break;	
		case 2 : 
			Ramassage(1);
			break;
		case 3 : 
			Ramassage(2);
			break;
		case 4 : 
			Ramassage(3);
			break;
		case 5 : 
			Empilage();
			break;
		case 7 :
			Panneau_Domotique();
			break;
		case 8 : 
			GoToZero_Cremaillere();
			break;
		case 9 : 
			reinitialisation();
			break;
		default :
			__Affichage_erreur(5);
			break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//============================================================================================================================
//	Fonction pour afficher le code de la carte afficheur
//============================================================================================================================

unsigned int8 Affichage_Score(unsigned int8 adresse_driver, unsigned int8 Total)
{
	i2c_start();
	if(i2c_write(adresse_driver) == 0)			//ADRESSE
	{
		i2c_write(Total);
	}
	else
	{ 
		i2c_stop();
		return 0;
	}
	i2c_stop();	
	return 1;
}

//============================================================================================================================
//	Fonction pour enclencher ou déclencher les pompes
//============================================================================================================================

unsigned int8 driver_Pompes(unsigned int8 adresse_driver, unsigned int8 pompe_A, unsigned int8 pompe_B, unsigned int8 pompe_C, unsigned int8 pompe_D, unsigned int8 pompe_E)
{
	delay_ms(2000);
	unsigned int8 ordre = 0;
	ordre = pompe_A*16 + pompe_B*8 + pompe_C*4 + pompe_D*2 + pompe_E;

	i2c_start();
	if(i2c_write(adresse_driver) == 0)			//ADRESSE
	{
		i2c_write(ordre);
	}
	else
	{ 
		i2c_stop();
		return 0;
	}
	i2c_stop();	
	delay_ms(2000);
	return 1;
}

//============================================================================================================================
//	Fonction pour lire l'état des pompes
//============================================================================================================================

unsigned int8 read_driver_pompes(int8 adresse_driver)
{
	int8 driver_etat;
	int8 ack=0;

	i2c_start();
	ack = i2c_write(adresse_driver+1);
	if(ack == 0)
	{
		driver_etat=i2c_read(0);
	}
	else driver_etat = 0b1000000;

	i2c_stop();
	return driver_etat;
}

//============================================================================================================================
//	Fonction pour allumer le panneau domotique
//============================================================================================================================

int1 Panneau_Domotique(void)
{
	static int8 action;
	static int8 etat;
	static int8 etat_cremaillere;

	switch(action)
	{
		case 0 :

				if(Etat!=1) 
				{
					Etat = go_driver_moteur(0xC0,1,DRV_MODE_VITESSE ,5000,DRV_ARRET_POSITION_RELATIVE,25500);
					return(0);
				}
				else 
				{
					driver_Pompes(0xA0,0,0,0,0,0);	
					Etat = 0 ;
					action = 1;
					return(1);
				}			

		break;

		case 1 :

			etat_cremaillere = __Check_action_end(0xC0);

			if(etat_cremaillere==1)
			{
				fprintf(ROBOTEQ,"!S 1 %07d_!S 2 %07d \r",50,50);
				fprintf(ROBOTEQ,"!PR 1 %07d_!PR 2 %07d \r",-25000,-25000);

				action = 2;
			}

		break;

		case 2 :
		/*
			delay_ms(5000);
			//__Check_commande_atteint(); 
            if(1)//flag_depl_ok == 1)                     //si le dÃ©placement est fini
            {	
				fprintf(ROBOTEQ,"!S 1 %07d_!S 2 %07d \r",50,50);
				fprintf(ROBOTEQ,"!PR 1 %07d_!PR 2 %07d \r",25000,25000);

				action = 3;
				points = points + 25;
            }
          */
          
          if(_Capdist==0)
          {
	          fprintf(ROBOTEQ,"!MS 1_!MS 2\r");                   
	          fprintf(ROBOTEQ,"^mmod 1 0_^mmod 2 0\r");
	          fprintf(ROBOTEQ,"^mmod 1 3_^mmod 2 3\r"); 
	          
	          action = 3;   
	      }  

        break;

		case 3 :
			
			//delay_ms(5000);
			//__Check_commande_atteint();
            if(1)//flag_depl_ok == 1)                     //si le dÃ©placement est fini
            {
            	Action_send = 1;
            	Check=1;
			   	action = 0;
				etat = 0;
				etat_cremaillere = 0;  
			}

		break;       				
	}
}

//============================================================================================================================
//	Fonction qui permet de ramasser les cubes (doit fournir un paramètre pour savoir de quelle côté de la croix on arrive)
//============================================================================================================================

int1 Ramassage(unsigned int8 cote)
{
	static int8 action;
	static int8 Etat;
	static int8 etat_cremaillere;
	static int8 etat_couronne;
	static signed int32 impulse_couronne;
	static int1 sens;

	static int8 etat_pompes;
	static int8 i;

	switch(action)
	{
		case 0 :

			switch(cote)
			{
				case 0 :

					impulse_couronne = 0;
					sens = 1;
					action = 2;

				break;

				case 1 :

					impulse_couronne = 16192;
					sens = 0;
					action = 1;

				break;

				case 2 :

					impulse_couronne = -32384;
					sens = 1;
					action = 1;

				break;

				case 3 :

					impulse_couronne = -16192;
					sens = 0;
					action = 1;

				break;
			}

		break;

		case 1 :

				if(Etat!=1) 
				{
					Etat = go_driver_moteur(0xC2,0,DRV_MODE_VITESSE ,5000,DRV_ARRET_POSITION_RELATIVE,impulse_couronne);
					return(0);
				}
				else 
				{	
					Etat = 0 ;
					action = 2;
					return(1);
				}			

		break;

		case 2 :
		
			etat_couronne = __Check_action_end(0xC2);

			if(etat_couronne==1)
			{	
				//if(impulse_couronne!=0)
				//{
				//	etat_couronne = __Check_action_end(0xC2);
				//}
				//else
				//{
				//	etat_couronne=1;
				//}		
	
				//if(etat_couronne==1)
				//{		
					if(Etat!=1) 
					{				
						Etat = go_driver_moteur(0xC0,0,DRV_MODE_VITESSE ,5000,DRV_ARRET_POSITION_RELATIVE,-22000);//go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL,100,DRV_ARRET_COURANT,500);
						return(0);			
					}
					else 
					{	
						Etat = 0 ;
						action = 3;
						return(1);
					}
				//}
			}

		break;

		case 3 :

			etat_cremaillere = __Check_action_end(0xC0);

			if(etat_cremaillere==1)
			{
				if(Etat!=1) 
				{				
					Etat = driver_Pompes(0xA0, 1, 1, 1, 1, 1);
					return(0);			
				}
				else 
				{	
					delay_ms(1000);
					Etat = 0;
					action = 4;
					return(1);
				}
			}

		break;

		case 4 :

			if(Etat!=1) 
			{				
				Etat = go_driver_moteur(0xC0,0,DRV_MODE_VITESSE ,5000,DRV_ARRET_POSITION_RELATIVE,22000);
				return(0);			
			}
			else 
			{	
				Etat = 0 ;
				action = 5;
				return(1);
			}

		break;

		break;

		case 5 :

			etat_cremaillere = __Check_action_end(0xC0);

			if(etat_cremaillere==1)
			{
				etat_pompes = read_driver_pompes(0xA0);
				if(etat_pompes==0b00011111 || i==1)
				{
					action = 6;
					i = 0;
				}
				else
				{
					if(etat_pompes==0)
					{
						action = 7;
						Obj_end=1;
					}
					else
					{
						action = 2;
						i++;
					}
				}
			}	

		break;

		case START :

			etat_cremaillere = __Check_action_end(0xC0);

			if(etat_cremaillere==1)
			{
				if(Etat!=1) 
				{				
					Etat = go_driver_moteur(0xC0,0,DRV_MODE_VITESSE ,5000,DRV_ARRET_POSITION_RELATIVE,20000);
					return(0);			
				}
				else 
				{	
					Etat = 0 ;
					action = 6;
					return(1);
				}
			}
			
		case 6 :

				if(Etat!=1) 
				{
					Etat = go_driver_moteur(0xC2,0,DRV_MODE_VITESSE ,5000,DRV_ARRET_POSITION_RELATIVE,-impulse_couronne);
					return(0);
				}
				else 
				{	
					Etat = 0 ;
					action = 7;
					return(1);
				}		

		case 7 :

			etat_couronne = __Check_action_end(0xC2);

			if(etat_couronne==1)
			{
				Action_send = 1;
				action = 0;
				Etat = 0;
				etat_cremaillere = 0;
				etat_pompes = 0;
				i = 0;	
				Check=1;
			}		

		break;

	}
}

//============================================================================================================================
//	Fonction pour empiler la tour de 5 étages. La solution (sensé être transmis par le raspberry à la carte principale)
//	est enregistré dans une variable.La fonction permet de monter les tours pour les différentes solution et pour les 2 côtés.
//	Avant de poser les cubes, on vérifie grâce à une autre fonction si on a un cube. Le comptage des points est aussi intégré
//	pour toutes les possibilités.
//============================================================================================================================

int1 Empilage(void)
{
	static int8 action;
	static int8 Etat;
	static int8 etat_cremaillere;
	static int8 etat_couronne;
	static int8 etat_pompes;
	static int1 etat_pompe_A;
	static int1 etat_pompe_B;
	static int1 etat_pompe_C;
	static int1 etat_pompe_D;
	static int1 etat_pompe_E;
	//int8 solution = 0;

	static int1 combinaison;
	static int8 etage;	
	static int8 i;	
	//static int8 points;// Surement à mettre en global
	
	//solution = 1;//(PORTA&0b11110000)/16;

	if(Team==1)
	{
		switch(solution)
		{
			case 0b0001 :
	
				switch(action)
				{
					case 0 :
	
						etat_pompes = read_driver_pompes(0xA0);
						etat_pompe_A = (etat_pompes&0b00010000)/16;
						etat_pompe_B = (etat_pompes&0b00001000)/8;
						etat_pompe_C = (etat_pompes&0b00000100)/4;
						etat_pompe_D = (etat_pompes&0b00000010)/2;
						etat_pompe_E = (etat_pompes&0b00000001);
	
	
						fprintf(ROBOTEQ,"!S 1 %07d_!S 2 %07d \r",vitesse_roboteq,vitesse_roboteq);
						fprintf(ROBOTEQ,"!PR 1 %07d_!PR 2 %07d \r",impulse,impulse);
	
						action = START;
	
					break;
	
					case START :
	
						delay_ms(1000);
						//__Check_commande_atteint();
	                  	if(1)//flag_depl_ok == 1)                     //si le dÃ©placement est fini
	                  	{  
							if(Etat!=1) 
							{
								Etat = go_driver_moteur(0xC0,1,DRV_MODE_VITESSE ,vitesse_crem,DRV_ARRET_POSITION_RELATIVE,-20000);
								return(0);
							}
							else 
							{	
								Etat = 0 ;
								action = 1;
								return(1);
							}
	                  	}   
	
					break;
	
					case 1 :
	
						etat_cremaillere = __Check_action_end(0xC0);
	
						if(etat_cremaillere==1)
						{  
	                  		if(bit_test(etat_pompes, 2) == 1)
	                  		{ 
								if(Etat!=1) 
								{	
									etat_pompe_C = 0;			
									Etat = driver_Pompes(0xA0, etat_pompe_A, etat_pompe_B, etat_pompe_C, etat_pompe_D, etat_pompe_E);
									return(0);			
								}
								else 
								{	
									etage++;
									points = points + etage;
									Etat = 0 ;
									action = 3;
									return(1);
								}
							}
							else
							{
								action = 4;
							}
	                  	}   
	
					break;
	
					case 2 : 
	
						etat_pompes = read_driver_pompes(0xA0);
						if(bit_test(etat_pompes, 2) == 0)
						{
							action = 3;
						}
	
					break;
	
					case 3 :
	  
						if(Etat!=1) 
						{
							Etat = go_driver_moteur(0xC0,1,DRV_MODE_VITESSE ,vitesse_crem,DRV_ARRET_POSITION_RELATIVE,(distance));
							return(0);
						}
						else 
						{	
							Etat = 0 ;
							action = 4;
							return(1);
						}	
	
					break;
	
					case 4 :
	
						etat_cremaillere = __Check_action_end(0xC0);
	
						if(etat_cremaillere==1)
						{
							fprintf(ROBOTEQ,"!S 1 %07d_!S 2 %07d \r",vitesse_roboteq,vitesse_roboteq);
							fprintf(ROBOTEQ,"!PR 1 %07d_!PR 2 %07d \r",-impulse,-impulse);
	
							action = 5;	
						}
	
					break;
	
					case 5 :
	
						delay_ms(1000);
						//__Check_commande_atteint();
	                  	if(1)//flag_depl_ok == 1)                     //si le dÃ©placement est fini
	                  	{   
	                  		if(bit_test(etat_pompes, 4) == 1)
	                  		{ 
								if(Etat!=1) 
								{	
									etat_pompe_A = 0;			
									Etat = driver_Pompes(0xA0, etat_pompe_A, etat_pompe_B, etat_pompe_C, etat_pompe_D, etat_pompe_E);
									return(0);			
								}
								else 
								{
									etage++;
									points = points + etage;	
									Etat = 0 ;
									action = 7;
									return(1);
								}
							}
							else
							{
								combinaison = 1;
								action = 8;
							}
	                  	}
	
					break;
	
					case 6 : 
	
						etat_pompes = read_driver_pompes(0xA0);
						if(bit_test(etat_pompes,4) == 0)
						{
							action = 7;
						}
	
					break;
	
					case 7 :
	
						if(Etat!=1) 
						{
							Etat = go_driver_moteur(0xC0,1,DRV_MODE_VITESSE ,vitesse_crem,DRV_ARRET_POSITION_RELATIVE,distance);
							return(0);
						}
						else 
						{	
							Etat = 0 ;
							action = 8;
							return(1);
						}
	
					break;
	
					case 8 :
	
						etat_cremaillere = __Check_action_end(0xC0);
	
						if(etat_cremaillere==1)
						{
							if(Etat!=1) 
							{
								Etat = go_driver_moteur(0xC2,1,DRV_MODE_VITESSE ,vitesse_cour,DRV_ARRET_POSITION_RELATIVE,16192);
								return(0);
							}
							else 
							{	
								Etat = 0 ;
								action = 9;
								return(1);
							}
						}
	
					break;
	
					case 9 :
	
						etat_couronne = __Check_action_end(0xC2);
	
						if(etat_couronne==1)
	                  	{   
	                  		if(bit_test(etat_pompes, 3) == 1)
	                  		{
								if(Etat!=1) 
								{	
									etat_pompe_B = 0;			
									Etat = driver_Pompes(0xA0, etat_pompe_A, etat_pompe_B, etat_pompe_C, etat_pompe_D, etat_pompe_E);
									return(0);			
								}
								else 
								{	
									etage++;
									points = points + etage;
									Etat = 0 ;
									action = 11;
									return(1);
								}
							}
							else
							{
								combinaison = 1;
								action = 12;
							}
	                  	}
	
					break;
	
					case 10 : 
	
						etat_pompes = read_driver_pompes(0xA0);
						if(bit_test(etat_pompes,3) == 0)
						{
							action = 11;
						}
	
					break;
	
					case 11 :
	
						if(Etat!=1) 
						{
							Etat = go_driver_moteur(0xC0,1,DRV_MODE_VITESSE ,vitesse_crem,DRV_ARRET_POSITION_RELATIVE,distance);
							return(0);
						}
						else 
						{	
							Etat = 0 ;
							action = 12;
							return(1);
						}
	
					break;
	
					case 12 :
	
						etat_cremaillere = __Check_action_end(0xC0);
	
						if(etat_cremaillere==1)
	                  	{ 
							if(Etat!=1) 
							{
								Etat = go_driver_moteur(0xC2,1,DRV_MODE_VITESSE ,vitesse_cour,DRV_ARRET_POSITION_RELATIVE,16192);
								return(0);
							}
							else 
							{	
								Etat = 0 ;
								action = 13;
								return(1);
							}
						}
	
					break;
	
					case 13 :
	
						etat_couronne = __Check_action_end(0xC2);
	
						if(etat_couronne==1)
	                  	{ 
	                  		if(bit_test(etat_pompes, 0) == 1)
	                  		{
								if(Etat!=1) 
								{	
									etat_pompe_E = 0;			
									Etat = driver_Pompes(0xA0, etat_pompe_A, etat_pompe_B, etat_pompe_C, etat_pompe_D, etat_pompe_E);
									return(0);			
								}
								else 
								{
									etage++;
									points = points + etage;	
									if(combinaison == 0)
									{
										points = points + 30;
									}
									Etat = 0 ;
									action = 15;
									return(1);
								}
							}
							else
							{
								combinaison = 1;
								action = 16;
							}
						}
	
					break;
	
					case 14 : 
	
						etat_pompes = read_driver_pompes(0xA0);
						if(bit_test(etat_pompes,0) == 0)
						{
							action = 15;
						}
	
					break;
	
					case 15 :
	
						if(Etat!=1) 
						{
							Etat = go_driver_moteur(0xC0,1,DRV_MODE_VITESSE ,vitesse_crem,DRV_ARRET_POSITION_RELATIVE,distance);
							return(0);
						}
						else 
						{	
							Etat = 0 ;
							action = 16;
							return(1);
						}
	
					break;
	
					case 16 :
	
						etat_cremaillere = __Check_action_end(0xC0);
	
						if(etat_cremaillere==1)
						{
							if(Etat!=1) 
							{
								Etat = go_driver_moteur(0xC2,1,DRV_MODE_VITESSE ,vitesse_cour,DRV_ARRET_POSITION_RELATIVE,-48576);
								return(0);
							}
							else 
							{	
								Etat = 0 ;
								action = 17;
								return(1);
							}
						}
	
					break;
	
					case 17 :
	
						etat_couronne = __Check_action_end(0xC2);
	
						if(etat_couronne==1)
	                  	{
	                  		if(bit_test(etat_pompes, 1) == 1)
	                  		{
								if(Etat!=1) 
								{	
									etat_pompe_D = 0;			
									Etat = driver_Pompes(0xA0, etat_pompe_A, etat_pompe_B, etat_pompe_C, etat_pompe_D, etat_pompe_E);
									return(0);			
								}
								else 
								{	
									etage++;
									points = points + etage;
									Etat = 0 ;
									action = 19;
									return(1);
								}
							}
							else
							{
								action = 19;
							}
						}
	
					break;
	
					case 18 : 
	
						etat_pompes = read_driver_pompes(0xA0);
						if(bit_test(etat_pompes,1) == 0)
						{
							action = 19;
						}
	
					break;
	
					case 19 :
	
						Etat = driver_Pompes(0xA0,0,0,0,0,0);
						Check=1;
						Action_send = 1;
						action = 0;
						etat = 0;
						Sens_rot_Couronne = 0;
						combinaison = 0;
						etage = 0;	
						i = 0;
	
					break;
	
				}
	
			break;
	
			
	
		}		
	}	
}

//============================================================================================================================
//	Fonction qui va réinitialiser la crémaillère en position 0, puis la remonter à 30000 impulse
//============================================================================================================================
	
	int1 GoToZero_Cremaillere(void)
	{
		static int8 action;
		static int8 Etat;
		static int8 etat_cremaillere;
	
		switch(action)
		{
			case 0 :
	
				if(Etat!=1) 
				{
					Etat = go_driver_moteur(0xC0,0,DRV_MODE_NON_REGUL ,100,DRV_ARRET_COURANT,750);
					return(0);
				}
				else 
				{	
					Etat = 0 ;
					action = 1;
					delay_ms(100);
					return(0);
				}
	
			break;
	
			case 1 :
	
				etat_cremaillere = __Check_action_end(0xC0);
		
				if(etat_cremaillere==1)
				{
					if(Etat!=1) 
					{				
						Etat = go_driver_moteur(0xC0,1,DRV_MODE_VITESSE ,5000,DRV_ARRET_POSITION_RELATIVE,30000);
						return(0);			
					}
					else 
					{	
						Etat = 0 ;
						action = 0;
						return(1);
					}
				}	
			break;
		}
	}	
	
//============================================================================================================================
//	Fonction qui va réinitialiser la couronne et la crémaillère
//============================================================================================================================

int1 reinitialisation(void)
{
	static int1 Zero_Couronne;
	static int1 Zero_Cremaillere;

	if(Zero_Cremaillere != 1)
	{
		Zero_Cremaillere = GoToZero_Cremaillere();
	}
	
	//if(Zero_Couronne != 1)			// Ne fonctionner pas toujours (surement pas à cause du code) donc enlever
	//{
	//	Zero_Couronne = __GoToZero();	
	//}
	Zero_Couronne = 1;
	if(Zero_Cremaillere == 1 && Zero_Couronne == 1)
	{
		Action_send = 1;
		Check=1;
		Zero_Couronne = 0;
		Zero_Cremaillere = 0;
	}
}

//=================================================================================================================================================================================================
// Fonction 	: GoToZero																														
//=================================================================================================================================================================================================
//	Développé par:		: Favre Lenny
//						: Borgeat Rémy     												
//  Date				: 24.02.2017															
//  Date de modif.		: 17.3.2017															
//-------------------------------------------------------------------------------------------------------------------------------------------------------------																
// Description 	:	Fonction qui place le barillet à son point zéro
// paramètres 	:	Aucun paramètre
// retourne 	:	retourne le status du driver											
//					0-> non utilisé																
//					1-> OK : ordre transmis et terminé													
//					2-> not ready  (le slave ne répond pas)															
//					3-> Le barillet n'a pas trouvé le point zéro															
//===================================================================================================================================================================================================
int1 __GoToZero(void)
{
	static signed int32 ActualPosition = 0;
	static signed int32 Position;
	static int8 Etat = 0;
	static int1 read = 0;
	
	if(Sens_rot_Couronne==0)
	{
		Position = 48576;
	}
	else
	{
		Position = -48576;
	}		

	if(_ZeroPoint == 0 && Etat == 0) return(1);
	else
	{	
		if(Etat!=1)
		{
			if(!read)
			{
				//ActualPosition = read_pos_moteur(0xC2); // on prend la pos du moteur
				delay_ms(20);
				read = 1;
			}		
			Etat = go_driver_moteur(0xC2,0,DRV_MODE_VITESSE,100,DRV_ARRET_POSITION_RELATIVE,Position);//ABSOLUE,(64768 + ActualPosition));	
			delay_ms(20);
			return(0);
		}
		else
		{
			if(!_ZeroPoint)
			{
				Etat = 0;
				read = 0;
				driver_moteur(0xC2,0); //arrêt du driver
				if(obj_Action==8)Action_send = 0;
				else Action_send=1;
				return(1);
			}
			else return(0);
		}
	}
}
//=================================================================================================================================================================================================
// Fonction 	: __Check_action_end																														
//=================================================================================================================================================================================================
//	Développé par:		: Borgeat Remy  
//						:   												
//  Date				: 28.02.2017															
//  Date de modif.		: 															
//-------------------------------------------------------------------------------------------------------------------------------------------------------------																
// Description 	:	Fonction qui check l'etat du driver moteur
// 				: 	En cas de surcharge ou driver pas connecte --> on affiche l'erreur
//				: 	En cas de surchauffe --> on attend 1s pour renvoyer l'ordre
// paramètres 	:	Addresse du driver
// retourne 	:	1 -> ordre fini, 0 -> ordre en cours ou erreur	
//===================================================================================================================================================================================================
int1 __Check_action_end(unsigned int8 driver_address)
{
	static unsigned int32 Time_ms = 0;
	static signed int16 impulses_toDo = 0;
	signed int16 ActualPosition = 0;
	static unsigned int8 passage_erreur = 0;
	static unsigned int8 Etat_d = 1;
	static unsigned int1 ok = 0;
	static unsigned int8 Etat = 0;
	static unsigned int1 read = 0;
	static unsigned int8 Etat_driver = 0;
	Etat_d = read_driver_moteur(driver_address);
	delay_ms(20);

	switch(Etat_d)
	{
		case 0: 
			Erreur_max_surchauffe = 0;
			Time_ms = 0;
			return(1); //driver arreter --> ordre fini 
			break;	
			
		case 1:	//en cours
			
			if(driver_address==0xC0)__Afficheur_7segments(10);
			else if(driver_address==0xC2) __Afficheur_7segments(11);
			else if(driver_address==0xC4)__Afficheur_7segments(12);

			return(0);//driver en mouvement, ou en erreur --> on renvoie 0	
			break;
					
		case 2: // surcharge on tire plus de courant que le maximum configure
	
			if(driver_address==0xC0)
			{
				while(!ok)
				{
					switch(Etat)
					{
						case 0:
							if(!read)
							{
								driver_moteur(0xC0,0);
								ActualPosition = read_pos_moteur(0xC0); // on prend la pos du moteur
								read = 1;
							}
							if(Etat_driver!=1) // on fait deplacer le moteur ds un sens(si quelquechose le coince)
							{
								Etat_driver = go_driver_moteur(0xC0,1,DRV_MODE_VITESSE,soll_vit_mov,DRV_ARRET_POSITION_ABSOLUE,(ActualPosition-250));
							}
							else
							{
								Etat_driver = 0;
								Etat++; // passe au depl suivant
								read = 0;
							}
							break;
						case 1://retourne a la postion 
							Etat_d = read_driver_moteur(0xC0);
							if(Etat_d == 0)
							{
								if(!read)
								{
									ActualPosition = ActualPosition - 250;
									impulses_toDo = EndPosition - ActualPosition ;
									read = 1;  
								}
								if(Etat_driver!=1)
								{
									Etat_driver = go_driver_moteur(0xC0,0,DRV_MODE_VITESSE,soll_vit_mov,DRV_ARRET_POSITION_ABSOLUE,(ActualPosition + impulses_toDo));
									
								}
								else
								{
									ok = 1; 
								}
							}								
							break;
					}
					}
			}
			else if(driver_address==0xC2) __Affichage_erreur(11); // surcharge ejection
			else if(driver_address==0xC4) __Affichage_erreur(12); // surcharge cremaillere		
			ok = 0;
			return(0);
			break;
			
		case 3: // surchauffe pont-h
			if(driver_address==0xC0)__Afficheur_7segments(16);
			else if(driver_address==0xC2) __Afficheur_7segments(17);
			else if(driver_address==0xC4) __Afficheur_7segments(18);
			
			if(Time_ms==0)Time_ms = GameTimeMS;
			else if(GameTimeMS - Time_ms >= TIME_SURCHAUFFE_MS)//on attend 1s
			{
				Time_ms = 0;
				
				if(driver_address == 0xC0)//moteur barillet
				{
					ActualPosition = read_pos_moteur(0xC0); //on reprend l'ordre
					if((ActualPosition-EndPosition)!= 0)
					{
						impulses_toDo = EndPosition - ActualPosition ; 
						go_driver_moteur(0xC0,0,DRV_MODE_VITESSE,soll_vit_mov,DRV_ARRET_POSITION_ABSOLUE,impulses_toDo);
					}
				}
				else if(driver_address == 0xC2)//moteur qui couche les modules
				{
					if((GameTimeMS-Time_ejection)<Time_ejection_toDo)
					{
						Time_ejection_toDo = Time_ejection_toDo - (GameTimeMS-Time_ejection); //calcul du temps qu'il reste a faire
						//renvoi de la suite de l'ordre
						if(Etat_ejection == 1) go_driver_moteur(0xC2,1,DRV_MODE_NON_REGUL,100,DRV_ARRET_TEMPS, Time_ejection_toDo);						
						else go_driver_moteur(0xC2,1,DRV_MODE_NON_REGUL,25,DRV_ARRET_TEMPS,Time_ejection_toDo);
					}	
				}
				else if(driver_address == 0xC4)
				{
					if(bras_out)go_driver_moteur(0xC4,0,DRV_MODE_NON_REGUL ,100,DRV_ARRET_COURANT,200); // rentre le bras
					else go_driver_moteur(0xC4,1,DRV_MODE_NON_REGUL ,100,DRV_ARRET_COURANT,200);	   // sort le bras		
				}
				passage_erreur++;
				if(passage_erreur > Erreur_max_surchauffe)// si on a 10 erreurs a la suite de surchauffe
				{
					if(driver_address == 0xC0)    __Affichage_erreur(13); //surcahuffe driver barrilet
					else if(driver_address==0xC2) __Affichage_erreur(14); //surchauffe driver ejection
					else if(driver_address==0xC4) __Affichage_erreur(15); //surchauffe driver cremaillere	
				}
				
			} 	
			return(0);						
			break;
		case 4://processing
			if(driver_address==0xC0)__Afficheur_7segments(13);
			else if(driver_address==0xC2) __Afficheur_7segments(14);
			else if(driver_address==0xC4)__Afficheur_7segments(15);
			return(0); 
			break; 
		case 5://slave ne repond pas
			if(driver_address == 0xC0)    __Affichage_erreur(16); //driver barillet ne repond pas
			else if(driver_address==0xC2) __Affichage_erreur(17); //driver ejection ne repond pas
			else if(driver_address==0xC4) __Affichage_erreur(18); //driver cremaillere ne repond pas			
			else ;//__Affichage_erreur();	
			return(0);			
			break;
	}
}


#endif
