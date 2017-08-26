#include <stdlib.h>
#include <time.h>
#include "Ratazana.h"
#include "../Camera.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
Ratazana::Ratazana(int x, int y): Entity("Ratazana")
{
	SetTag("Boss");
	state = IDLE;
	fodasse = false;
	b4_walking = true;
	srand (time(NULL));
	randomize = rand()%2;

	// ADD RENDER
	RenderComponent* render = new RenderComponent("img/characters/bosses/ratazana/ratazana_parada_1416x280.png", 6, 0.1);
	render->SetOwner(this);
	AddComponent(render);

	// ADD TRANSFORM
	TransformComponent* transform = new TransformComponent(
		Rect( x, y, GetComponent<RenderComponent>("RenderComponent")->GetWidth(),
		GetComponent<RenderComponent>("RenderComponent")->GetHeight() ), 0, Point(0.5, 0.5) );
	transform->SetOwner(this);
	AddComponent(transform);

	// ADD MOVE
	MoveComponent* move = new MoveComponent(200, 400, 5);
	move->SetOwner(this);
	AddComponent(move);

	// ADD BOXCOLLIDER
	BoxColliderComponent* boxCollider = new BoxColliderComponent(
		Rect( GetComponent<TransformComponent>("TransformComponent")->GetPosition().x,
			  GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
			  GetComponent<RenderComponent>("RenderComponent")->GetWidth(),
			  GetComponent<RenderComponent>("RenderComponent")->GetHeight()),
		Point( GetComponent<TransformComponent>("TransformComponent")->GetScale().getX(),
				GetComponent<TransformComponent>("TransformComponent")->GetScale().getY()
		));
	boxCollider->SetOwner(this);
	AddComponent(boxCollider);

	// ADD HEALTHCOMPONENT
	HealthComponent* healthComponent = new HealthComponent(100);
	healthComponent->SetOwner(this);
	AddComponent(healthComponent);

	/*************************************************************
	 *
	 * Construindo os filhos da ratazana
	 *
	 *************************************************************/
	MinionRatazana* minion_0 = new MinionRatazana(
			this,
			this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x-64,
			this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y+97);
	MinionRatazana* minion_1 = new MinionRatazana(
			this,
			this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x,
			this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y+97);
	MinionRatazana* minion_2 = new MinionRatazana(
			this,
			this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x+64,
			this->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y+97);
	EntityManager::GetInstance().addEntity(minion_0);
	EntityManager::GetInstance().addEntity(minion_1);
	EntityManager::GetInstance().addEntity(minion_2);
	minionArray.emplace_back(minion_0);
	minionArray.emplace_back(minion_1);
	minionArray.emplace_back(minion_2);
	minionArray[0]->state = MinionRatazana::WALKING;
	minionArray[0]->attacking = true;
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void Ratazana::Update(float dt)
{

	aux.Update(dt);

	if(aux.Get() > 10)
	{
		Ratazana::state = WALKING;
	}

	// if(minionArray[0] == NULL)
	// {
	// 	std::cout << "oi" << std::endl;
	// 	if(minionArray[1] == NULL)
	// 	{
	// 		std::cout << "oi" << std::endl;
	// 		if(minionArray[2] == NULL)
	// 		{
	// 			std::cout << "oi" << std::endl;
	// 			Ratazana::state = WALKING;
	// 		}
	// 	}
	// }




	GetComponent<RenderComponent>("RenderComponent")->Update(dt);
//	GetComponent<BoxColliderComponent>("BoxColliderComponent")->Update(dt);

	std::cout << "size:" << minionArray.size() << std::endl;

	if(minionArray.size() <= 0)
		state = WALKING;

	for(unsigned int i=0; i<minionArray.size(); i++)
	{
		minionArray[i]->GetComponent<RenderComponent>("RenderComponent")->Render(
				minionArray[i]->GetComponent<TransformComponent>("TransformComponent"));
	}

	/*************************************************************
	 *
	 * Ratazana esta parada
	 *
	 *************************************************************/
	if(state == IDLE)
	{
		for(unsigned int i=0; i<minionArray.size(); i++)
		{
			// bool gamb = false;
			// for(unsigned int i=0; i<minionArray.size(); i++)
			// {
			// 	if(minionArray[i]->attacking == true)
			// 	{
			// 		gamb = true;
			// 	}
			// }
			// if(gamb == false)
			// {
			// 	minionArray[0]->attacking = true;
			// }
			/*************************************************************
			 *
			 * Minion esta andando
			 *
			 *************************************************************/
			if(minionArray[i]->state == MinionRatazana::WALKING)
			{
				/*************************************************************
				 *
				 * Minion esta atacando
				 *
				 *************************************************************/
				if(minionArray[i]->attacking == true)
				{
					if(minionArray[i]->GetComponent<TransformComponent>("TransformComponent")->
					   GetPosition().x >= EntityManager::GetInstance().GetEntityByName("Player")->
					   GetComponent<TransformComponent>("TransformComponent")->GetPosition().x+32)
					{
						minionArray[i]->GetComponent<MoveComponent>("MoveComponent")->WalkLeft();
						minionArray[i]->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(false);
					}
					else
					{
						minionArray[i]->attacking = false;
					}
				}
				/*************************************************************
				 *
				 * Minion esta voltando de um ataque
				 *
				 *************************************************************/
				else
				{
					if(minionArray[i]->GetComponent<TransformComponent>("TransformComponent")->
					   GetPosition().x < minionArray[i]->return_position)
					{
						minionArray[i]->GetComponent<MoveComponent>("MoveComponent")->WalkRight();
						minionArray[i]->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(true);
					}
					else
					{
						minionArray[i]->state = MinionRatazana::IDLE;
						if(minionArray.size() > i+1)
						{
								minionArray[i+1]->state = MinionRatazana::WALKING;
								minionArray[i+1]->attacking = true;
						}
						else
						{
							minionArray[0]->state = MinionRatazana::WALKING;
							minionArray[0]->attacking = true;
						}
					}
				}
			}
		}
	}
	/*************************************************************
	 *
	 * Ratazana esta andando
	 *
	 *************************************************************/
	else if(state == WALKING)
	{
		// SAIU DO ESTADO PARADO E ESTA SE PREPARANDO PARA ANDAR
		if(b4_walking)
		{
			if(!fodasse)
			{
				this->GetComponent<TransformComponent>("TransformComponent")->AddToPos(Point(0,60));
				fodasse = true;
			}

			if(pre_walking.Get() < 0.5)
			{
				this->GetComponent<RenderComponent>("RenderComponent")->
						Open("img/characters/bosses/ratazana/ratazana_intermediaria_784x188.png", 0);
				this->GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(2);
			}

			pre_walking.Update(dt);
			if(pre_walking.Get() > 5)
			{
				b4_walking = false;
			}
		}
		// JA ESTA PREPARADO PARA ANDAR E VAI ANDAR
		else
		{
			timer.Update(dt);

			/*************************************************************
			 *
			 * Se tiver randomizado para esquerda
			 *
			 *************************************************************/
			if(randomize == 1)
			{
				//std::cout << "ESQ->DIR" << std::endl;
				this->GetComponent<MoveComponent>("MoveComponent")->WalkRight();
				this->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(true);
			}
			/*************************************************************
			 *
			 * Se tiver randomizado para direita
			 *
			 *************************************************************/
			else
			{
				//std::cout << "DIR->ESQ" << std::endl;
				this->GetComponent<MoveComponent>("MoveComponent")->WalkLeft();
				this->GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(false);
			}

			if(timer.Get() > 5)
			{
				timer.Restart();
				//srand (time(NULL));
				randomize = rand()%2;
				/*************************************************************
				 *
				 * De forma aleatoria, a ratazana pode atacar da direita ou
				 * da esquerda do player
				 *
				 *************************************************************/
				if(randomize)
				{
					this->GetComponent<TransformComponent>("TransformComponent")->SetPosition(
						Rect(
							Camera::pos.x-0,
							GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
							GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
							GetComponent<TransformComponent>("TransformComponent")->GetPosition().h
					));
				}
				else
				{
					this->GetComponent<TransformComponent>("TransformComponent")->SetPosition(
						Rect(
							Camera::pos.x+1024,
							GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
							GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
							GetComponent<TransformComponent>("TransformComponent")->GetPosition().h
					));
				}
				std::cout << "RATAZANA STATE == WALKING" << std::endl;
			}
		}
	}
}
