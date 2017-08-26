#include "HatTimerComponent.h"
#include "PlayerStateComponent.h"

/*************************************************************
 *
 * Construtor inicializa a musica que vai tocar
 * quando o player coleta o item hat
 *
 *************************************************************/
HatTimerComponent::HatTimerComponent(): sound("audio/11_usando_especial/usando_especial_intro.ogg")
{
	SetName("HatTimerComponent");
	sound.Play(0);
	playingIntro = true;
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
HatTimerComponent::~HatTimerComponent()
{
	if(this->GetOwner()->HaveComponent("PlayerStateComponent"))
	{
		this->GetOwner()->GetComponent<PlayerStateComponent>
		("PlayerStateComponent")->SetState(PlayerStateComponent::IDLE);
	}
	sound.Stop();
	this->GetOwner()->RemoveComponent("HatTimerComponent");
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void HatTimerComponent::Update(float dt)
{
	time.Update(dt);
	if(time.Get() > 8)
	{
		this->~HatTimerComponent();
	}

	if (playingIntro)
	{
		if (!sound.IsPlaying())
		{
			sound = Sound("audio/11_usando_especial/usando_especial_loop.ogg");
			sound.Play(-1);
			playingIntro = false;
		}
	}
}
