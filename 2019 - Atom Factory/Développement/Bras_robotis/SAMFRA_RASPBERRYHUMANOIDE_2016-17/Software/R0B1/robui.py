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
==== Nom du(des) fichier(s) source		: robui.py						====
====--------------------------------------------------------------------====
==== Createur (Nom, Prenom, Localite)	: Francelet Samy, Rechy			====
==== Classe								: EL-3A							====
==== Date de creation					: 12.05.2017					====
==== Date de la derniere modification	: 12.05.2017					====
====--------------------------------------------------------------------====
==== Description succincte du programme:								====
==== ----------------------------------									====
==== Contient le code de l'interface utilisateur						====
============================================================================
==== Rappel:															====
==== ------																====
==== Si, apres avoir lu uniquement les commentaires d'un programme,		====
==== vous n'en comprenez pas le fonctionnement, alors jetez le tout !	====
============================================================================
"""

import kivy	# Importe Kivy
kivy.require("1.10.0") # Version minimale necessaire pour faire tourner l'application

import axControl							# Pour controler les moteurs
import time									# Pour les delais et autres
from kivy.app import App					# Application principale
from kivy.uix.widget import Widget			# Pour creer des Widgets
from kivy.uix.gridlayout import GridLayout	# Layout en grille pour faire le menu
from kivy.uix.slider import Slider			# Les sliders pour regler la duree
from kivy.uix.label import Label			# Le label d'affichage
from kivy.uix.button import Button			# Les boutons
from kivy.properties import ObjectProperty	# Pour creer des attributs objets dans un widget
from kivy.properties import ListProperty	# Pour creer des attributs listes dans un widget
from kivy.properties import StringProperty	# Pour creer des attributs string dans un widget

class Menu(GridLayout):
	""" Menu principal de l'interface utilisateur """
	
	# Cree le tableau contenant tous les servos
	tabServo = ListProperty()

	# Cree tous les boutons
	btnMove1 = ObjectProperty(Button)
	btnMove2 = ObjectProperty(Button)
	btnMove3 = ObjectProperty(Button)
	btnProg1 = ObjectProperty(Button)
	btnProg2 = ObjectProperty(Button)
	btnProg3 = ObjectProperty(Button)

	# Cree tous les Sliders
	slider1 = ObjectProperty(Slider)
	slider2 = ObjectProperty(Slider)
	slider3 = ObjectProperty(Slider)


	def Check(self):
		""" Check tous les servos connectes et stock la valeur dans tabServo """
		self.ids.lblText.text = "Check des servos"
		time.sleep(0.5)
		self.tabServo = axControl.checkAllServo(14) # Check tous les servos
		#time.sleep(2) # Attends 2 secondes


	def StartMouvement(self, filename):
		""" Demarre un mouvement enregistrer """
		self.ids.lblText.text = "En mouvement"
		time.sleep(0.5)
		# Execute le mouvement
		axControl.doFullMouvement(filename, 0.015)

		self.ids.lblText.text = "En attente"
		time.sleep(0.5)

	def ProgMouvement(self, filename, numSlider):
		""" Programme un mouvement, la duree du mouvement est reglable avec le slider """
		self.Check()
		self.ids.lblText.text = "Programmation"
		time.sleep(0.5)
		if numSlider is 1:
			# Programme le mouvement
			axControl.saveFullMouvement(filename, self.ids.slider1.value, 0.01, self.tabServo)
			#time.sleep(self.ids.slider1.value/100)
		elif numSlider is 2:
			# Programme le mouvement
			axControl.saveFullMouvement(filename, self.ids.slider2.value, 0.01, self.tabServo)
			#time.sleep(self.ids.slider2.value/100)
		elif numSlider is 3:
			# Programme le mouvement
			axControl.saveFullMouvement(filename, self.ids.slider3.value, 0.01, self.tabServo)
			#time.sleep(self.ids.slider3.value/100)
		self.ids.lblText.text = "En attente"
		axControl.progMode(True)
		time.sleep(0.5)

class RobUIApp(App):
	""" Application principale """
	def build(self):
		""" Constructeur de l'application """
		rob = Menu() # Cree un menu
		return rob # Retourne ce menu

if __name__ == "__main__":
	RobUIApp().run()
