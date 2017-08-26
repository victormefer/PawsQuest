#include <stdlib.h>
#include <cmath>
#include <time.h>
#include "Esquilo.h"
#include "Nut.h"
#include "../components/TransformComponent.h"
#include "../components/RenderComponent.h"
#include "../components/MoveComponent.h"
#include "../components/BoxColliderComponent.h"
#include "../components/GravityComponent.h"
#include "../states/SecondPhaseState.h"

Esquilo::Esquilo(int x, int y): Entity("Esquilo")
{
	thowing = false;
	srand (x*3+y*94);
	SetTag("Boss");
	state = WALKINGONTREE;
	phase = 0 ;
	randomize = rand()%2;
	tree_position = EntityManager::GetInstance().GetEntityByName("Arvore_esquilo")->GetComponent
					<TransformComponent>("TransformComponent")->GetPosition();

	// ADD RENDER
	RenderComponent* render = new RenderComponent("img/characters/bosses/Squirel/esquilo_correndo.png", 7, 0.1);
	render->SetOwner(this);
	AddComponent(render);

	// ADD TRANSFORM
	TransformComponent* transform = new TransformComponent(
		Rect( x, y, GetComponent<RenderComponent>("RenderComponent")->GetWidth(),
		GetComponent<RenderComponent>("RenderComponent")->GetHeight() ), 0, Point(1, 1) );
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
}

void Esquilo::Update(float dt)
{
	Rect currentPosition = this->GetComponent<TransformComponent>("TransformComponent")->GetPosition();
	/*************************************************************
	 *
	 * Throwing
	 *
	 *************************************************************/
	if(state == THROWING)
	{
				if(timer.Get() == 0)
				{
					GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(2);
					GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.1);
					GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/bosses/Squirel/esquilo_esperando.png");

				}
			timer.Update(dt);
				if(timer.Get() > 4.3 && !thowing)
				{
					GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(3);
					GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.2);
					GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/bosses/Squirel/esquilo_jogandonoz.png");
					thowing = true;
				}

				if(timer.Get() > 5)
				{
					for(int i=0; i <= phase ; i++)
					{
						randomize = rand()%3;
						Entity* e = new Nut(currentPosition.x, currentPosition.y, randomize,this);
						EntityManager::GetInstance().addEntity(e);

					}
					thowing =false;
					timer.Restart();
				}

	}
	/*************************************************************
	 *
	 * Walking
	 *
	 *************************************************************/
	else if(state == WALKINGTOTREE)
	{
		if(timer.Get() == 0)
		{
			GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(7);
			GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.15);
			GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/bosses/Squirel/esquilo-robo_semnoz.png");
			GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(true);
		}
		if(currentPosition.x < tree_position.x + 253 +64)
		{
			std::cout << "DIREITA" << std::endl;
			this->GetComponent<MoveComponent>("MoveComponent")->WalkToHorizontal(tree_position.x + 253 +65, 300);
		}
		else
		{
			state = CLIMBING;
		}
	}
	else if(state == CLIMBING)
	{
		if (timer.Get() == 0 ){
			GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(2);
			GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.1);
			GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/bosses/Squirel/esquilo_subindo.png");
			GetComponent<RenderComponent>("RenderComponent")->SetFacingLeft(false);
		}
		if(currentPosition.y > tree_position.y + 140)
		{
			std::cout << "SUBINDO" << std::endl;
			this->GetComponent<MoveComponent>("MoveComponent")->WalkToVertical(tree_position.y + 140, 300);
		}
		else
		{
			timer.Restart();
			state = WALKINGONTREE;
		}
	}
	else if(state == WALKINGONTREE)
	{
		if (timer.Get() == 0 ){
			GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(7);
			GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.1);
			GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/bosses/Squirel/esquilo_correndo.png");

			this->GetComponent<TransformComponent>("TransformComponent")->SetPosition(Rect(
			EntityManager::GetInstance().GetEntityByName("Arvore_esquilo")->
			GetComponent<TransformComponent>("TransformComponent")->GetPosition().x + 129,
			EntityManager::GetInstance().GetEntityByName("Arvore_esquilo")->
			GetComponent<TransformComponent>("TransformComponent")->GetPosition().y+ 87-52,
			 GetComponent<RenderComponent>("RenderComponent")->GetWidth(),
			 GetComponent<RenderComponent>("RenderComponent")->GetHeight()));
		}
		timer.Update(dt);
		if (timer.Get() >0.5){
			if(currentPosition.x > tree_position.x + 46)
			{
				std::cout << "esquerda" << std::endl;
				this->GetComponent<MoveComponent>("MoveComponent")->WalkToHorizontal(tree_position.x + 46, 300);
			}
			else
			{
				timer.Restart();
				state = THROWING;
			}
		}
	}
	else if(state == FALLING)
	{
		if (timer.Get() == 0 ){
			GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(2);
			GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.1);
			GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/bosses/Squirel/esquilo_caindo.png");
		}

			if(currentPosition.y < 640 -64 -32 -2 )
			{
				std::cout << "fall" << std::endl;
				this->GetComponent<MoveComponent>("MoveComponent")->WalkToVertical(640, 400);
			}
			else
			{
				timer.Restart();
				state = DOWN;
			}
		}
		else if(state == DOWN)
		{
				if (timer.Get() == 0 ){
					this->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(0,32+15));
					GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(2);
					GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.1);
					GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/bosses/Squirel/esquilo_atordoado.png");
				}
				timer.Update(dt);
				if(timer.Get() > 2)
				{
					timer.Restart();
					state = WALKINGTOTREE;
				}
			}
	this->GetComponent<RenderComponent>("RenderComponent")->Update(dt);
}

void Esquilo::Fall(){
	std::cout << "FALLLLLLLLLLLLLLLLLL" << std::endl;
	this->state= FALLING;
	timer.Restart();
}

void Esquilo::Damage(){
	phase++;
	state = WALKINGTOTREE;
	timer.Restart();
	GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(2);
	GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.15);
	GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/bosses/Squirel/esquilo_dano.png");
//	while (timer.Get() > 0.3){
//		timer.Restart();
//	}
	if(phase == 3)
	{
		std::cout<<"morreu"<<std::endl;
		Game::GetInstance().GetCurrentState().SetBossDead();
	}
}







//		cannonAngle = atan2((float)InputManager::GetInstance().GetMouseY() - (float)box.y - Camera::pos.y,
//							  (float)InputManager::GetInstance().GetMouseX() - (float)box.x - Camera::pos.x ) * 180/3.1415;
