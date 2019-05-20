///============================================================================================
///	void MoveServo(int number, int position)
///--------------------------------------------------------------------------------------------
///	Michel Jonathan, 13.04.2015, V1.0
///--------------------------------------------------------------------------------------------
///	Permet de modifier la valeur de consigne (l'angle) d'un servomoteur
///	Position défini la longueur de l'impulsion en [100us]
///============================================================================================
void MoveServo(int number, int position)
{
	// Protection pour ne pas bloquer le servo en butée
	if(position < MINSERVOPOSITION)
		position = MINSERVOPOSITION;
	
	if (position > MAXSERVOPOSITION)
		position = MAXSERVOPOSITION;
	// Définition de position du servomoteur
	ServoTab[number].Position = position;
	
	enable_interrupts(INT_TIMER2);
	delay_ms(500);

	disable_interrupts(INT_TIMER2);
}

///============================================================================================
/// void SetServo(int number, int state)
///--------------------------------------------------------------------------------------------
///	Michel Jonathan, 13.04.2015, V1.0
///--------------------------------------------------------------------------------------------
///	Permet de définir la sortie propre à chaque servomoteur
///	output_bit() demande l'adresse du bit utilisé (par exemple avec un "#define PIN_A3 5651")
///============================================================================================
void SetServo(int number, int state)
{
	switch (number)
	{
		case 0:		// Pour le servomoteur droit
			output_bit(PIN_D6,state);	
			break;
		default :
			break;
	}
	
}

///============================================================================================
/// void CheckServo()
///--------------------------------------------------------------------------------------------
///	Michel Jonathan, 16.04.2015, V1.0
///--------------------------------------------------------------------------------------------
///	Gère la commande des servomoteurs
///	Doit être appelé toutes les 100us
///============================================================================================
void CheckServo()
{
	int i;
	for (i = 0; i < MAXSERVO; i++)
	{
		if(ServoTab[i].Count<ServoTab[i].Position)
		{
			// Ton
			SetServo(i,1);
			ServoTab[i].Count++;
		} 
		else 
		{
			if(ServoTab[i].Count<197) 
			{
				// Toff
				SetServo(i,0);
				ServoTab[i].Count++;
			} 
			else 
			{
				// Fin de la période
				ServoTab[i].Count = 0;
			}
		}
	}
}

///============================================================================================
/// void OpenServo(int number)
///--------------------------------------------------------------------------------------------
///	Michel Jonathan, 16.04.2015, V1.0
///--------------------------------------------------------------------------------------------
///	Déplace un servomoteur à sa position ouverte définie avec ServoTab[x].OpenValue
///============================================================================================
void OpenServo(int number)
{
	MoveServo(number, ServoTab[number].OpenValue);
}
///============================================================================================
/// void CloseServo(int number)
///--------------------------------------------------------------------------------------------
///	Michel Jonathan, 16.04.2015, V1.0
///--------------------------------------------------------------------------------------------
///	Déplace un servomoteur à sa position fermée définie avec ServoTab[x].CloseValue
///============================================================================================
void CloseServo(int number)
{
	MoveServo(number, ServoTab[number].CloseValue);
}

///	Initialisation de la structure des servomoteurs:
void __Init_Servos(void)
{
	unsigned int8 i=0;
	for (i = 0; i < MAXSERVO; i++)
	{
		ServoTab[i].Position = 0;
		ServoTab[i].Count = 0;
	}

	///	Configuration du TIMER2 pour 100us:
///--------------------------------------------------------------------
	setup_timer2(TMR_INTERNAL, 1973);
	// 1/((80MHz)/4)*1*2000 = 100us
	enable_interrupts(INT_TIMER2);
}

///	Interruption TIMER2
///--------------------------------------------------------------------
#INT_TIMER2 HIGH
void timer2_isr()
{
	set_timer2(0);
	CheckServo();
 }