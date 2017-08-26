#ifndef MINIONRATAZANA_H_
#define MINIONRATAZANA_H_

#include "Entity.h"
#include "../components/TransformComponent.h"
#include "../components/RenderComponent.h"
#include "../components/MoveComponent.h"
#include "../components/BoxColliderComponent.h"
#include "../components/HealthComponent.h"

class MinionRatazana: public Entity
{
public:
	MinionRatazana(Entity* ratazana_pai, int x, int y);
	void Update(float dt);
	enum MinionRatazanaState {IDLE,WALKING};
	MinionRatazanaState state;
	Entity* ratazana_pai;
	bool attacking;
	int return_position;
};

#endif
