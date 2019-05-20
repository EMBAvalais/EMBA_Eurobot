using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;

namespace Eurobot
{
    class PathFinder
    {
        public struct T_zoneInterdite
        {
            public Point A, B, C, D;
            public int Activated;

            //public T_zoneInterdite() { }
        }

        public struct Point_Valeur
        {
            public int actif;
            public int from;
            public float cout;
            public float cout_heur;
            //public Point_Valeur() { }
        }

        public Point_Valeur[] valeurs;
        public T_zoneInterdite[] zoneInterdites;
        public Point[] listPathFinding;

        public int listPathCount = 0;


        

        public PathFinder(DataGridView zonesIntDataGrid)
        {
            zoneInterdites = new T_zoneInterdite[zonesIntDataGrid.Rows.Count - 1];
            valeurs = new Point_Valeur[zoneInterdites.Count() * 4 + 2];
            listPathFinding = new Point[zoneInterdites.Count() * 4 + 2];

            for (int i = 0; i < zoneInterdites.Count(); i++)
            {
                zoneInterdites[i].Activated = 0;
            }

            for (int i = 0; i < zonesIntDataGrid.Rows.Count - 1; i++)
            {
                zoneInterdites[i].A = new Point(Convert.ToInt32(zonesIntDataGrid.Rows[i].Cells[1].Value), Convert.ToInt32(zonesIntDataGrid.Rows[i].Cells[2].Value));
                zoneInterdites[i].B = new Point(Convert.ToInt32(zonesIntDataGrid.Rows[i].Cells[3].Value), Convert.ToInt32(zonesIntDataGrid.Rows[i].Cells[4].Value));
                zoneInterdites[i].C = new Point(Convert.ToInt32(zonesIntDataGrid.Rows[i].Cells[5].Value), Convert.ToInt32(zonesIntDataGrid.Rows[i].Cells[6].Value));
                zoneInterdites[i].D = new Point(Convert.ToInt32(zonesIntDataGrid.Rows[i].Cells[7].Value), Convert.ToInt32(zonesIntDataGrid.Rows[i].Cells[8].Value));

                zoneInterdites[i].Activated = 1;
            }
        }


        ///============================================================================================
        /// void StartPathFinding()
        ///--------------------------------------------------------------------------------------------
        ///	Barman Corentin, 01.06.2014, V1.0
        ///--------------------------------------------------------------------------------------------
        /// Permet d'initialiser les données du pathfinder
        ///============================================================================================
        void StartPathFinding()
        {
            int i = 0;
            for (i = 0; i < valeurs.Count(); i++)
            {
                valeurs[i].actif = 0;
            }

            valeurs[0].actif = 2;
        }


        ///============================================================================================
        /// void EndPathFinding(int lastObjectif)
        ///--------------------------------------------------------------------------------------------
        ///	Barman Corentin, 01.06.2014, V1.0
        ///--------------------------------------------------------------------------------------------
        /// Lorsque le pathfinder a trouvé le meilleur chemin, cette fonction permet de terminer
        /// et de charger la liste des points qui devront être traversés
        ///============================================================================================
        void EndPathFinding(int lastObjectif, Point firstPoint)
        {
            int fromObj = lastObjectif;
            int temp;
            int count = 0;

            count++;

            //On parcourt le chemin calculé à l'envers jusqu'à trouver le point de départ
            //On ajoute les points de passages dans le tableau listPathFinding
            while (fromObj != 0)
            {
                temp = (fromObj - 1) % 4;
                if (temp == 0)
                {
                    listPathFinding[count].X = zoneInterdites[(fromObj - 1) / 4].A.X - 1;
                    listPathFinding[count].Y = zoneInterdites[(fromObj - 1) / 4].A.Y - 1;
                    count++;
                }
                else if (temp == 1)
                {
                    listPathFinding[count].X = zoneInterdites[(fromObj - 1) / 4].B.X + 1;
                    listPathFinding[count].Y = zoneInterdites[(fromObj - 1) / 4].B.Y - 1;
                    count++;
                }
                else if (temp == 2)
                {
                    listPathFinding[count].X = zoneInterdites[(fromObj - 1) / 4].C.X + 1;
                    listPathFinding[count].Y = zoneInterdites[(fromObj - 1) / 4].C.Y + 1;
                    count++;
                }
                else if (temp == 3)
                {
                    listPathFinding[count].X = zoneInterdites[(fromObj - 1) / 4].D.X - 1;
                    listPathFinding[count].Y = zoneInterdites[(fromObj - 1) / 4].D.Y + 1;
                    count++;
                }
                fromObj = valeurs[fromObj].from;
            }

            listPathFinding[count] = firstPoint;

            listPathCount = count;
        }


        ///============================================================================================
        /// int ChooseWay(Point *posActuelle, int objectif)
        ///--------------------------------------------------------------------------------------------
        ///	Barman Corentin, 01.06.2014, V1.0
        ///--------------------------------------------------------------------------------------------
        /// Cette fonction est la fonction principale du pathfinder, elle va tout d'abord initialiser
        /// le trajet en remmettant à 0 les valeurs. Puis, elle vérifiera tout d'abord si il est
        /// possible d'atteindre la position objectif directement, et si non va calculer toutes les
        /// options à partir de ce point. Les calculs seront rééfectués à partir du point possédant la
        /// meilleur pondération (parmis les pondérations précédentes et celles qui viennent d'être
        /// calculées) et ainsi de suite jusqu'à trouver la position d'arrivée.
        /// Le résultat est ensuite stocké dans une liste de valeurs qu'il faudra charger au fur et à
        /// mesure des déplacements effectuées.
        /// Cette fonction retourne 1 si un chemin a été trouvé, sinon elle retourne 0
        /// Ce type d'algorithme de pathfinder est appelé A*.
        ///============================================================================================
        public int PathFinder_ChooseWay(Point posActuelle, Point objectif, int nbr)
        {
            Point robotDestination = new Point();
            Point pointTemporaire = new Point();
            Point posActu = new Point();
            int i = 0;
            int current = 0;
            int countOverflow = 0;
            posActu.X = posActuelle.X;
            posActu.Y = posActuelle.Y;

            //Définis la position objectif
            robotDestination.X = objectif.X;
            robotDestination.Y = objectif.Y;

            listPathFinding[0].X = robotDestination.X;
            listPathFinding[0].Y = robotDestination.Y;

            StartPathFinding();

            //On lui laisse effectuer 30 opérations de calcul avant de déterminer qu'aucun chemin n'a été trouvé
            while (countOverflow < nbr)
            {
                countOverflow++;
                //Vérifie si on coupe une zone interdite
                if (PathFinder_CheckPath(posActu, robotDestination) == 1)
                {
                    //Cela signifie que le chemin est libre
                    EndPathFinding(current, posActuelle);
                    return 1;
                }

                //Calcul tous les chemins possibles
                for (i = 0; i < zoneInterdites.Count(); i++)
                {
                    if (zoneInterdites[i].Activated == 1)
                    {
                        //Charge une coordonnée
                        pointTemporaire.X = zoneInterdites[i].A.X - 1;
                        pointTemporaire.Y = zoneInterdites[i].A.Y - 1;
                        PathFinder_DefineBestObjectif(posActu, pointTemporaire, robotDestination, i * 4 + 1, current);

                        pointTemporaire.X = zoneInterdites[i].B.X + 1;
                        pointTemporaire.Y = zoneInterdites[i].B.Y - 1;
                        PathFinder_DefineBestObjectif(posActu, pointTemporaire, robotDestination, i * 4 + 2, current);

                        pointTemporaire.X = zoneInterdites[i].C.X + 1;
                        pointTemporaire.Y = zoneInterdites[i].C.Y + 1;
                        PathFinder_DefineBestObjectif(posActu, pointTemporaire, robotDestination, i * 4 + 3, current);

                        pointTemporaire.X = zoneInterdites[i].D.X - 1;
                        pointTemporaire.Y = zoneInterdites[i].D.Y + 1;
                        PathFinder_DefineBestObjectif(posActu, pointTemporaire, robotDestination, i * 4 + 4, current);
                    }
                }

                float currentCout = 400000;

                for (i = 0; i < valeurs.Count(); i++)
                {
                    if (valeurs[i].actif == 1 && valeurs[i].cout_heur < currentCout)
                    {
                        currentCout = valeurs[i].cout_heur;
                        current = i;
                    }
                }

                valeurs[current].actif = 2;

                int temp = (current - 1) % 4;
                if (temp == 0)
                {
                    posActu.X = zoneInterdites[(current - 1) / 4].A.X - 1;
                    posActu.Y = zoneInterdites[(current - 1) / 4].A.Y - 1;
                }
                else if (temp == 1)
                {
                    posActu.X = zoneInterdites[(current - 1) / 4].B.X + 1;
                    posActu.Y = zoneInterdites[(current - 1) / 4].B.Y - 1;
                }
                else if (temp == 2)
                {
                    posActu.X = zoneInterdites[(current - 1) / 4].C.X + 1;
                    posActu.Y = zoneInterdites[(current - 1) / 4].C.Y + 1;
                }
                else if (temp == 3)
                {
                    posActu.X = zoneInterdites[(current - 1) / 4].D.X - 1;
                    posActu.Y = zoneInterdites[(current - 1) / 4].D.Y + 1;
                }
            }
            EndPathFinding(current, posActuelle);
            return 0;
        }

        ///============================================================================================
        /// int intersectSegment(Point *A, Point *B, Point *I, Point *P)
        ///--------------------------------------------------------------------------------------------
        ///	Barman Corentin, 01.06.2014, V1.0
        ///--------------------------------------------------------------------------------------------
        /// Définis si le segment AB coupe le segment IP
        /// Retourne 0 si ils ne se touchent pas et 1 si oui
        ///============================================================================================
        int PathFinder_intersectSegment(Point A, Point B, Point I, Point P)
        {
            float t, u, denom;
            int denom_int = 0;
            Point D = new Point(), E = new Point();

            D.X = B.X - A.X;
            D.Y = B.Y - A.Y;
            E.X = P.X - I.X;
            E.Y = P.Y - I.Y;

            denom = D.X * E.Y - D.Y * E.X;
            denom_int = Convert.ToInt32(denom);

            if (denom_int == 0)
                return 0;   // erreur, cas limite, les deux segments sont parallèles
        			        // Ils ne se touchent donc pas

            t = -(A.X * E.Y - I.X * E.Y - E.X * A.Y + E.X * I.Y) / denom;

            if (t < 0 || t > 1)
                return 0; //Ne coupe pas


            u = -(-D.X * A.Y + D.X * I.Y + D.Y * A.X - D.Y * I.X) / denom;

            if (u < 0 || u > 1)
                return 0; //Ne coupe pas

            return 1; //Coupe donc le segment
        }



        ///============================================================================================
        /// void DefineBestObjectif(Point *pbase, Point *temp, Point *destination, int numberChoosed, int start)
        ///--------------------------------------------------------------------------------------------
        ///	Barman Corentin, 01.06.2014, V1.0
        ///--------------------------------------------------------------------------------------------
        /// Cette fonction permet de déterminer la pondération de chaque point (son cout, sa distance)
        /// La pondération de chaque point est calculée une seule fois dans tout l'algorithme, et on 
        /// stocke également le point par lequel on provient afin de pouvoir déterminer plus tard le 
        /// chemin le plus court à emprunter
        ///============================================================================================
        void PathFinder_DefineBestObjectif(Point pbase, Point temp, Point destination, int numberChoosed, int start)
        {
            //Vérifie si on peut se rendre au point de la zone interdite ainsi que si le point n'a pas déjà été calculé
            //Si non on ne fait pas les calculs suivants, car le point n'est pas un objectif valide depuis l'endroit où l'on se trouve
            if (PathFinder_CheckPath(pbase, temp) == 1 && valeurs[numberChoosed].actif != 2)
            {
                //Cela signifie que le chemin est libre
                //Calcul de la distance à vol d'oiseau jusqu'à l'objectif
                float distance, dist_1, dist_2;
                float d_x, d_y;

                d_x = temp.X - pbase.X;
                d_y = temp.Y - pbase.Y;

                dist_1 = (d_x * d_x) + (d_y * d_y);
                dist_1 = (float)Math.Sqrt(dist_1);

                //Calcul de la distance à vol d'oiseau jusqu'à la destination
                d_x = destination.X - temp.X;
                d_y = destination.Y - temp.Y;

                dist_2 = (d_x * d_x) + (d_y * d_y);
                dist_2 = (float)Math.Sqrt(dist_2);

                //Cela donne le coût du déplacement
                distance = dist_1 + valeurs[start].cout;

                if (distance < valeurs[numberChoosed].cout || valeurs[numberChoosed].actif == 0)
                {
                    valeurs[numberChoosed].cout = distance;
                    valeurs[numberChoosed].cout_heur = distance + dist_2;
                    valeurs[numberChoosed].from = start;
                }

                //Active le point pour ne pas refaire le calcul
                valeurs[numberChoosed].actif = 1;
            }
        }


        ///============================================================================================
        /// int CheckPath(float pbaseX, float pbaseY, float objectifX, float objectifY)
        ///--------------------------------------------------------------------------------------------
        ///	Barman Corentin, 01.06.2014, V1.0
        ///--------------------------------------------------------------------------------------------
        /// Cette fonction vérifie si le trajet direct entre la position pbase et objectif rentre 
        /// en intersection avec une des zones interdites.
        ///============================================================================================
        int PathFinder_CheckPath(Point pbase, Point objectif)
        {
            int i = 0;

            if (pbase.X == objectif.X && pbase.Y == objectif.Y)
                return 0;

            //Test si on peut aller directement à l'objectif
            for (i = 0; i < zoneInterdites.Count(); i++)
            {
                //Regarde si la zone interdite est activée
                if (zoneInterdites[i].Activated == 1)
                {
                    //Vérifie si on coupe un des segment
                    if (PathFinder_intersectSegment(pbase, objectif, zoneInterdites[i].A, zoneInterdites[i].B) == 1)
                        return 0;
                    if (PathFinder_intersectSegment(pbase, objectif, zoneInterdites[i].B, zoneInterdites[i].C) == 1)
                        return 0;
                    if (PathFinder_intersectSegment(pbase, objectif, zoneInterdites[i].C, zoneInterdites[i].D) == 1)
                        return 0;
                    if (PathFinder_intersectSegment(pbase, objectif, zoneInterdites[i].D, zoneInterdites[i].A) == 1)
                        return 0;
                }
            }

            return 1;
        }
    }
}
