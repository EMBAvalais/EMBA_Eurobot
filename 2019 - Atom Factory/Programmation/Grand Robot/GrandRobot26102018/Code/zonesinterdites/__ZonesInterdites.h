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
enum{X, Y};

int x3 = 0;
int y3 = 3;
int x2 = 2;
int y2 = 1;

int32 start_point_X, start_point_Y, end_point_X, end_point_Y;
signed int32 spot_X, spot_Y; 

//*********************************************************************************************************************
// checkPath
//
// Cette fonction permet de vérifier si le trajet du point A à B passe sur une zone interdite
//
// Developpe par : Aurélien Rithner
// Date :          16.10.2018
// Revision :		V1.0
//
// parametres  : -
// return      : -
//
//*********************************************************************************************************************
int checkPath();

void checkPtsRelai();

//*********************************************************************************************************************
// findPath
//
// Cette fonction permet de trouver le trajet pour arriver à la destination en évitant les zones interdites
//
// Developpe par : Aurélien Rithner
// Date :          16.10.2018
// Revision :		V1.0
//
// parametres  : -
// return      : -
//
//*********************************************************************************************************************
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
int16 getDist(int16 x1, int16 y1, int16 x2, int16 y2);

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
void checkIntersection(int16 pt1X, int16 pt1Y, int16 pt2X, int16 pt2Y);

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
int getPos(int16 px, int16 py, int16 rx1, int16 ry1, int16 rx4, int16 ry4);


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
void findRel(int16 xStart, int16 yStart, int16 xEnd, int16 yEnd, int i_zone);

#include "zonesinterdites/__ZonesInterdites.c"

#endif 