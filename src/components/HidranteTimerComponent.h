#ifndef HIDRANTETIMERCOMPONENT_H_
#define HIDRANTETIMERCOMPONENT_H_

#include "Component.h"
#include "../Timer.h"

class HidranteTimerComponent: public Component
{
public:
	HidranteTimerComponent();
	~HidranteTimerComponent();
	void Update(float dt);
	void StartAnimation();
	bool first_animation;
	bool second_animation;
	bool aux;
	bool flag;
private:
	Timer time;
};

#endif
