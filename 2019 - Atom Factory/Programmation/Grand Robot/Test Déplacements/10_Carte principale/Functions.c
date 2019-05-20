/*====================================================================================================
===																									==
===											EMVs - EUROBOT	  										==
===											--------------											==
======================================================================================================
===	 Auteur				: Borgeat RÃ©my					  										==
===  Date				: 24.3.2016   															==
===  Nom du programme 	: Eurobot2016														==
===  Version 			: V1.0																		==
======================================================================================================
=== Description :																					==
=== Fonctions utilisÃ©e pour le robot secondaire															==
=== !!!! on peut amÃ©liorer l'envoi et le simplifier grÃ¢ce au printf!!!!!!! A checker plus tard
====================================================================================================*/

#ifndef ___Functions_c
#define ___Functions_c

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

//----------------------------------------------------------------------------------------------------
//  Nom: 	    Afficheur 7 segments
//	Auteur :	BORR
//	Date:	    6.1.16
//  Statut :    Fonctionnel
//  Futur :     n.a.
//----------------------------------------------------------------------------------------------------
//  Description : GÃ¨re 2 afficheur 7 segments
//	ParamÃ¨tre(s): int8 nombre -> nombre<=99
//  RÃ©sultat :    / 
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
		static unsigned int16 dizaine = 0; // variable qui va rÃ©cupÃ©rer le chiffre des dizaine 
		static unsigned int16 unite = 0; // variable qui va rÃ©cupÃ©rer le chiffre des unitÃ©
	
		dizaine = nombre/10; //rÃ©cupÃ©ration du nombre des dizaine
		unite   = nombre%10; //rÃ©cupÃ©ration du nombre des unitÃ©s
	
		dizaine = dizaine * 4096; //dÃ©calage vers la droite car sortie sur RB12 Ã  RB15
		unite = unite * 4096; //dÃ©calage vers la droite car sortie sur RB12 Ã  RB15
		
		_En_Diz = 0; // possibilitÃ© d'afficher sur l'afficheur des dizaine	
		PORTB = dizaine; //affichage de la valeur sur l'afficheur
		_En_Diz = 1; // Afficheur dizaine allumÃ©, mais on ne peux plus changer la valeur
	
		_EN_Uni = 0; // possibilitÃ© d'afficher sur afficheur unitÃ© 
		PORTB = unite; // affichage des unitÃ© sur l'afficheur des unitÃ© 
		_EN_Uni = 1; // Afficheur unitÃ© allumÃ©, mais on ne peux plus changer la valeur
	}

}

/*void __Affichage_Erreur(int8 nombre)		//MODIFIE
{
	// Indique l'erreur
	flagError=1;
	// DÃ©finit l'erreur
	NO_ERROR=nombre;
	
	// Bloque lÃ 
	while(1){}
	
	// Quitte la fonction
	return;
}*/
//----------------------------------------------------------------------------------------------------
//  Nom: 	    __Detected
//	Auteur :	BORR
//	Date:	    13.05.16
//  Statut :    fonctionnel
//  Futur :     n.a.
//----------------------------------------------------------------------------------------------------
//  Description : On check si des adversaire sont Ã  proximitÃ©, si c'est le cas -> on s'arrete tant 
//	que l'adversaire est a proximitÃ©
//	ParamÃ¨tre(s): /
//  RÃ©sultat :    / 
//----------------------------------------------------------------------------------------------------
void __Detected(void)
{   
	//unsigned int8 toto;
	static int8 Tempo_bal; 
	static int1 _Detected; 
   toto=Check_balise(); // on checkla valeur de la balise
   // Lecture de la valeur de la dÃ©tection
   Tempo_bal++;
   if(toto>=BalSensitivity)
   {
      Tempo_bal = 0;
      _Detected = 1;
      fprintf(ROBOTEQ,"!EX\r"); // ArrÃªt d'urgence
      // Attend Ã©loignement adversaire
      while(toto>= BalSensitivity)
      {
         if(flagBaliseCheck==1) // on check si l'adversaire est toujours la
         {   __Afficheur_7segments(90);
            toto=Check_Balise();
            flagBaliseCheck=0;
			Flag_Arret_Moteur=0;
			Timer_Arret_Moteur=0;
         }   
         if(flagTimeOUt == 1)//si on est à la fin du temps on sort de la boucle
         {
            toto = 0;
         }   
      }
      __Afficheur_7segments(0);
   }
   else if(Tempo_bal == 4 && _Detected)
   {
      _Detected = 0; 
      fprintf(ROBOTEQ,"!MG\r");
   }
   flagBaliseCheck=0;
   // Quitte la fonction
   return;   
}
//----------------------------------------------------------------------------------------------------
//  Nom: 	    Recule
//	Auteur :	BORR
//	Date:	    28.1.16
//  Statut :    fonctionnel
//  Futur :     n.a.
//----------------------------------------------------------------------------------------------------
//  Description : fait reculer le robot Ã  une vitesse voulue et Ã  un nbre d'impulsion voulue
//	ParamÃ¨tre(s): nbre d'impulsion, vitesse , nombre de caractÃ¨re
//  RÃ©sultat :    / 
//----------------------------------------------------------------------------------------------------
void __Recule(unsigned int32 impulse,unsigned int32 vitesse)
{
		Balise_set_plage(1);//plage à l'arrière du robot
	
	/*	char vitesse_string[5];
		char impulse_string[6];
		sprintf(vitesse_string,"%Lu",vitesse);
		sprintf(impulse_string,"%Lu",impulse);

		// RÃ©glage vitesse moteur droite
		fprintf(ROBOTEQ,"!S 1 %05s_!S 2 %05s \r",vitesse_string,vitesse_string);
		// AvancÃ©e
		fprintf(ROBOTEQ,"!PR 1 %06s_!PR 2 -%06s \r",impulse_string,impulse_string);*/
		
		//a tester si sa marche, si sa marche, enlever toutes les autres lignes sauf balise_set_....
			fprintf(ROBOTEQ,"!S 1 %u_!S 2 %u \r",vitesse,vitesse);
			fprintf(ROBOTEQ,"!PR 1 %u_!PR 2 %u \r",impulse,-impulse);
}
//----------------------------------------------------------------------------------------------------
//  Nom: 	    Avance
//	Auteur :	BORR
//	Date:	    28.1.16
//  Statut :    fonctionnel
//  Futur :     n.a.
//----------------------------------------------------------------------------------------------------
//  Description : fait avancer le robot Ã  une vitesse voulue et Ã  un nbre d'impulsion voulue
//	ParamÃ¨tre(s): nbre d'impulsion, vitesse , nombre de caractÃ¨re
//  RÃ©sultat :    / 
//----------------------------------------------------------------------------------------------------
void __Avance(unsigned int32 impulse,unsigned int32 vitesse)
{
		Balise_set_plage(2);//plage à l'avant du robot
		
	/*	char vitesse_string[5];
		char impulse_string[6];
		
		sprintf(vitesse_string,"%Lu",vitesse);
		sprintf(impulse_string,"%Lu",impulse);

		// RÃ©glage vitesse moteur droite
		fprintf(ROBOTEQ,"!S 1 %06s_!S 2 %06s\r",vitesse_string,vitesse_string);
		// AvancÃ©e
		fprintf(ROBOTEQ,"!PR 2 %06s_!PR 1 -%06s\r",impulse_string,impulse_string);*/
		
		 //a tester si sa marche
			fprintf(ROBOTEQ,"!S 1 %u_!S 2 %u \r",vitesse,vitesse);
			fprintf(ROBOTEQ,"!PR 1 %u_!PR 2 %u \r",-impulse,impulse);
}
//----------------------------------------------------------------------------------------------------
//  	Nom    :	    tourne sur plce
// 		Auteur :		BORR
//		Date    :	    28.1.16
//  	Statut  :    	fomctionnel
//  	Futur   :     	n.a.
//----------------------------------------------------------------------------------------------------
//  Description : effectue un virage sur place grÃ¢ce Ã  l'angle donnÃ©
//	ParamÃ¨tre(s): angle,vitesse
//  RÃ©sultat :    / 

//  Constante(s): diametre_roue, Entraxe_roue et impulsion_roue
//----------------------------------------------------------------------------------------------------
void __Tourne_sur_place(signed int32 angle,unsigned int32 vitesse)
{
		_Tim3On= 0;
		signed int32 impulsion_tot;
		// si sa marche ajouter
			signed int32 impulse_g = 0;
			signed int32 impulse_d = 0;	

		char vitesse_string[5];	
	//	char impulsion_tot_string[6];
	//	
		sprintf(vitesse_string,"%Lu",vitesse);

//---------------------------------------------------------------------//
//				        	calcul pas simplifiÃ©
//---------------------------------------------------------------------//
// calcul du nombre d'impulsion nÃ©cessaire Ã  effectuer l'angle demander
//---------------------------------------------------------------------////		
//		distance_tot = Entre_axe_roue * Pi * (angle/360);
//		distance_tour_roue =  diametre_roue * Pi;
//		nbre_tour = distance_tot/distance_tour_roue; 
//		impulsion_tot =  2nbre_tour* impulsion_tour; 		
//---------------------------------------------------------------------//
 
//calcul simplifiÃ©
		
		impulsion_tot = (impulsion_tour * angle * Entraxe_roue/ (diametre_roue * 360));
		
		
		
		
	/*	sprintf(impulsion_tot_string,"%Ld",impulsion_tot);

		// RÃ©glage vitesse moteur 
		fprintf(ROBOTEQ,"!S 1 %05s_!S 2 %05s \r",vitesse_string,vitesse_string);
		// tourne sur place 
		fprintf(ROBOTEQ,"!PR 1 %06s_!PR 2 %06s \r",impulsion_tot_string,impulsion_tot_string);*/
// si sa marche ajouter et enlever le reste
		impulse_d = impulsion_tot;
		impulse_g = impulsion_tot;

		fprintf(ROBOTEQ,"!S 1 %05s_!S 2 %05s \r",vitesse_string,vitesse_string);
		fprintf(ROBOTEQ,"!PR 1 %d_!PR 2 %d \r",impulse_g,impulse_d);



}

//----------------------------------------------------------------------------------------------------
//  	Nom    :	    tourne sur plce
// 		Auteur :		BORR
//		Date    :	    28.1.16
//  	Statut  :    	fomctionnel
//  	Futur   :     	n.a.
//----------------------------------------------------------------------------------------------------
//  Description : effectue un virage sur place grÃ¢ce Ã  l'angle donnÃ©
//	ParamÃ¨tre(s): angle,vitesse
//  RÃ©sultat :    / 

//  Constante(s): diametre_roue, Entraxe_roue et impulsion_roue
//----------------------------------------------------------------------------------------------------
void __Tourne_sur_placeP(signed int32 angle,unsigned int32 vitesse)
{
		_Tim3On= 0;
		signed int32 impulsion_tot;
		// si sa marche ajouter
			signed int32 impulse_g = 0;
			signed int32 impulse_d = 0;	

		char vitesse_string[5];	
	//	char impulsion_tot_string[6];
	//	
		sprintf(vitesse_string,"%Lu",vitesse);

//---------------------------------------------------------------------//
//				        	calcul pas simplifiÃ©
//---------------------------------------------------------------------//
// calcul du nombre d'impulsion nÃ©cessaire Ã  effectuer l'angle demander
//---------------------------------------------------------------------////		
//		distance_tot = Entre_axe_roue * Pi * (angle/360);
//		distance_tour_roue =  diametre_roue * Pi;
//		nbre_tour = distance_tot/distance_tour_roue; 
//		impulsion_tot =  2nbre_tour* impulsion_tour; 		
//---------------------------------------------------------------------//
 
//calcul simplifiÃ©
		
		impulsion_tot = (impulsion_tour * angle * Entraxe_roue/ (diametre_roue * 360));
		
		
		
		
	/*	sprintf(impulsion_tot_string,"%Ld",impulsion_tot);

		// RÃ©glage vitesse moteur 
		fprintf(ROBOTEQ,"!S 1 %05s_!S 2 %05s \r",vitesse_string,vitesse_string);
		// tourne sur place 
		fprintf(ROBOTEQ,"!PR 1 %06s_!PR 2 %06s \r",impulsion_tot_string,impulsion_tot_string);*/
// si sa marche ajouter et enlever le reste
		impulse_d = impulsion_tot;
		impulse_g = impulsion_tot;

		fprintf(ROBOTEQ,"!S 1 %05s_!S 2 %05s \r",vitesse_string,vitesse_string);
		fprintf(ROBOTEQ,"!P 1 %d_!P 2 %d \r",impulse_g,impulse_d);



}

//=================================================================================================================================================================================================
// Fonction 	: driver_Servo																															
//=================================================================================================================================================================================================
//	Développé par:		: Favre Lenny
//						:     												
//  Date				: 16.03.2017															
//  Date de modif.		: 															
//-------------------------------------------------------------------------------------------------------------------------------------------------------------																
// Description 	:  	Permet d'envoyer une position à un servo précis
// paramètres 	:  	Adresse_driver 	= Adresse I2C du driver	(int8)
//					Ordre		 	= ordre à effectuer (de 0:1ms à 100: 2ms) (int16)
//					Servo			= Servo à programmer (1 à 4) (int8)
// retourne 	:  	Retourne le status du driver
//					0 -> Not ready  (le slave ne répond pas)
//					1 -> OK : ordre transmis
//===================================================================================================================================================================================================
unsigned int8 driver_Servo(unsigned int8 Adresse_driver, unsigned int16 Ordre, unsigned  Servo)
{
	i2c_start();
	if(!i2c_write(Adresse_driver))			//ADRESSE
	{
		i2c_write(Servo);
		i2c_write(Ordre%201);
	}
	else
	{ 
		i2c_stop();
		return 0;
	}
	i2c_stop();	
	return 1;
}

//=================================================================================================================================================================================================
// Fonction 	: driver_Servo_Angle																															
//=================================================================================================================================================================================================
//	Développé par:		: Favre Lenny
//						:     												
//  Date				: 16.03.2017															
//  Date de modif.		: 															
//-------------------------------------------------------------------------------------------------------------------------------------------------------------																
// Description 	:  	Permet d'envoyer un angle à un servo précis
// paramètres 	:  	Adresse_driver 	= Adresse I2C du driver	(int8)
//					AngleMax		= Angle maximum du servomoteur (ex. : 90°, 180°,...)(int16)
//					Angle		 	= Angle sur lequel se positionner (de 0 à AngleMax) (int16)
//					Servo			= Servo à programmer (1 à 4) (int8)
// retourne 	:  	Retourne le status du driver
//					0 -> Not ready  (le slave ne répond pas)
//					1 -> OK : ordre transmis
//===================================================================================================================================================================================================
unsigned int8 driver_Servo_Angle(unsigned int8 Adresse_driver, unsigned int16 AngleMax, unsigned int16 Angle, unsigned int8 Servo)
{
	i2c_start();
	if(!i2c_write(Adresse_driver)&&AngleMax!=0)			//ADRESSE
	{
		i2c_write(Servo);
		i2c_write((int16)(Angle*200/AngleMax));
	}
	else
	{ 
		i2c_stop();
		return 0;
	}
	i2c_stop();	
	return 1;
}

//=================================================================================================================================================================================================
// Fonction    : Go_Turbine                                                                                             
//=================================================================================================================================================================================================
//   Développé par:      : Favre Lenny
//                  :                                         
//  Date            : 23.03.2017                                             
//  Date de modif.      :                                              
//-------------------------------------------------------------------------------------------------------------------------------------------------------------                                                
// Description    :     Permet d'allumer la turbine
// paramètres    :     Adresse_driver    = Adresse I2C du driver   (int8)
//               Servo         = Servo à programmer (1 à 4) (int8)
// retourne    :     Retourne le status du driver
//               0 -> Not ready  (le slave ne répond pas)
//               1 -> OK : ordre transmis
//===================================================================================================================================================================================================
unsigned int8 Go_Turbine(unsigned int8 Adresse_driver, unsigned  Servo)
{
   i2c_start();
   if(!i2c_write(Adresse_driver))         //ADRESSE
   {
      i2c_write(Servo);
      i2c_write(100);
   }
   else
   { 
      i2c_stop();
      return 0;
   }
   i2c_stop();   
   return 1;
}

//=================================================================================================================================================================================================
// Fonction    : Stop_Turbine                                                                                             
//=================================================================================================================================================================================================
//   Développé par:      : Favre Lenny
//                  :                                         
//  Date            : 23.03.2017                                             
//  Date de modif.      :                                              
//-------------------------------------------------------------------------------------------------------------------------------------------------------------                                                
// Description    :     Permet d'éteindre la turbine
// paramètres    :     Adresse_driver    = Adresse I2C du driver   (int8)
//               Servo         = Servo à programmer (1 à 4) (int8)
// retourne    :     Retourne le status du driver
//               0 -> Not ready  (le slave ne répond pas)
//               1 -> OK : ordre transmis
//===================================================================================================================================================================================================
unsigned int8 Stop_Turbine(unsigned int8 Adresse_driver, unsigned  Servo)
{
   i2c_start();
   if(!i2c_write(Adresse_driver))         //ADRESSE
   {
      i2c_write(Servo);
      i2c_write(0);
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