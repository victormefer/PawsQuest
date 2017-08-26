#ifndef IA_WALKFORWARDCOMPONENT_H_
#define IA_WALKFORWARDCOMPONENT_H_

#include "Component.h"

class IA_WalkForwardComponent: public Component
{
public:
	IA_WalkForwardComponent(int);
	~IA_WalkForwardComponent();
	void Update(float);
	float Distance();
	int distance;
	bool walking;
	bool walkingLeft;
	bool checking;
};

#endif
