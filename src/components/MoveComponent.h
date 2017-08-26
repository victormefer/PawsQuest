#ifndef MOVECOMPONENT_H_
#define MOVECOMPONENT_H_

#include "Component.h"
#include "TransformComponent.h"
#include "../managers/EntityManager.h"
#include "../physics/Point.h"

class MoveComponent: public Component
{

public:
	MoveComponent(float walkSpeed, float runSpeed, float acceleration);
	void Update(float dt);
	void WalkLeft();
	void WalkRight();
	void WalkUp();
	void WalkDown();
	void RunLeft();
	void RunRight();
	void Jump();
	void Falling();
	void SetFalling();
	float GetVerticalSpeed();
	float GetSpeed();
	void Bounce();
	void SetWalkSpeed(float);
	void SetRunSpeed(float);
	void SetAcceletarion(float);
	void WalkTo(Point position, float speed );
	void WalkToVertical(float position, float speed );
	void WalkToHorizontal(float position, float speed );

private:
	float walkSpeed, runSpeed, acceleration, verticalSpeed, minVerticalSpeed;
	float currentSpeed,currentVerticalSpeed;

};

#endif
