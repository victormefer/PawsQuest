#include <vector>
#include "EnemyStateComponent.h"
#include "../managers/ResourceManager.h"

/*************************************************************
 *
 * Para esse construtor teremos que receber a ia
 *
 *************************************************************/
EnemyStateComponent::EnemyStateComponent(Component* ia)
{
	SetName("EnemyStateComponent");
	stateChange = false;
	this->transformComponent = ia->GetOwner()->GetComponent<TransformComponent>("TransformComponent");
	this->renderComponent = ia->GetOwner()->GetComponent<RenderComponent>("RenderComponent");
	this->iaComponent = ia;

	if(this->iaComponent->GetName() == "IA_WalkRightLeftComponent")
		state = WALKING;
	if(this->iaComponent->GetName() == "IA_WalkUpDownComponent")
		state = IDLE;
	if(this->iaComponent->GetName() == "IA_FollowComponent")
		state = IDLE;
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void EnemyStateComponent::Update(float dt)
{
	if (stateChange)
	{
		stateChange = false;
		switch(state)
		{
			case IDLE:
				if(EntityManager::GetInstance().GetEntityByName(this->GetOwner()->GetName())->
					GetComponent<RenderComponent>("RenderComponent") != NULL)
				{
					renderComponent->SetFrameCount(renderComponent->GetFrameCount());
					renderComponent->SetFrameTime(renderComponent->GetFrameTime());
					EnemyStateComponent::Idle();
				}
				break;

			case WALKING:
				if(EntityManager::GetInstance().GetEntityByName(this->GetOwner()->GetName())->
						GetComponent<RenderComponent>("RenderComponent") != NULL)
				{
					renderComponent->SetFrameCount(renderComponent->GetFrameCount());
					renderComponent->SetFrameTime(renderComponent->GetFrameTime());
					EnemyStateComponent::Walking();
				}
				break;

			default:
				std::cout << "ENEMYSTATECOMPONENT::UPDATE()DEFAULT" << std::endl;
				break;
		}
	}
}

/*************************************************************
 *
 * Idle
 *
 *************************************************************/
void EnemyStateComponent::Idle()
{

}

/*************************************************************
 *
 * Walking
 *
 *************************************************************/
void EnemyStateComponent::Walking()
{

}

/*************************************************************
 *
 * GetState
 *
 *************************************************************/
EnemyStateComponent::EnemyState EnemyStateComponent::GetState()
{
	return state;
}

/*************************************************************
 *
 * SetState
 *
 *************************************************************/
void EnemyStateComponent::SetState(EnemyState state)
{
	if (this->state != state)
		stateChange = true;
	this->state = state;
}
