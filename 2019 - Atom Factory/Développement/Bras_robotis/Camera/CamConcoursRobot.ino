#include "TrigoCam.h"
#include <Pixy2.h>
#include <SD.h>

Pixy2 pixy;
TrigoCam Cam;

int incomingByte = 0;  // for incoming serial data

// the setup function runs once when you press reset or power the board
void setup() 
{
  Serial.begin(9600);
  pixy.init();
  Cam.InitCam(0,-8,162,124);
  Cam.SetCorrection(5,5);
}

// the loop function runs over and over again forever
void loop() 
{
  double posY = Cam.getPosY(pixy.ccc.blocks[0].m_x, pixy.ccc.blocks[0].m_y);
  double posX = Cam.getPosX(pixy.ccc.blocks[0].m_x, pixy.ccc.blocks[0].m_y);
  double Send = ((posX)*1000 + (posY));
  Serial.print("POSITION X:");
  Serial.print('\t');
  Serial.println(posX);
  Serial.print("POSITION Y:");
  Serial.print('\t');
  Serial.println(posY);
  Serial.println("");
}
