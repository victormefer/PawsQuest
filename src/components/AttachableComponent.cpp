#include "AttachableComponent.h"
#include "TransformComponent.h"
#include "../managers/EntityManager.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
AttachableComponent::AttachableComponent()
{
	SetName("AttachableComponent");
	this->attachedTo = NULL;
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void AttachableComponent::Update(float dt)
{
	if(attachedTo != NULL)
	{
		Rect rect1;
		rect1 = attachedTo->GetComponent<TransformComponent>("TransformComponent")->GetPosition();
		Rect rect2 = this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition();
		this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->SetPosition(Rect(
				rect1.x,
				rect1.y,
				rect2.w,
				rect2.h	));
	}
}

/*************************************************************
 *
 * Attach
 *
 *************************************************************/
void AttachableComponent::Attach(Entity* toAttach)
{
	std::cout << 'q' << std::endl;
	//this->attachedTo = toAttach;
	//std::cout << EntityManager::GetInstance().GetEntityByName("Player")->GetName() << std::endl;
	std::cout<< attachedTo << std::endl;
	std::cout  << "como assim" << std::endl;
	this->attachedTo = EntityManager::GetInstance().GetEntityByName("Player");
	std::cout << 'h' << std::endl;
}
