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
==== Permet de controler les servomoteurs facilement					====
==== Contient les fonctions d'apprentissage de mouvement				====
==== et de lecture de ses mouvements									====
============================================================================
==== Rappel:															====
==== ------																====
==== Si, apres avoir lu uniquement les commentaires d'un programme,		====
==== vous n'en comprenez pas le fonctionnement, alors jetez le tout !	====
============================================================================
"""

import axFiles					# Le gestionnaire de fichier
import axDriver					# Le driver des moteurs AX-12A
import time						# Pour les sleeps et autres

delayTime = 0.02				# Delai ajustable entre chaque mouvement
nbStep = 250					# Nombre de step du programme de test

#========================================================================================
def checkAllServo(IDmax):
	""" Ping jusqu'a IDmax, et dit si un servo est sur cette ID
		Retourne un tableau de tous les servo connectes
		IDmax = valeur max de l'ID des moteurs """
	i = 1 # Index de boucle
	tabServo = [] # Cree un tableau vide pour stocker les servos presents

	while i <= IDmax: # Toutes les IDs jusqu'a IDmax
		if axDriver.ping(i) == True: # Check si le servo est present
			tabServo.append(i) # Ajoute l'ID du servo au tableau
		i += 1 # Increment i pour passer au prochain servo

	return tabServo # Retourne les servo connectes
#========================================================================================

#========================================================================================
def progMode(state):
	""" Active ou desactive le couple de tous les servos selon
		la valeur de state (True/False)
		state = booleen de l'etat du torque """
	# Envoie la commande setTorque a tous les servos
	axDriver.setTorque(axDriver.BROADCASTID, state)
#========================================================================================

#========================================================================================
def getMouvementSteps(Servos):
	""" Recupere la position de tous les servo connectes,
		Retourne le dictionnaire des positions
		Servos = tableau contenant les IDs des servos qu'on veut lire """
	dictPosition = {} # Cree un dictionnaire vide
	progMode(False) # Desactive le couple des servos

	for servo in Servos: # Pour chaque servo
		# Ajoute la position du servo au dico
		dictPosition[servo] = axDriver.getPosition(servo)
		time.sleep(0.001) # Attends un petit peu pour eviter le timeout du servo

	return dictPosition # Retourne le dictionnaire
#========================================================================================

#========================================================================================
def saveFullMouvement(filename, nbSteps, delay, Servos):
	""" Enregistre un mouvement entier dans un fichier
		filename = string contenant le nom du fichier
		nbSteps = nombre d'etape que l'on souhaite enregistrer
		delay = delai en secondes entre chaque etape
		Servos = tableau contenant les IDs des servos qu'on veut lire """
	tabPositions = [] # Cree un tableau vide
	i = 0 # Index de boucle

	while i <= nbSteps: # Fait toutes les etapes
		# Sauvegarde l'etape dans le tableau
		tabPositions.append(getMouvementSteps(Servos))
		time.sleep(delay) # Delai entre chaque etape
		i += 1 # Incremente l'index

	# Ecrit toutes les etapes dans le fichier
	axFiles.writeFile(tabPositions, filename)
#========================================================================================

#========================================================================================
def sendMouvementStep(positions):
	""" Envoie une etape de mouvement
		positions = dictionnaire de position
		delay = delai en secondes entre chaque etape """
	progMode(True) # Active le couple des servos
	for servo in positions: # Pour chaque servo
		# Ecrit la position dans le registre de chaque servo
		axDriver.setPosition(servo, positions[servo])
	axDriver.action(axDriver.BROADCASTID) # Tous les servos bougent
#========================================================================================

#========================================================================================
def doFullMouvement(filename, delay):
	""" Execute un mouvement entier venant d'un fichier, etape par etape,
		avec un delai reglable entre chaque etape
		filename = string contenant le nom du fichier,
		delay = delai en secondes entre chaque etape """
	mouvement = axFiles.readFile(filename) # Lis les positions
	for step in mouvement: # Pour chaque etape du mouvement
		sendMouvementStep(step) # Envoie le mouvement
		time.sleep(delay) # Patiente

#========================================================================================
def backToMiddlePos():
	""" Renvoie les servos a la position centrale 0x1FF """
	progMode(True) # Active le couple de servos
	axDriver.goToPosition(axDriver.BROADCASTID, 0x1FF) # Renvoie a la position 0x1FF

#========================================================================================
if __name__ == "__main__": # Code executer si ce fichier est lance en main$
	tabServos = checkAllServo(7)
	progMode(True) # Active le couple
	print("Prog dans 3sec")
	time.sleep(3)
	print("PROG")
	saveFullMouvement("TestFile", 500, 0.01, tabServos)
	print("Fin de la prog")
	time.sleep(5)
	print("Debut de la repet")
	doFullMouvement("TestFile", 0.01)
	progMode(False) # Desactive le couple
