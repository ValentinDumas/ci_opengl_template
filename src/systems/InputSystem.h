#ifndef DREAMINENGINE_INPUTSYSTEM_H
#define DREAMINENGINE_INPUTSYSTEM_H

#include "utils/InputEnum.h"
#include "utils/ComponentStore.h"

#include "components/Sprite.h"
#include "components/Input.h"

#include <vector>

class InputSystem {
private :


public :
	void update(std::vector<InputEnum> inputs, ComponentStore<Input> inputs_c, ComponentStore<Sprite> sprites);
};



#endif