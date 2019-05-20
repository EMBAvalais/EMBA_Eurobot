/*

//////////////////////////////////////////////////////////////
////// Liste des codes d'erreur de la plaque principale //////
//////////////////////////////////////////////////////////////

Les erreur sont, actuellement, uniquement affich�es et le programme bloque si mode affichage d�finit.
Sachant qu'on les d�tecte, on peut remplacer les affichage d'erreurs par des actions
permettant la continuit� du programme.

01	-	Driver Moteur d�connect� ou ne r�pond pas lors de l'init.
02	-	D�marreur pas en place au d�marrage du robot
03	-	Erreur : sortie de la machine d'�tat
04	-	Driver Moteur d�connect� ou ne r�pond pas lors de la machine d'�tat (Action_Writting)
05	-	Objectif � r�aliser ind�termin� (Action_Writting)
		Le plus souvent, � cause d'objectifs mal charg�s.
06	-	Erreur d'envoi IIC, module � correspondre ne r�pond pas (Send_I2C)
07	-	Erreur de demande de donn�es IIC, module � correspondre ne r�pond pas (Ask_I2C)
08	-	Le driver n'a pas r�pondu lors de la configuration de la base de d�part

*/