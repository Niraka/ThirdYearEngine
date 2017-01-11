/**


@author Austin */
#ifndef AI_DIRECTION_H
#define AI_DIRECTION_H


struct AIDirection
	{
		enum Dir_state
		{
			DIR_FORWARD = 1,
			DIR_BACKWARD = 2,
			DIR_RIGHT = 3,
			DIR_LEFT = 4,
			DIR_FORWARD_RIGHT = 5,
			DIR_FORWARD_LEFT = 6,
			DIR_BACKWARD_RIGHT = 7,
			DIR_BACKWARD_LEFT = 8
		};
		bool b_forward;
		bool b_backward;
		bool b_right;
		bool b_left;
		bool b_diag_fRight;
		bool b_diag_bRight;
		bool b_diag_fLeft;
		bool b_diag_bLeft;
	};
#endif