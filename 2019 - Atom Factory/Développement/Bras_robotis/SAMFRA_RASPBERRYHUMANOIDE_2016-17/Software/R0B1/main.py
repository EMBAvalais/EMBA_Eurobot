"""
============================================================================
====																	====
====				EMVs - Ecole des metiers du Valais					====
====																	====
============================================================================
====																	====
====					  Programmation en Python						====
====					 --------------------------						====
====																	====
====--------------------------------------------------------------------====
==== Nom du programme					: Controleur des servo AX-12A	====
==== Version							: V1.0							====
==== Nom du(des) fichier(s) source		: axControl.py					====
====--------------------------------------------------------------------====
==== Createur (Nom, Prenom, Localite)	: Francelet Samy, Rechy			====
==== Classe								: EL-3A							====
==== Date de creation					: 12.05.2017					====
==== Date de la derniere modification	: 12.05.2017					====
====--------------------------------------------------------------------====
==== Description succincte du programme:								====
==== ----------------------------------									====
==== Fonction principale, lance uniquement l'application Kivy			====
============================================================================
==== Rappel:															====
==== ------																====
==== Si, apres avoir lu uniquement les commentaires d'un programme,		====
==== vous n'en comprenez pas le fonctionnement, alors jetez le tout !	====
============================================================================
"""

import robui				# Importe l'interface utilisateur

if __name__ == "__main__": 	# Si ce fichier est appele en main
	robui.RobUIApp().run() 	# Lance le programme
