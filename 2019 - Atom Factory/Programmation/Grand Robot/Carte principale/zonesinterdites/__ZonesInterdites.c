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

#ifndef ___Zones_interdites_c
#define ___Zones_interdites_c


int checkPath()
{
	path_found = 0;
		
    start_point.X = Pos_x;
    start_point.Y = Pos_y;

    end_point.X = oXp;
    end_point.Y = oYp;

    checkIntersection(start_point.X, start_point.Y, end_point.X, end_point.Y);
		
	if (intersection_found > 0)
	{
			path_found = 0;
	}
	else
	{
			path_found = 1;
	}

	return path_found;
  
}

void findPath()
{
    i_rel = 0;

    //On trouve le premier point relai
    findRel(start_point.X, start_point.Y, end_point.X, end_point.Y, 0);

    //On vérifie si depuis le premier point relai on intercepte encore une zone
    checkIntersection(PtsRelai[i_rel - 1].X, PtsRelai[i_rel - 1].Y, end_point.X, end_point.Y);

    if(path_found < 1)
    {
    	int i = 0;
	    //Si on intecepte encore une zone alors intersection_found sera >1
	    while(intersection_found > 0)
	    {
	        //Tant qu'on intercepte une zone depuis le point relai on continue à en chercher un autre
	        i++;
	        findRel(PtsRelai[i_rel - 1].X, PtsRelai[i_rel - 1].Y, end_point.X, end_point.Y, 0);
	        checkIntersection(PtsRelai[i_rel - 1].X, PtsRelai[i_rel - 1].Y, end_point.X, end_point.Y);
	    }
    }
    


}


//*********************************************************************************************************************
// getDist
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
double getDist(double x1, double y1, double x2, double y2)
{
    return (sqrt(pow((x2-x1),2)) + (pow((y2-y1),2)));
}

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
void checkIntersection(double pt1X, double pt1Y, double pt2X, double pt2Y)
{
	struct Coord spot;

    int zoneToCheck = 0;

    intersection_found = 0;

    int j;
    for ( j= 0; j < 10; j++)
    {
        TabIntersection[j] = 0;
    }
    

    double dX = pt2X-pt1X;
    double dY = pt2Y-pt1Y;

    int i = 0;

    do
    {
        i++;

        //On calcule des points le long du trajet
        spot.X = (dX*i)/100;
        spot.Y = (dY*i)/100;


        //Pour chaque point du trajet on vérifie s'il est dans une zone
        for(zoneToCheck = 0; zoneToCheck < 10; zoneToCheck++)
        {
            //On vérifie si le point se trouve dans la zone interdite
	        if ((spot.X+pt1X) >= TabZones[zoneToCheck][0] && (spot.X+pt1X) <= TabZones[zoneToCheck][2])
	        {
		        if ((spot.Y+pt1Y) >= TabZones[zoneToCheck][1] && (spot.Y+pt1Y) <= TabZones[zoneToCheck][3])
		        {
			       
                    TabIntersection[intersection_found] = zoneToCheck;
                    intersection_found++;
			
		        }
			
			
	        }
        }
	
    }while (i < 100 && intersection_found == 0);

    if(intersection_found > 0)
    {
    	path_found = 0;
    }
    else
    {
    	path_found = 1;
    }
}


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
int getPos(int px, int py, int rx1, int ry1, int rx4, int ry4)
{
    int pos;

    if (px > rx4)
    {
        if (py > ry4)
        {
            pos = 4; //Le point se trouve en bas à droite de la zone
        }
        else if (py > ry1)
        {
            pos = 3; //Le point se trouve à droite de la zone
        }
        else
        {
            pos = 2; //Le point se trouve en haut à droite de la zone
        }
    }
    else if (px > rx1)
    {
        if (py > ry4)
        {
            pos = 5; //Le point se trouve en bas de la zone
        }
        else if (py > ry1)
        {
            pos = 8; //Le point se trouve dans la zone
        }
        else
        {
            pos = 1; //Le point se trouve en haut de la zone
        }
    }
    else
    {
        if (py > ry4)
        {
            pos = 6; //Le point se trouve en bas à gauche de la zone
        }
        else if (py > ry1)
        {
            pos = 7; //Le point se trouve à gauche de la zone
        }
        else
        {
            pos = 0; //Le point se trouve en haut à gauche de la zone
        }
    }

    return pos;
        
}


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
void findRel(int xStart, int yStart, int xEnd, int yEnd, int i_zone)
{
	//On récupère la position des deux points par rapport à la zone
    int posStart = getPos(xStart, yStart, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][1], TabZones[TabIntersection[i_zone]][2], TabZones[TabIntersection[i_zone]][y4]);
    int posEnd = getPos(xEnd, yEnd, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][1], TabZones[TabIntersection[i_zone]][2], TabZones[TabIntersection[i_zone]][y4]);

    int relay_point_number = 0;

    if(posStart == 8 || posEnd == 8)
    {
    	path_found = 0;
    }	
    else
    {
	    switch (posStart)
	    {
	        case 0:
	            if (posEnd == 3)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y2];
	                relay_point_number = 1;
	                path_found = true;
	            }
	            else if (posEnd == 4)
	            {
	                if ((getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3]) + getDist(TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3], xEnd, yEnd)) > (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2]) + getDist(TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2], xEnd, yEnd)))
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y2];
	                    relay_point_number = 1;
	                }
	                else
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y3];
	                    relay_point_number = 1;
	                }
	                path_found = true;
	            }
	            else if (posEnd == 5)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y3];
	                relay_point_number = 1;
	                path_found = true;
	            }
	            break;

	        case 1:
	            if (posEnd == 3 || posEnd == 4)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y2];
	                relay_point_number = 1;
	                path_found = true;
	            }
	            else if (posEnd == 5)
	            {
	                if (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1]) + getDist(TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3], xEnd, yEnd) < getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2]) + getDist(TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4], xEnd, yEnd))
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y1];
	                    PtsRelai[i_rel+1].X = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel+1].Y = TabZones[TabIntersection[i_zone]][y3];
	                    relay_point_number = 2;
	                }
	                else
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y2];
	                    PtsRelai[i_rel+1].X = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel+1].Y = TabZones[TabIntersection[i_zone]][y4];
	                    relay_point_number = 2;
	                }
	                path_found = true;
	            }
	            else if (posEnd == 6 || posEnd == 7)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y1];
	                relay_point_number = 1;
	                path_found = true;
	            }

	            break;

	        case 2:
	            if (posEnd == 5)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y4];
	                relay_point_number = 1;
	                path_found = true;
	            }
	            else if (posEnd == 6)
	            {
	                if ((getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1]) + getDist(TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1], xEnd, yEnd)) < (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4]) + getDist(TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4], xEnd, yEnd)))
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y1];
	                    relay_point_number = 1;
	                }
	                else
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y4];
	                    relay_point_number = 1;
	                }
	                path_found = true;
	            }
	            else if (posEnd == 7)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y1];
	                relay_point_number = 1;
	                path_found = true;
	            }

	            break;

	        case 3:
	            if (posEnd == 5 || posEnd == 6)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y4];
	                relay_point_number = 1;
	                path_found = true;
	            }
	            else if (posEnd == 7)
	            {
	                if (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2]) + getDist(TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1], xEnd, yEnd) < getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4]) + getDist(TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3], xEnd, yEnd))
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y2];
	                    PtsRelai[i_rel + 1].X = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel + 1].Y = TabZones[TabIntersection[i_zone]][y1];
	                    relay_point_number = 2;
	                }
	                else
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y4];
	                    PtsRelai[i_rel + 1].X = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel + 1].Y = TabZones[TabIntersection[i_zone]][y3];
	                    relay_point_number = 2;
	                }
	                path_found = true;
	            }
	            else if (posEnd == 0 || posEnd == 1)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y2];
	                relay_point_number = 1;
	                path_found = true;
	            }

	            break;

	        case 4:
	            if (posEnd == 7)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y3];
	                relay_point_number = 1;
	                path_found = true;
	            }
	            else if (posEnd == 0)
	            {
	                if ((getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2]) + getDist(TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2], xEnd, yEnd)) < (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3]) + getDist(TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3], xEnd, yEnd)))
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y2];
	                    relay_point_number = 1;
	                }
	                else
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y3];
	                    relay_point_number = 1;
	                }
	                path_found = true;
	            }
	            else if (posEnd == 1)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y2];
	                relay_point_number = 1;
	                path_found = true;
	            }

	            break;

	        case 5:
	            if (posEnd == 2 || posEnd == 3)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y4];
	                relay_point_number = 1;
	                path_found = true;
	            }
	            else if (posEnd == 1)
	            {
	                if (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3]) + getDist(TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1], xEnd, yEnd) < getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4]) + getDist(TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2], xEnd, yEnd))
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel + 1].Y = TabZones[TabIntersection[i_zone]][y3]; 
	                    PtsRelai[i_rel + 1].X = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y1];
	                    relay_point_number = 2;
	                }
	                else
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel + 1].Y = TabZones[TabIntersection[i_zone]][y4];
	                    PtsRelai[i_rel + 1].X = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y2]; 
	                    relay_point_number = 2;
	                }
	                path_found = true;
	            }
	            else if (posEnd == 7 || posEnd == 0)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y3];
	                relay_point_number = 1;
	                path_found = true;
	            }

	            break;

	        case 6:
	            if (posEnd == 3)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y4];
	                relay_point_number = 1;
	                path_found = true;
	            }
	            else if (posEnd == 2)
	            {
	                if ((getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1]) + getDist(TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1], xEnd, yEnd)) < (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4]) + getDist(TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4], xEnd, yEnd)))
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y1];
	                    relay_point_number = 1;
	                }
	                else
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y4];
	                    relay_point_number = 1;
	                }
	                path_found = true;
	            }
	            else if (posEnd == 1)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y1];
	                relay_point_number = 1;
	                path_found = true;
	            }

	            break;

	        case 7:
	            if (posEnd == 5 || posEnd == 4)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y3];
	                relay_point_number = 1;
	                path_found = true;
	            }
	            else if (posEnd == 3)
	            {
	                if (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1]) + getDist(TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2], xEnd, yEnd) < getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3]) + getDist(TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4], xEnd, yEnd))
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel + 1].Y = TabZones[TabIntersection[i_zone]][y1];
	                    PtsRelai[i_rel + 1].X = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y2];
	                    relay_point_number = 2;
	                }
	                else
	                {
	                    PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel + 1].Y = TabZones[TabIntersection[i_zone]][y3];
	                    PtsRelai[i_rel + 1].X = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y4];
	                    relay_point_number = 2;
	                }
	                path_found = true;
	            }
	            else if (posEnd == 2 || posEnd == 1)
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y1];
	                relay_point_number = 1;
	                path_found = true;
	            }


	            break;

	        case 8:

	            path_found = false;

	            break;

	        default:
	            path_found = false;
	            break;
	    }

	    i_rel = i_rel + relay_point_number;    
    }
 
}

/*
void checkIntersection(double pt1X, double pt1Y, double pt2X, double pt2Y)
{
	struct Coord spot;

	
	int isInZone = 0;
	int zoneToCheck = 0;
	enum{x1, y1, x2, y2, x3, y3, x4, y4};

	double dX = pt2X-pt1X;
	double dY = pt2Y-pt1Y;

	int i = 0;
	do
	{
		i++;

		//On calcule des points le long du trajet
		spot.X = (dX*i)/100;
		spot.Y = (dY*i)/100;

        isInZone = 0;

        //Pour chaque point du trajet on vérifie s'il est dans une zone
        for(zoneToCheck = 0; zoneToCheck < NbreZone_check; zoneToCheck++)
		{
	        //On vérifie si le point se trouve dans la zone interdite
			if ((spot.X+pt1X) >= TabZones[zoneToCheck][x1] && (spot.X+pt1X) <= TabZones[zoneToCheck][x4])
			{
				if ((spot.Y+pt1Y) >= TabZones[zoneToCheck][y1] && (spot.Y+pt1Y) <= TabZones[zoneToCheck][y4])
				{
					//Si on a déjà trouvé une intersection,
					if (intersection_found > 0)
					{
						//On vérifie si ce n'est pas avec la même zone alors on peut ajouter une intersection
						if (TabIntersection[intersection_found-1] != zoneToCheck)
						{
							TabIntersection[intersection_found] = zoneToCheck;
							intersection_found++;
						}
					}
					//Si c'est la première intersection qu'on trouve alors on l'ajoute
					else
					{
						TabIntersection[intersection_found] = zoneToCheck;
						intersection_found++;
					}
					
				}
					
					
			}
		}
			
	}while (i < 100);
}

int getPos(int px, int py, int rx1, int ry1, int rx4, int ry4)
{
    int pos;

    if (px > rx4)
    {
        if (py > ry4)
        {
            pos = 4; //Le point se trouve en bas à droite de la zone
        }
        else if (py > ry1)
        {
            pos = 3; //Le point se trouve à droite de la zone
        }
        else
        {
            pos = 2; //Le point se trouve en haut à droite de la zone
        }
    }
    else if (px > rx1)
    {
        if (py > ry4)
        {
            pos = 5; //Le point se trouve en bas de la zone
        }
        else if (py > ry1)
        {
            pos = 8; //Le point se trouve dans la zone
        }
        else
        {
            pos = 1; //Le point se trouve en haut de la zone
        }
    }
    else
    {
        if (py > ry4)
        {
            pos = 6; //Le point se trouve en bas à gauche de la zone
        }
        else if (py > ry1)
        {
            pos = 7; //Le point se trouve à gauche de la zone
        }
        else
        {
            pos = 0; //Le point se trouve en haut à gauche de la zone
        }
    }

    return pos;
        
}

void findRel(int posStart, int posEnd, int i_zone)
{
	int path_found = false;
    int relay_point_number = 0;   
    switch (posStart)
    {
	    case 0:
	        if (posEnd == 3)
	        {
	            PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y2];
	            relay_point_number = 1;
	            path_found = true;
	        }
	        else if (posEnd == 4)
	        {
	            if ((getDist(Pos_x, Pos_y, TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3]) + getDist(TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3], oXp, oYp)) > (getDist(Pos_x, Pos_y, TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2]) + getDist(TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2], oXp, oYp)))
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y2];
	                relay_point_number = 1;
	            }
	            else 
	            {
	                PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y3];
	                relay_point_number = 1;
	            }
	            path_found = true;
	        }
	        else if (posEnd ==5)
	        {
	        	PtsRelai[i_rel].X = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel].Y = TabZones[TabIntersection[i_zone]][y2];
	            relay_point_number = 1;
	            path_found = true;
	        }
	        break;

	    case 1:

	        break;

	    case 2:

	        break;

	    case 3:

	        break;

	    case 4:

	        break;

	    case 5:

	        break;

	    case 6:

	        break;

	    case 7:

	        break;

	    case 8:

	        break;

	    default :
	        path_found = false;
	        break;
    }

    i_rel = i_rel+relay_point_number;
}

void findPath()
{
	enum{x1, y1, x2, y2, x3, y3, x4, y4};

	

	//On récupère la position des deux points par rapport à la zone
	int pos1 = getPos(Pos_x, Pos_y, TabZones[TabIntersection[0]][x1], TabZones[TabIntersection[0]][y1], TabZones[TabIntersection[0]][x4], TabZones[TabIntersection[0]][y4]);
	int pos2 = getPos(oXp, oYp, TabZones[TabIntersection[0]][x1], TabZones[TabIntersection[0]][y1], TabZones[TabIntersection[0]][x4], TabZones[TabIntersection[0]][y4]);

	findRel(pos1, pos2, 0);

	checkIntersection(PtsRelai[0].X, PtsRelai[0].Y, oXp, oYp);

	if(intersection_found == 0)
	{
		goToObj();
	}
	else
	{
		pos1 = getPos(PtsRelai[0].X, PtsRelai[0].Y, TabZones[TabIntersection[0]][x1], TabZones[TabIntersection[0]][y1], TabZones[TabIntersection[0]][x4], TabZones[TabIntersection[0]][y4]);
		findRel(pos1, pos2, 1)
	}
	

}

void checkPath()
{
	checkIntersection(Pos_x, Pos_y, oXp, oYp);

	if(intersection_found == 0)
	{
		__DeplToDo(oType);
	}
	else
	{
		findPath();
	}

}
*/

#endif 