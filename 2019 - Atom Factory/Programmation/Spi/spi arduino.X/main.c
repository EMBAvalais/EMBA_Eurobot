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


//------------------------------------------------------------------------------------------
//-  Configuration du pic
//-  et déclarations des librairies
//------------------------------------------------------------------------------------------


#include <18F45k22.h>
#include <18F45K22_register.h>

#device adc=8

#use delay(crystal=20000000)

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES NOBROWNOUT            	//No brownout reset
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST               	//Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES NOPLLEN

#include <lcd216_8.c>


#bit CS     = PORTA.5

int8 test[16];

struct etat {
  unsigned int8 bras;
  unsigned int8 msg;
  unsigned int8 cam;
};

struct etat stat;

//*********************************************************************************************************************
// Fonction permettant d'initialiser le microcontroleur
//
// Développé par : Daniel Duay
// Date          : 15.04.2010 
// Révision      :
//
// paramètres    : none
// return        : none
//
//*********************************************************************************************************************
void init_uc(void) 
{
trisa = 0xDF;
trisb = 0xFF;
trisd = 0xFF;
trise = 0x00;
trisc = 0xD6;

#use spi (MASTER, MODE=0, BAUD=1000000, FORCE_HW)
}


//*********************************************************************************************************************
// Fonction permettant de lire l'état de l'arduino
//
// Développé par : Daniel Duay
// Date          : 07.02.2019 
// Révision      :
//
// paramètres    : structure contenant l'état des 3 variables
//                 bras variable pour sauvegarder l'état du bras
//                 msg variable pour signaler si les messages reçu par le slave sont corrects
//                 cam variable pour sauvegarder l'état de la caméra
// return        : retourne le status de l'arduino
//                 3 bits low bit 0..2(status du bras)       
//				   0-> Arret  (le bras a fini tout traitement et attend le prochain ordre)	
//				   1-> Marche (le bras est entrain d'exécuter l'ordre)													
//				   2-> Erreur bras
//                 2 bits middle bit 3..4 (réception message)
//				   0-> pas de message ou ordre pas traité
//				   1-> message reçu + checksum OK
//                 2-> erreur CRC réception message
//                 3 bits high bit 5..7 (status de la caméra)       
//				   0-> aucune détection (la caméra ne détecte aucun palet)	
//				   1-> détection niveau 1 (la caméra détecte un palet, le robot doit ralentir )													
//				   2-> détection niveau 2 (la caméra détecte un palet très proche, le robot doirt s'arrêter)													
//
//*********************************************************************************************************************
Read_etat_arduino(struct etat *value) 
{
unsigned int8 arduino_etat=0;

CS	= 0;
delay_us(1);
arduino_etat = spi_read(0x00);
value->bras =  (arduino_etat & 0x07);
value->msg =  (arduino_etat & 0x18) >> 3;
value->cam =  (arduino_etat & 0xE0) >> 5;
CS	= 1;
}

//*********************************************************************************************************************
// Fonction permettant de donner un ordre à l'arduino
//
// Développé par : Daniel Duay
// Date          : 07.02.2019 
// Révision      :
//
// paramètres    : cmd      = commande à exécuter (int8) valeur de 1 à 255
//                 taille   = longueur des datas à envoyer max. 16 bytes (int8)
//                 data     = valeur à envoyer (int8))
// return        : none
//													
//
//*********************************************************************************************************************
unsigned int8 Write_cmd_arduino(unsigned int8 cmd,unsigned int8 taille, unsigned int8 *data ) 
{
unsigned int8 boucle;
unsigned int8 crc;

if (taille > 16) taille = 16;           // taille du buffer max. à envoyer
CS	= 0;
delay_us(1);
spi_write(cmd);     // commande à envoyer
crc = cmd;
spi_write(taille);  // longueur des datas
crc = crc + taille;

for (boucle=0;boucle<taille;boucle++)   // data à envoyer
{
    spi_write(data[boucle]);        
    crc = crc + data[boucle];
}
crc = 0xFF - crc + 1;   // calcul du CRC
spi_write(crc);         // envoi du CRC
delay_us(10);
CS	= 1;
}

void main()
{


init_uc();
lcd_init();
 
lcd_gotoxy( 1, 1);
printf(lcd_putc,"TEST SPI");

stat.bras = 0;
stat.msg = 0;
stat.cam = 0;
 
while(1)
{
test = "test arduino 123";
Write_cmd_arduino(0x05,16, &test );
Read_etat_arduino(&stat);
lcd_gotoxy( 1, 2);
printf(lcd_putc,"ctrl : %u ",stat.msg);
delay_ms(1000);
test = "hello";
Write_cmd_arduino(0x02,5, &test );
Read_etat_arduino(&stat);
lcd_gotoxy( 1, 2);
printf(lcd_putc,"ctrl : %u ",stat.msg);
delay_ms(1000);
test = "Z";
Write_cmd_arduino(0x13,1, &test );
Read_etat_arduino(&stat);
lcd_gotoxy( 1, 2);
printf(lcd_putc,"ctrl : %u ",stat.msg);
delay_ms(1000);


}
}

    






