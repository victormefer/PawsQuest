#include <cmath>
#include "ProjectileComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "../managers/EntityManager.h"

/***********************************************************************
*
* Construtor
*
***********************************************************************/
ProjectileComponent::ProjectileComponent(float distance, float velocity, float ang)
{
	this->distance = distance;
	this->velocity.x = velocity*cos(ang*3.1415/180);
	this->velocity.y = velocity*sin(ang*3.1415/180);
	this->ang = ang;
}

/***********************************************************************
*
* Update
*
***********************************************************************/
void ProjectileComponent::Update(float dt)
{
	this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
			AddToPos(Point(velocity.x*dt,velocity.y*dt));
	distance -= sqrt(pow(velocity.x*dt,2) + pow(velocity.y*dt,2));
}

/***********************************************************************
*
* SetFacing
*
***********************************************************************/
void ProjectileComponent::SetFacing()
{
	if(ang >= 90 && ang <270)
		this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(true);
	else
		this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(false);
}
