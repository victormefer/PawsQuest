#include "WoofTimerComponent.h"
#include "../managers/EntityManager.h"

/*************************************************************
 *
 * WoofTimerComponent
 *
 *************************************************************/
WoofTimerComponent::WoofTimerComponent()
{
	SetName("WoofTimerComponent");
}

/*************************************************************
 *
 * WoofTimerComponent
 *
 *************************************************************/
WoofTimerComponent::~WoofTimerComponent()
{

}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void WoofTimerComponent::Update(float dt)
{
 	time.Update(dt);
	if(time.Get() > 2)
	{
		this->GetOwner()->Delete();
	}
}
