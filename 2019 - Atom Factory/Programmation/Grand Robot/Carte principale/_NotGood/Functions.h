
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

unsigned int16 soll_vit_rot  = 1450;
unsigned int16 soll_vit_rot_zero = 2000; 
unsigned int16 soll_vit_mov = 1200;

signed int32 Endposition = 0; //position qui doit etre atteinte a la fin du depl
unsigned int8 Etat_ejection = 0;
int1 bras_out = 0;
int1 bras_in  = 0;
int1 flag_module_fond = 0;
void __ReadObjectifs(void);
int1 Ejecte(void);
int1 __Check_action_end(unsigned int8 driver_address);
void __resetEEPROM(void);
void __reset_roboteq(void);
void __GetRoboteqPID(unsigned int8 valeur);
void __SetRoboteqPID(unsigned int8 P1,I1,D1,P2,I2,D2,ac1,dc1,ac2,dc2);
unsigned int8 __Ask_I2C(unsigned int8 Adr);
unsigned int8 __Send_I2C(unsigned int8 Adr,unsigned int8* TabToSend);
void Ramassage(void);
void __Gestion_surcharge(unsigned int8 Adresse_driver);
void EjectionModule(unsigned int8 nbre_repet_ToDo);
void __Action_Writting(unsigned int8 ActionToDo);
void __ReadZones_Interdites(void);
int1 __Poussage(void);
int1 __Rentrage(void);
int1 __GoToZero(void);
void Deposage(void);
void Pos_barillet_module_du_fond(void);
void Ramassage_1module(void);
#include "Functions.c"

#endif
