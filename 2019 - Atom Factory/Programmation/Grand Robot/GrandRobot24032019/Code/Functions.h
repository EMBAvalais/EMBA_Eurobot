
/*====================================================================================================
===																									==
===											EMVs - EUROBOT	  										==
===											--------------											==
======================================================================================================
===	 Auteur				: Amand Axel     					  										==
===  Date				: 30.04.2015    															==
===  Nom du programme 	: TestCartePrinc.mcp														==
===  Version 			: V1.0																		==
======================================================================================================
=== Description :																					==
=== Contrôle du robor secondaire.																	==
====================================================================================================*/

#ifndef ___Functions_h
#define ___Functions_h


//unsigned int16 soll_vit_rot  = 1450;
unsigned int16 soll_vit_rot_zero = 2000; 
unsigned int16 soll_vit_mov = 1200;

int1 Sens_rot_Couronne = 0;

signed int32 Endposition = 0; //position qui doit etre atteinte a la fin du depl
unsigned int8 Etat_ejection = 0;
int1 bras_out = 0;
//int1 bras_in  = 0;
//int1 flag_module_fond = 0;


void Standby_stop();
void Standby_scan();
void Take_front();
void Take_side();
void Take_goldenium();
void Put_balance();
void Put_accelerator();
void Check_action_done();

unsigned int8 Write_cmd_arduino(unsigned int8 cmd,unsigned int8 taille, unsigned int8 *data ) ;
Read_etat_arduino(struct etat *value) ;

void __ReadObjectifs(void);
void __resetEEPROM(void);
void __reset_roboteq(void);
void __GetRoboteqPID(unsigned int8 valeur);
void __SetRoboteqPID(unsigned int8 P1,I1,D1,P2,I2,D2,ac1,dc1,ac2,dc2);
unsigned int8 __Ask_I2C(unsigned int8 Adr);
unsigned int8 __Send_I2C(unsigned int8 Adr,unsigned int8* TabToSend);
void __Action_Writting(unsigned int8 ActionToDo);
void __ReadZones_Interdites(void);
int1 reinitialisation(void);
int1 __Check_action_end(unsigned int8 driver_address);

#include "Functions.c"

#endif
