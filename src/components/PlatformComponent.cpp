#include "PlatformComponent.h"
#include "MoveComponent.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
PlatformComponent::PlatformComponent(TransformComponent* tc, int range)
{
	SetName("PlatformComponent");
	this->range = range;
	this->initial_y = tc->GetPosition().y;
	this->boolbom = false;
	//ESSA FOI DAS BOAS
	tc->GetOwner()->AddComponent(new MoveComponent(300,400,10));
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void PlatformComponent::Update(float dt)
{
	if(this->GetOwner()->HaveComponent("MoveComponent"))
	{
		Rect rect = this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
				GetPosition();

		if(rect.y < (initial_y-range))
		{
			boolbom=false;
		}
		if(rect.y > (initial_y+range))
		{
			boolbom=true;
		}

		if(!boolbom)
		{
			this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->WalkToVertical(rect.y+range,300);
		}
		else
		{
			this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->WalkToVertical(rect.y-range,300);
		}

	}
}
