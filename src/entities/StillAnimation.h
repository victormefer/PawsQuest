#ifndef STILLANIMATION_H
#define STILLANIMATION_H

#include "Entity.h"
#include "../components/RenderComponent.h"
#include "../components/TransformComponent.h"
#include "../Timer.h"

class StillAnimation : public Entity
{
public:
	StillAnimation(float x, float y, float rotation, std::string entName,
				   std::string filename, int frameCount, float frameTime,
				   float timeLimit, bool ends);
	void Update(float dt);
	//void Render();
	//bool IsDead();
private:
	Timer endTimer;
	float timeLimit;
	bool oneTimeOnly;
};

#endif
