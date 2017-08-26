#ifndef CAMERACOMPONENT_H_
#define CAMERACOMPONENT_H_

#include "Component.h"
#include "../entities/Entity.h"
#include "../physics/Point.h"

class CameraComponent : public Component
{
public:
	CameraComponent(float speed);
	CameraComponent(Entity* focus);
	void Follow(Entity* focus);
	void Unfollow();
};

#endif
