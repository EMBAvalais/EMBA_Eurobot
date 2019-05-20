#ifndef _SERVOMOTEUR_H
#define _SERVOMOTEUR_H

// Nombre de servomoteurs (0 à MAXSERVO-1)
#DEFINE MAXSERVO 1
// Valeurs min et max de l'impulsion en [100us] pour la protection des servomoteurs
#DEFINE MINSERVOPOSITION 9
#DEFINE MAXSERVOPOSITION 20
// Normalement 9 et 21 pour 900us et 2.1ms

// Structure pour la gestion des servomoteurs
struct T_Servo{
	int Position;
	int Count;
	int OpenValue;
	int CloseValue;
};

struct T_Servo ServoTab[MAXSERVO];

void MoveServo(int number, int position);
void SetServo(int number, int state);
void OpenServo(int number);
void CloseServo(int number);
void CheckServo();
void __Init_Servos();

#include "servomoteur/servomoteur.c"

#endif

///====================================================================
/// 			COMMANDE DES SERVOMOTEURS - PRINCIPE
///====================================================================
///
///	Le but est de générer des sorties pour la commandes de servomoteurs.
///	Les sorties sont mises à jour chaque 100us grâce au TIMER2.
///	Les impulsions de commande sont envoyées en continu.
///
///====================================================================
/// 			COMMANDE DES SERVOMOTEURS  - UTILISATION
///====================================================================
///
///	MAXSERVO permet de définir le nombre de servomoteurs utilisés
///	MINSERVOPOSITION et MAXSERVOPOSITION fixent les valeurs min et max
///	des impulsions à générer pour la commande des servomoteurs, en
///	général on se limite à 900us (9) et 2.1ms (21)
///
///	CheckServo(): gère la commande des servomoteurs, à appeler toutes
///	toutes les 100us
///
///	MoveServo(number, position): permet de modifier la valeur de consigne
///	d'un servomoteur
///
///	SetServo(numer, state): utilisé par CheckServo(), le switch case
///	permet de définir les sorties propres à chaque servomoteurs.