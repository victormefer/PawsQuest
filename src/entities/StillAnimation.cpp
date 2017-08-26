#include "StillAnimation.h"
#include "../managers/EntityManager.h"

/* ************************************************************
*
* Construtor
*
*************************************************************/
StillAnimation::StillAnimation(float x, float y, float rotation, std::string entName, std::string filename, int frameCount, float frameTime, float timeLimit, bool ends) : Entity(entName)
{
	RenderComponent* sprite = new RenderComponent(filename, frameCount, frameTime);
	sprite->SetOwner(this);
	this->AddComponent(sprite);

	TransformComponent* transform = new TransformComponent( Rect(x, y, GetComponent<RenderComponent>("RenderComponent")->GetWidth(), GetComponent<RenderComponent>("RenderComponent")->GetHeight()), rotation, Point(1, 1) );
	transform->SetOwner(this);
	this->AddComponent(transform);

	this->timeLimit = timeLimit;
	oneTimeOnly = ends;
	if (ends)
		endTimer = Timer();
}

/* ************************************************************
*
* Update
*
*************************************************************/
void StillAnimation::Update(float dt)
{
	if(endTimer.Get() > timeLimit)
	{
		EntityManager::GetInstance().removeEntity(this->GetId());
	}
	GetComponent<RenderComponent>("RenderComponent")->Update(dt);
	if (oneTimeOnly)
		endTimer.Update(dt);
}

/* ************************************************************
*
* Render
*
*************************************************************/
/*void StillAnimation::Render()
{
	GetComponent<RenderComponent>("RenderComponent")->Render(GetComponent<TransformComponent>("TransformComponent"));
}*/

/* ************************************************************
*
* IsDead
*
*************************************************************/
/*bool StillAnimation::IsDead()
{
	if (oneTimeOnly)
	{
		if (endTimer.Get() <= timeLimit)
			return false;
		else
			return true;
	}
	else
		return false;
}*/
