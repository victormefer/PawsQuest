#ifndef HANGINGCOMPONENT_H_
#define HANGINGCOMPONENT_H_

#include "Component.h"
#include "../physics/Rect.h"

class HangingComponent: public Component
{
public:
	HangingComponent();
	void Update(float);
	void SetHanging(bool, Point = Point());
private:
	bool hanging;
	float angle;
	bool goingRight;
};

#endif
