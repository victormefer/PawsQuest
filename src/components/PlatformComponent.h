#ifndef PLATFORMCOMPONENT_H_
#define PLATFORMCOMPONENT_H_

#include "Component.h"
#include "TransformComponent.h"

class PlatformComponent: public Component
{
public:
	PlatformComponent(TransformComponent* tc, int range);
	void Update(float dt);
private:
	int range;
	int initial_y;
	bool boolbom;
};

#endif
