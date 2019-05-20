
/*====================================================================================================
===																									==
===											EMVs - EUROBOT	  										==
===											--------------											==
======================================================================================================
===	 Auteur				: Borgeat Remy    					  										==
===  Date				: 30.1.2017    															==
===  Nom du programme 	: CartePrinc.mcp														==
===  Version 			: V1.0																		==
======================================================================================================
=== Description :																					==
=== Ce fichier gere les deplacement du robot														==
====================================================================================================*/

#ifndef ___Depl_c
#define ___Depl_c

//*********************************************************************************************************************
// arrondi_float
//
// Cette fonction permet d'arrondir un nombre decimal en entier relatif
// 12.7863 => 13
// 14.45621 => 14 
//
// Developpe par : Louis Mayencourt
// Date :          01.12.2010 
// Revision :		V1.0
//
// parametres  : nombre a convertir 
// return      : nombre converti
//
//*********************************************************************************************************************
signed int32 arrondi_float_signed(float nombre)
{
	float chiffres_apres_virgule;		// contient les chiffres apres la virgule du float a convertir 

// prend les chiffres apres la virgule
	chiffres_apres_virgule = nombre-floor(nombre);

// test si il faut arrondir vers le bas ou le haut
	if(chiffres_apres_virgule>=0.5) return( (signed int32)(ceil(nombre)));
	else return( (signed int32)(floor(nombre)));
}

void __Affichage_Erreur(int8 nombre)
{
	No_erreur = nombre; 
	flag_error = 1; 
		// Quitte la fonction
	return;
}

//----------------------------------------------------------------------------------------------------
//  Nom: 	    Check_commande_atteint
//	Auteur :	BORREM
//	Date:	    18.2.15
//  Statut :    fonctionnel
//----------------------------------------------------------------------------------------------------
//  Description : Check si la commande donné aux moteurs a été finie
void __Check_commande_atteint(void)
{
	int1 comm_atteinte_m1,comm_atteinte_m2 = 0;
	fprintf(ROBOTEQ,"?DR\r");
//il renvoie DR=x:x
	delay_ms(20);
//on vérifie que le premier caractère n'indique pas une répétiotion de commande
	if(RoboteQ_receiveBuffer[0] != '!' && RoboteQ_receiveBuffer[0] != '?' && RoboteQ_receiveBuffer[0] != '~' && RoboteQ_receiveBuffer[0] != '^' && RoboteQ_receiveBuffer[0] != '#')
	{
		comm_atteinte_m1 = RoboteQ_receiveBuffer[3]; // affectation du premier x dans la variable
		comm_atteinte_m2 = RoboteQ_receiveBuffer[5]; // affectation du deuxième x dans la variable
	}
	if(comm_atteinte_m1 == 1 && comm_atteinte_m2== 1) // si commande des deux moteurs dini 
	{
		flag_depl_ok =1 ; // on peut passer au déplacement suivant
	}
}
/**
* \fn void __Get_amp(int channel)
* \brief Recupere la valeur du courant dans les moteurs
*
* \author Borgeat Remy
* \version 1.0
* \date 9.6.2017
*
* \param[in] channel--> 1 moteur 1, 2  moteur 2 
* \return Ne retourne rien
*/
float64 __Get_amp(int channel)
{
	unsigned int16 ampere = 0;
	unsigned int8 i = 2;
	if(channel == 1)
	{
		fprintf(ROBOTEQ,"?A 1\r");
	}
	else
	{
		fprintf(ROBOTEQ,"?A 2\r");
	} 
	//il renvoie DR=x:x
	delay_ms(10);
	//on verifie que le premier caractere n'indique pas une répétiotion de commande
	if(RoboteQ_receiveBuffer[0] == 'A')
	{
		while(RoboteQ_receiveBuffer[i]!= '\r')
		{
			if(RoboteQ_receiveBuffer[i]!=0x2D) // 0x2D -> signe '-' en ascii, courant neg -> on prend en abs
			{
				ampere  *= 10;
				ampere  += RoboteQ_receiveBuffer[i]-0x30;
			}
			i++; 
		}
		return(ampere);
	}
	else
	{
		return(0);
	}
}
/**
* \fn void __Get_enco_value(int1 start_end)
* \brief Recupere la valeur des encodeurs du robot
*
* \author Borgeat Remy
* \version 1.0
* \date 9.6.2017
*
* \param[in] 1 -> enco au depart, 0 -> enco a la fin
* \return Ne retourne rien
*/
void __Get_enco_value(int1 start_end)
{
	unsigned int8 i = 2;
	int1 flag_inverted = 0;
	if(start_end) // si recuperation enco au depart --> on clear tout
	{
		value_enco_g_start = 0;
		value_enco_d_start = 0;
		value_enco_g_end   = 0;
		value_enco_d_end   = 0;
	}

	fprintf(ROBOTEQ,"?C\r"); // on demande la valeur des encodeurs
	delay_ms(20);
	
	if(RoboteQ_receiveBuffer[0] == 'C') // si on re�oit C=xxxx:xxxx
	{
		while(RoboteQ_receiveBuffer[i]!= ':')
		{
			if(start_end)
			{
				if(RoboteQ_receiveBuffer[i]==0x2D) // 0x2D -> signe '-' en ascii
				{
					flag_inverted = 1;
				}
				else
				{
					value_enco_g_start *= 10;
					value_enco_g_start += RoboteQ_receiveBuffer[i]-0x30; // on met les caractere dans la variable
				}				
			}
			else
			{
				if(RoboteQ_receiveBuffer[i]==0x2D) // 0x2D -> signe '-' en ascii
				{
					flag_inverted = 1;
				}
				else
				{
					value_enco_g_end *= 10;
					value_enco_g_end += RoboteQ_receiveBuffer[i]-0x30; // on met les caractere dans la variable
				}
			}
			i++;
		}
		if(flag_inverted) //si l'on a recu un nbre d'impulses negatifs
		{
			if(start_end) 
			{
				value_enco_g_start = 0-value_enco_g_start; // on inverse tout
				flag_inverted = 0;
			}
			else
			{
				value_enco_g_end = 0-value_enco_g_end;	// on inverse tout
				flag_inverted = 0;
			}
		}
		i++;
		while(RoboteQ_receiveBuffer[i]!='\r')//tant que la transmission n'est pas fini
		{
			if(start_end)
			{
				if(RoboteQ_receiveBuffer[i]==0x2D)// 0x2D -> signe '-' en ascii
				{
					flag_inverted = 1;
				}
				else
				{
					value_enco_d_start *= 10;
					value_enco_d_start += RoboteQ_receiveBuffer[i]-0x30;
				}
			}
			else
			{
				if(RoboteQ_receiveBuffer[i]==0x2D)// 0x2D -> signe '-' en ascii
				{
					flag_inverted = 1;
				}
				else
				{
					value_enco_d_end *= 10;
					value_enco_d_end += RoboteQ_receiveBuffer[i]-0x30;			
				}
			}
			i++;		
		}
		if(flag_inverted)//si l'on a recu un nbre d'impulses negatifs
		{
			if(start_end)
			{
				value_enco_d_start = 0-value_enco_d_start;// on inverse tout
				flag_inverted = 0;
			}
			else
			{
				value_enco_d_end = 0-value_enco_d_end;// on inverse tout
				flag_inverted = 0;
			}
		}
	}
	if(!start_end)
	{
		Dist_Do = ((value_enco_g_end-value_enco_g_start)+(value_enco_d_end-value_enco_d_start))/2; // calcul distance parcourue
	}
}
/**
* \fn void __Actual_pos(void)
* \brief Actualise la position xy du robot s'il doit switcher d'objectifs
*
* \author Borgeat Remy
* \version 1.0
* \date 9.6.2017
*
* \param[in] -
* \return Ne retourne rien
*/
void __actual_pos(void)
{
	signed int32 Dist_Do_mm = 0;
	signed int32 dx = 0;
	signed int32 dy = 0;
	__Get_enco_value(0); // recuperation delta x,y
							
	Dist_Do_mm = (signed int32)(Dist_Do/(COEFF_D/10));
	///////////////////////// Calcul dx,dy ////////////////////////////
	if(0 <= Orient && Orient <= PI)//entre 0 et 180deg
	{
		dx =  (signed int16)(cos(Orient) * Dist_Do_mm);
		dy =  (signed int16)(sin(Orient) * Dist_Do_mm);	
	}
	else if(( (Orient>PI) && ((3*PI)/2 >= Orient)) || (Orient <= (-PI/2) && Orient > -PI))//180 et 270deg
	{
		Dist_Do_mm = 0-Dist_Do_mm;
		dx = (signed int16)(sin(3*(PI/2)-Orient) * Dist_Do_mm);
		dy = (signed int16)(cos(3*(PI/2)-Orient) * Dist_Do_mm);
	}
	else if(((Orient>(3*PI/2)) && (Orient < (2*PI))) || (Orient < 0 && Orient > (-PI/2)))//270deg et 360deg
	{
		Dist_Do_mm = 0-Dist_Do_mm; 
		dx = (signed int16)(sin(-(PI/2)-Orient) * Dist_Do_mm);
		dy = (signed int16)(cos(-(PI/2)-Orient) * Dist_Do_mm);
	}
	Pos_x = (signed int16)(Pos_x - dx); //mise a jour pos x
	Pos_y = (signed int16)(Pos_y - dy);	//mise a jour pos y
}
/*
	Borgeat R�my

	20.2.2017

	Initialise la postion de d�part du robot.
	Gere le cote duquel se trouve le robot
*/
void __Init_pos(void)
{
	Pos_x = read_eeprom(800);
	Pos_y = read_eeprom(802);
	Orient_deg = read_eeprom(804);

	//si on est de l'autre cote du terrain
	if(TEAM)
	{
		Pos_x = TableWidth-Pos_x;
		if(Orient_deg<=180)Orient_deg=180-Orient_deg ;
		else Orient_deg = 540 - Orient_deg ;
	}		
	Orient = (float64)(Orient_deg*PI/180);
}

/**
* \fn void __Action_Writting(unsigned int8 _Command)
* \brief Demande d'écriture, entre 0x00 et 0x79.
*
* \author Barman Corentin / rev. Amand Axel
* \version 2.0
* \date 19.11.2015
*
* \param[in] _Command Choisit la commande à effectuer
* \return Ne retourne rien
*/
void __DeplToDo(unsigned int8 _Command)
{
	switch(_Command)
	{
		// !!! En ajoutant des types de déplacement,
		//		pensez à les gérer dans __LoadObj() tout en bas du fichier.
		//		Comme le X est par exemple utiliser pour donner un angle,
		//		si comme un dépl. PàP vous faîtes TailleTable - X ....
		//		Autant dire que le robot va faire n'importe quoi ^^
		case 0 :
			__Turn((signed int16) oXp);			
			break;
		case 1 :
			__PaP(oXp, oYp);
			break;
		case 2 :
			__Progress(oXp, oYp); //se d�place d'une certaine distance, jusqu'a ce qu'on tape dans un bord, ou que l'ordre soit fini
			break;
		case 3 :
			__Nothing();
			break;
		default:
			__Affichage_erreur(4);
			break;
	}

	// Quitte la fonction
	return;
	
	
}


void __Stop()
{
		
	/////////////////// effacer l'ordre en cours  /////////////////// 
   	fprintf(ROBOTEQ,"^MMOD 1 0_^MMOD 2 0\r"); //passage en open loop speed
   	delay_ms(10);
   	fprintf(ROBOTEQ,"^MMOD 1 3_^MMOD 2 3\r"); //passage en closed loop count postion
   	
   	Etat_rob = Wait_end;
}   	
/**
* \fn void __Turn(signed int16 _Ang)
* \brief Tourne sur place jusqu'a l'angle donne.
*
* \author Borgeat Remy
* \version 1.0
* \date 9.6.2017
*
* \param[in] Angle d'arrive 
* \return Ne retourne rien
*/
void __Turn(signed int16 _Ang)
{
	float64 AngToDo = 0;			
	signed int32 AngToDo_int = 0;	//ang a effectuer en nombre d'impulses
	signed int32 impulse_g = 0; 	//impulse mot g
	signed int32 impulse_d = 0;		//impulse mot d
	float64 temporaire = 0;

	// Convertit la valeur de l'angle en radian
	AngToDo = (_Ang * CONV_DEG_RAD) - Orient ;

	if(oCoteTourn==2&&AngToDo>0) // on force le robot a tourner sur la droite
	{
		AngToDo += -2 * PI; //on tourne sur la gauche
	}	
	else if(oCoteTourn==1&&AngToDo<0) // on force le robot à tourner sur la gauche 	
	{
		AngToDo += 2 * PI;//On tourne sur la droite	
	}
	
	if(AngToDo > PI && oCoteTourn==0) // on a plus de 180°
	{
		AngToDo -= 2*PI; // on tourne ds l'autre sens
	}
	else if(AngToDo < -PI  && oCoteTourn==0) // si on moins que -180°  
	{
		AngToDo += 2 * PI; // on tourne ds l'autre sens
	}	

	if(AngToDo>-0.0001 && AngToDo<0.0001) AngToDo = 0;// mise a 0 de l'angle, car il se peut que des erreus de calculs viennent 
	temporaire = (float64)((AngToDo * (ENTRAXE_ROUESFOLLES/DIAM_ENCO) * IMPULSES_ENCO * 2 / PI )) ; // on calcul le nbre d'impulse nécessaire pour la rotation
	AngToDo_int = (signed int32)(arrondi_float_signed(temporaire));	
	// on envoie les donnee au ROBOTEQ
	fprintf(ROBOTEQ,"!S 1 %04u_!S 2 %04u \r",oVitMax,oVitMax);
	
	//balise 
	balise_on = 0;
	
	impulse_g = AngToDo_int;
	impulse_d = 0-AngToDo_int;
	fprintf(ROBOTEQ,"!PR 1 %d_!PR 2 %d \r",impulse_g,impulse_d);
	
	Depl_send = 1;
	Orient = (float64)(_Ang * CONV_DEG_RAD); // mise � jour de l'angle
}
/**
* \fn void __PaP(signed int16 _X, signed int16 _Y)
* \brief Depl Pap du robot.
*		Le deplacement se fait tel que :
*			- Rotation vers le point a� atteindre
*			- Deplacement ligne droite
* \author Borgeat Remy
* \version 1.0
* \date 9.6.2017
*
* \param[in] coordonee x,y de la pos d'arrivee
* \return Ne retourne rien
*/
void __PaP(signed int16 _X, signed int16 _Y)
{

	float64	dx,dy,distToDo = 0;	
	signed int32 distToDo_int = 0;	//dist a effectuer
	signed int32 AngToDo_int = 0;	//ang a effectuer
	signed int32 impulse_g = 0;	 	//impulse mot gauche
	signed int32 impulse_d = 0;		//impulse mot droite
	static int1 etat_deplacement = 0;
	float64 AngToDo = 0;
	float64 temporaire = 0;
	
	
	dx = (_X - Pos_x) * (COEFF_D/10); //calcul deplacment en x et transformation en pas
	dy = (_Y - Pos_Y) * (COEFF_D/10); //calcul deplacment en y et transformation en pas
	distToDo = sqrt((dx*dx)+(dy*dy)); //calcul de la distance
	distToDo_int = distToDo ;

	switch(etat_deplacement)
	{
		case 0: // gestion de l'angle
		
			///////////////////////////////////////////////
			//////////Calcul de l'angle////////////////////
			///////////////////////////////////////////////
				if(dx >= 0) // 1er et 4eme quadrant
				{
					AngToDo = asin(dy/distToDo) - Orient;	
				}
				
				else if(dx <= 0 && dy > 0)//2eme quandrant
				{
					AngToDo = acos(dx/distToDo) - Orient;
				}
				
				else if(dx < 0 && dy <= 0)//3eme quadrant
				{
					AngToDo = asin(abs(dy)/distToDo) + PI - Orient;	
				}
				
			////////////////////////////////////////////////
			////////////Gestion de l'angle//////////////////
			////////////////////////////////////////////////
				if(oAvAr)
				{
					AngToDo += PI;	
					if(AngToDo > PI) // si on a plus de 180°
					{
						AngToDo -= 2*PI; // on tourne ds l'autre sens
					}
					else if(AngToDo < -PI) // si on moins que -180°  
					{
						AngToDo += 2 * PI; // on tourne ds l'autre sens
					}
				}					
				if(oCoteTourn==2&&AngToDo>0) // on force le robot a tourner sur la droite
				{
					AngToDo += -2 * PI; //on tourne sur la gauche
				}	
				
				else if(oCoteTourn==1&&AngToDo<0) // on force le robot à tourner sur la gauche 	
				{
					AngToDo += 2 * PI;//On tourne sur la droite	
				}				
				
				else if(oCoteTourn==0)
				{
					if(AngToDo > PI) // si on a plus de 180°
					{
						AngToDo -= 2*PI; // on tourne ds l'autre sens
					}
					else if(AngToDo < -PI) // si on moins que -180°  
					{
						AngToDo += 2 * PI; // on tourne ds l'autre sens
					}	
				}
				
			if(AngToDo>-0.0001 && AngToDo<0.0001) AngToDo = 0;// mise a 0 de l'angle, car il se peut que des erreus de calculs viennent 
			temporaire = (float64)((AngToDo * (ENTRAXE_ROUESFOLLES/DIAM_ENCO) * IMPULSES_ENCO * 2 / PI )) ; // on calcul le nbre d'impulse nécessaire pour la rotation
			AngToDo_int = (signed int32)(arrondi_float_signed(temporaire));
			///////////////////////////////////////////////////
			/////////////////Envoi de l'angle au Roboteq///////
			///////////////////////////////////////////////////
			if(AngToDo_int != 0)
			{
				//balise
				balise_on = 0; //desactive la balise sur une rotation
				
				fprintf(ROBOTEQ,"!S 1 100_!S 2 100\r");
				// on envoie les donnee au ROBOTEQ
							
				impulse_g = AngToDo_int;
				impulse_d = 0-AngToDo_int;
				fprintf(ROBOTEQ,"!PR 1 %d_!PR 2 %d \r",impulse_g,impulse_d);
				
				etat_deplacement  = 1;	
			}					
			else
			{			
				fprintf(ROBOTEQ,"!PR 1 1_!PR 2 1\r");
				etat_deplacement = 1;
			}	
			Orient = (float64)(Orient + AngToDo);	
			break;
		case 1 : // gestion de la distance
		
			if(distToDo!=0)//si on doit faire avancer le robot
			{		
				__Check_commande_atteint(); 
				__Get_enco_value(1);	//recupere la valeur des encos du pt de depart
				
				if(flag_depl_ok == 1)//On attend que le deplacment precedent soit fini(angle)
				{
					fprintf(ROBOTEQ,"!S 1 %04u_!S 2 %04u \r",oVitMax,oVitMax);
					
					flag_depl_ok = 0;
					
					if(oAvAr)//si on recule
					{		
						Balise_set_plage(1);//plage � l'arriere du robot						
						distToDo_int = 0 - distToDo_int; //impulse negative --> recule
					}
					else 
					{
						Balise_set_plage(0);//plage � l'avant du robot
					}
					//balise	
					balise_on = 1; // active la balise sur un depl
					////////////////////////////////////////////////////
					////////////envoie au Roobreq///////////////////////
					///////////////////////////////////////////////////
	
					fprintf(ROBOTEQ,"!PR 1 %07d_!PR 2 %07d \r",-distToDo_int,distToDo_int);						
					Depl_send = 1;							//indique que l'on a fini d'envoyer les ordres du déplacment
					etat_deplacement = 0;
					Dist_x = (signed int16)(_X - Pos_x);	//mise a jour pos x
					Dist_y = (signed int16)(_Y - Pos_y); 	//mise a jour pos y
				}	
			}
			else
			{				
				Depl_send = 1;
				etat_deplacement = 0;
			}
		break;
	}
	// Quitte la fonction
	return;
}
/*
	/**
* \fn void __Progress(int16 _X, int16 _Y)
* \brief Fonction utile pour s'etalonner dans un bord 
* \		 s'arrete en detectant une limite de courant 
* \author Borgeat Remy
* \version 1.0
* \date 23.2.2017
*
* \return Ne retourne rien
*/
void __Progress(int16 _X, int16 _Y)
{
	static unsigned int8 etat_depl;
	float64 amp = 0;				//courant dans le moteur 1
	float64 amp2 = 0;				//courant dans le moteur 2 
	static int1 m1_stop,m2_stop;	//arret moteur 1 et arret moteur 2

	float64 Dist = 0; 

	switch(etat_depl)
	{
		case 0:
		 	Dist = sqrt(((_X - Pos_x) * (_X - Pos_x)) + ((_Y - Pos_y) * (_Y - Pos_y))) + DIST_SECU_PROGRESS; // calcul distance de depl 
		 	Dist *= (COEFF_D/10);	//conversion mm en pas
			flag_depl_ok = 0;
			
			//balise	
			balise_on = 1; // active la balise sur un depl				
			
			if(oAvAr)//si on recule
			{	
				Balise_set_plage(1);//plage � l'arriere du robot					
				Dist = 0 - Dist; 	// on inverse la distance
			}
			else 
			{
				Balise_set_plage(0);//plage � l'avant du robot
			}
			////////////////////////////////////////////////////
			////////////envoie au Roobreq///////////////////////
			///////////////////////////////////////////////////
			//__Get_enco_value(1);
			
			fprintf(ROBOTEQ,"!S 1 %04u_!S 2 %04u \r",oVitMax,oVitMax);	
			fprintf(ROBOTEQ,"!PR 1 %d_!PR 2 %d \r",-Dist,-Dist);		
			
			etat_depl = 1;
			delay_ms(20);
			
			break;
		case 1: 
			amp = (float64)(__Get_amp(1));	//recup du courant du mot 1
			amp2 =(float64)(__Get_amp(2));	//recup du courant du mot 2
			amp /= 10;					  	// roboteq envoie 15A pour 1,5A --> /10
			amp2 /= 10;					 	// roboteq envoie 15A pour 1,5A --> /10
			if(amp >= amp_limit)		 	//Seuil courant ds mot 1 detecte 
			{
				fprintf(ROBOTEQ,"!MS 1\r");	//Stop le mot 1 
				m1_stop = 1;
			}
			if(amp2 >= amp_limit)			//Seuil courant ds mot 2 detecte
			{
				fprintf(ROBOTEQ,"!MS 2\r");	//Stop le mot 2
				m2_stop = 1;
			}	
			if(m1_stop==1 && m2_stop==1)	//les 2 moteurs stopes
			{

				fprintf(ROBOTEQ,"^MMOD 1 0_^MMOD 2 0\r"); 	//passage en open loop speed
				delay_ms(10);
				fprintf(ROBOTEQ,"^MMOD 1 3_^MMOD 2 3\r"); 	//passage en closed loop count postion
								
				Depl_send = 1; 							  	//fin du d�placment
				etat_depl = 0;

				fprintf(ROBOTEQ,"!PR 1 1_!PR 2 1\r");	  
				
				Dist_x = (signed int16)(_X-Pos_x);			//mise a jour pos x
				Dist_y = (signed int16)(_Y-Pos_y);			//mise a jour pos y
			}
			else // si pos atteinte
			{					
				__Check_commande_atteint(); 
				if(flag_depl_ok == 1) //On attend que le deplacment precedent soit fini(angle)
				{
					Dist_x =  cos(Orient) * Dist;			//mise a jour pos x
					Dist_y =  sin(Orient) * Dist;			//mise a jour pos y

					//remise a zero des varaibles
					flag_depl_ok = 0;
					Depl_send = 1;
					m1_stop = 0;
					m2_stop = 0;								
					etat_depl = 0;			
				}
			}
			break;
	}
}
/**
* \fn void __Nothing(void)
* \brief Passe l'objectif
*
* \author Borgeat Remy
* \version 1.0
* \date 9.6.2017
*
* \return Ne retourne rien
*/

void __Nothing(void)
{
	flag_depl_ok = 1; 
	Depl_send=1;
	balise_on = 0;
	// Quitte la fonction
	return;
}
/**
* \fn void __LoadObj(unsigned int8 _Obj)
* \brief Charge le prochain objectif
*
* \author Borgeat Remy
* \version 2.0
* \date 9.6.2017
*
* \param [in] _Obj Numero de l'objectif desire
* \return Ne retourne rien
*/
void __LoadObj(unsigned int16 _Obj,unsigned int16 pts)
{	
	// Enregistre Xp, en [mm]
	oXp=TabObjectifs[_Obj][pts][0];

	// Enregistre Yp, en [mm]
	oYp=TabObjectifs[_Obj][pts][1];

	// Enregistre le type de deplacement, en [nbre]
	oType=TabObjectifs[_Obj][pts][2];

	// Enregistre si avance ou recule
	oAvAr=TabObjectifs[_Obj][pts][3];

	// Enregistre le cote duquel tourner
	oCoteTourn=TabObjectifs[_Obj][pts][4];

	// Enregistre la vitesse maximum, en [mm/s] (en [0/000] pour RoboteQ)
	oVitMax=TabObjectifs[_Obj][pts][5];

	//Enregistre l'action a faire
	Obj_Action = TabObjectifs[_Obj][pts][6];
	
	//Enregistre si le pt est symetrique ou non
	Pt_commun = TabObjectifs[_Obj][pts][7];
	
	//ponderation objectifs
	Ponderation = TabObjectifs[_Obj][pts][8];	
	
	//Objectifs fini ou non
	Obj_end	= TabObjectifs[_Obj][pts][9]; 
	
	//prochain objectifs
	Next_obj = TabObjectifs[_Obj][pts][10];
	
	keep_obj = TabObjectifs[_Obj][pts][11];

	// Switch les donnees selon la base choisie et le mode
	if(TEAM)
	{
		switch(oType)
		{
			case 0 :
				if(oXp<=180)oXp=180-oXp; //gestion angle
				else oXp = 540 - oXp;
				break;
			case 1 :
				// PaP ou retient sur place, calcul automatique de l'angle, inversion oX et oCoteTourn
				// Enregistre Xp, en [mm]
				oXp = TableWidth - oXp;
				// Enregistre le cote duquel tourner
				if(oCoteTourn==1)oCoteTourn=2;
				else if(oCoteTourn==2)oCoteTourn=1;
				else oCoteTourn=0;
	
				break;
			default :
				break;
		}		
	}						
}
#endif

//----------------------------------------------------------------------------------------------------
//  Nom: 	    RDA_isr
//	Auteur :	AMANAX
//	Date:	    27.03.2015
//  Statut :    OK
//----------------------------------------------------------------------------------------------------
//  Description : Interruption pour la rÃ©ception RS232. 
#INT_RDA2
void RDA2_isr(void)
{
	// Pour la lecture du caractÃ¨re reÃ§u
	char myChar;
	// RÃ©ception
	myChar = fgetc(ROBOTEQ);
	// Ajout au buffer et incrÃ©mentation de la longeur du buffer
	RoboteQ_receiveBuffer[RoboteQ_receiveLenght] = myChar;
	RoboteQ_receiveLenght++;
	
	// Si on trouve la fin de la commande
	if(myChar == '\r')
	{
		// On dit qu'on peut lire le buffer de rÃ©ception
		RoboteQ_receiveToProceed = RoboteQ_receiveLenght;
		RoboteQ_receiveLenght=0;
	}

}