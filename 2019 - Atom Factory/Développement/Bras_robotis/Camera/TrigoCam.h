#ifndef TrigoCam_h
#define TrigoCam_h

class TrigoCam
{
	public:
		//==============================================================
		//FONCTIONS PUBLIQUES
		//==============================================================
		
		//Fonction d'initialisation de la position de la caméra
		void InitCam(int, int, int, int);
		
		//Ajustage des valeurs de corrections X et Y
		void SetCorrection(int, int);
		
		//Fonction de calcul de la position XY
		double getPosX(double, double);
    double getPosY(double, double);
		
		
	private:
	
		//==============================================================
		//FONCTIONS PRIVEES
		//==============================================================

    //Fonction de calcul de X0_1
    double TrigoCam::CalcX(double);
    
		//Fonction de calcul de X1
		double CalcX1(double);
		
		//Fonction de calcul de X2
		double CalcX2(double);
		
		//Fonction de calcul de l'angle Beta
		double CalcBeta();
		
		//==============================================================
		// VARIABLES PARAMETRES
		//==============================================================
		
		//offset X de l'image (mieux de laisser à 0)
		double offsetX = 0;
		
		//distance entre la caméra et le début de la zone. Cette valeur
		//est négative si la caméra est sur la zone
		double offsetY = 0;
		
		//hauteur de la caméra
		double HauteurCam = 0;
		
		//offset entre le 0 et la caméra sur l'axe X
		double offsetXCam = 0;
		
		//corrections X et Y environ 5mm ou moins
		int corrY = 0;
		int corrX = 0;
		
		//==============================================================
		// VARIABLES POUR LES CALCULS
		//==============================================================
		
		//nombre de Pixels X où se trouve l'objet détecté
		double nPixelsX = 0;
		
		//nombre de Pixels Y où se trouve l'objet détecté
		double nPixelsY = 0;
		
		//variables de positions XY
		double posX = 0;
		double posY = 0;
};

#endif
