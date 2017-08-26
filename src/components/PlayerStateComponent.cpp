#include "PlayerStateComponent.h"
#include "MoveComponent.h"
#include "../Game.h"

/*************************************************************
 *
 * Construtor inicialmente seta o estado do player sera IDLE
 *
 *************************************************************/
PlayerStateComponent::PlayerStateComponent()
{
	SetName("PlayerStateComponent");
	state = IDLE;
	oldState = IDLE;
	inDamageCooldown = false;
	//stateChange = false;
}

/*************************************************************
 *
 * Update verifica em todos os frame se o estado do player
 * mudou, caso tenha mudado vemos para qual estado ele foi
 * e tomamos as devidas providencias
 *
 *************************************************************/
void PlayerStateComponent::Update(float dt)
{
	if(inDamageCooldown)
	{
		damageCooldown.Update(dt);
		if(damageCooldown.Get() > 0.1*count)
		{
			if(blinkChange)
				this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Disable();
			else
				this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Enable();
			count++;
			blinkChange = !blinkChange;
		}
			if(damageCooldown.Get() > 1)
			{
				count = 0;
				inDamageCooldown = false;
				this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Enable();
			}
	}
	if (state != oldState)
	{
		//stateChange = false;
		oldState = state;
		/*************************************************************
		 *
		 * As animacoes mudam muito dependendo da fase que o player
		 * se encontra. Em algumas ele tem oculos, em outras nao
		 *
		 *************************************************************/
		/*************************************************************
		 *
		 * Fases que o cachorro usa oculos
		 *
		 *************************************************************/
		if(Game::GetInstance().GetCurrentState().number == 2)
		{
			switch(state)
			{
				case IDLE:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(16);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_parado_oculos_32x32.png");
					break;

				case WALKING:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(8);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_andando_oculos_32x32.png");
					break;

				case RUNNING:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(8);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.10);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_correndo_oculos_32x32.png");
					break;

				case JUMPING:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(5);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_pulando_oculos_32x64.png",true);
					break;

				case FALLING:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(1);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_caindo_oculos_34x40.png");
					break;

				case BARKING:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(6);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_barking_oculos_32x32.png");
					break;

				case DAMAGED:
					if(!inDamageCooldown)
					{
						EntityManager::GetInstance().GetEntityByName( "Player" )->
							GetComponent<HealthComponent>("HealthComponent")->
							ModifyCurrentHealth('-',25);
						this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(4);
						this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
						this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_damaged_oculos_32x32.png");
					}
					break;

				case PUSHING:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(8);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_empurrando_oculos_32x32.png");
					break;

				case SPECIAL:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(8);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_hat_272x36.png");
					break;

				case HANGING:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(8);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.2);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_pendurado_oculos_34x32.png");
					break;

				case DEAD:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(19);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.2);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_dead_oculos_32x32.png");
					break;
			}
		}

		/*************************************************************
		 *
		 * Fases que o cachorro nao usa oculos
		 *
		 *************************************************************/
		else
		{
			switch(state)
			{
				case IDLE:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(16);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_parado_32x32.png");
					break;

				case WALKING:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(8);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_andando_32x32.png");
					break;

				case RUNNING:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(8);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.10);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_correndo_32x32.png");
					break;

				case JUMPING:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(5);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_pulando_32x64.png",true);
					break;

				case FALLING:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(1);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_caindo_34x40.png");
					break;

				case BARKING:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(6);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_barking_32x32.png");
					break;

				case DAMAGED:

						EntityManager::GetInstance().GetEntityByName( "Player" )->
							GetComponent<HealthComponent>("HealthComponent")->
							ModifyCurrentHealth('-',25);
						this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(4);
						this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
						this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_damaged_32x32.png");

					break;

				case PUSHING:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(8);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_empurrando_32x32.png");
					break;

				case SPECIAL:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(8);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.08);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_hat_272x36.png");
					break;

				case HANGING:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(8);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.2);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_pendurado_34x32.png");
					break;

				case DEAD:
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(19);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.2);
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/player/player_dead_32x32.png");
					break;
			}
		}
	}
}

/*************************************************************
 *
 * GetState
 *
 *************************************************************/
PlayerStateComponent::PlayerState PlayerStateComponent::GetState()
{
	return state;
}

/*************************************************************
 *
 * SetState
 *
 *************************************************************/
void PlayerStateComponent::SetState(PlayerState state)
{
	if(!(state == DAMAGED && inDamageCooldown))
	{
		this->state = state;
	}
}

/*************************************************************
 *
 * EndDamaged
 *
 *************************************************************/
void PlayerStateComponent::EndDamaged()
{
	this->inDamageCooldown = true;
	this->damageCooldown.Restart();
	PlayerStateComponent::SetState(IDLE);
}
