#include <math.h>
#include "TrigoCam.h"
#include <SD.h>

#define PI 3.14159265358979323846264338327950288419716939937510

//==============================================================
//InitCalc: Fonction d'initialisation de la position de la
//       caméra.
//==============================================================
void TrigoCam::InitCam(int OX, int OY, int HC, int OXC)
{
  //set les différentes variables
  offsetX = OX;
  offsetY = OY;
  HauteurCam = HC;
  offsetXCam = OXC;
}

void TrigoCam::SetCorrection(int CRX, int CRY)
{
  corrY = CRY;
  corrX = CRX;
}

double TrigoCam::getPosY(double nPixelsX, double nPixelsY)
{
  double angleY = (offsetY / HauteurCam)*2*PI/360;
  double angleY2 = (atan(angleY) + (40*2*PI/360));
  double tailleY = tan(angleY2) * HauteurCam - offsetY;
  posY = tailleY * nPixelsY / 199 + corrY;
  return((uint32_t)posY);
}

double TrigoCam::getPosX(double nPixelsX, double nPixelsY)
{
  double tailleX = CalcX(nPixelsY);
  double tailleXMax = CalcX(0);
  double X0_1 = (tailleXMax - tailleX) / 2;
  return((tailleX * (uint32_t)nPixelsX / 319) + corrX + X0_1);
}

double TrigoCam::CalcX(double nPixelsY)
{
  double angleY = (offsetY / HauteurCam)*2*PI/360;
  double angleY2 = (atan(angleY) + (40*2*PI/360));
  double tailleY = tan(angleY2) * HauteurCam - offsetY;
  posY = tailleY * nPixelsY / 199 + corrY;
  double beta = CalcBeta();
  double X1 = CalcX1(beta);
  double X2 = CalcX2(beta);
  double tailleX = X1 + X2;
  return(tailleX);
}

double TrigoCam::CalcX1(double Beta)
{
  double angleY = (offsetY / HauteurCam)*2*PI/360;
  double angleY2 = (atan(angleY) + (40*2*PI/360));
  double tailleY = tan(angleY2) * HauteurCam - offsetY;
  double HypCAmObj = sqrt((tailleY - posY + offsetY)*(tailleY - posY + offsetY) + HauteurCam*HauteurCam);
  double result = (tan(90*2*PI/360 - Beta) * HypCAmObj);
  return(result);
}

double TrigoCam::CalcX2(double Beta)
{
  double angleY = (offsetY / HauteurCam)*2*PI/360;
  double angleY2 = (atan(angleY) + (40*2*PI/360));
  double tailleY = tan(angleY2) * HauteurCam - offsetY;
  double HypCAmObj = sqrt((tailleY - posY + offsetY)*(tailleY - posY + offsetY) + HauteurCam*HauteurCam);
  double result = (tan(Beta - 30*2*PI/360) * HypCAmObj);
  return(result);
}

double TrigoCam::CalcBeta()
{
  double angleY = (offsetY / HauteurCam)*2*PI/360;
  double angleY2 = (atan(angleY) + (40*2*PI/360));
  double tailleY = tan(angleY2) * HauteurCam - offsetY;
  double HypMax = sqrt((tailleY + offsetY)*(tailleY + offsetY) + HauteurCam*HauteurCam);
  double HypMaxBeta = sqrt(HypMax * HypMax + (offsetXCam - offsetX) * (offsetXCam - offsetX));
  return(asin(HypMax / HypMaxBeta));
}
