#ifndef PROJECTILECOMPONENT_H_
#define PROJECTILECOMPONENT_H_

#include "Component.h"
#include "../physics/Point.h"

class ProjectileComponent: public Component
{
public:
	ProjectileComponent(float distance, float velocity, float ang);
	void Update(float);
	void SetFacing();
	float distance;
	Point velocity;
	float ang;
};

#endif
