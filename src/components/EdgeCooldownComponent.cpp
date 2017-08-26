#include "EdgeCooldownComponent.h"
#include "PlayerStateComponent.h"
#include "GravityComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "../Save.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
EdgeCooldownComponent::EdgeCooldownComponent()
{
	SetName("EdgeCooldownComponent");
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void EdgeCooldownComponent::Update(float dt)
{
	if(cooldown.Get()>0)
	{
		cooldown.Update(dt);
		if(cooldown.Get() > 5)
		{
			this->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->SetState(PlayerStateComponent::IDLE);
			this->GetOwner()->GetComponent<GravityComponent>("GravityComponent")->Enable();
			this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Enable();
			this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")
					->SetPosition(Rect(Save::CheckPoint.x,Save::CheckPoint.y,64,64));
			cooldown.Restart();
		}
	}
}

/*************************************************************
 *
 * Start
 *
 *************************************************************/
 void EdgeCooldownComponent::Start()
 {
	 cooldown.Update(Game::GetInstance().GetDeltaTime());
 }
