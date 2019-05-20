/*
* \file ___data.h
* \brief Data pour le robot.
* \ EMVs Eurobot - Driver Moteur
* \author Amand Axel
* \version 2.0
* \date 11.03.2016
* \copyright GNU Public License
*/

#ifndef ___data_H
#define ___data_H

	
	int1 Depl_send = 0;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	////////// Gestion erreurs
	int1 Base = 0;
	int16 TableWidth =3000;
	unsigned int8 NbreZone_check = 0;
	char RoboteQ_receiveBuffer[256]={};			// Buffer des données reçues
	unsigned int8 TabSentRS232[256]={0};


	
	unsigned int16 TIME_SURCHAUFFE_MS = 1000;
	unsigned int8 Erreur_max_surchauffe = 10;
	unsigned int32 Time_ejection = 0;
	unsigned int32 Time_ejection_toDo = 0;
	int1 Action_send = 0;	

	signed int16 TabObjectifs[7][13][12] = {0};
	unsigned int16 TabZones[10][8] = {0};

	// Objectif en cours
	signed int16 oXp=0,oYp=0,oType=0,oAvAr=0,oCoteTourn=0,oVitMax=0,Obj_Action = 0,Pt_commun = 0,Ponderation = 0,Obj_end = 0,Next_obj = 0,keep_obj = 0;	
	
	
	////////// UART
	unsigned int8 UART_WD_DELAY = 20;	// D�lai du watchdog UART, en [ms]; par pas de 1 [ms]
	unsigned int8 UART_NBR_REP_NAK = 5;	// Combien de fois maximum il faut r�p�ter une commande si le r�cepteur n'a pas compris 
	// Adresse UART du driver
	unsigned int32 UART_ADDR = 2;
	
	////////// IIC
	// Combien de fois maximum il faut r�p�ter une commande si le r�cepteur n'a pas compris
//	unsigned int8 IIC_NBR_REP_NAK = 5;	
	// Combien de fois on r��ssaie un envoie
//	unsigned int8 IIC_NBR_REP_ENV = 5;
 	//Adresse IIC du driver
//	unsigned int8 DRIVER_IIC_ADR = 0x50;
//	unsigned int8 TabToSendIIC[60]={0};

	
	////////// Balise /////////
	unsigned int8 MAX_VALUE_DETECT_BALISE = 3; // Valeur maximum pour la d�tection de l'adversaire (action trig si <=)
	unsigned int16 TIME_TO_CHECK_BAL=200;	// Temps avant chaque check balise

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Mise en marche/arr�t
int1 flagMarche = 0;

// Pour le nombre d'objectifs d�j� enregistr�s
unsigned int16 NbreObjectifs = 0;
	// Pour conna�tre le prochain objectif � atteindre
unsigned int16 NextObj = 0;

////PC
#endif