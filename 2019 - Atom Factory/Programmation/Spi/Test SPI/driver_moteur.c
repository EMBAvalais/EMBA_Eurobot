//==========================================================================================
//																							
//						EMVs - Fonctions pour DRIVER MOTEUR MAXON 											
//						--------------------------												
//																							
//=========================================================================================
//	D�velopp� par:		: Carrupt Aur�lien    												
//						: Duay Daniel    												
//  Date				: 15.03.2013															
//  Date de modif.		: 09.05.2015															
//  Nom de la lib	 	: driver_moteur.c													
//  Version 			: V2.0																
//=========================================================================================
// Description :																			
//=============																			
//	Ce code contient les fonctions qui permettent au master de communiquer avec le driver  	
//	de moteur V3.0																			
//  
//========================================================================================
//DIRECTIVES DE PRECOMPILATIONS
//========================================================================================

#DEFINE DRV_MODE_COURANT 0		// r�gulation en mode courant 
#DEFINE DRV_MODE_VITESSE 1		// r�gulation en mode vitesse 
#DEFINE DRV_MODE_NON_REGUL 2	// mode r�gulation d�sactiv�e 
#DEFINE DRV_STOP 0				// Arr�t du moteur et arr�t d'urgence
#DEFINE DRV_RESET 1				// Reset du driver

#DEFINE DRV_ARRET_COURANT 0					// Arret en courant 
#DEFINE DRV_ARRET_POSITION_ABSOLUE 1		// Arret en position absoulue
#DEFINE DRV_ARRET_POSITION_RELATIVE 2		// Arret en position relative
#DEFINE DRV_ARRET_TEMPS 3					// Arret en position temps 
			
//=================================================================================================================================================================================================
// Fonction 	: go_driver_moteur																																
//=================================================================================================================================================================================================
//	D�velopp� par:		: Duay Daniel
//						:     												
//  Date				: 09.05.2015															
//  Date de modif.		: 															
//-------------------------------------------------------------------------------------------------------------------------------------------------------------																
// Description 	:  	Permet d'envoyer un ordre de d�placement au moteur		 	      																	
// param�tres 	:  	adresse_driver 	= Adresse I2C du driver (int8)																			
//					mode_regulation : 	DRV_MODE_COURANT (int8) -> r�gulation en courant ->param�tre_1 = valeur du courant qu'on souhaite maintenir [mA] (int16)
//										DRV_MODE_VITESSE (int8) -> r�gulation en vitesse  ->param�tre_1 = valeur de vitesse qu'on souhaite maintenir [impulse/s] (int16)
//										DRV_MODE_NON_REGUL (int8) -> r�gulation d�sactiv�e ->param�tre_1 = valeur de la PWM 0-100 en %  (int16)
//					mode_d'arret 	: 	DRV_ARRET_POSITION_ABSOLUE (int8)	-> 	parametre_2 = position a atteindre [impulse] (int32)																			  
//										DRV_ARRET_POSITION_RELATIVE (int8)	->	parametre_2 = nombre d'impulsion d'encodeur a effectuer [impulse] (int32)
//										DRV_ARRET_TEMPS (int8)				->	parametre_2 = temps du parcours [ms] (int32)
//										DRV_ARRET_COURANT (int8)			->	!! Non impl�ment� !! parametre_2 = valeur du courant d'arr�t souhait� [mA] (int32)								
// retourne 	:  retourne le status du driver											
//				   0-> non utilis�																
//				   1-> OK : ordre transmis														
//				   2-> not ready  (le slave ne r�pond pas)															
//===================================================================================================================================================================================================
unsigned int8 go_driver_moteur(int8 adresse_driver, int8 direction, int8 mode_regulation, int16 parametre_1, int8 mode_arret, signed int32 parametre_2)
{
	int8 val1, val2, val3, val4, val5, val6;
	int8 config;
	
	
	config = ((mode_regulation & 0b00000111)<<5) + ((direction & 0b00000001)<<4) + (mode_arret & 0b00000111);
	val1 = make8(parametre_1, 0);
	val2 = make8(parametre_1, 1);
	val3 = make8(parametre_2, 0);
	val4 = make8(parametre_2, 1);
	val5 = make8(parametre_2, 2);
	val6 = make8(parametre_2, 3);

	i2c_start();
	if(!i2c_write(adresse_driver))			//ADRESSE
	{
		i2c_write(0x48);					//Type de commande (4 bits high) et nombre de donn�e (4 bits low) 
		i2c_write(config);					//configuration
		i2c_write(val1);					// parametre_1
		i2c_write(val2);
		i2c_write(val3);					// parametre_2
		i2c_write(val4);
		i2c_write(val5);					
		i2c_write(val6);
	}
	else
	{ 
		i2c_stop();
		return 2;
	}
	i2c_stop();	
	return 1;
}


//=================================================================================================================================================================================================
// Fonction 	: config_driver_moteur_pid																																
//=================================================================================================================================================================================================
//	D�velopp� par:		: Duay Daniel
//						:     												
//  Date				: 09.05.2015															
//  Date de modif.		: 															
//-------------------------------------------------------------------------------------------------------------------------------------------------------------																
// Description 	:  	Permet de configurer les valeurs du PID du r�gulateur driver moteur	 	      																	
// param�tres 	:  	adresse_driver 	= Adresse I2C du driver (int8)
//					reg_P 			= Valeur P du r�gulateur (int16)  valeur en milli�me  ex: 1250 = 1.25
//					reg_I 			= Valeur I du r�gulateur (int16)			idem
//					reg_D 			= Valeur D du r�gulateur (int16)			idem
// retourne 	:  retourne le status du driver											
//				   0-> non utilis�																
//				   1-> OK : ordre transmis														
//				   2-> not ready  (le slave ne r�pond pas)															
//===================================================================================================================================================================================================
unsigned int8 config_driver_moteur_pid(int8 adresse_driver, int16 reg_P, int16 reg_I, int16 reg_D)
{
	int8 val1, val2, val3, val4, val5, val6;

	val1 = make8(reg_P, 0);
	val2 = make8(reg_P, 1);
	val3 = make8(reg_I, 0);
	val4 = make8(reg_I, 1);
	val5 = make8(reg_D, 0);
	val6 = make8(reg_D, 1);

	i2c_start();
	if(!i2c_write(adresse_driver))			//ADRESSE
	{
		i2c_write(0x37);					//Type de commande (4 bits high) et nombre de donn�e (4 bits low) 
		i2c_write(val1);					// parametre P
		i2c_write(val2);
		i2c_write(val3);					// parametre I
		i2c_write(val4);
		i2c_write(val5);					// parametre D					
		i2c_write(val6);
	}
	else
	{ 
		i2c_stop();
		return 2;
	}
	i2c_stop();	
	return 1;
}


//=================================================================================================================================================================================================
// Fonction 	: config_driver_moteur																																
//=================================================================================================================================================================================================
//	D�velopp� par:		: Duay Daniel
//						:     												
//  Date				: 09.05.2015															
//  Date de modif.		: 															
//-------------------------------------------------------------------------------------------------------------------------------------------------------------																
// Description 	:  	Permet de configurer les rampes d'acc�l�ration et de d�c�l�ration ainsi que le courant max du moteur
// param�tres 	:  	adresse_driver 	= Adresse I2C du driver (int8)
//					acceleration 	= valeur d'acc�l�ration en imp./sec (int16)
//					deceleration 	= valeur de d�c�l�ration en imp./sec (int16) 
//					courant_max 	= Valeur du courant max en mA (int16)
// retourne 	:  retourne le status du driver											
//				   0-> non utilis�																
//				   1-> OK : ordre transmis														
//				   2-> not ready  (le slave ne r�pond pas)															
//===================================================================================================================================================================================================
unsigned int8 config_driver_moteur(int8 adresse_driver, int16 acceleration, int16 deceleration, int16 courant_max)
{
	int8 val1, val2, val3, val4, val5, val6;

	val1 = make8(acceleration, 0);
	val2 = make8(acceleration, 1);
	val3 = make8(deceleration, 0);
	val4 = make8(deceleration, 1);
	val5 = make8(courant_max, 0);
	val6 = make8(courant_max, 1);

	i2c_start();
	if(!i2c_write(adresse_driver))			//ADRESSE
	{
		i2c_write(0x27);					//Type de commande (4 bits high) et nombre de donn�e (4 bits low) 
		i2c_write(val1);					// acc�l�ration
		i2c_write(val2);
		i2c_write(val3);					// d�c�l�ration
		i2c_write(val4);
		i2c_write(val5);					// courant max					
		i2c_write(val6);
	}
	else
	{ 
		i2c_stop();
		return 2;
	}
	i2c_stop();	
	return 1;
}


//=================================================================================================================================================================================================
// Fonction 	: driver_moteur																																
//=================================================================================================================================================================================================
//	D�velopp� par:		: Duay Daniel
//						:     												
//  Date				: 09.05.2015															
//  Date de modif.		: 															
//-------------------------------------------------------------------------------------------------------------------------------------------------------------																
// Description 	:  	Permet d'envoyer des ordres courts direct comme d'arr�ter le moteur m�me s'il n'a pas fini l'ordre pr�c�dent ou reset le driver
// param�tres 	:  	adresse_driver 	= Adresse I2C du driver	(int8)
//					ordre		 	= ordre � effectuer (stop = 0, reset = 1) (int8)
// retourne 	:  retourne le status du driver											
//				   0-> non utilis�																
//				   1-> OK : ordre transmis														
//				   2-> not ready  (le slave ne r�pond pas)															
//===================================================================================================================================================================================================
unsigned int8 driver_moteur(int8 adresse_driver, int8 ordre)
{
	i2c_start();
	if(!i2c_write(adresse_driver))			//ADRESSE
	{
		i2c_write(((ordre << 4) & 0b00010000) + 0x01);					//Type de commande (4 bits high) et nombre de donn�e (4 bits low) 
	}
	else
	{ 
		i2c_stop();
		return 2;
	}
	i2c_stop();	
	return 1;
}


/*====================================================================================================================================================================================================
== Fonction 	: read_driver_moteur	 														
== Cr�ateur 	: CARRUPT AURELIEN																	
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------																
== Description 	:  Permet de lire l'�tat du driver								      	
== param�tre 	:  Prend l'adresse du driver a atteindre 								
== retourne 	:  retourne le status du driver											
==				   0-> Arret
==				   1-> Marche																
==				   2-> Surcharge															
==				   3-> not ready  (le slave ne r�pond pas)															
/*===================================================================================================================================================================================================*/
unsigned int8 read_driver_moteur(int8 adresse_driver)
{
	int8 driver_etat=0;
	int8 ack=0;
	i2c_start();
	ack = i2c_write(adresse_driver+1);
	if(ack == 0)
	{
		driver_etat=i2c_read(0);
	}
	else driver_etat = 3;

	i2c_stop();
	return driver_etat;
}	
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------