//===============================================================
//	Robot_Arm.h
//===============================================================
//
//	Header qui contient la déclaration de la classe Robot_Arm
//
//
//===============================================================

#ifndef __Robot_Arm_h__
#define __Robot_Arm_h__

#include Robot_Arm.c

class Robot_Arm 
{
	public:
		Robot_Arm(int8 servo_number = 5, int8 interaxis_distance = 70, int8 angle_max = 50 ); //Constructeur
		process();				//A inclure dans la boucle infinie
		setSpeed(int16 speed);	//Vitesse des servos
		setMode(int8 mode);		//Mode dans lequel se trouve le bras
		void Go_Pos(float x_pos, float y_pos, int1 x_right);

	protected:
		void Check_Dist_Atom(float x_atom, float y_atom);
		void Go_Atom();
		void Pick_Atom();
		void Stock_Atom();

		enum{STANDBY, CLEAN, PICK_FRONT, PICK_LEFT, PICK_RIGHT} Arm_State = STANDBY;
		enum{NO_ATOM, ATOM_DETECTED, ATOM_IN_RANGE, ARM_IN_POSITION, STOCK_ATOM} Clean_State = NO_ATOM;

		int16 arm_length_max = 0;
		int16 arm_length_min = 0;
		int16 arm_interaxis_distance = 0;
		int16 angle_to_aim = 0;

		int1 atom_detected = 0;
		int1 atom_in_range = 0;
		int1 arm_in_position = 0;
		int1 atom_picked = 0;

		int16 posX_atom;
		int16 posY_atom;

		
		int8 tab_id[5] = {1,2,9,3,14};

		float dist_to_atom = 0.0;


}

#endif