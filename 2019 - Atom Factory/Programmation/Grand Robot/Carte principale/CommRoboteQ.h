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
char RoboteQ_dataBuffer[256]={};			// Buffer des donn�es envoy�es

// Gestion de la r�ception
char RoboteQ_receiveBuffer[256]={};			// Buffer des donn�es re�ues
unsigned int8 RoboteQ_receiveToProceed = 0;	// Position maximale pour la r�ception
unsigned int8 RoboteQ_receiveLenght = 0;	// Longeur totale de la donn�e

// Gestion de l'ajout au buffer de r�ception
char RoboteQ_values[2][10];

/******************************************************************************************************/
/* Envoi
/******************************************************************************************************/

//----------------------------------------------------------------------------------------------------
//  Nom: 	    __EnvoiComm
//	Auteur :	AMANAX
//	Date:	    27.03.2015
//  Statut :    Ok
//----------------------------------------------------------------------------------------------------
//  Description : Envoi des commandes au  module RoboteQ
//	Param�tre(s): Tableau de commande
//  R�sultat :    / 
//----------------------------------------------------------------------------------------------------
void __EnvoiComm(char* ptrBuffy)
{
	// Envoi commande
//	__Afficheur_7segments(1);
	unsigned int8 ToEndSend=0;
	while(*(ptrBuffy+ToEndSend)!='\r') // Attend de voir la fin de tableau
	{
		fputc(*(ptrBuffy+ToEndSend),ROBOTEQ); // Envoi la commande
		ToEndSend++;
	}	
	fputc('\r',ROBOTEQ); // Envoi le caract�re de fin de commande
//	__Afficheur_7segments(2);
	// Quitte la fonction
	return;	
}	

void __TimeOut(void)
{
	// Force l'arr�t de RoboteQ
	strcpy(RoboteQ_databuffer,"!MG");
	__EnvoiComm(RoboteQ_dataBuffer);
	// Emp�che les interruptions
	disable_interrupts(INTR_GLOBAL);
	// Ne fait plus rien
	while(1){}
	
	// Quitte l'interruption
	return;
}
		
/******************************************************************************************************/
/* R�ception
/******************************************************************************************************/

//----------------------------------------------------------------------------------------------------
//  Nom: 	    __CheckEnc
//	Auteur :	AMANAX
//	Date:	    17.05.2015
//  Statut :    Ok
//----------------------------------------------------------------------------------------------------
//  Description : M�J la valeur des encodeurs
//	Param�tre(s): /
//  R�sultat :    / (mais modifie la valeur des encodeurs lus)
//----------------------------------------------------------------------------------------------------
/*void __CheckEnc(void)
{
	// Vide les tableaux des valeurs
	strcpy(RoboteQ_values[0],"          ");
	strcpy(RoboteQ_values[1],"          ");
	// Demande la valeur des encodeurs
	strcpy(RoboteQ_dataBuffer,"?C 1 \r");
	__EnvoiComm(RoboteQ_dataBuffer);

	delay_ms(10);
	// Pour la capture la valeur de l'encodeur
	unsigned int8 i=2,j=0;
	//On v�rifie si le premier caract�re re�u n'indique pas la r�p�tition d'une commande
	if(RoboteQ_receiveBuffer[0] != '!' && RoboteQ_receiveBuffer[0] != '?' && RoboteQ_receiveBuffer[0] != '~' && RoboteQ_receiveBuffer[0] != '^' && RoboteQ_receiveBuffer[0] != '#')
	{
		//On coupe le message
		// Exemple : A=10:210 deviendra ->
		// 	A	10	210
		while(RoboteQ_receiveBuffer[i]!=13) // On commence du [2] pour sauter le 'C='. Le +3 est pour le C,= et : (C=xxx:xxx).
		{ 
			if(RoboteQ_receiveBuffer[i] == ':' || RoboteQ_receiveBuffer[i] == 0x45) j=i+1; // Si on lit la valeur de l'encodeur 2, on passe � la deuxi�me ligne du tableau
			else
			{
				// Si lecture de la premi�re ligne
				if(j==0)
				{
					// Stockage de la valeur du premier encodeur
					RoboteQ_values[0][i-2] = RoboteQ_receiveBuffer[i];
				}
				else
				{
					// Stockage de la valeur du deuxi�me encodeur
					RoboteQ_values[1][i-j] = RoboteQ_receiveBuffer[i];
				}	
			}
			i++;
		}	
	}
	Val_enco1=atoi32(RoboteQ_values[0]);
	Val_enco2=atoi32(RoboteQ_values[1]);
	// Quitte la fonction
	return;
}
*/


void __Detected(void)
{	
	unsigned int8 ValueBal;
	ValueBal=Check_balise();
		// Lecture de la valeur de la d�tection
		if(ValueBal>=BalSensitivity)
		{
			strcpy(RoboteQ_dataBuffer,"!EX"); // Arr�t d'urgence
			__EnvoiComm(RoboteQ_dataBuffer);
			// Attend �loignement adversaire
			while(ValueBal>= BalSensitivity)
			{
				if(flagBaliseCheck==1)
				{
					ValueBal=Check_Balise();
					flagBaliseCheck=0;
				}	
			}
			strcpy(RoboteQ_dataBuffer,"!MG"); // Enl�ve arr�t d'urgence
			__EnvoiComm(RoboteQ_dataBuffer);						
		}
		flagBaliseCheck=0;
		// Quitte la fonction
		return;	
}

//----------------------------------------------------------------------------------------------------
//  Nom: 	    RDA_isr
//	Auteur :	AMANAX
//	Date:	    27.03.2015
//  Statut :    OK
//----------------------------------------------------------------------------------------------------
//  Description : Interruption pour la r�ception RS232. 
#INT_RDA
void RDA_isr(void)
{
//	__Afficheur_7segments(3);
	disable_interrupts(INT_TIMER4);
	// Pour la lecture du caract�re re�u
	char myChar;
	// R�ception
	myChar = fgetc(ROBOTEQ);
	// Ajout au buffer et incr�mentation de la longeur du buffer
	RoboteQ_receiveBuffer[RoboteQ_receiveLenght] = myChar;
	RoboteQ_receiveLenght++;
	
	// Si on trouve la fin de la commande
	if(myChar == '\r')
	{
		// On dit qu'on peut lire le buffer de r�ception
		RoboteQ_receiveToProceed = RoboteQ_receiveLenght;
		RoboteQ_receiveLenght=0;
//		__Afficheur_7segments(4);
	}
	enable_interrupts(INT_TIMER4);
	// Quitte l'interruption
	return;
}

#endif

// il faut que je compare  la valeur d�sir�e et la valeur r�el de l'encodeur
//pas de boucle!!!
// si valeur enco = valeur voulu --> on passe au deuxi�me mouvement
// m�me proc�d�
// deuxi�me mouvement fini--> on arr�te le moteur


//----------------------------------------------------------------------------------------------------
//  Nom: 	    __CheckEncoStat
//	Auteur :	AMANAX
//	Date:	    01.05.2015
//  Statut :    Ok
//----------------------------------------------------------------------------------------------------
//  Description : Check si les encodeurs sont arriv�s � la valeur d�sir�e.
//	Param�tre(s): Valeur moteur 1 et valeur moteur 2, ainsi que la longeur totale des deux valeurs
//  R�sultat :    / 
//------------------------------- ---------------------------------------------------------------------
/*void __CheckEncoStat(signed int32 Value1,signed int32 Value2 /*, unsigned int8 Length*//*)*/
//{	
	// Variables utiles
/*	static signed int32 Tot1 = 0,Tot2 = 0;
	signed int32 Val1,Val2;
	
	// Comptabilise le total des impulsions (travail en position relative)
	Tot1 = Value1 + Val_enco1 + impulse_effectue_1;
	Tot2 = Value2 + Val_enco2 +	impulse_effectue_2;
	strcpy(RoboteQ_values[0],"          ");
	strcpy(RoboteQ_values[1],"          ");
	// Attend d'avoir les bonnes valeurs (avec une certaine marge d'erreur)
	if((Val1<(Tot1-50) || Val1>(Tot1+50))&&(Val2<(Tot2+50) || Val2>(Tot2-50)))
	{
		// Demande la valeur des encodeurs
		strcpy(RoboteQ_dataBuffer,"?C 1 \r");
		__EnvoiComm(RoboteQ_dataBuffer);
		delay_ms(10);
	
		// Pour la capture la valeur de l'encodeur
		unsigned int8 i=2,j=0;
		//On v�rifie si le premier caract�re re�u n'indique pas la r�p�tition d'une commande
		if(RoboteQ_receiveBuffer[0] != '!' && RoboteQ_receiveBuffer[0] != '?' && RoboteQ_receiveBuffer[0] != '~' && RoboteQ_receiveBuffer[0] != '^' && RoboteQ_receiveBuffer[0] != '#')
		{
			//On coupe le message
			// Exemple : A=10:210 deviendra ->
			// 	A	10	210
			while(RoboteQ_receiveBuffer[i] != 0x0D)//for(i=2;i<(Length+3);i++) // On commence du [2] pour sauter le 'C='. Le +3 est pour le C,= et : (C=xxx:xxx).
			{ 
				if(RoboteQ_receiveBuffer[i] == ':') j=i+1; // Si on lit la valeur de l'encodeur 2, on passe � la deuxi�me ligne du tableau
				else
				{
					// Si lecture de la premi�re ligne
					if(j==0)
					{
						// Stockage de la valeur du premier encodeur
						RoboteQ_values[0][i-2] = RoboteQ_receiveBuffer[i];
					}
					else
					{
						// Stockage de la valeur du deuxi�me encodeur
						RoboteQ_values[1][i-j] = RoboteQ_receiveBuffer[i];
					}	
				}
				i++;
			}	
		}
		
		// Transforme les tableaux en nombres (Tab[4]={1,2,3,4} => TabVal = 1234)
		Val1=atoi32(RoboteQ_values[0]);
		Val2=atoi32(RoboteQ_values[1]);

	}
	else
	{
		flag_depl_ok =1 ;
		impulse_effectue_1 += Value1;
		impulse_effectue_2 += Value2;		
	}

		
	
	// Quitte la fonction
	return;
}
*/
//----------------------------------------------------------------------------------------------------
//  Nom: 	    Check_commande_atteint
//	Auteur :	BORREM
//	Date:	    18.2.15
//  Statut :    -
//----------------------------------------------------------------------------------------------------
//  Description : Check si la commande donn� aux moteurs a �t� finie
void __Check_commande_atteint(void)
{
	int1 comm_atteinte_m1,comm_atteinte_m2 = 0;
	strcpy(RoboteQ_dataBuffer,"?DR\r");
	__EnvoiComm(RoboteQ_dataBuffer);	
	
//il renvoie DR=x:x
	delay_ms(100);
//on v�rifie que le premier caract�re n'indique pas une r�p�tiotion de commande
if(RoboteQ_receiveBuffer[0] != '!' && RoboteQ_receiveBuffer[0] != '?' && RoboteQ_receiveBuffer[0] != '~' && RoboteQ_receiveBuffer[0] != '^' && RoboteQ_receiveBuffer[0] != '#')
	{
		comm_atteinte_m1 = RoboteQ_receiveBuffer[3]; // affectation du premier x dans la variable
		comm_atteinte_m2 = RoboteQ_receiveBuffer[5]; // affectation du deuxi�me x dans la variable
	}
	if(comm_atteinte_m1 == 1 && comm_atteinte_m2== 1) // si commande des deux moteurs dini 
	{
		flag_depl_ok =1 ; // on peut passer au d�placement suivant
	}
	return;
}