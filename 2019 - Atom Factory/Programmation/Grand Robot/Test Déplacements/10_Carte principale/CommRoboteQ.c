/*====================================================================================================
===																									==
===											EMVs - EUROBOT	  										==
===											--------------											==
======================================================================================================
===	 Auteur				: Amand Axel (reprise)				  										==
===  Date				: 05.03.2015																==
===  Nom du programme 	: InterfaceRoboteQuC.mcp													==
===  Version 			: V1.0																		==
======================================================================================================
=== Description :																					==
=== Fonctions d'initialisation du dsPIC30F6014A.				    								==
====================================================================================================*/

#ifndef ___CommRoboteQ
#define ___CommRoboteQ

///===============================================================================================================
/// 	Variables globales

// Gestion de l'envoi

// Gestion de la réception
char RoboteQ_receiveBuffer[256]={};			// Buffer des données reçues
unsigned int8 RoboteQ_receiveToProceed = 0;	// Position maximale pour la réception
unsigned int8 RoboteQ_receiveLenght = 0;	// Longeur totale de la donnée
int1 Flag_Arret_Moteur=0; //MODIFIE
unsigned int8 Timer_Arret_Moteur=0; //MODIFIE
signed int32 Vit_mot1 = 0; //MODIFEE
signed int32 Vit_mot2 = 0;//MODIFIE

// Gestion de l'ajout au buffer de réception
char RoboteQ_values[2][10];

/******************************************************************************************************/
/* Envoi
/******************************************************************************************************/
void __TimeOut(void)
{
	// Force l'arrêt de RoboteQ
	fprintf(ROBOTEQ,"!EX\r");
	// Empêche les interruptions
	disable_interrupts(INT_TIMER3);
	disable_interrupts(INT_RDA);


		Etat_prog_gauche = fin_gauche;


	// Quitte l'interruption
	return;
}
//----------------------------------------------------------------------------------------------------
//  Nom: 	    Check_commande_atteint
//	Auteur :	BORREM
//	Date:	    18.2.15
//  Statut :    -
//----------------------------------------------------------------------------------------------------
//  Description : Check si la commande donné aux moteurs a été finie
void __Check_commande_atteint(void)
{
	int1 comm_atteinte_m1,comm_atteinte_m2 = 0;
	fprintf(ROBOTEQ,"?DR\r");
//il renvoie DR=x:x
	delay_ms(100);
//on vérifie que le premier caractère n'indique pas une répétiotion de commande
	
	if(RoboteQ_receiveBuffer[0] != '!' && RoboteQ_receiveBuffer[0] != '?' && RoboteQ_receiveBuffer[0] != '~' && RoboteQ_receiveBuffer[0] != '^' && RoboteQ_receiveBuffer[0] != '#')
	{
		comm_atteinte_m1 = RoboteQ_receiveBuffer[3]; // affectation du premier x dans la variable
		comm_atteinte_m2 = RoboteQ_receiveBuffer[5]; // affectation du deuxième x dans la variable
	}
	
	if(comm_atteinte_m1 == 1 && comm_atteinte_m2== 1) // si commande des deux moteurs dini 
	{
		_Tim3On= 1; //permet le check d'adversaire
		flag_depl_ok =1 ; // on peut passer au déplacement suivant
	}
	__CheckVitMoteur();						//MODIFIE
	if(abs(Vit_mot1)<=20 || abs(Vit_mot2)<=20)	//MODIFIE
	{										//MODIFIE
		Flag_Arret_Moteur=1;				//MODIFIE
		if(Timer_Arret_Moteur==25)			//MODIFIE
		{									//MODIFIE
			__Afficheur_7segments(70);		//MODIFIE
			fprintf(ROBOTEQ,"!EX\r");		//MODIFIE
		}									//MODIFIE
	}										//MODIFIE
	else									//MODIFIE
	{										//MODIFIE
		Flag_Arret_Moteur=0;				//MODIFIE
		Timer_Arret_Moteur=0;				//MODIFIE
	}										//MODIFIE
}

//----------------------------------------------------------------------------------------------------
//  Nom: 	    Roboteq_test
//	Auteur :	BORR
//	Date:	 	11.05.16
//  Statut : 	non-fonctionnel
//  Futur :     n.a.
//----------------------------------------------------------------------------------------------------
//  Description : test le roboteq si il y a des erreus
//	ParamÃ¨tre(s): 
//  RÃ©sultat :    / 
//  Constante(s): 
//----------------------------------------------------------------------------------------------------
void Roboteq_test(void)
{
	//erreur peut venir de plusieurs chose en même temps!! le code ne gère pas ça!!
	static int Roboteq_erreur;
	int i = 3;
	static unsigned int erreur1,erreur2,erreur3,erreur4,erreur5,erreur6,erreur7,erreur8;
	fprintf(ROBOTEQ,"?FF\r");
	delay_ms(100);
	if(RoboteQ_receiveBuffer[0] != '!' && RoboteQ_receiveBuffer[0] != '?' && RoboteQ_receiveBuffer[0] != '~' && RoboteQ_receiveBuffer[0] != '^' && RoboteQ_receiveBuffer[0] != '#')
	{
		while(RoboteQ_receiveBuffer[i] != 0x0D)//for(i=2;i<(Length+3);i++) // On commence du [2] pour sauter le 'C='. Le +3 est pour le C,= et : (C=xxx:xxx).
		{ 
			// Stockage de la valeur du premier encodeur
			RoboteQ_values[0][i-3] = RoboteQ_receiveBuffer[i];
			i++;
		}
		
			
	}
	Roboteq_erreur = atoi32(RoboteQ_values[0]);

	erreur8 = (Roboteq_erreur & 0b10000000) >> 7;
	erreur7 = (Roboteq_erreur & 0b01000000) >> 6;
	erreur6 = (Roboteq_erreur & 0b00100000) >> 5;
	erreur5 = (Roboteq_erreur & 0b00010000) >> 4;
	erreur4 = (Roboteq_erreur & 0b00001000) >> 3;
	erreur3 = (Roboteq_erreur & 0b00000100) >> 2;
	erreur2 = (Roboteq_erreur & 0b00000010) >> 1;
	erreur1 = (Roboteq_erreur & 0b00000001);
	
	if(erreur1 == 1)
	{
		__Afficheur_7segments(60);//overheat
		__TimeOut();	
	}	
	if(erreur2 == 1)
	{
		__Afficheur_7segments(61);//overvoltage	
		__TimeOut();
	}
	if(erreur3 == 1)
	{
		__Afficheur_7segments(62);//undervoltage	
		__TimeOut();
	}
	if(erreur4 == 1)
	{
		__Afficheur_7segments(63);//short circuit
		__TimeOut();	
	}
	if(erreur5 == 1)
	{
		__Afficheur_7segments(64);//emergency stop
	}
	if(erreur6 == 1)
	{
		__Afficheur_7segments(65);//sepex excitation fault
		__TimeOut();
	}
	if(erreur7 == 1)
	{
		__Afficheur_7segments(66);// mosfet failure
		__TimeOut();	
	}
	if(erreur8 == 1)
	{
		__Afficheur_7segments(67);//startup configuration fault
		__TimeOut();	
	}
}
     
//----------------------------------------------------------------------------------------------------
//  Nom: 	    __CheckVitMoteur	//MODIFIE
//	Auteur :	FAVLEN
//	Date:	    22.05.17
//  Statut :    Ok
//----------------------------------------------------------------------------------------------------
//  Description : Check si les moteurs sont arrêtés
//	Paramètre(s): /
//  Résultat :    /
//----------------------------------------------------------------------------------------------------
void __CheckVitMoteur(void)
{
	// Vide les tableaux des valeurs
	strcpy(RoboteQ_values[0],"          ");
	strcpy(RoboteQ_values[1],"          ");
	// Demande la valeur des encodeurs
	fprintf(ROBOTEQ,"?S\r");

	delay_ms(10);
	// Pour la capture la valeur de l'encodeur
	unsigned int8 i=2,j=0;
	//On vérifie si le premier caractère reçu n'indique pas la répétition d'une commande
	if(RoboteQ_receiveBuffer[0] != '!' && RoboteQ_receiveBuffer[0] != '?' && RoboteQ_receiveBuffer[0] != '~' && RoboteQ_receiveBuffer[0] != '^' && RoboteQ_receiveBuffer[0] != '#')
	{
		//On coupe le message
		// Exemple : A=10:210 deviendra ->
		// 	A	10	210
		while(RoboteQ_receiveBuffer[i] != 0x0D)//for(i=2;i<(Length+3);i++) // On commence du [2] pour sauter le 'C='. Le +3 est pour le C,= et : (C=xxx:xxx).
		{ 
			if(RoboteQ_receiveBuffer[i] == ':') j=i+1; // Si on lit la valeur de l'encodeur 2, on passe à la deuxième ligne du tableau
			else
			{
				// Si lecture de la première ligne
				if(j==0)
				{
					// Stockage de la valeur du premier encodeur
					RoboteQ_values[0][i-2] = RoboteQ_receiveBuffer[i];
				}
				else
				{
					// Stockage de la valeur du deuxième encodeur
					RoboteQ_values[1][i-j] = RoboteQ_receiveBuffer[i];
				}	
			}
				i++;
			}	
	}
	Vit_mot1=atoi32(RoboteQ_values[0]);
	Vit_mot2=atoi32(RoboteQ_values[1]);
	// Quitte la fonction
	return;
}
#endif