#ifndef CAT_H
#define CAT_H

#include "Entity.h"
#include "../managers/EntityManager.h"
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
#include "../Timer.h"
#include "../audio/Sound.h"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>

#define CAT_SPEED 300 // pixels per second
#define CAT_SPEED_DOWN 200 // pixels per second
#define VASE_SPEED 500 // pixels per second

class Cat : public Entity
{
public:
	enum CatState { IDLE, WALKING, DESCENDING, THROWING, DEAD };

	Cat();
	void Update(float dt);

	void ChangePlatform();
	void ThrowVase(int vase);
	void WalkToVase();

	void SetStarted(bool started);

private:
	CatState state;
	bool goingLeft, start;
	int platform, vasePlatform;
	int curVase, vaseThrown;
	bool vaseFalling;
	int missesLeft;
	Timer timer;
	Point point;
	std::vector<Entity*> closeGrounds;
	Sound meow;
};

#endif
