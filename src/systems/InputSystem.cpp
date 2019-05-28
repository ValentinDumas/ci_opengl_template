#include "InputSystem.h"

void InputSystem::update(std::vector<InputEnum> inputs, ComponentStore<Input> inputs_c , ComponentStore<Sprite> sprites)
{
	for (std::unordered_map<unsigned int, unsigned int>::iterator it = inputs_c.getMap().begin(); it != inputs_c.getMap().end(); ++it) {
		auto itSprite = sprites.getMap().find(it->first);
		if (itSprite != sprites.getMap().end()) {
			Sprite* sprite = sprites.get(itSprite->first);
			Input* input = inputs_c.get(itSprite->first);

			for (int i = 0; i < inputs.size(); i++) {
				if (inputs[i] == input->m_up)
					sprite->Position.y -= input->m_speed_up;
				if (inputs[i] == input->m_down)
					sprite->Position.y += input->m_speed_down;
				if (inputs[i] == input->m_right)
					sprite->Position.x += input->m_speed_right;
				if (inputs[i] == input->m_left)
					sprite->Position.x -= input->m_speed_left;
			}
		}
	}
	/**/
}
