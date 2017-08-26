#ifndef EDGECOOLDOWNCOMPONENT_H_
#define EDGECOOLDOWNCOMPONENT_H_

#include "Component.h"
#include "../Timer.h"

class EdgeCooldownComponent: public Component
{
public:
	EdgeCooldownComponent();
	void Update(float dt);
	void Start();
private:
	Timer cooldown;
};

#endif
