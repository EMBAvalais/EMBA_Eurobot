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
==== Nom du programme					: Driver servo AX-12A			====
==== Version							: V1.0							====
==== Nom du(des) fichier(s) source		: axDriver.py					====
====--------------------------------------------------------------------====
==== Createur (Nom, Prenom, Localite)	: Francelet Samy, Rechy			====
==== Classe								: EL-3A							====
==== Date de creation					: 30.03.2017					====
==== Date de la derniere modification	: 12.05.2017					====
====--------------------------------------------------------------------====
==== Description succincte du programme:								====
==== ----------------------------------									====
==== Contient toutes les fonctions necessaires pour driver efficacement	====
==== les servomoteurs AX-12A											====
============================================================================
==== Rappel:															====
==== ------																====
==== Si, apres avoir lu uniquement les commentaires d'un programme,		====
==== vous n'en comprenez pas le fonctionnement, alors jetez le tout !	====
============================================================================
"""

import serial					# Pour communiquer en UART
import time						# Pour les sleeps et autres
import RPi.GPIO as GPIO			# Module de controle des GPIO
import axReg					# Import des registres des AX-12A
import sys						# Pour recuperer la taille des tableaux

registers = axReg.AXRegisters	# Recupere les registres

#========================================================================================
# Constantes importantes du AX-12A
AX_SYNC_WRITE = 0x83		# Commande SyncWrite
AX_RESET = 6				# Commande reset to factory
AX_ACTION = 5				# Commande Action
AX_REG_WRITE = 4			# Commande Register Write
AX_WRITE_DATA = 3			# Commande Write Data
AX_READ_DATA = 2			# Commande Read Data
AX_PING = 1					# Commande Ping
AX_POSITION = 0x1E			# Adresse de la targeted position
AX_TORQUE_ENABLE = 0x18		# Adresse du torque enable
AX_MOVING_SPEED = 0x20		# Adresse de la vitesse
AX_PRESENT_POSITION = 0x24	# Adresse de la position actuelle
BROADCASTID = 0xFE			# Adresse de broadcast, pour communiquer a tous les servos
#========================================================================================

#========================================================================================
# Port serie
port = serial.Serial()		# Cree un objet port serie
port.baudrate = 1000000		# Baudrate en bauds/sec
port.port = "/dev/ttyAMA0"	# Le port serie
port.timeout = 0.5			# Timeout apres 500ms
port.open()					# Ouvre le port
#========================================================================================

#========================================================================================
# GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
tx = GPIO.HIGH						# Etat haut pour le TX
rx = GPIO.LOW						# Etat bas pour le RX
directionPin = 18					# Utilise la pin 18 pour la direction
GPIO.setup(directionPin, GPIO.OUT)	# Configure la directionPin en output
disableDirPin = False				# Permet de desactive la pin de direction au besoin
#========================================================================================

#========================================================================================
# Dictionnaire contenant les erreurs
dictErrors =    {
					0 : "Pas d'erreur",
					1 : "Input Voltage",
					2 : "Angle Limit",
					4 : "Overheating",
					8 :	"Range",
					16 : "Checksum",
					32 : "Overload",
					64 : "Instruction",
					200 : "Timeout",
					201 : "Mauvais ID",
					202 : "Mauvais checksum"
				}
#========================================================================================

#========================================================================================
def sizeof(tab):
	""" Retourne le nombre de case d'un tableau
		tab = tableau dont on veut la taille """
	return ((sys.getsizeof(tab)- 36)/4)
#========================================================================================

#========================================================================================
def direction(d):
	""" Choisi la direction des donnees, soit rx, soit tx
		d = direction (RX/TX) """
	if not disableDirPin:
		GPIO.output(directionPin, d) # Parametre la pin
		time.sleep(0.0005) # Sleep de 50us pour reduire les erreurs de checksum
#========================================================================================

#========================================================================================
def sendData(ID, instruction, params):
	""" Permet d'envoyer une instruction au moteur AX-12A selectionne
		ID = ID du moteur, instruction = instrution desiree,
		params = tableau contenant les parametres desires """
	direction(tx) # Choisi la direction TX
	port.flushInput() # Vide le contenu du port UART

	length = sizeof(params) + 2 # Calcul la longueur, nbParam + 2

	checksum = ID + length + instruction # Calcul de la premiere partie du checksum

	for param in params: # Ajout de chaque parametre dans le checksum
		checksum += param

	checksum = 255 - (checksum%256) # Finalisation du calcul du checksum

	port.write(chr(0xFF)) # Premier start
	port.write(chr(0xFF)) # Second start
	port.write(chr(ID)) # ID du servo
	port.write(chr(length)) # Longueur du paquet
	port.write(chr(instruction)) # Instruction a envoyer

	for param in params: # Ajout de tous les parametres
		port.write(chr(param))

	port.write(chr(checksum)) # Envoi du checksum
#========================================================================================

#========================================================================================
def receiveData(ID):
	""" Permet de recevoir les donnees de l'AX-12A selectionne
		ID = ID du moteur en int """
	vals = [] # Cree un tableau vide
	direction(rx) # Choisi la direction RX
	checksum = ID # Ajoute l'ID dans le checksum

	try :
		start1 = port.read() # Lis le premier start 0xFF
		assert ord(start1) == 0xFF # Controle si le start byte est correct
	except :
		print("Le servo " + str(ID) + " est timeout")
		return [200]
	else :
		try :
			start2 = port.read() # Deuxieme start, pas utilise
			origin = port.read() # Lis l'ID d'origine
			assert ord(origin) == ID # Controle si les ID correspondent
			length = ord(port.read()) # Lis la longeur du paquet
			checksum += length # Ajoute la longueur au checksum
			length -= 1 # Enleve une longueur correspondant au checksum
			while length > 0:
				data = port.read() # Lis la valeur envoyee
				checksum += ord(data) # Ajoute la valeur au checksum
				vals.append(ord(data)) # Ajoute la valeur lue dans le tableau
				length -= 1
		except AssertionError:
			print ("Mauvaise adresse du servo, attendue : " + str(ID) + " recue : " + origin)
			return [201] # Mauvaise adresse
		else :
			try:
				data = port.read() # Lis le checksum
				vals.append(ord(data)) # L'ajoute a la fin de la liste
				checksum = 255 - (checksum%256) # Calcul final du checksum
				assert vals[-1] == checksum # Controle si le checksum recu correspond
			except AssertionError:
				print ("Mauvais checksum du servo " + str(ID))
				return [202] # Erreur de checksum

			del vals[-1] # Supprime le checksum de vals
			return vals # Retourne les donnees lues
#========================================================================================

#========================================================================================
def ping(ID):
	""" Fonction servant a PING un moteur pour voir son etat et son type d'erreur,
		Retourne l'etat du servo (Utilisable/Non-utilisable)(True/False)
		ID = ID du moteur en int """
	sendData(ID, AX_PING, []) # Envoie un ping, ne contient pas de parametres
	error = receiveData(ID) # Receptionne le numero d'erreur
	if error[0] is 0: # Si il n'y a pas d'erreur
		return True # Indique que le servo est utilisable
	else:
		print(dictErrors[error[0]]) # Affiche l'erreur recue a l'utilisateur
		return False # Indique que le servo est inutilisable
#========================================================================================

#========================================================================================
def goToPosition(ID, position):
	""" Bouge le servo a la position indiquee. 1 degre = 3
		ID = ID du moteur en int, position = position desiree en int """
	pos1 = position & 0b0000000011111111 # Position low
	pos2 = (position & 0b1111111100000000)/256 # Position high
	values = [AX_POSITION, pos1, pos2] # Prepare le tableau de parametres
	# Envoie un Write_data a l'adresse de position
	sendData(ID, AX_WRITE_DATA, values) # Envoie la position
#========================================================================================

#========================================================================================
def setPosition(ID, position):
	""" Ecrit la prochaine position dans le registre,
		mais le servo n'ira a la position que quand il
		recevra la commande ACTION. 1 degre = 3
		ID = ID du moteur en int, position = position desiree en int """
	pos1 = position & 0b0000000011111111 # Position low
	pos2 = (position & 0b1111111100000000)/256 # Position high
	values = [AX_POSITION, pos1, pos2] # Prepare le tableau de parametres
	# Envoie un Write_data a l'adresse de position
	sendData(ID, AX_REG_WRITE, values) # Envoie la position
#========================================================================================

#========================================================================================
def action(ID):
	""" Le servo lance les actions en attente
		ID = ID du servo en int """
	sendData(ID, AX_ACTION, []) # Envoie la commande ACTION, pas de parametres
#========================================================================================

#========================================================================================
def getPosition(ID):
	""" Fonction lisant la position du servo selectionne
		Retourne la position du servo
		ID = ID du servo en int """
	values = [AX_PRESENT_POSITION, 2] # Parametres pour lire les 2 bytes de position
	sendData(ID, AX_READ_DATA, values) # Envoie un ReadData sur l'adresse de la position
	positions = receiveData(ID) # Recoit les positions (positions[0] est l'etat d'erreur)
	if positions[0] is not 0:
		print(dictErrors[positions[0]]) # Affiche l'erreur si il y en a une
		return
	else:
		pos = positions[1] + positions[2]*256 # Stock la position sous une seule variable
		return pos # Retourne la position
#========================================================================================

#========================================================================================
def setTorque(ID, state):
	""" Active ou desactive selon la valeur de state (True/False)
		ID = ID du servo en int, state = booleen de l'etat du torque """
	values = [AX_TORQUE_ENABLE, state] # Parametres d'adresse et d'etat du couple
	sendData(ID, AX_WRITE_DATA, values) # Envoie un changement d'etat du couple
#========================================================================================

#========================================================================================
#if __name__ == "__main__": # Permet de tester le driver si ce fichier est utilise en main

#========================================================================================
