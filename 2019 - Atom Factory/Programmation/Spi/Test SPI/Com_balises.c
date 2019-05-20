#ifndef Com_balises
#define Com_balises
	
void Balise_config_plage(int8 no_plage, int8 deb_plage, int8 fin_plage)
{	
	i2c_start();
	debug1 = i2c_write(0x20);			// adresse de la balise
	i2c_write(0x10);			// instruction de config
	i2c_write(no_plage);
	i2c_write(deb_plage);
	i2c_write(fin_plage);
	i2c_write('@');				// fin de la communication
	i2c_stop();
}

void Balise_set_plage(int8 select_plage)
{
	i2c_start();
	i2c_write(0x20);			// adresse de la balise
	i2c_write(0x80);			// instruction de set
	i2c_write(select_plage);
	i2c_write('@');				// fin de la communication
	i2c_stop();	
}

int Check_balise(void)
{
	int ack_balise;

	i2c_start();
	ack_balise=i2c_write(0x21);			// adresse de balise en lecture
	if(ack_balise==0){					// si elle est détectée - demander sa lecture
		delay_us(30);
		value_balise=i2c_read(0);
	}
	i2c_stop();

	return value_balise;
}

#endif