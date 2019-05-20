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

#ifndef ___Depl
#define ___Depl


/////////////////  Deplacement Progress  ////////////////////////////////
float64 amp_limit = 1.6;				 // limite de courant depl progress
unsigned int16 DIST_SECU_PROGRESS = 100; // distance de secu sur le deplacement progress en mm
	
/////////////////  Localisation  ////////////////////////////////
signed int16 Dist_x,Dist_y=0;
signed int16 Pos_x = 0; //en mm
signed int16 Pos_y = 0;//en mm
signed int16 Orient_deg = 0;
float64 Dorient = 0; 
float64 Orient = 0;
float64 DIAM_ENCO = 3.48139;	// Diamètre des encodeurs, en [cm]
float64 IMPULSES_ENCO = 5000;	// Nombre d'impulsions de l'encodeur (sans compter le x4 du QEI)
float64 ENTRAXE_ROUESFOLLES = 29.51922;//31.6006	// Entraxe entre les deux centres des roues folles, en [cm]

///////////////// Calcul ////////////////////////////////////////
float64 COEFF_D	= (float64) (IMPULSES_ENCO*4)/(DIAM_ENCO*PI);	// Nbre de pas pour 1 [cm]
float64 CONV_DEG_RAD = (float64) (PI / 180);

////////////////////// Gestion de la reception ////////////////////////////////////
unsigned int8 RoboteQ_receiveToProceed = 0;	// Position maximale pour la rÃ©ception
unsigned int8 RoboteQ_receiveLenght = 0;	// Longeur totale de la donnÃ©e
signed int32 Dist_Do = 0;

///////////////////// Impulsions //////////////////////////////////////////////////
signed int32 value_enco_g_start = 0;		//valeur enco debut deplacment
signed int32 value_enco_d_start = 0;		//valeur enco debut deplacement
signed int32 value_enco_g_end = 0;			//valeur enco fin deplacment
signed int32 value_enco_d_end = 0;			//valeur enco fin deplacement	


/////////////////  Prototype fct  ////////////////////////////////
void __DeplToDo(unsigned int8 _Command);	// 0--> turn, 1--> PaP, 2--> progress, 4-->nothing
void __Turn(signed int16 _Ang);				
void __PaP(int16 _X, int16 _Y);
void __Progress(int16 _X, int16 _Y);
void __Nothing(void);
float64 __Get_amp(int channel);
void __Init_pos(void);
void __LoadObj(unsigned int16 _Obj); // Charge les différents paramètres des objectifs selon lequel est sélectionné
float64 __Conv_Ang_4Quadr(float64 _Ang); // Convertit un angle selon le cadran de l'objectif.
void __Get_enco_value(int1 start_end);
#include "Deplacement/___Depl.c"
#endif