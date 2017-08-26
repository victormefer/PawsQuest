/*
 * Nut.h
 *
 *  Created on: 10/07/2015
 *      Author: Avell G1511
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../timer.h"
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

class Nut : public Entity
{
public:
	Nut(int x, int y, int type,Entity* boss);
	void Update(float dt);
	Entity* boss;
private:
	int type;
	Timer threw;
	Timer exploxion;
	bool exploded;
};

#endif


