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
==== Nom du programme					: Gestio. de fichier AX-12A		====
==== Version							: V1.0							====
==== Nom du(des) fichier(s) source		: axFiles.py					====
====--------------------------------------------------------------------====
==== Createur (Nom, Prenom, Localite)	: Francelet Samy, Rechy			====
==== Classe								: EL-3A							====
==== Date de creation					: 05.05.2017					====
==== Date de la derniere modification	: 12.05.2017					====
====--------------------------------------------------------------------====
==== Description succincte du programme:								====
==== ----------------------------------									====
==== Gere les fichiers contenant les positions des servo AX-12A			====
============================================================================
==== Rappel:															====
==== ------																====
==== Si, apres avoir lu uniquement les commentaires d'un programme,		====
==== vous n'en comprenez pas le fonctionnement, alors jetez le tout !	====
============================================================================
"""

#========================================================================================
# Constantes utilisees par le programme
repertoire = "robFiles" + "/"	# Nom du dossier contenant les fichiers rob1
extension = ".rob1"				# Extension des fichiers de positions
#========================================================================================

#========================================================================================
def checkFile(filename):
	""" Permet de check si le fichier existe deja, afin d'informer
		l'utilisateur en cas de soucis,
		Retourne l'etat du fichier : 0 = n'existe pas, 1 = existe
		filename = string du nom de fichier """

	fileRepo = repertoire + filename + extension # Position du fichier

	try: # Essaye d'ouvir en lecture
		test = open(fileRepo, "r")
	except: # Si on arrive pas a ouvrir le fichier
		return 0 # Indique le fichier non existant
	else: # Sinon, si le fichier s'est ouvert
		test.close() # S'assure de fermer le fichier
		return 1 # Indique que le fichier existe
#========================================================================================

#========================================================================================
def renewFile(filename):
	""" Permet de clear le contenu d'un fichier, ou de creer un nouveau fichier
	filename = string du nom de fichier """

	fileRepo = repertoire + filename + extension # Position du fichier

	# Ouvre en ecriture et l'ecrase
	# La methode with ferme le fichier automatiquement
	with open(fileRepo, "w") as robFile:
		robFile.write(filename + "\n") # Ecrit le nom du fichier au debut
#========================================================================================

#========================================================================================
def writeStep(dictPosition, filename):
	""" Ecrit une etape avec toutes les positions des moteurs
		contenues dans le dictionnaire positions,
		Retourne : 0 = erreur lors de l'ecritrue, 1 = ecriture reussie
		dictPosition = dictionnaire de position ,filename = string du nom de fichier """
	fileRepo = repertoire + filename + extension # Position du fichier
	try:
		# Ouvre le fichier en append, sans l'ecraser
		# La methode with ferme le fichier automatiquement
		with open(fileRepo, "a") as robFile:
			for motorID in dictPosition.keys(): # Boucle tout le dictionnaire
				# Ecrit une ligne pour chaque position de moteur
				robFile.write(str(motorID) + ":" + str(dictPosition[motorID]) + "\n")

			robFile.write("StepEnd\n") # Indique la fin d'une etape
		return 1 # Pas de probleme lors de l'ecriture
	except:
		return 0 # Un probleme a ete rencontre
#========================================================================================

#========================================================================================
def writeFile(tabPositions, filename):
	""" Ecrit un fichier en entier, plutot que etape par etape
		Retourne : 0 = erreur lors de l'ecriture, 1 = ecritures reussies
		tabPositions = tableau de dictionnaire de positions,
		filename = string du nom de fichier """
	# S'assure qu'un fichier est present et vide
	renewFile(filename)
	# Ecrit etape par etape
	for step in tabPositions:
		if writeStep(step, filename) == 0: # Si il y a une erreur
			return 0 # Indique une erreur

	return 1 # Indique que tout va bien
#========================================================================================

#========================================================================================
def readFile(filename):
	""" Lis le fichier en entier, et retourne un tableau de dictionnaire
		contenants les positions des moteurs, chaque dictionnaire contient
		une etape, et le tableau contient les dictionnaires de chaque etapes.
		Retourne un tableau de dictionnaire de position
		Retourne 0 en cas d'erreur,
		filename = string du nom de fichier """
	fileRepo = repertoire + filename + extension # Position du fichier
	tabPositions = [] # Cree un tableau vide
	dictPosition = {} # Cree un dictionnaire vide
	try:
		# Ouvre en mode lecture
		# La methode with ferme le fichier automatiquement
		with open(fileRepo, "r") as robFile:
			contenu = robFile.read().splitlines()
		assert contenu[0] == filename # Controle si le fichier correspond
	except AssertionError:
		return 1
	except:
		return 0 # Retourne 0 en cas d'erreur
	else:
		del(contenu[0]) # Supprime le nom de fichier du contenu lisible
		for line in contenu: # Parcours toutes les lignes
			if line == "StepEnd": # Si on arrive a la fin d'un pas
				tabPositions.append(dictPosition) # Ajoute l'etape dans le tableau
				dictPosition = {} # Vide le dictionnaire
			else:
				try:
					# Stock la position dans le dictionnaire
					dictPosition[int(line.split(":")[0])] = int(line.split(":")[1])
				except ValueError:
					# Affiche la ligne qui contient l'erreur
					print str(contenu.index(line)) + " : " + line

		return tabPositions # Retourne le tableau rempli
#========================================================================================

#========================================================================================
#if __name__ == "__main__": # Code executer si ce fichier est lance en main
#========================================================================================
