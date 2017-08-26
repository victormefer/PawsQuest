/*
 * Nut.cpp
 *
 *  Created on: 10/07/2015
 *      Author: Avell G1511
 */

#include "Nut.h"

#define POS1 26900
#define POS2 27250
#define POS3 27540


Nut::Nut(int x, int y, int type,Entity* boss): Entity("Nut"){

	this->exploded = false;
	this->type = type;
	SetTag("Pushable");
	this->boss = boss;
	// ADD RENDER
	RenderComponent* render = new RenderComponent("img/characters/bosses/Squirel/noz.png", 1, 1);
	render->SetOwner(this);
	AddComponent(render);

	// ADD TRANSFORM
	TransformComponent* transform = new TransformComponent(
			Rect( x, y, GetComponent<RenderComponent>("RenderComponent")->GetWidth(),
			GetComponent<RenderComponent>("RenderComponent")->GetHeight() ), 0, Point(1,1) );
	transform->SetOwner(this);
	AddComponent(transform);

	// ADD MOVE
	MoveComponent* move = new MoveComponent(200, 500, 5);
	move->SetOwner(this);
	AddComponent(move);

	// ADD BOXCOLLIDER
	BoxColliderComponent* boxCollider = new BoxColliderComponent(
			Rect( 512, 500, GetComponent<RenderComponent>("RenderComponent")->GetWidth(),
			GetComponent<RenderComponent>("RenderComponent")->GetHeight()),
			Point( GetComponent<TransformComponent>("TransformComponent")->GetScale().getX(),
					GetComponent<TransformComponent>("TransformComponent")->GetScale().getY()
			));
	boxCollider->SetOwner(this);
	AddComponent(boxCollider);

	// ADD GRAVITY
	GravityComponent* gravityComponent = new GravityComponent();
	gravityComponent->SetOwner(this);
	AddComponent(gravityComponent);


}

void Nut::Update(float dt){
	Rect rect= GetComponent<TransformComponent>("TransformComponent")->GetPosition();
	if(threw.Get() < 0.2 ){
		threw.Update(dt);
		GetComponent<MoveComponent>("MoveComponent")->Jump();
	}

	if(this->GetComponent<GravityComponent>("GravityComponent")->isGrounded){
		if(exploxion.Get() == 0){
			GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(2);
			GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.1);
			GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/bosses/Squirel/noz_piscando.png");
		}

		exploxion.Update(dt);

		if(exploxion.Get()>5 && !exploded){
			GetComponent<RenderComponent>("RenderComponent")->SetFrameCount(12);
			GetComponent<RenderComponent>("RenderComponent")->SetFrameTime(0.2);
			GetComponent<RenderComponent>("RenderComponent")->Open("img/characters/bosses/Squirel/explosao_da_noz.png");
			SetTag("Ground");
			exploded = true;
		}
		if(exploxion.Get()>7){
			SetTag("Pushable");
			this->Delete();

		}
	}
	else
	{
		if(type == 0){
			if( rect.x > POS1){
				GetComponent<MoveComponent>("MoveComponent")->WalkToHorizontal(POS1, 200);
			}
		}else if( type == 1){
			if( rect.x > POS2){
				GetComponent<MoveComponent>("MoveComponent")->WalkToHorizontal(POS2, 200);
			}
		}else if( type == 2){
			if( rect.x > POS3){
				GetComponent<MoveComponent>("MoveComponent")->WalkToHorizontal(POS3, 200);
			}
		}
	}



	GetComponent<RenderComponent>("RenderComponent")->Update(dt);
}
