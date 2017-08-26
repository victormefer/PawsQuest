#ifndef HATTIMERCOMPONENT_H_
#define HATTIMERCOMPONENT_H_

#include "Component.h"
#include "../Timer.h"
#include "../audio/Sound.h"

class HatTimerComponent: public Component
{
public:
	HatTimerComponent();
	~HatTimerComponent();
	Timer time;
	void Update(float);
private:
	Sound sound;
	bool playingIntro;
};

#endif
