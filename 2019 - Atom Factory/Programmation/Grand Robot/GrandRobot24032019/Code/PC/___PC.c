/*
* \file ___PC.c
* \brief Gère la communication PC (fcts.)
* \ EMVs Eurobot - Driver Moteur
* \author Amand Axel
* \version 2.0
* \date 20.11.2015
* \copyright GNU Public License
*/

#ifndef ___PC_C
#define ___PC_C

// Bits & define
	// Contient la trame à décoder
unsigned int8 TabToDecode[256]={0};
unsigned int8 PosTabToDecode = 0;
unsigned int8 ToDoUART = 0;
	// Contient les valeurs décodées
unsigned int32 TabDecoded[256]={0};
	// Attend une réponse
int1 UARTWaitResp=0;
	// Nombre de fois à renvoyer
unsigned int8 UARTToSendBack=0;
	

/**
* \fn void __Init_UART(void)
* \brief Initie l'UART.
*
* \author Amand Axel
* \version 2.0
* \date 20.11.2015
*
* \return Ne retourne rien
*/
void __Init_UART(void)
{
	// Réception
	enable_interrupts(INT_RDA);

	// Quitte la fonction
	return;
}

/**
* \fn void RDA_isr(void)
* \brief Interruption RDA, récupère les caractères du RS232.
*
* \author Amand Axel
* \version 2.0
* \date 20.11.2015
*
*/
#INT_RDA
void RDA_isr(void)
{	
	// Checksum UART
	static unsigned int8 HashR1, HashR2, HashC1, HashC2;
	if(PCh_flagUARTReadyToDecode==0)
	{
		// Active le watchdog UART
		PCh_flagUARTWatchdog = 1;
		// Traite la réception
		while(kbhit(RS232))
		{
			// Récupération donnée
			unsigned int8 Dataa = fgetc(RS232);
			
			// Si c'est une réponse à un envoi, on remet à 0 l'attente de réponse et la fausse erreur
			if(UARTWaitResp && Dataa==ACK) 
			{
				UARTWaitResp=0;
				UARTToSendBack=0;
				
			}	
			// Si ce n'est pas OK, renvoie un certain nombre de fois
			else if(UARTWaitResp && Dataa==NAK)
			{
				if(UARTToSendBack<UART_NBR_REP_NAK) {__SendBackUART();UARTToSendBack++;}
				else {UARTWaitResp=0;UARTToSendBack=0;}
			}
			// Réception
			else
			{	
				// Début de transmission
				if(Dataa == STX&&ToDoUART==0)
				{
					HashC1 = HashC2 = 0;
					ToDoUART=1; 
					PosTabToDecode=0;
				}
				// Fin de transmission
				else if(Dataa == ETX&&ToDoUART==5)		
				{		
					if(HashC1==ETX||HashC1==CR)HashC1++; // Pour éviter de détecter une fausse fin de tableau, le caractère ETC doit être réservé.
					if(HashC2==ETX||HashC2==CR)HashC2++; // Pour éviter de détecter une fausse fin de tableau, le caractère ETC doit être réservé.
					// Si trame OK
					if(HashC1==HashR1 && HashC2==HashR2)
					{
						TabToDecode[PosTabToDecode] = ETX;
						// Décode le tableau
						__CommDecode(TabToDecode,TabDecoded);
						if(TabDecoded[0]==UART_ADDR)
						{	
							// Dit qu'on est prêts à recevoir
							PCh_flagUARTReadyToDecode=1;
							// Renvoie un simple OK
							fputc(ACK,RS232);
							// Dit qu'on attend une réponse
							UARTWaitResp=1;
						}	
					}
					else fputc(NAK,RS232); // Erreur de réception, envoi un pas ok
					ToDoUART = 0;
					PosTabToDecode=0;
					UARTToSendBack=0;
					// Désactive le watchdog UART
					PCh_flagUARTWatchdog = 0;
				}
				// Saute l'espace
				else if(ToDoUART==1)ToDoUART=2;
				// Enregistre le premier Hash
				else if(ToDoUART==2)
				{
					HashR1 = Dataa;
					ToDoUART=3;	
				}	
				// Saute l'espace
				else if(ToDoUART==3)ToDoUART=4;
				// Enregistre le second Hash
				else if(ToDoUART==4)
				{
					HashR2 = Dataa;
					ToDoUART=5;
				}
				// Capture la trame
				else if(ToDoUART == 5) 
				{
					// Hash les valeurs reçues
					HashC1 += Dataa;
					HashC2 = (HashC2+Dataa)*(PosTabToDecode+1);	
					// Retire l'incrément ASCII et enregistre
					TabToDecode[PosTabToDecode] = Dataa;
					
					PosTabToDecode++;
				}
			}			
		}	
	}		
	// Quitte l'interruption
	return;
}

/**
* \fn void __UART_Decode(char* Tab)
* \brief Décode la trame de l'UART.
*
* \author Amand Axel
* \version 2.0
* \date 20.11.2015
*
* \param[in] (*)_Tab Tableau avec lequel travailler
* \return Ne retourne rien
*/
void __UART_Decode(unsigned int32* _Tab)
{
	unsigned int16 index = 0;
	unsigned int16 Xo,Yo = 0;
	signed int16 phi = 0;	
	static int16 memo;
	static int16 Memorise;
	unsigned int16 Adresse = 0;
	// Regarde quoi faire
	switch(*(_Tab+1)) // On saute la première adresse mémoire qui contient l'adresse du driver
	{
		// Test Comm - LED Blink
		case 0 :
			LED1=LED2=LED3=1;
			break;
		// Demande si est connecté	
		case 1 :
			fputc(0x31,RS232);
			break;
		// Reset la plaque
		case 2 :
			reset_cpu();
			break;
		// Demande si RoboteQ connecté
		case 3 :
			// ?
			break;
		// Configuration du robot
		case 4 :			
			break;
		// Change d'objectif
		case 10 :
			flagMarche = (int1)(*(_Tab+2));
			break;
		//	Arrêt d'urgence
		case 11 :
			
			break;
		// Set la position de départ
		case 12 :
			Xo = *(_Tab+2);
			Yo = *(_Tab+3);
			phi = *(_Tab+4);
			
			write_eeprom(0xFF0,Xo);
			write_eeprom(0xFF2,Yo);
			write_eeprom(0xFF4,phi);
			
			__Init_pos();	
			break;
		
		// Enregistre le nombre d'objectifs
		case 20 :
		memo = 0;
		Memorise = 0;
		nbre_obj = *(_Tab+2);
		write_eeprom(0xFFE, nbre_obj);//on sauvegarde les objectifs dans l'EEPROM
		delay_ms(5);
		__ReadObjectifs();
		__ReadZones_Interdites();
		
			break;
		// Sauvegarde un objectif en EEPROM
		case 21 :
		if(memo <= 0xF00)
		{			
			for(index = memo; index <  (memo + 28); index += 2)
			{
				write_eeprom(index, *( _Tab +((index - memo)/2) + 3));//on sauvegarde les objectifs dans l'EEPROM
				
			}
			memo = index; //offset afin d'aller écrie plus loin dans l'eeprom
		}	
		
		break;
		// Définit le prochain objectif à charger
		case 22 :
			NextObj=(unsigned int16)*(_Tab+2);
			break;
		// Set les PIDs de roboteQ
		case 23 :
			while(index<250)//reset le tableau
			{
				 TabSentRS232[index] = '\r';
				 index++;
			}
			index = 0;
			index = 0;
			while(index<10) // on recupere les donnees
			{
				 __GetRoboteqPID(index);
				 index++;
			}
			__SendBackUART(); // on envoie a la plaque
			index = 0;
			break;
		case 24 :
			__SetRoboteqPID(*(_Tab+2),*(_Tab+3),*(_Tab+4),*(_Tab+5),*(_Tab+6),*(_Tab+7),*(_Tab+8),*(_Tab+9),*(_Tab+10),*(_Tab+11));
			__reset_Roboteq();
			break;
		
		//erase eeprom
		case 25 :
			__resetEEPROM();
			reset_cpu();    
			break;		
		
			break;
		// Ouvre ou ferme l'étau
		case 30 :
			break;
		// Position hold ou release du servo
		case 31 :
			break;			
		case 19 :
			for(Adresse = Memorise ; Adresse <= 16 + Memorise ; Adresse += 2)
			{
				write_eeprom(Adresse + 0xF2A , *( _Tab +((Adresse - Memorise)/2) + 3));//on sauvegarde les objectifs dans l'EEPROM
				delay_ms(5);
			}
			Memorise = Adresse; //offset afin d'aler écrie plus loin dans l'eeprom
		
			break;
		// Ne lit plus les objectifs en ROM avant une nouvelle écriture	
		case 50 :			
			break;	
			
			// Avertit le PC d'une action inconnue
		default :
			fprintf(RS232,"Carte Principale : Commande Inconnue\r");
			break;
	}
	
	// Permet de recevoir à nouveau
	PCh_flagUARTReadyToDecode = 0;

	// Quitte la fonction
	return;
}

/**
* \fn void __SendBackUART(void)
* \brief Envoi des commandes en UART
*
* \author Amand Axel
* \version 2.0
* \date 11.01.2016
*
* \return Ne retourne rien

*/
void __SendBackUART(void)
{
	char* ptrBuffy = TabSentRS232;
	// Envoi commande
	unsigned int8 ToEndSend=0;
	while(*(ptrBuffy+ToEndSend)!='\r' && *(ptrBuffy+ToEndSend)!=ETX) // Attend de voir la fin de tableau
	{
		fputc(*(ptrBuffy+ToEndSend),RS232); // Envoi la commande
		ToEndSend++;
	}	
	fputc(*(ptrBuffy+ToEndSend),RS232); // Envoi le caractère de fin de commande
	TabSentRS232[ToEndSend]=*(ptrBuffy+ToEndSend);
	
	// Quitte la fonction
	return;	
}	

// Décode un tableau
void __CommDecode(unsigned int8* _TabToDec,unsigned int32* _TabDec)
{
	// Permet de se balader dans le tableau
	unsigned int8 i=1,j=0,ki=0;
	char TempTab[11]={0}; // Taille max d'un int32 + NULL
	// On décode tout
	while(_TabToDec[i]!=ETX)
	{
		// On cherche la fin d'un nombre
		while(_TabToDec[i]!=SPACE)
		{
			TempTab[j]=(char)(_TabToDec[i]);
			i++;j++;
		}	
		TempTab[j]=NUL;
		i++;j=0;
		// On enregistre le nombres
		_TabDec[ki]=(unsigned int32)atoi32(TempTab);
		ki++;
	}
	
	// Quitte la fonction
	return;	
}	

#endif