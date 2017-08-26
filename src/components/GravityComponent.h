#ifndef GRAVITYCOMPONENT_H_
#define GRAVITYCOMPONENT_H_

#include "Component.h"
#define gravityForce GRAVITY_FORCE

class GravityComponent: public Component
{
public:
	GravityComponent(float mass=1);
	float mass;
	float gravityForce;
	bool isGrounded;
	void Update(float);
};

#endif
