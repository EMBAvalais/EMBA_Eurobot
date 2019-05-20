/*====================================================================================================
===																									==
===											EMVs - EUROBOT	  										==
===											--------------											==
======================================================================================================
===	 Auteur				: Amand Axel     					  										==
===  Date				: 30.04.2015    															==
===  Nom du programme 	: TestCartePrinc.mcp														==
===  Version 			: V1.0																		==
======================================================================================================
=== Description :																					==
=== Contrôle du robor secondaire.																	==
====================================================================================================*/

#ifndef ___Functions
#define ___Functions
// Définit la vitesse du quartz (prendre en compte si PLL employée)

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
void __Afficheur_7segments(int8 nombre,int1 ToBlank=0);
//----------------------------------------------------------------------------------------------------
//  Nom: 	    Recule
//	Auteur :	BORR
//	Date:	    28.1.16
//  Statut :    fonctionnel
//  Futur :     n.a.
//----------------------------------------------------------------------------------------------------
//  Description : fait reculer le robot à une vitesse voulue et à un nbre d'impulsion voulue
//	Paramètre(s): nbre d'impulsion, vitesse , nombre de caractère
//  Résultat :    / 
//----------------------------------------------------------------------------------------------------
void __Recule(unsigned int32 impulse,unsigned int32 vitesse);
//----------------------------------------------------------------------------------------------------
//  Nom: 	    Avance
//	Auteur :	BORR
//	Date:	    28.1.16
//  Statut :    fonctionnel
//  Futur :     n.a.
//----------------------------------------------------------------------------------------------------
//  Description : fait avancer le robot à une vitesse voulue et à un nbre d'impulsion voulue
//	Paramètre(s): nbre d'impulsion, vitesse , nombre de caractère
//  Résultat :    / 
//----------------------------------------------------------------------------------------------------
void __Avance(unsigned int32 impulse,unsigned int32 vitesse);
//----------------------------------------------------------------------------------------------------
//  	Nom    :	    	tourne sur plce
// 	Auteur :		BORR
//	Date    :	    	28.1.16
//  	Statut  :    	pas encore testé sur le terrain
//  	Futur   :     	n.a.
//----------------------------------------------------------------------------------------------------
//  Description : effectue un virage sur place grâce à l'angle donné
//	Paramètre(s): angle,vitesse
//  Résultat :    / 

//  Constante(s): diametre_roue, Entraxe_roue et impulsion_roue
//----------------------------------------------------------------------------------------------------
void __Tourne_sur_place(signed int32 angle,unsigned int32 vitesse);

void __Tourne_sur_placeP(signed int32 angle,unsigned int32 vitesse);

void __TimeOut(void);	

void __Detected(void);
//----------------------------------------------------------------------------------------------------
//  Nom: 	    Check_commande_atteint
//	Auteur :	BORREM
//	Date:	    18.2.15
//  Statut :    Fonctionnel
//----------------------------------------------------------------------------------------------------
//  Description : Check si la commande donné aux moteurs a été finie

void __Init_dsPIC(void);
//----------------------------------------------------------------------------------------------------
//  Nom: 	    read_d_moteur
//	Auteur :	BORREM
//	Date:	    20.4.16
//  Statut :    -
// 	on retourne 1 si erreur et 0 si pas d'erreur
//----------------------------------------------------------------------------------------------------
int8 read_d_moteur(int addresse_driver);

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
void Roboteq_test(void);

//----------------------------------------------------------------------------------------------------
//  Nom: 	    __CheckVitMoteur
//	Auteur :	FAVLEN
//	Date:	    22.05.17
//  Statut :    Ok
//----------------------------------------------------------------------------------------------------
//  Description : Check si les moteurs sont arrêtés
//	Paramètre(s): /
//  Résultat :    /
//----------------------------------------------------------------------------------------------------
void __CheckVitMoteur(void);

#include "Com_balises.c"
#include "Init.c"
#include "CommRoboteQ.c"
#include "Functions.c"


#endif