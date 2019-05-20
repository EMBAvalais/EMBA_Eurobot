//------------------------------------------------------------------------------------------
//-                        SPI arduino
//-
//-   NOM:       Programme principal
//-   Date:      30.01.2019
//-   Version:   1.0
//-   Auteur:    Daniel Duay
//-
//-
//-   description:
//-   Ce programme permet de tester la communication entre un arduino et un pic18f45k22 en utilisant le bus SPI
//-
//-
//-
//-
//------------------------------------------------------------------------------------------


// include the SPI library:
#include <SPI.h>

struct STRUCT_SPI {
  byte cmd;
  char data [17];
};

STRUCT_SPI spi_pic;
volatile byte pt_pos;
volatile boolean data_ok;
volatile byte status_slave;


void SlaveInit(void) 
{

  // turn on SPI in slave mode 
  SPCR |= _BV(SPE);
  pinMode(MISO, OUTPUT);

  // turn on interrupts
  SPCR |= _BV(SPIE);
  
 
  // get ready for an interrupt 
  pt_pos = 0;   // buffer empty
  data_ok = false;
  status_slave = 0;
}


void setup() {
  Serial.begin(9600);
  SlaveInit();
}


// SPI interrupt routine
ISR (SPI_STC_vect)
{
byte caract = SPDR;                              // grab byte from SPI Data Register
static byte crc;
static byte taille;
static byte cmd;

status_slave = status_slave & 0xE7;                       // reset Data Register


  if(pt_pos == 0 && caract != 0 ) cmd = caract;          // sauve la commande à exécuter
  else if (pt_pos == 0 && caract == 0 ) cmd = 0;

    if (cmd > 0)
    {
      if(pt_pos == 0)
        {
          data_ok = false;
          crc = 0;
        }
      else if (pt_pos == 1)
        {
          if (caract <= 16) taille = caract + 2;         // sauve la taille des datas à recevoir + offset du byte de commande et de taille
          else taille = 18; 
        }  
      else if (pt_pos < taille)
        {
            spi_pic.data [pt_pos -2] = caract;
        }
      else if (pt_pos == taille)
        {
            crc = crc + caract;
            if (crc == 0)           // check le CRC si OK
              {
                data_ok = true;
                spi_pic.cmd = cmd;
                spi_pic.data [pt_pos -2] = '\0';
                status_slave = status_slave | 0x08;                        // indique au master que le message et le CRC est correct
              }  
            else 
            {
                status_slave = status_slave | 0x10;                        // indique au master que le CRC du message est incorrect
            }
            pt_pos = 0;
        }   
    
      crc = crc + caract;
      pt_pos++;
    }
    
    SPDR = status_slave;
}

void loop() 
{
  if (digitalRead (SS) == HIGH) pt_pos = 0;
     
    
  if (data_ok == 1)
      {
      Serial.print ("Commande : ");
      Serial.println (spi_pic.cmd);
      Serial.print ("Data : ");
      Serial.println (spi_pic.data);
      pt_pos = 0;
      data_ok = false;
      } 
    
}
