#ifndef BREAKABLEPLATAFORMCOMPONENT_H_
#define BREAKABLEPLATAFORMCOMPONENT_H_

#include "Component.h"
#include "TransformComponent.h"
#include "../Timer.h"

class BreakablePlatformComponent: public Component
{
public:
	BreakablePlatformComponent();
	void Update(float dt);
	void Break();
private:
	bool broken;
	Timer brokenTime;
};

#endif
