#ifndef IA_FOLLOWCOMPONENT_H_
#define IA_FOLLOWCOMPONENT_H_

#include "Component.h"
#include "../Timer.h"

class IA_FollowComponent: public Component
{
public:
	IA_FollowComponent(int distance);
	void Update(float dt);
	float Distance();
	int distance;
	Timer rest;
};

#endif
