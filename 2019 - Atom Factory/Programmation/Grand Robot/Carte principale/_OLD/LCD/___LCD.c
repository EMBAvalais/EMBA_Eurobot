/*
* \file ___LCD.c
* \brief G�re l'afficheur LCD I2C (fcts.)
* \ EMVs Eurobot - Driver Moteur
* \author Amand Axel
* \version 2.0
* \date 20.11.2015
* \copyright GNU Public License
*/

#ifndef ___LCD_C
#define ___LCD_C

void __Init_LCD(void)
{
	// Config LCD IIC
	i2c_start();
	i2c_write(0x50);	// Adresse du LCD
	i2c_write(0xFE);	// Commande
	i2c_write(0x52);	// Contraste
	i2c_write(0x24);	// 36 sur 50
	i2c_write(0xFE);	// Commande
	i2c_write(0x53);	// Brightness backlight
	i2c_write(6);		// 6 sur 8
	i2c_write(0xFE);	// Commande
	i2c_write(0x51);	// Efface l'�cran
	i2c_stop();
	
	// Quitte la fonction
	return;
}

// __ClearLCD
// Ne prend rien.
// Ne retourne rien.
void __ClearLCD(void)
{
	// Start l'I2C
	i2c_start();

	// Se connecte au LCD
	i2c_write(0x50);

	// Clear le LCD
	i2c_write(0xFE);
	i2c_write(0x51);

	// Ferme la liaison I2C
	i2c_stop();

	// Quitte la fonction
	return;
}

// __WriteLCD
// Ecrit ou envoi une commande au LCD.
// Prend quoi �crire.
// Ne retourne rien.
void __WriteLCD(unsigned int8 _Command)
{
	// Start l'I2C
	i2c_start();
unsigned int8 ack=i2c_write(0x50);
	// Se connecte au LCD
	if(ack==0)
	// Ecrit ou envoi la comande au LCD
	i2c_write(_Command);

	// Ferme la liaison I2C
	i2c_stop();

	// Quitte la fonction
	return;
}

// __WriteCount
// Permet d'�crire la valeur de la roue folle.
// Prend la valeur � �crire et le mode (0 = �crit. int, 1 = �crit. float tronqu�)
// Ne retourne rien.
void __WriteCount(float64 _Value, int1 _Mode)
{
	// Index d'affichage
	unsigned int8 IAff=0, TabValue[16];
	
	// Selon mode d'affichage choisi
	// Transforme le nombre en cha�ne de caract�re
	if(_Mode == 0)
	sprintf(TabValue,"%7Ld ",(int32)_Value);
	else	
	sprintf(TabValue,"%6.3f ",(float64)_Value);
		
	// Affiche les caract�res � la suite
	while(TabValue[IAff]!=0x00)
	{
		__WriteLCD(TabValue[IAff]);
		Iaff++;
	}	

	// Quitte la fonction
	return;	
}	

// __SautLig
// Saute � la seconde ligne
// Ne prend rien.
// Ne retourne rien.
void __SautLig(unsigned int8 _Lig)
{
	// Start l'I2C
	i2c_start();

	// Se connecte au LCD
	i2c_write(0x50);

	// Saute � la seconde ligne
	i2c_write(0xFE);
	i2c_write(0x45);
	i2c_write(_Lig);
	// Ferme la liaison I2C
	i2c_stop();
	
	// Quitte la fonction
	return;	
}

#endif