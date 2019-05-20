
/*====================================================================================================
===																									==
===											EMVs - EUROBOT	  										==
===											--------------											==
======================================================================================================
===	 Auteur				: Amand Axel
						: Borgeat R�my     					  										==
===  Date				: 30.04.2015    															==
===  Nom du programme 	: Function.c														==
===  Version 			: V1.0																		==
======================================================================================================
=== Description :																					==
=== Contient des fonctions pour le robot																==
====================================================================================================*/

#ifndef ___Functions_c
#define ___Functions_c


#DEFINE START 30




//unsigned int8 points = 0;//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Actions � effectuer
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
			Standby_stop();
			break;	
		case 2 : 
			Standby_scan();
			break;
		case 3 : 
			Take_front();
			break;
		case 4 : 
			Take_side();
			break;
		case 5 : 
			Take_goldenium();
			break;
		case 7 :
			Put_balance();
			break;
		case 8 : 
			Put_accelerator();
			break;
		case 9 : 
			//reinitialisation();
			break;
		default :
			//__Affichage_erreur(5);
			break;
	}
}

//*********************************************************************************************************************
// Fonction permettant d'ordonner à l'arduino de ne rien faire et
// garder le bras immobile 
//=====================================================================================================================
// Développé par : Rithner Aurélien
// Date          : 01.03.2019 
// Révision      :
//
// paramètres    : aucun
// return        : rien
//
//*********************************************************************************************************************
void Standby_stop()
{
	data_to_transmit[0] = 1;
	Write_cmd_arduino(10,1, &data_to_transmit );

	LED1 = 1;
	
	Action_send = 1;
}

//*********************************************************************************************************************
// Fonction permettant d'ordonner à l'arduino de ne rien faire mais de
// scaner la zone et enlever les palets qui pourraient gêner le déplacement 
//=====================================================================================================================
// Développé par : Rithner Aurélien
// Date          : 01.03.2019 
// Révision      :
//
// paramètres    : aucun
// return        : rien
//
//*********************************************************************************************************************
void Standby_scan()
{
	data_to_transmit[0] = 2;
	Write_cmd_arduino(10,1, &data_to_transmit );

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
	
	Action_send = 1;

}

//*********************************************************************************************************************
// Fonction permettant d'ordonner à l'arduino de prendre les palets qui se trouvent
// devant lui
//=====================================================================================================================
// Développé par : Rithner Aurélien
// Date          : 01.03.2019 
// Révision      :
//
// paramètres    : aucun
// return        : rien
//
//*********************************************************************************************************************
void Take_front()
{
	Write_cmd_arduino(20,1, &data_to_transmit );
	LED3 = 1;
	delay_ms(50);
	
	Read_etat_arduino(&stat);
	while(stat.msg != 1)
	{
		Write_cmd_arduino(20,1, &data_to_transmit );
		delay_ms(50);
		Read_etat_arduino(&stat);
	}
	delay_ms(200);
	LED3 = 0;
	/*
	
	
	while(!_DEMA)
	{
		LED1 = 1;
		delay_ms(200);
		LED1 = 0;
		delay_ms(200);
		
		LED1 = 1;
		delay_ms(200);
		LED1 = 0;
		delay_ms(200);
		
		LED1 = 1;
		delay_ms(200);
		LED1 = 0;
		delay_ms(200);
		
	}	
	*/
	Action_send = 1;
}

//*********************************************************************************************************************
// Fonction permettant d'ordonner à l'arduino de prendre les palets qui se trouvent
// sur le côté 
//=====================================================================================================================
// Développé par : Rithner Aurélien
// Date          : 01.03.2019 
// Révision      :
//
// paramètres    : aucun
// return        : rien
//
//*********************************************************************************************************************
void Take_side()
{
	Write_cmd_arduino(30,1, &data_to_transmit );
	Action_send = 1;
}

//*********************************************************************************************************************
// Fonction permettant d'ordonner à l'arduino de prendre le goldenium
// devant lui
//=====================================================================================================================
// Développé par : Rithner Aurélien
// Date          : 01.03.2019 
// Révision      :
//
// paramètres    : aucun
// return        : rien
//
//*********************************************************************************************************************
void Take_goldenium()
{
	Write_cmd_arduino(40,1, &data_to_transmit );
	Action_send = 1;
}

//*********************************************************************************************************************
// Fonction permettant de vider les réservoirs dans la balancce
//=====================================================================================================================
// Développé par : Rithner Aurélien
// Date          : 01.03.2019 
// Révision      :
//
// paramètres    : aucun
// return        : rien
//
//*********************************************************************************************************************
void Put_balance()
{
	Action_send = 1;
	
}

//*********************************************************************************************************************
// Fonction permettant de vider le réservoir dans l'accélérateur
//=====================================================================================================================
// Développé par : Rithner Aurélien
// Date          : 01.03.2019 
// Révision      :
//
// paramètres    : aucun
// return        : rien
//
//*********************************************************************************************************************
void Put_accelerator()
{
	
	Action_send = 1;
}


void Check_action_done()
{
	Read_etat_arduino(&stat);
	
	if(stat.bras == 0)
	{
		flag_action_done = 1;
	}
	else if(stat.bras == 2)
	{
		//LCD ERREUR BRAS
		flag_action_done = 0;
	}
	else
	{
		flag_action_done = 0;
	}			
}	


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//*********************************************************************************************************************
// Fonction permettant de donner un ordre � l'arduino
//
// D�velopp� par : Daniel Duay
// Date          : 07.02.2019 
// R�vision      :
//
// param�tres    : cmd      = commande � ex�cuter (int8) valeur de 1 � 255
//                 taille   = longueur des datas � envoyer max. 16 bytes (int8)
//                 data     = valeur � envoyer (int8))
// return        : none
//													
//
//*********************************************************************************************************************
unsigned int8 Write_cmd_arduino(unsigned int8 cmd,unsigned int8 taille, unsigned int8 *data ) 
{
	unsigned int8 boucle;
	unsigned int8 crc;
	
	if (taille > 16) taille = 16;           // taille du buffer max. � envoyer
	CS1	= 0;
	delay_us(1);
	spi_write(cmd);     // commande � envoyer
	crc = cmd;
	delay_us(10);
	spi_write(taille);  // longueur des datas
	crc = crc + taille;
	delay_us(10);
	
	for (boucle=0;boucle<taille;boucle++)   // data � envoyer
	{
	    spi_write(data[boucle]);        
	    crc = crc + data[boucle];
	    delay_us(10);
	}
	crc = 0xFF - crc + 1;   // calcul du CRC
	spi_write(crc);         // envoi du CRC
	delay_us(10);
	CS1	= 1;
}

//*********************************************************************************************************************
// Fonction permettant de lire l'�tat de l'arduino
//
// D�velopp� par : Daniel Duay
// Date          : 07.02.2019 
// R�vision      :
//
// param�tres    : structure contenant l'�tat des 3 variables
//                 bras variable pour sauvegarder l'�tat du bras
//                 msg variable pour signaler si les messages re�u par le slave sont corrects
//                 cam variable pour sauvegarder l'�tat de la cam�ra
// return        : retourne le status de l'arduino
//                 3 bits low bit 0..2(status du bras)       
//				   0-> Arret  (le bras a fini tout traitement et attend le prochain ordre)	
//				   1-> Marche (le bras est entrain d'ex�cuter l'ordre)													
//				   2-> Erreur bras
//				   3-> Action en traitement
//				   4-> Action termin�e
//                 2 bits middle bit 3..4 (r�ception message)
//				   0-> pas de message ou ordre pas trait�
//				   1-> message re�u + checksum OK
//                 2-> erreur CRC r�ception message
//                 3 bits high bit 5..7 (status de la cam�ra)       
//				   0-> aucune d�tection (la cam�ra ne d�tecte aucun palet)	
//				   1-> d�tection niveau 1 (la cam�ra d�tecte un palet, le robot doit ralentir )													
//				   2-> d�tection niveau 2 (la cam�ra d�tecte un palet tr�s proche, le robot doirt s'arr�ter)													
//
//*********************************************************************************************************************
Read_etat_arduino(struct etat *value) 
{
	unsigned int8 arduino_etat=0;
	
	CS1	= 0;
	delay_us(1);
	arduino_etat = spi_read(0x00);
	value->bras =  (arduino_etat & 0x07);
	value->msg =  (arduino_etat & 0x18) >> 3;
	value->cam =  (arduino_etat & 0xE0) >> 5;
	delay_us(1);
	CS1	= 1;
}


/*
	Fct qui reset une partie de l'eeprom en
	remettant les valeurs � 0xffff
	
	Auteur : Borgeat R�my
	Date   : 9.2.2017
*/
void __resetEEPROM(void)
{
	unsigned int16 adresse = 0;
	for(adresse = 0; adresse <= 0xFFF; adresse +=  2)
	{
		write_eeprom(adresse, 0xFFFF);//on �crase l'eeprom
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
	Auteur : Borgeat R�my
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
	Fct qui va changer les param�tre PID du roboteq.
	Les parametre ont ete recu du pc et ont les save en
	dans l'eeprom du roboteq
	
	Auteur : Borgeat R�my
	Date   : 16.2.2017
*/
void __SetRoboteqPID(unsigned int8 P1,I1,D1,P2,I2,D2,ac1,dc1,ac2,dc2)
{
	//envoi des param�tres PID au ROBOTEQ
	fprintf(ROBOTEQ,"^KP 1 %u_^KI 1 %u_^KD 1 %u_^KP 2 %u_^KI 2 %u_^KD 2 %u \r",P1,I1,D1,P2,I2,D2);
	fprintf(ROBOTEQ,"^MAC 1 %u_^MDEC 1 %u_^MAC 2 %u_^MDEC 2 %u \r",ac1,dc1,ac2,dc2);// envoie au Roboteq

	write_eeprom(300,P1);
	write_eeprom(302,I1);
	write_eeprom(304,D1);
	write_eeprom(306,P2);
	write_eeprom(308,I2);
	write_eeprom(310,D2);
	
	//Sauvegarde en eeprom
	fputc('%',ROBOTEQ);//pas le choix de faire un putc, car le % est un caract�re r�serv� pour le pritnf
	fprintf(ROBOTEQ,"EESAV \r");//envoie du reste de la commande

}

// R�cup�re tous les objectifs et les stock en eeprom
void __ReadObjectifs(void)
{
	// Lit les objectifs stock�s en EEPROM
	// Les �l�ments d'objectifs sont stock�s chaque deux dans l'EEPROM
	unsigned int16 i = 0;
	unsigned int8 j1, j2, j3 = 0;
	unsigned int16 y = 0;
	static int16 offset = 0;
	unsigned int16 NumObj = 0;
	unsigned int16 Obj = 0;
	
	for(j1 = 0; j1< 7; j1++)
	{
		 for(j2 = 0; j2< 13; j2++)
		{
			for(j3 = 0; j3< 12; j3++)
			{
				TabObjectifs[j1][j2][j3] = 0;
			}
		}
	}			
				
	nbre_obj = read_eeprom(0xFFE);
	if(nbre_obj == 0xFF)
	{
		nbre_obj = 0;
	}
	
	offset = 0;
	
	for(y = 0; y < nbre_obj; y++)
	{
		Obj = read_eeprom(offset);//on check si il reste des objectifs
		NumObj = read_eeprom(offset+2);
		for( i = 0 ; i < 24; i += 2)
		{			
			TabObjectifs[Obj][NumObj][(i/2)] = read_eeprom(i+4+offset);//remplir le tableau avec les objectifs
		}	
		
		offset += 28;// offset de +24,afin de lire les objectifs suivant
	}	
	
	NbreObjectifs= nbre_obj;	
	
/*
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
	*/
	
			

}
// R�cup�re tous les objectifs et les stock en eeprom
void __ReadZones_Interdites(void)
{
	// Lit les objectifs stock�s en EEPROM
	// Les �l�ments d'objectifs sont stock�s chaque deux dans l'EEPROM
	unsigned int16 i = 0;
	unsigned int16 y = 0;
	unsigned int16 temp_read = 0;
	static int16 offset = 0xF2A;
	unsigned int16 NumZone = 0;
	

	while(y==0)
	{
		NumZone = read_eeprom(offset);//on check si il reste des objectifs
		if(NumZone!=0xFFFF)//Si il en reste
		{
			for( i = 0 ; i < 16; i += 2)
			{
				temp_read = read_eeprom(i+2+offset);//remplir le tableau avec les objectifs
				
				TabZonesPC[(i/2)] = temp_read;
			}	

			TabZones[NumZone-1][0] = TabZonesPC[0];
			TabZones[NumZone-1][1] = TabZonesPC[1];
			TabZones[NumZone-1][2] = TabZonesPC[4];
			TabZones[NumZone-1][3] = TabZonesPC[5];
			
			if(TabZones[NumZone-1][0] < MARGE)TabZones[NumZone-1][0] = 0; else TabZones[NumZone-1][0] -= (MARGE/2);	
			if(TabZones[NumZone-1][1] < MARGE)TabZones[NumZone-1][1] = 0; else TabZones[NumZone-1][1] -= (MARGE/2);	
			if(TabZones[NumZone-1][2] > (SIZE_TABLE_X-MARGE))TabZones[NumZone-1][2] = 3000; else TabZones[NumZone-1][2] += (MARGE/2);	
			if(TabZones[NumZone-1][3] > (SIZE_TABLE_Y-MARGE))TabZones[NumZone-1][3] = 2000; else TabZones[NumZone-1][3] += (MARGE/2);
			
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



#endif
