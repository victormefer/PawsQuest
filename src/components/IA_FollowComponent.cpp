#include <cmath>
#include "IA_FollowComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "MoveComponent.h"
#include "BoxColliderComponent.h"
#include "../managers/EntityManager.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
IA_FollowComponent::IA_FollowComponent(int distance)
{
	this->distance = distance;
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void IA_FollowComponent::Update(float dt)
{
	rest.Update(dt);
	if(this->GetOwner()->GetComponent<BoxColliderComponent>("BoxColliderComponent")
	   ->IsColliding(this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")
	   ->GetPosition(),EntityManager::GetInstance().GetEntityByName("Player")->
	   GetComponent<TransformComponent>("TransformComponent")->GetPosition()))
	{
		rest.Restart();
	}
	if(rest.Get()>2)
	{
		if(distance > IA_FollowComponent::Distance())
		{
			if(this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
			   GetPosition().x < EntityManager::GetInstance().GetEntityByName("Player")->
			   GetComponent<TransformComponent>("TransformComponent")->GetPosition().x + 63)
			{
				this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->WalkRight();
				this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(true);
			}
			if(this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
			   GetPosition().x >= EntityManager::GetInstance().GetEntityByName("Player")->
			   GetComponent<TransformComponent>("TransformComponent")->GetPosition().x - 60)
			{
				this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->WalkLeft();
				this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(false);
			}
		}
	}

}

/*************************************************************
 *
 * Distance calcula a distancia do dono dessa entidade ao player
 *
 *************************************************************/
float IA_FollowComponent::Distance(){
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
