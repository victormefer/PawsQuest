#ifndef IA_WALKRIGHTLEFTCOMPONENT_H_
#define IA_WALKRIGHTLEFTCOMPONENT_H_

#include "Component.h"
#include "../physics/Rect.h"

class IA_WalkRightLeftComponent: public Component
{
public:
	IA_WalkRightLeftComponent(int,int);
	~IA_WalkRightLeftComponent();
	void Update(float);
	int first, last;
	bool walkRight;
};

#endif
