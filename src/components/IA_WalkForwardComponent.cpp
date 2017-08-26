#include "IA_WalkForwardComponent.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "HealthComponent.h"
#include "MoveComponent.h"
#include "RenderComponent.h"
#include "../Camera.h"
#include "../managers/EntityManager.h"
#include "../entities/Entity.h"
#include "../messages/Message.h"
#include "../managers/MessageManager.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
IA_WalkForwardComponent::IA_WalkForwardComponent(int distance)
{
	SetName("IA_WalkForwardComponent");
	this->distance = distance;
	walking = false;
	walkingLeft = false;
	checking = true;
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
IA_WalkForwardComponent::~IA_WalkForwardComponent()
{

}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void IA_WalkForwardComponent::Update(float)
{
	if(checking)
	{
		if(distance > IA_WalkForwardComponent::Distance())
		{
			if(this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
					 GetPosition().x < EntityManager::GetInstance().GetEntityByName("Player")->
					 GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
			{
				walking = true;
				walkingLeft = true;
				checking = false;
			}
			else
			{
				walking = true;
				walkingLeft = false;
				checking = false;
			}
		}
	}
	if(walking)
	{
		if(walkingLeft)
		{
			this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->WalkRight();
			this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(true);
		}
		else
		{
			this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->WalkLeft();
			this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(false);
		}

		for (auto it = EntityManager::mapEntity["Ground"].begin();
				it != EntityManager::mapEntity["Ground"].end();
				++it)
		{
			if(it->second->HaveComponent("BoxColliderComponent") &&
					it->second->GetName() != this->GetOwner()->GetName())
			{
				if(EntityManager::GetInstance().GetEntityById(it->first)->
				   GetComponent<BoxColliderComponent>("BoxColliderComponent")->
				   IsColliding(
						   EntityManager::GetInstance().GetEntityById(it->first)->
						   GetComponent<TransformComponent>("TransformComponent")->GetPosition(),
						   EntityManager::GetInstance().GetEntityById(this->GetOwner()->GetId())->
						   GetComponent<TransformComponent>("TransformComponent")->GetPosition()
				   ))
				{
					this->GetOwner()->GetComponent<HealthComponent>("HealthComponent")->ModifyCurrentHealth('-',100);
//					it->second->SendMessage(new Message(Message::COLLISION_DETECTED, this->GetOwner(), it->second));
				}
			}

		}
	}
}

/*************************************************************
 *
 * Distance calcula a distancia do dono dessa entidade ao player
 *
 *************************************************************/
float IA_WalkForwardComponent::Distance(){
	float x = fabs(this->GetOwner()->GetComponent<TransformComponent>
			  ("TransformComponent")->GetPosition().x -
			  EntityManager::GetInstance().GetEntityByName("Player")->
			  GetComponent<TransformComponent>("TransformComponent")->GetPosition().x);
	float y = fabs(this->GetOwner()->GetComponent<TransformComponent>
			  ("TransformComponent")->GetPosition().y -
			  EntityManager::GetInstance().GetEntityByName("Player")->
			  GetComponent<TransformComponent>("TransformComponent")->GetPosition().y);
	return sqrt(pow(x,2) +  pow(y,2));
}
