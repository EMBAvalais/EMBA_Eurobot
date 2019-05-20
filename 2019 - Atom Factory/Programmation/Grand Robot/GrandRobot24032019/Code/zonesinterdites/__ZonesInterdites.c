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

//*********************************************************************************************************************
// checkPath
//
// Cette fonction permet de vérifier si le trajet du point A à B passe sur une zone interdite
//
// Developpe par : Aurélien Rithner
// Date :          16.10.2018
// Revision :		V1.0
//
// parametres  : -
// return      : -
//
//*********************************************************************************************************************
int checkPath()
{
	path_found = 0;
		
    start_point_X = Pos_x;
    start_point_Y = Pos_y;

    end_point_X = oXp;
    end_point_Y = oYp;

    checkIntersection(start_point_X, start_point_Y, end_point_X, end_point_Y);
		
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

void checkPtsRelai()
{
	//On vérifie si un des points relais se trouve trop près du bord
	path_tooclose = 0;
    int i = 1;
    do
    {
    	if(PtsRelai[i_rel - i][X] < (MARGE/2) || PtsRelai[i_rel - i][Y] < (MARGE/2) || PtsRelai[i_rel - i][X] > (SIZE_TABLE_X-(MARGE/2)) || PtsRelai[i_rel - i][Y] > (SIZE_TABLE_Y-(MARGE/2)))
    	{
    		path_tooclose = 1;
    	}
    	i++;

    }while(!path_tooclose && i <= relay_point_number);

	if(path_impossible == 0)
	{
	    //Alors on recalcul le trajet en passant par l'autre côté de la zone interdite
	    if(path_tooclose)
	    {
	    	path_opposite = 1;
	    	i_rel = i_rel-relay_point_number;
	    	findRel(PtsRelai[i_rel - 1][X], PtsRelai[i_rel - 1][Y], end_point_X, end_point_Y, 0);
	    }
	}
	else
	{
		//Alors on recalcul le trajet en passant par l'autre côté de la zone interdite
	    if(path_tooclose)
	    {
	    	__Stop();
	    }
	    else
	    {
		    path_impossible = 0;
		} 
		
	}	    


}

//*********************************************************************************************************************
// findPath
//
// Cette fonction permet de trouver le trajet pour arriver à la destination en évitant les zones interdites
//
// Developpe par : Aurélien Rithner
// Date :          16.10.2018
// Revision :		V1.0
//
// parametres  : -
// return      : -
//
//*********************************************************************************************************************
void findPath()
{
   	int i = 0;
   	int exit = 0;
    //Si on intercepte encore une zone alors intersection_found sera > 0
    while(intersection_found > 0 && !exit && !flag_end)
    {
        //Tant qu'on intercepte une zone depuis le point relai on continue à en chercher un autre
        i++;
        
        if(path_impossible == 1)
        {
       	 	path_opposite = 1;
       	}
       	else
       	{
	      	path_opposite = 0;
	    }
	      								 
        
        //On trouve le premier point relai
        findRel(PtsRelai[i_rel - 1][X], PtsRelai[i_rel - 1][Y], end_point_X, end_point_Y, 0);
        
        //On vérifie si un des points relais se trouve trop près du bord
   		//Si c'est le cas alors on a recalculé le trajet en passant de l'autre côté de la zone
        checkPtsRelai();
        if(path_impossible == 1)
        {
	        exit = 1;
	    } 
        //On vérifie si depuis le premier point relai on intercepte encore une zone
        checkIntersection(PtsRelai[i_rel - 1][X], PtsRelai[i_rel - 1][Y], end_point_X, end_point_Y);
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
int16 getDist(int16 x1, int16 y1, int16 x2, int16 y2)
{
    return (sqrt(pow(fabs(x2-x1),2)) + (pow(fabs(y2-y1),2)));
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
void checkIntersection(int16 pt1X, int16 pt1Y, int16 pt2X, int16 pt2Y)
{
	

    int zoneToCheck = 0;

    intersection_found = 0;

    int j;
    for ( j= 0; j < 10; j++)
    {
        TabIntersection[j] = 0;
    }
    

    signed int32 dX = pt2X-pt1X;
    signed int32 dY = pt2Y-pt1Y;

    int i = 0;

    do
    {
        i++;

        //On calcule des points le long du trajet
        spot_X = (dX*i)/100;
        spot_Y = (dY*i)/100;


        //Pour chaque point du trajet on vérifie s'il est dans une zone
        for(zoneToCheck = 0; zoneToCheck < 10; zoneToCheck++)
        {
            //On vérifie si le point se trouve dans la zone interdite
	        if ((spot_X+pt1X) > TabZones[zoneToCheck][0] && (spot_X+pt1X) < TabZones[zoneToCheck][2])
	        {
		        if ((spot_Y+pt1Y) > TabZones[zoneToCheck][1] && (spot_Y+pt1Y) < TabZones[zoneToCheck][3])
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
int getPos(int16 px, int16 py, int16 rx1, int16 ry1, int16 rx4, int16 ry4)
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
void findRel(int16 xStart, int16 yStart, int16 xEnd, int16 yEnd, int i_zone)
{
	//On récupère la position des deux points par rapport à la zone
    int posStart = getPos(xStart, yStart, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][1], TabZones[TabIntersection[i_zone]][2], TabZones[TabIntersection[i_zone]][y4]);
    int posEnd = getPos(xEnd, yEnd, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][1], TabZones[TabIntersection[i_zone]][2], TabZones[TabIntersection[i_zone]][y4]);

    relay_point_number = 0;



    if(posStart == 8 || posEnd == 8)
    {
    	path_found = 0;
    	//path_impossible = 1;
    }	
    else
    {
	    switch (posStart)
	    {
	        case 0:

	        	if(path_opposite)
			    {
			    	if (posEnd == 3)
		            {

		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3];
	                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y4];
	                    relay_point_number = 2;
		                path_found = true;
		            }
		            else if (posEnd == 4)
		            {
		                if ((getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3]) + getDist(TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3], xEnd, yEnd)) > (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2]) + getDist(TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2], xEnd, yEnd)))
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3];
		                    relay_point_number = 1;
		                }
		                else
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                    relay_point_number = 1;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 5)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
	                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y4];
	                    relay_point_number = 2;
		                path_found = true;
		            }
			    }
			    else
			    {
	            	if (posEnd == 3)
		            {

		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                relay_point_number = 1;
		                path_found = true;
		            }
		            else if (posEnd == 4)
		            {
		                if ((getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3]) + getDist(TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3], xEnd, yEnd)) > (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2]) + getDist(TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2], xEnd, yEnd)))
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                    relay_point_number = 1;
		                }
		                else
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3];
		                    relay_point_number = 1;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 5)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y4];

		                relay_point_number = 2;
		                path_found = true;
		            }
			    }


	            break;

	        case 1:
	        	if(path_opposite)
	        	{
	    			if (posEnd == 3)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y3];
		                PtsRelai[i_rel+2][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel+2][Y] = TabZones[TabIntersection[i_zone]][y4];
		                relay_point_number = 3;
		                path_found = true;
		            }
		            else if (posEnd == 4)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y3];
		                relay_point_number = 2;
		                path_found = true;
		            }
		            else if (posEnd == 5)
		            {
		                if (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1]) + getDist(TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3], xEnd, yEnd) < getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2]) + getDist(TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4], xEnd, yEnd))
		                {
		                	PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y4];
		                    relay_point_number = 2;
		                }
		                else
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y3];		                    
		                    relay_point_number = 2;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 6)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y4];
		                relay_point_number = 2;
		                path_found = true;
		            }
		            else if(posEnd == 7)
		            {
		            	PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y4];
		                PtsRelai[i_rel+2][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel+2][Y] = TabZones[TabIntersection[i_zone]][y3];
		                relay_point_number = 3;
		            }
	        	}
	        	else
	        	{
		            if (posEnd == 3 || posEnd == 4)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                relay_point_number = 1;
		                path_found = true;
		            }
		            else if (posEnd == 5)
		            {
		                if (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1]) + getDist(TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3], xEnd, yEnd) < getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2]) + getDist(TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4], xEnd, yEnd))
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y3];
		                    relay_point_number = 2;
		                }
		                else
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y4];
		                    relay_point_number = 2;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 6 || posEnd == 7)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                relay_point_number = 1;
		                path_found = true;
		            }
	            }	
	            break;

	        case 2:

	        	if(path_opposite)
	        	{
	        		if (posEnd == 5)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                relay_point_number = 1;
		                path_found = true;
		            }
		            else if (posEnd == 6)
		            {
		                if ((getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1]) + getDist(TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1], xEnd, yEnd)) < (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4]) + getDist(TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4], xEnd, yEnd)))
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                    relay_point_number = 1;
		                }
		                else
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                    relay_point_number = 1;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 7)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y3];
		                relay_point_number = 2;
		                path_found = true;
		            }
	        	}
	        	else
	        	{
		            if (posEnd == 5)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                relay_point_number = 1;
		                path_found = true;
		            }
		            else if (posEnd == 6)
		            {
		                if ((getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1]) + getDist(TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1], xEnd, yEnd)) < (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4]) + getDist(TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4], xEnd, yEnd)))
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                    relay_point_number = 1;
		                }
		                else
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                    relay_point_number = 1;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 7)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                relay_point_number = 1;
		                path_found = true;
		            }
		        }

	            break;

	        case 3:

	        	if(path_opposite)
	        	{
	        		if(posEnd == 5)
		            {
		            	PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y1];
		                PtsRelai[i_rel+2][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel+2][Y] = TabZones[TabIntersection[i_zone]][y3];
		                relay_point_number = 3;
		                path_found = true;
		            }
		            else if (posEnd == 6)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y1];
		                relay_point_number = 2;
		                path_found = true;
		            }
		            else if (posEnd == 7)
		            {
		                if (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2]) + getDist(TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1], xEnd, yEnd) < getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4]) + getDist(TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3], xEnd, yEnd))
		                {
		                	PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y3];
		                    
		                    relay_point_number = 2;
		                }
		                else
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y1];
		                    relay_point_number = 2;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 0)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y3];
		                relay_point_number = 2;
		                path_found = true;
		            }
		            else if (posEnd == 1)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y3];
		                PtsRelai[i_rel+2][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel+2][Y] = TabZones[TabIntersection[i_zone]][y1];
		                relay_point_number = 3;
		                path_found = true;
		            }
	        	}
	        	else
	        	{
	        		if(posEnd == 5 || posEnd == 6)
		            {
		            	PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                relay_point_number = 1;
		                path_found = true;
		            }
		            else if (posEnd == 7)
		            {
		                if (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2]) + getDist(TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1], xEnd, yEnd) < getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4]) + getDist(TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3], xEnd, yEnd))
		                {
		                	PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y1];
		                    
		                    relay_point_number = 2;
		                }
		                else
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y3];
		                    relay_point_number = 2;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 0 || posEnd == 1)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                relay_point_number = 1;
		                path_found = true;
		            }
		            
	        	}
	            
	            

	            break;

	        case 4:

	        	if(path_opposite)
	        	{
	        		if (posEnd == 7)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y1];
		                relay_point_number = 2;
		                path_found = true;
		            }
		            else if (posEnd == 0)
		            {
		                if ((getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2]) + getDist(TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2], xEnd, yEnd)) < (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3]) + getDist(TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3], xEnd, yEnd)))
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3];
		                    relay_point_number = 1;
		                }
		                else
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                    relay_point_number = 1;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 1)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y1];
		                relay_point_number = 2;
		                path_found = true;
		            }
	        	}
	        	else
	        	{
		            if (posEnd == 7)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3];
		                relay_point_number = 1;
		                path_found = true;
		            }
		            else if (posEnd == 0)
		            {
		                if ((getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2]) + getDist(TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2], xEnd, yEnd)) < (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3]) + getDist(TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3], xEnd, yEnd)))
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                    relay_point_number = 1;
		                }
		                else
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3];
		                    relay_point_number = 1;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 1)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y2];
		                relay_point_number = 1;
		                path_found = true;
		            }
		        }
	            break;

	        case 5:

	        	if(path_opposite)
	        	{
	        		if (posEnd == 2)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y1];
		                relay_point_number = 2;
		                path_found = true;
		            }
		            else if (posEnd == 3)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y1];
		                PtsRelai[i_rel+2][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel+2][Y] = TabZones[TabIntersection[i_zone]][y2];
		                relay_point_number = 3;
		                path_found = true;
		            }
		            else if (posEnd == 1)
		            {
		                if (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3]) + getDist(TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1], xEnd, yEnd) < getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4]) + getDist(TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2], xEnd, yEnd))
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y2];
		                    relay_point_number = 2;
		                }
		                else
		                {
		                	PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3]; 
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y1];
		                     
		                    relay_point_number = 2;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 7)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y2];
		                PtsRelai[i_rel+2][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel+2][Y] = TabZones[TabIntersection[i_zone]][y1];
		                relay_point_number = 3;
		                path_found = true;
		            }
		            else if(posEnd == 0)
		            {
						PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y2];
		                relay_point_number = 2;
		                path_found = true;
		            }
	        	}
	        	else
	        	{
		            if (posEnd == 2 || posEnd == 3)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                relay_point_number = 1;
		                path_found = true;
		            }
		            else if (posEnd == 1)
		            {
		                if (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3]) + getDist(TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1], xEnd, yEnd) < getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4]) + getDist(TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2], xEnd, yEnd))
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3]; 
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y1];
		                    relay_point_number = 2;
		                }
		                else
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y2]; 
		                    relay_point_number = 2;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 7 || posEnd == 0)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3];
		                relay_point_number = 1;
		                path_found = true;
		            }
				}
	            break;

	        case 6:

	        	if(path_opposite)
	        	{
        			
	                if (posEnd == 3)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y2];
		                relay_point_number = 2;
		                path_found = true;
		            }
		            else if (posEnd == 2)
		            {
		                if ((getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1]) + getDist(TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1], xEnd, yEnd)) < (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4]) + getDist(TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4], xEnd, yEnd)))
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                    relay_point_number = 1;
		                }
		                else
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                    relay_point_number = 1;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 1)
		            {
						PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y2];
		                relay_point_number = 2;
		                path_found = true;
		            }
	        	}
	        	else
	        	{
		            if (posEnd == 3)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                relay_point_number = 1;
		                path_found = true;
		            }
		            else if (posEnd == 2)
		            {
		                if ((getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1]) + getDist(TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1], xEnd, yEnd)) < (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4]) + getDist(TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4], xEnd, yEnd)))
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                    relay_point_number = 1;
		                }
		                else
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y4];
		                    relay_point_number = 1;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 1)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                relay_point_number = 1;
		                path_found = true;
		            }
	            }
	            break;

	        case 7:

	        	if(path_opposite)
	        	{
	        		if (posEnd == 5)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y2];
		                PtsRelai[i_rel+2][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel+2][Y] = TabZones[TabIntersection[i_zone]][y4];
		                relay_point_number = 3;
		                path_found = true;
		            }
		            if (posEnd == 4)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y2];
		                relay_point_number = 2;
		                path_found = true;
		            }
		            else if (posEnd == 3)
		            {
		                if (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1]) + getDist(TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2], xEnd, yEnd) < getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3]) + getDist(TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4], xEnd, yEnd))
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3];
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y4];
		                    relay_point_number = 2;
		                }
		                else
		                {
		                	PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y2];
		                    relay_point_number = 2;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 2)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y4];
		                relay_point_number = 2;
		                path_found = true;
		            }
		            else if (posEnd == 1)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3];
		                PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y4];
		                PtsRelai[i_rel+2][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel+2][Y] = TabZones[TabIntersection[i_zone]][y2];
		                relay_point_number = 3;
		                path_found = true;
		            }
	        	}
	        	else
	        	{
		            if (posEnd == 5 || posEnd == 4)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3];
		                relay_point_number = 1;
		                path_found = true;
		            }
		            else if (posEnd == 3)
		            {
		                if (getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x1], TabZones[TabIntersection[i_zone]][y1]) + getDist(TabZones[TabIntersection[i_zone]][x2], TabZones[TabIntersection[i_zone]][y2], xEnd, yEnd) < getDist(xStart, yStart, TabZones[TabIntersection[i_zone]][x3], TabZones[TabIntersection[i_zone]][y3]) + getDist(TabZones[TabIntersection[i_zone]][x4], TabZones[TabIntersection[i_zone]][y4], xEnd, yEnd))
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x2]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y2];
		                    relay_point_number = 2;
		                }
		                else
		                {
		                    PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x3]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y3];
		                    PtsRelai[i_rel+1][X] = TabZones[TabIntersection[i_zone]][x4]; PtsRelai[i_rel+1][Y] = TabZones[TabIntersection[i_zone]][y4];
		                    relay_point_number = 2;
		                }
		                path_found = true;
		            }
		            else if (posEnd == 2 || posEnd == 1)
		            {
		                PtsRelai[i_rel][X] = TabZones[TabIntersection[i_zone]][x1]; PtsRelai[i_rel][Y] = TabZones[TabIntersection[i_zone]][y1];
		                relay_point_number = 1;
		                path_found = true;
		            }
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


#endif 