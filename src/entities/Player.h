#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../components/TransformComponent.h"
#include "../components/RenderComponent.h"
#include "../components/InputComponent.h"
#include "../components/PlayerStateComponent.h"
#include "../components/MoveComponent.h"
#include "../components/BoxColliderComponent.h"
#include "../components/GravityComponent.h"
#include "../components/HealthComponent.h"
#include "../components/EnergyComponent.h"
#include "../components/CoinComponent.h"
#include "../components/HangingComponent.h"
#include "../components/EdgeCooldownComponent.h"

class Player : public Entity
{
public:
	Player(int x, int y, int phase);
//	void Update(float dt);
private:
};

#endif
