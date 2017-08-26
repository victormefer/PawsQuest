#ifndef ENEMYSTATECOMPONENT_H_
#define ENEMYSTATECOMPONENT_H_

#include "Component.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "BoxColliderComponent.h"
#include "IA_WalkRightLeftComponent.h"
#include "IA_WalkUpDownComponent.h"
#include "../managers/EntityManager.h"

class EnemyStateComponent : public Component
{
public:
	EnemyStateComponent(Component*);
	enum EnemyState { IDLE, WALKING};
	void Update(float dt);
	EnemyState GetState();
	void SetState(EnemyState state);
	void SetFacingLeft(bool left);
	bool FacingLeft();
private:
	void Idle();
	void Walking();
	EnemyState state;
	bool stateChange;
	TransformComponent* transformComponent;
	RenderComponent* renderComponent;
	Component* iaComponent;
};

#endif
