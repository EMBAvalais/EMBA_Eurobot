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
//-  et d�clarations des librairies
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
// D�velopp� par : Daniel Duay
// Date          : 15.04.2010 
// R�vision      :
//
// param�tres    : none
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
// Fonction permettant de lire l'�tat de l'arduino
//
// D�velopp� par : Daniel Duay
// Date          : 07.02.2019 
// R�vision      :
//
// param�tres    : structure contenant l'�tat des 3 variables
//                 bras variable pour sauvegarder l'�tat du bras
//                 msg variable pour signaler si les messages re�u par le slave sont corrects
//                 cam variable pour sauvegarder l'�tat de la cam�ra
// return        : retourne le status de l'arduino
//                 3 bits low bit 0..2(status du bras)       
//				   0-> Arret  (le bras a fini tout traitement et attend le prochain ordre)	
//				   1-> Marche (le bras est entrain d'ex�cuter l'ordre)													
//				   2-> Erreur bras
//                 2 bits middle bit 3..4 (r�ception message)
//				   0-> pas de message ou ordre pas trait�
//				   1-> message re�u + checksum OK
//                 2-> erreur CRC r�ception message
//                 3 bits high bit 5..7 (status de la cam�ra)       
//				   0-> aucune d�tection (la cam�ra ne d�tecte aucun palet)	
//				   1-> d�tection niveau 1 (la cam�ra d�tecte un palet, le robot doit ralentir )													
//				   2-> d�tection niveau 2 (la cam�ra d�tecte un palet tr�s proche, le robot doirt s'arr�ter)													
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
// Fonction permettant de donner un ordre � l'arduino
//
// D�velopp� par : Daniel Duay
// Date          : 07.02.2019 
// R�vision      :
//
// param�tres    : cmd      = commande � ex�cuter (int8) valeur de 1 � 255
//                 taille   = longueur des datas � envoyer max. 16 bytes (int8)
//                 data     = valeur � envoyer (int8))
// return        : none
//													
//
//*********************************************************************************************************************
unsigned int8 Write_cmd_arduino(unsigned int8 cmd,unsigned int8 taille, unsigned int8 *data ) 
{
unsigned int8 boucle;
unsigned int8 crc;

if (taille > 16) taille = 16;           // taille du buffer max. � envoyer
CS	= 0;
delay_us(1);
spi_write(cmd);     // commande � envoyer
crc = cmd;
spi_write(taille);  // longueur des datas
crc = crc + taille;

for (boucle=0;boucle<taille;boucle++)   // data � envoyer
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

    






