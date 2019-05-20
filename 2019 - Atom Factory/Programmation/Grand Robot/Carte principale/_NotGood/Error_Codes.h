/*

//////////////////////////////////////////////////////////////
////// Liste des codes d'erreur de la plaque principale //////
//////////////////////////////////////////////////////////////

Les erreur sont, actuellement, uniquement affichées et le programme bloque si mode affichage définit.
Sachant qu'on les détecte, on peut remplacer les affichage d'erreurs par des actions
permettant la continuité du programme.

01	-	Driver Moteur déconnecté ou ne répond pas lors de l'init.
02	-	Démarreur pas en place au démarrage du robot
03	-	Erreur : sortie de la machine d'état
04	-	Driver Moteur déconnecté ou ne répond pas lors de la machine d'état (Action_Writting)
05	-	Objectif à réaliser indéterminé (Action_Writting)
		Le plus souvent, à cause d'objectifs mal chargés.
06	-	Erreur d'envoi IIC, module à correspondre ne répond pas (Send_I2C)
07	-	Erreur de demande de données IIC, module à correspondre ne répond pas (Ask_I2C)
08	-	Le driver n'a pas répondu lors de la configuration de la base de départ

*/