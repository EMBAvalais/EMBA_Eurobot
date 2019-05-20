//===============================================================
//	Robot_Arm.h
//===============================================================
//
//	Contient la description de la classe Robot_Arm
//
//
//===============================================================

Robot_Arm::Robot_Arm(int8 servo_number, int8 interaxis_distance)
{
	arm_length_min = interaxis_distance+(2*interaxis_distance*cos(angle_max*PI/180));
	arm_length_max = 3 * interaxis_distance; 
	arm_interaxis_distance = interaxis_distance;
	Arm_State = STANDBY;
}

Robot_Arm::process()
{
	switch(Arm_State)
	{
		case STANDBY:
			
		break;

		case CLEAN:

			switch(Clean_State)
			{
				case NO_ATOM:
					if(atom_detected > 0)
					{
						//Slow down robot speed
						Clean_State = ATOM_DETECTED;
					}
				break;

				case ATOM_DETECTED:
					Check_Dist_Atom();

					if(atom_in_range)
					{
						//Stop Robot
						Clean_State = ATOM_IN_RANGE;
					}
				break;

				case ATOM_IN_RANGE:
					Go_Atom();

					if(arm_in_position)
					{
						Clean_State = ARM_IN_POSITION;
					}
				break;

				case ARM_IN_POSITION:
					Pick_Atom();

					if(atom_picked)
					{
						Clean_State = STOCK_ATOM;
					}
				break;

				case STOCK_ATOM:
					Stock_Atom();

					if(atom_stocked)
					{
						Clean_State = WAIT_ATOM;
					}
			}

		break;

		case PICK_FRONT:

		break;

		case PICK_LEFT:

		break;

		case PICK_RIGHT:

		break;


	}
}

void Robot_Arm::Check_Dist_Atom()
{
	float x_powed = pow(posX_atom, 2);
	float y_powed = pow(posY_atom, 2);
	
	float x_and_y = x_powed + y_powed;
	
	dist_to_atom = sqrt(x_and_y);

	if(dist_to_atom >= arm_length_min && dist_to_atom <= arm_length_max)
	{
		atom_in_range = 1;
	}
}

void Robot_Arm::Go_Atom()
{
	
	if(!x_right)
	{
		angle_to_aim = (atan(posY_atom/posX_atom)*57.2958*3.316666) + 215;
	}
	else
	{
		angle_to_aim = ((180-(atan(posY_atom/posX_atom))*57.2958)*3.316666) + 215;
	}
	
	float tmp1 = dist_to_atom-ARM_INTERAXIS_LENGTH;
	float tmp2 = tmp1/2;
	float tmp3 = tmp2/ARM_INTERAXIS_LENGTH;
	
	float angle_pos = acos(tmp3)*180/PI;
	
	int16 servo_pos_1 = 512-(angle_pos*3.41);
	int16 servo_pos_2 = 525-(2*angle_pos*3.41);//-((180-angle_pos)*3.41);
	int16 servo_pos_3 = 809-(angle_pos*3.41);
	
	Servo_goal_position(tab_id[0], angle_to_aim);
	Servo_goal_position(tab_id[1], servo_pos_1);
	Servo_goal_position(tab_id[2], servo_pos_2);
	Servo_goal_position(tab_id[3], servo_pos_3);

	arm_in_position = 1;

	
	
}



void Robot_Arm::Go_Pos(float x_pos, float y_pos, int1 x_right)
{
		
	float x_powed = pow(x_pos, 2);
	float y_powed = pow(y_pos, 2);
	
	float x_and_y = x_powed + y_powed;
	
	float dist_to_pos = sqrt(x_and_y);

	if(dist_to_pos >= arm_length_min && dist_to_pos <= arm_length_max)
	{
		if(!x_right)
		{
			angle_to_aim = (atan(y_pos/x_pos)*57.2958*3.316666) + 215;
		}
		else
		{
			angle_to_aim = ((180-(atan(y_pos/x_pos))*57.2958)*3.316666) + 215;
		}
		
		float tmp1 = dist_to_pos-ARM_INTERAXIS_LENGTH;
		float tmp2 = tmp1/2;
		float tmp3 = tmp2/ARM_INTERAXIS_LENGTH;
		
		float angle_pos = acos(tmp3)*180/PI;
		
		int16 servo_pos_1 = 512-(angle_pos*3.41);
		int16 servo_pos_2 = 525-(2*angle_pos*3.41);//-((180-angle_pos)*3.41);
		int16 servo_pos_3 = 809-(angle_pos*3.41);
		
		Servo_goal_position(tab_id[0], angle_to_aim);
		Servo_goal_position(tab_id[1], servo_pos_1);
		Servo_goal_position(tab_id[2], servo_pos_2);
		Servo_goal_position(tab_id[3], servo_pos_3);

		arm_in_position = 1;
	
	}	

}

Robot_Arm::Pick_Atom()
{
	//Descendre le moteur linéaire
	//Activer la pompe

	//Si on détecte moteur linéaire contre le palet avec mesure courant ou fin de course
	//On stoppe moteur linéaire
		//on vérifie si la pompe a detecté la prise
		//si oui oui remonte le moteur linéaire
	

}

Robot_Arm::Stock_Atom()
{
	//Faire les différents mouvements pour ranger le palet

}

