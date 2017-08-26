#include <stdlib.h>
#include <time.h>
#include <string>
#include "InputComponent.h"
#include "EnergyComponent.h"
#include "ProjectileComponent.h"
#include "WoofTimerComponent.h"
#include "PlayerStateComponent.h"
#include "HangingComponent.h"
#include "../audio/Music.h"
#include "../audio/Sound.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
InputComponent::InputComponent()
{
	SetName("InputComponent");
}

/*************************************************************
 *
 * Update escuta eventos de teclado e define os possiveis
 * comportamentos que o cachorro pode assumir dependendo do
 * tipo do evento
 *
 *************************************************************/
void InputComponent::Update(float dt)
{

	bool pressing = false;
	barkingTime.Update(dt);

	/************************************************************************
	 *
	 * Obriga o estado do cachorro a durar no minimo 0.5 segundos depois
	 * que ele late, ou seja, se ele late enquanto ele esta parado a animacao
	 * do latido vai durarno minimo 0.5
	 *
	 ************************************************************************/
	if(barkingTime.Get() > 0.5)
	{

		/***********************************************************************
		*
		* Walking
		*
		************************************************************************/
		if(this->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() !=
			PlayerStateComponent::DAMAGED &&
			this->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() !=
			PlayerStateComponent::SPECIAL &&
			this->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() !=
			PlayerStateComponent::DEAD)
		{
			if(InputManager::GetInstance().IsKeyDown(LSHIFT_KEY) &&
			   GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() != PlayerStateComponent::HANGING)
			{
				if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
				{
					pressing = true;
					if(GetOwner()->GetComponent<GravityComponent>("GravityComponent")->isGrounded &&
						GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() != PlayerStateComponent::PUSHING)
					{
						GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->SetState(PlayerStateComponent::RUNNING);
					}
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(false);
					this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->RunRight();
				}
				if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
				{
					pressing = true;
					if(GetOwner()->GetComponent<GravityComponent>("GravityComponent")->isGrounded &&
						GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() != PlayerStateComponent::PUSHING)
					{
						GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->SetState(PlayerStateComponent::RUNNING);
					}
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(true);
					this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->RunLeft();
				}
			}
			else if(GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() != PlayerStateComponent::HANGING)
			{
				if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
				{
					pressing = true;
					if(GetOwner()->GetComponent<GravityComponent>("GravityComponent")->isGrounded &&
						GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() != PlayerStateComponent::PUSHING)
					{
						GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->SetState(PlayerStateComponent::WALKING);
					}
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(false);
					this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->WalkRight();
				}
				if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
				{
					pressing = true;
					if(GetOwner()->GetComponent<GravityComponent>("GravityComponent")->isGrounded &&
						GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() != PlayerStateComponent::PUSHING)
					{
						GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->SetState(PlayerStateComponent::WALKING);
					}
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(true);
					this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->WalkLeft();
				}
			}

			/***********************************************************************
			*
			* Jump
			*
			**********************************************************************/
			if (InputManager::GetInstance().IsKeyDown(SPACE_KEY))
			{
				pressing = true;
				if((InputManager::GetInstance().IsKeyDown(SPACE_KEY)) &&
				   (GetOwner()->GetComponent<GravityComponent>("GravityComponent")->isGrounded ||
					GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() == PlayerStateComponent::HANGING))
				{
					this->GetOwner()->GetComponent<PlayerStateComponent>
					("PlayerStateComponent")->SetState(PlayerStateComponent::JUMPING);
					GetOwner()->GetComponent<HangingComponent>("HangingComponent")->SetHanging(false);
					timer.Restart();
					timer.Update(dt);
				}
				else if(timer.Get()>0)
				{
					timer.Update(dt);
				}
				if((timer.Get()>0) && (timer.Get()<0.15))
				{
					this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->Jump();
				}
			}

			if(!InputManager::GetInstance().IsKeyDown(SPACE_KEY) && (timer.Get()>0))
			{
				 timer.Restart();
			}

			if ((this->GetOwner()->GetComponent<GravityComponent>("GravityComponent")->isGrounded) &&
				(!pressing || (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY) &&
				InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))))
			{
				this->GetOwner()->GetComponent<PlayerStateComponent>
				("PlayerStateComponent")->SetState(PlayerStateComponent::IDLE);
			}


			/***********************************************************************
			*
			* Woof
			*
			**********************************************************************/

			if (InputManager::GetInstance().KeyRelease(SDLK_z) &&
				GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() != PlayerStateComponent::HANGING)
			{
				if(barkingTime.Get() > 2)
				{
					pressing = true;
					if(EntityManager::GetInstance().GetEntityByName("Player")->
					HaveComponent("EnergyComponent"))
					{
						if(EntityManager::GetInstance().GetEntityByName("Player")->
						GetComponent<EnergyComponent>("EnergyComponent")->GetCurrentEnergy() >=
						25)
						{
							this->GetOwner()->GetComponent<PlayerStateComponent>
							("PlayerStateComponent")->SetState(PlayerStateComponent::BARKING);
							this->GetOwner()->GetComponent<EnergyComponent>("EnergyComponent")->
							ModifyCurrentEnergy('-',25);
							/***********************************************************************
							*
							* Criando a bullet
							*
							**********************************************************************/
							Entity* e = new Entity("Prefab");
							e->SetTag("Prefab");
							e->AddComponent(new TransformComponent(
							EntityManager::GetInstance().GetEntityByName("Player")->
							GetComponent<TransformComponent>("TransformComponent")->
							GetPosition(), 0, Point(1,1)));
							e->AddComponent(new RenderComponent("img/global/latido_160x32.png",5,1));
							e->AddComponent(new WoofTimerComponent());
							/***********************************************************************
							*
							* Garantindo q ela seja renderizada no angulo certo
							*
							**********************************************************************/
							if(this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->GetFacingLeft())
							{
								e->AddComponent(new ProjectileComponent(500,700,180));
								e->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(true);
							}
							else
							{
								e->AddComponent(new ProjectileComponent(500,700,0));
								e->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(false);
							}
							EntityManager::GetInstance().addEntity(e);

							/***********************************************************************
							*
							* Som aleatorio do latido
							*
							**********************************************************************/
							srand (time(NULL));
							std::stringstream sstm;
							sstm << "audio/nome_" << rand()%12 << ".ogg";
							std::string result = sstm.str();
							Sound* sound = new Sound(result);
							sound->Play(0);
							barkingTime.Restart();
						}
					}
				}
			}
		}
		else
		{
			if(this->GetOwner()->GetComponent<PlayerStateComponent>
			("PlayerStateComponent")->GetState() == PlayerStateComponent::DAMAGED)
			{
				InputComponent::Damaged(dt);
			}
			else if (this->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() ==
			PlayerStateComponent::SPECIAL)
			{
				if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
				{
					pressing = true;
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(true);
				}
				if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
				{
					pressing = true;
					this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(false);
				}

				if(this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->GetFacingLeft())
				{
					this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->RunLeft();
				}
				else
				{
					this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->RunRight();
				}

			}
		}
	}
}

/***********************************************************************
 *
 * Kill Jump para o pulo se o cachorro colide com algo em cima dele
 *
 * *********************************************************************/
void InputComponent::KillJump(){
	this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->SetFalling();
	timer.Restart();
}

/***********************************************************************
 *
 * Kill Jump para o pulo se o cachorro colide com algo em cima dele
 *
 * *********************************************************************/
void InputComponent::Damaged(float dt)
{
	if(damageCooldown.Get() == 0)
		this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->Jump();
	damageCooldown.Update(dt);
	if(damageCooldown.Get() < 0.5)
	{
		if(this->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->GetFacingLeft())
		{
			this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->RunRight();
		}
		else
		{
			this->GetOwner()->GetComponent<MoveComponent>("MoveComponent")->RunLeft();
		}
	}
	else
	{
		this->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->EndDamaged();
		damageCooldown.Restart();
	}
}


