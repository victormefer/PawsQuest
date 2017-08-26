#include "HidranteTimerComponent.h"
#include "RenderComponent.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
HidranteTimerComponent::HidranteTimerComponent()
{
	SetName("HidranteTimerComponent");
	first_animation = false;
	second_animation = false;
	aux = false;
	flag = false;
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
HidranteTimerComponent::~HidranteTimerComponent()
{

}

/*************************************************************
 *
 * Update garante que quando ocorrer a colisao player hidrante
 * imagens intermediarias serao mostradas antes da animacao
 * final do hidrante explodido
 *
 *************************************************************/
void HidranteTimerComponent::Update(float dt)
{
	if(first_animation)
	{
		time.Update(dt);
		if(time.Get() < 0.6)
		{
			if(!aux)
			{
				this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")
				->SetFrameCount(6);
				this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")
				->SetFrameTime(0.2);
				this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")
				->Open("img/global/save/hidrante_1_383x104.png",1);
				aux = true;
			}
		}
		else
		{
			first_animation = false;
			second_animation = true;
		}
	}
	if(second_animation)
	{
		if(!flag)
		{
			this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")
			->SetFrameCount(5);
			this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")
			->SetFrameTime(0.05);
			this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")
			->Open("img/global/save/hidrante_2_321x105.png",0);
			second_animation = false;
			flag = true;
		}
	}
}

/*************************************************************
 *
 * StartAnimation inicia a primeira animacao, ou seja, a
 * animacao do hidrante comecando a explodir
 *
 *************************************************************/
void HidranteTimerComponent::StartAnimation()
{
	first_animation = true;
}
