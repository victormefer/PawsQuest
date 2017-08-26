#include "IA_WalkUpDownComponent.h"
#include "TransformComponent.h"
#include "MoveComponent.h"
#include "EnemyStateComponent.h"
#include "../managers/EntityManager.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
IA_WalkUpDownComponent::IA_WalkUpDownComponent(int up, int down)
{
	SetName("IA_WalkUpDownComponent");
	this->up = up;
	this->down = down;
	this->walkUp = true;
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
IA_WalkUpDownComponent::~IA_WalkUpDownComponent()
{

}

/*************************************************************
 *
 * IA
 *
 *************************************************************/
void IA_WalkUpDownComponent::Update(float dt)
{
	if(walkUp)
		{
			if(this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y > up)
			{
				this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->WalkUp();
				this->GetOwner()->GetComponent<EnemyStateComponent>("EnemyStateComponent")->SetState(EnemyStateComponent::WALKING);
			}
			else if(this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y <= down)
			{
				walkUp = false;
			}
		}
		else
		{
			if(this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y < down)
			{
				this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->WalkDown();
				this->GetOwner()->GetComponent<EnemyStateComponent>("EnemyStateComponent")->SetState(EnemyStateComponent::WALKING);
			}
			else if(this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y >= up)
			{
				walkUp = true;
			}
		}
}
