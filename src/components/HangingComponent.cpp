#include "HangingComponent.h"
#include "PlayerStateComponent.h"
#include "TransformComponent.h"
#include "../managers/EntityManager.h"

HangingComponent::HangingComponent()
{
	SetName("HangingComponent");
	hanging = false;
	goingRight = true;
	angle = 0;
}


void HangingComponent::Update(float dt)
{
	if (hanging)
	{
		this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->SetRotation(angle);
		if (goingRight)
		{
			angle -= 112.5 * dt;
			if (angle <= -45)
				goingRight = false;
		}
		else
		{
			angle += 112.5 * dt;
			if (angle >= 45)
				goingRight = true;
		}
	}
}

void HangingComponent::SetHanging(bool hanging, Point center)
{
	this->hanging = hanging;
	if (hanging)
	{
		this->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->SetState(PlayerStateComponent::HANGING);
		Rect rect = this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition();
		this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->SetPosition( Rect(
			center.x - rect.w / 2,
			center.y - rect.h / 2,
			rect.w,
			rect.h ));
	}
	else
	{
		this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->SetRotation(0);
		angle = 0;
		goingRight = true;
	}
}
