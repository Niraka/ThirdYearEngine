#include "Scene\Modules\AIWander.h"

AIWander::AIWander()
{


}

AIWander::~AIWander()
{


}

void AIWander::initialise()
{
	i_direction = 0;
	m_dir.b_forward = true;
	m_dir.b_backward = false;
	m_dir.b_right = false;
	m_dir.b_left = false;
	m_dir.b_diag_fRight = false;
	m_dir.b_diag_fLeft = false;
	m_dir.b_diag_bRight = false;
	m_dir.b_diag_bLeft = false;
}


void AIWander::Wander()
{

	
	i_direction = rand() % 8 + 1;

	setDirection(i_direction, true);

}

bool AIWander::start()
{
	if (b_wander == true)
	{
		return true;
	}
}

bool AIWander::stop()
{
	return false;
}

//void AIWander::reset()
//{
//
//}

void AIWander::onUpdate(AIRequestedNode& node)
{
	node.distance += getMovement();
}

void AIWander::setDirection(int i_dir, bool b_check)
{
	switch (i_dir)
	{
	case 1:
		m_dir.b_forward = b_check;
		break;
	case 2:
		m_dir.b_backward = b_check;
		break;
	case 3:
		m_dir.b_right = b_check;
		break;
	case 4:
		m_dir.b_left = b_check;
		break;
	case 5:
		m_dir.b_diag_fRight = b_check;
		break;
	case 6:
		m_dir.b_diag_fLeft = b_check;
		break;
	case 7:
		m_dir.b_diag_bRight = b_check;
		break;
	case 8:
		m_dir.b_diag_bLeft = b_check;
		break;
	}
}
glm::vec3 AIWander::getMovement()
{

	if (m_dir.b_forward == true) //FORWARD MOVEMENT
	{
		v_values.x = 0.0;
		v_values.y = 0.0;
		v_values.z = -1.0;

		m_dir.b_backward = false;
		m_dir.b_right = false;
		m_dir.b_left = false;
		m_dir.b_diag_fRight = false;
		m_dir.b_diag_fLeft = false;
		m_dir.b_diag_bRight = false;
		m_dir.b_diag_bLeft = false;

		return v_values;
	}
	else if (m_dir.b_backward == true)//BACKWARD MOVEMENT
	{
		v_values.x = 0.0;
		v_values.y = 0.0;
		v_values.z = 1.0;

		m_dir.b_forward = false;
		m_dir.b_right = false;
		m_dir.b_left = false;
		m_dir.b_diag_fRight = false;
		m_dir.b_diag_fLeft = false;
		m_dir.b_diag_bRight = false;
		m_dir.b_diag_bLeft = false;

		return v_values;
	}
	else if (m_dir.b_right == true)//RIGHT MOVEMENT
	{
		v_values.x = 1.0;
		v_values.y = 0.0;
		v_values.z = 0.0;

		m_dir.b_backward = false;
		m_dir.b_forward = false;
		m_dir.b_left = false;
		m_dir.b_diag_fRight = false;
		m_dir.b_diag_fLeft = false;
		m_dir.b_diag_bRight = false;
		m_dir.b_diag_bLeft = false;

		return v_values;
	}
	else if (m_dir.b_left == true)//LEFT MOVEMENT
	{
		v_values.x = -1.0;
		v_values.y = 0.0;
		v_values.z = 0.0;
		m_dir.b_backward = false;
		m_dir.b_right = false;
		m_dir.b_forward = false;
		m_dir.b_diag_fRight = false;
		m_dir.b_diag_fLeft = false;
		m_dir.b_diag_bRight = false;
		m_dir.b_diag_bLeft = false;
		return v_values;
	}
	else if (m_dir.b_diag_fRight == true)//FORWARD_RIGHT MOVEMENT
	{
		v_values.x = 1.0;
		v_values.y = 0.0;
		v_values.z = -1.0;

		m_dir.b_backward = false;
		m_dir.b_right = false;
		m_dir.b_left = false;
		m_dir.b_forward = false;
		m_dir.b_diag_fLeft = false;
		m_dir.b_diag_bRight = false;
		m_dir.b_diag_bLeft = false;

		return v_values;
	}
	else if (m_dir.b_diag_fLeft == true)//FORWARD_LEFT MOVEMENT
	{
		v_values.x = -1.0;
		v_values.y = 0.0;
		v_values.z = -1.0;

		m_dir.b_backward = false;
		m_dir.b_right = false;
		m_dir.b_left = false;
		m_dir.b_diag_fRight = false;
		m_dir.b_forward = false;
		m_dir.b_diag_bRight = false;
		m_dir.b_diag_bLeft = false;

		return v_values;
	}
	else if (m_dir.b_diag_bRight == true)//BACKWARD_RIGHT MOVEMENT
	{
		v_values.x = 1.0;
		v_values.y = 0.0;
		v_values.z = 1.0;

		m_dir.b_backward = false;
		m_dir.b_right = false;
		m_dir.b_left = false;
		m_dir.b_diag_fRight = false;
		m_dir.b_diag_fLeft = false;
		m_dir.b_forward = false;
		m_dir.b_diag_bLeft = false;

		return v_values;
	}
	else if (m_dir.b_diag_bLeft == true)//BACKWARD_LEFT MOVEMENT
	{
		v_values.x = -1.0;
		v_values.y = 0.0;
		v_values.z = 1.0;

		m_dir.b_backward = false;
		m_dir.b_right = false;
		m_dir.b_left = false;
		m_dir.b_diag_fRight = false;
		m_dir.b_diag_fLeft = false;
		m_dir.b_diag_bRight = false;
		m_dir.b_forward = false;

		return v_values;
	}
}
float AIWander::getSpeed()
{
	return f_velocity;
}

void AIWander::setSpeed(float f_vel)
{
	f_velocity = f_vel;
}