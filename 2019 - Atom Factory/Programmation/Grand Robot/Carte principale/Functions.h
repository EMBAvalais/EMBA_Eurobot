
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

void __Afficheur_7segments(int8 nombre,int1 ToBlank=0);
int1 Eject(void);

//unsigned int16 soll_vit_rot  = 1450;
unsigned int16 soll_vit_rot_zero = 2000; 
unsigned int16 soll_vit_mov = 1200;

int1 Sens_rot_Couronne = 0;

signed int32 Endposition = 0; //position qui doit etre atteinte a la fin du depl
unsigned int8 Etat_ejection = 0;
int1 bras_out = 0;
//int1 bras_in  = 0;
//int1 flag_module_fond = 0;
void __ReadObjectifs(void);
int1 __Check_action_end(unsigned int8 driver_address);
void __resetEEPROM(void);
void __reset_roboteq(void);
void __GetRoboteqPID(unsigned int8 valeur);
void __SetRoboteqPID(unsigned int8 P1,I1,D1,P2,I2,D2,ac1,dc1,ac2,dc2);
unsigned int8 __Ask_I2C(unsigned int8 Adr);
unsigned int8 __Send_I2C(unsigned int8 Adr,unsigned int8* TabToSend);
void __Gestion_surcharge(unsigned int8 Adresse_driver);
void __Action_Writting(unsigned int8 ActionToDo);
void __ReadZones_Interdites(void);

unsigned int8 driver_Pompes(unsigned int8 Adresse_driver, unsigned int8 pompe_A, unsigned int8 pompe_B, unsigned int8 pompe_C, unsigned int8 pompe_D, unsigned int8 pompe_E);
unsigned int8 read_driver_pompes(int8 adresse_driver);
int1 Panneau_Domotique(void);
int1 Ramassage(unsigned int8 cote);
int1 Empilage(void);
int1 GoToZero_Cremaillere(void);
int1 reinitialisation(void);
int1 __GoToZero(void);
int1 __Check_action_end(unsigned int8 driver_address);

#include "Functions.c"

#endif
