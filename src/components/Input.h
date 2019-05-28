#ifndef DREAMINENGINE_INPUT_H
#define DREAMINENGINE_INPUT_H

#include "utils/InputEnum.h"


class Input {
private:
	/*InputEnum m_left;
	InputEnum m_right;
	InputEnum m_up;
	InputEnum m_down;

	int m_speed_left;
	int m_speed_right;
	int m_speed_up;
	int m_speed_down;*/

public:
	//Input(InputEnum left = Q, InputEnum right = D, InputEnum up = Z, InputEnum down = S, int speed_left = 20, int speed_right = 20, int speed_up = 20, int speed_down = 20);
	Input(InputEnum left = ARROW_LEFT, InputEnum right = ARROW_RIGHT, InputEnum up = ARROW_UP, InputEnum down = ARROW_DOWN, int speed_left = 10, int speed_right = 10, int speed_up = 10, int speed_down = 10) :
		m_left(left), m_right(right), m_up(up), m_down(down),
		m_speed_left(speed_left), m_speed_right(speed_right), m_speed_up(speed_up), m_speed_down(speed_down) {
	}
	InputEnum m_left;
	InputEnum m_right;
	InputEnum m_up;
	InputEnum m_down;

	int m_speed_left;
	int m_speed_right;
	int m_speed_up;
	int m_speed_down;
};




#endif //DREAMINENGINE_INPUT_H