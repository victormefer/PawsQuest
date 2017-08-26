#include "BreakablePlatformComponent.h"
#include "RenderComponent.h"
#include "BoxColliderComponent.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
BreakablePlatformComponent::BreakablePlatformComponent()
{
	SetName("BreakablePlatformComponent");
	broken = false;
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void BreakablePlatformComponent::Update(float dt){
	if(broken)
	{
		brokenTime.Update(dt);

		if(brokenTime.Get()> 1.2)
		{
			//this->owner->GetComponent<RenderComponent>("RenderComponent")->Disable();
			this->GetOwner()->GetComponent<BoxColliderComponent>("BoxColliderComponent")->Disable();
		}
		if(brokenTime.Get()> 4)
		{
			brokenTime.Restart();
			this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(1);
			this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(1);
			this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/fase_2/plataforma_quebravel_64x32.png");
			this->GetOwner()->GetComponent<BoxColliderComponent>("BoxColliderComponent")->Enable();
			broken = false;

		}
	}
}

/*************************************************************
 *
 * Updeita baseado na posicao do owner
 *
 *************************************************************/
void BreakablePlatformComponent::Break(){
	if(!broken){
		broken = true;
		this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(7);
		this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.17);
		this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/fase_2/plat_quebra.png",true);
	}
}
