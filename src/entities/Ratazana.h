#ifndef RATAZANA_H_
#define RATAZANA_H_

#include <vector>
#include <memory>
#include "Entity.h"
#include "../components/TransformComponent.h"
#include "../components/RenderComponent.h"
#include "../components/MoveComponent.h"
#include "../components/BoxColliderComponent.h"
#include "../components/HealthComponent.h"
#include "MinionRatazana.h"
#include "../Timer.h"

class Ratazana: public Entity
{
public:
	Ratazana(int x, int y);
	void Update(float dt);
	enum RatazanaState { IDLE, WALKING};
	RatazanaState state;
	Timer timer;
	int randomize = 0;
	std::vector<MinionRatazana*> minionArray;
	Timer pre_walking;
	bool b4_walking;
	Timer aux;
	bool fodasse;
};

#endif
