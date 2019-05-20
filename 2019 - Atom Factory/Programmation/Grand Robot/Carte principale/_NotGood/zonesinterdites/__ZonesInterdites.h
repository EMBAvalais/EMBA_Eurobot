/*====================================================================================================
===																									==
===											EMVs - EUROBOT	  										==
===											--------------											==
======================================================================================================
===	 Auteur				: Rithner Aurélien   					  									==
===  Date				: 30.04.2015    															==
===  Nom du programme 	: Zones_interdites.c														==
===  Version 			: V1.0																		==
======================================================================================================
=== Description :																					==
=== Contient les fonctions qui permettent de gérer et d'éviter les zones interdites					==
====================================================================================================*/

#ifndef ___Zones_interdites_h
#define ___Zones_interdites_h



enum{x1, y1, x4, y4};

int x3 = 0;
int y3 = 3;
int x2 = 2;
int y2 = 1;

int checkPath();

void findPath();


//*********************************************************************************************************************
// checkIntersection
//
// Cette fonction permet de calculer la distance entre 2 points
//
// Developpe par : Aurélien Rithner
// Date :          16.10.2018
// Revision :		V1.0
//
// parametres  : coord x,y du point de départ et d'arrivée
// return      : la distance entre les deux points
//
//*********************************************************************************************************************
double getDist(double x1, double y1, double x2, double y2);

//*********************************************************************************************************************
// checkIntersection
//
// Cette fonction permet de vérifier si une ou plusieurs zone interdites se trouvent entre les deux points
//
// Developpe par : Aurélien Rithner
// Date :          16.10.2018
// Revision :		V1.0
//
// parametres  : coord x,y du point de départ et d'arrivée
// return      : modification en global de intersection_found et de TabIntersection
//
//*********************************************************************************************************************
void checkIntersection(double pt1X, double pt1Y, double pt2X, double pt2Y);

//*********************************************************************************************************************
// getPos
//
// Cette fonction permet de définir la position relative d'un point par rapport à une zone rectangulaire
// Il y a 9 zones possibles qui sont déterminées en prolongeant les côtés du rectangle, les zones sont numérotées
// dans le sens des aiguilles d'une montre, en partant de en haut à gauche avec la zone 0. La zone 8 correspond au rectangle. 
//
// Developpe par : Aurélien Rithner
// Date :          16.10.2018
// Revision :		V1.0
//
// parametres  : px et py coordonnées du point, rx1 et ry1 sommet en haut à gauche, rx4 et ry4 sommet en bas à droite 
// return      : entier de 0 à 8
//
//*********************************************************************************************************************
int getPos(int px, int py, int rx1, int ry1, int rx4, int ry4);


//*********************************************************************************************************************
// finRel
//
// Cette fonction permet de de trouver le chemin le plus court pour éviter la zone interdite en définissant les points
// relais
//
// Developpe par : Aurélien Rithner
// Date :          16.10.2018
// Revision :		V1.0
//
// parametres  : xStart et yStart coordonnées du point de départ, xEnd et yEnd coordonnées du point de départ,
// return      : entier de 0 à 8
//
//*********************************************************************************************************************
void findRel(int xStart, int yStart, int xEnd, int yEnd, int i_zone);

#include "zonesinterdites/__ZonesInterdites.c"

#endif 