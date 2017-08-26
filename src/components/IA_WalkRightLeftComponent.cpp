#include "IA_WalkRightLeftComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "MoveComponent.h"
#include "BoxColliderComponent.h"
#include "EnemyStateComponent.h"
#include "../managers/EntityManager.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
IA_WalkRightLeftComponent::IA_WalkRightLeftComponent(int first,int last)
{
	SetName("IA_WalkRightLeftComponent");
	this->first = first;
	this->last = last;
	this->walkRight = true;
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
IA_WalkRightLeftComponent::~IA_WalkRightLeftComponent()
{

}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void IA_WalkRightLeftComponent::Update(float dt)
{
	if(walkRight)
	{
		if(this->GetOwner()->GetComponent<BoxColliderComponent>("BoxColliderComponent")
				->IsColliding(this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")
						->GetPosition(),EntityManager::GetInstance().GetEntityByName("Player")->
						GetComponent<TransformComponent>("TransformComponent")->GetPosition()))
		{
			walkRight = false;
		}
		else
		{
			if(this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x < last)
			{
				this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->WalkRight();
				this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(true);
				this->GetOwner()->GetComponent<EnemyStateComponent>("EnemyStateComponent")->SetState(EnemyStateComponent::WALKING);
			}
			else if(this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x >= last)
			{
				walkRight = false;
			}
		}
	}
	else
	{
		if(this->GetOwner()->GetComponent<BoxColliderComponent>("BoxColliderComponent")
				->IsColliding(this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")
						->GetPosition(),EntityManager::GetInstance().GetEntityByName("Player")->
						GetComponent<TransformComponent>("TransformComponent")->GetPosition()))
		{
			this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
					AddToPos(Point(5,0));
			walkRight = true;
		}
		else
		{
			if(this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x > first)
			{
				this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->WalkLeft();
				this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(false);
				this->GetOwner()->GetComponent<EnemyStateComponent>("EnemyStateComponent")->SetState(EnemyStateComponent::WALKING);
			}
			else if(this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x <= first)
			{
				walkRight = true;
			}
		}
	}
}
