#ifndef WOOFTIMERCOMPONENT_H_
#define WOOFTIMERCOMPONENT_H_

#include "Component.h"
#include "../Timer.h"

class WoofTimerComponent: public Component
{
public:
	WoofTimerComponent();
	~WoofTimerComponent();
	void Update(float);
private:
	Timer time;
};

#endif
