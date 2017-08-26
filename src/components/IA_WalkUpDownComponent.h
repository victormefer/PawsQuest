#ifndef IA_WALKUPDOWNCOMPONENT_H_
#define IA_WALKUPDOWNCOMPONENT_H_

#include "Component.h"

class IA_WalkUpDownComponent: public Component
{
public:
	IA_WalkUpDownComponent(int,int);
	~IA_WalkUpDownComponent();
	void Update(float);
	int up, down;
	bool walkUp;
};

#endif
