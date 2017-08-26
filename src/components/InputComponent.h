#ifndef INPUTCOMPONENT_H_
#define INPUTCOMPONENT_H_

#include "Component.h"
#include "PlayerStateComponent.h"
#include "MoveComponent.h"
#include "../managers/EntityManager.h"
#include "../managers/InputManager.h"
#include "../components/GravityComponent.h"
#include "../managers/GravityManager.h"
#include "../Timer.h"

class InputComponent: public Component
{
public:
	InputComponent();
	void Update(float dt);
	void KillJump();
	void Damaged(float);
	Timer timer;
private:
	
	Timer damageCooldown;
	Timer barkingTime;
};

#endif

