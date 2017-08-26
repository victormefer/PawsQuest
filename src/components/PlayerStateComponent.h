#ifndef PLAYERSTATECOMPONENT_H_
#define PLAYERSTATECOMPONENT_H_

#include "Component.h"
#include "RenderComponent.h"
#include "../managers/EntityManager.h"
#include "HealthComponent.h"
#include "../Timer.h"

class PlayerStateComponent : public Component
{
public:
	enum PlayerState { IDLE, WALKING, RUNNING, JUMPING, FALLING, BARKING, DAMAGED, PUSHING, SPECIAL, HANGING, DEAD };
	PlayerStateComponent();
	void Update(float dt);
	PlayerState GetState();
	void SetState(PlayerState state);
	void EndDamaged();
private:
	int count=1;
	bool inDamageCooldown;
	Timer blink;
	Timer damageCooldown;
	PlayerState state, oldState;
	bool blinkChange = true;
};

#endif
