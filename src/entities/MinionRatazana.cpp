#include "MinionRatazana.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
MinionRatazana::MinionRatazana(Entity* ratazana_pai, int x, int y): Entity("MinionRatazana")
{
	SetTag("Boss");
	state = IDLE;
	attacking = false;
	this->ratazana_pai = ratazana_pai;
	this->return_position = x;

	// ADD RENDER
	RenderComponent* render = new RenderComponent("img/characters/bosses/ratazana/ratinho_800x104.png", 4, 0.1);
	render->SetOwner(this);
	AddComponent(render);

	// ADD TRANSFORM
	TransformComponent* transform = new TransformComponent(
		Rect( x, y, GetComponent<RenderComponent>("RenderComponent")->GetWidth(),
		GetComponent<RenderComponent>("RenderComponent")->GetHeight() ), 0, Point(0.5, 0.5) );
	transform->SetOwner(this);
	AddComponent(transform);

	// ADD MOVE
	MoveComponent* move = new MoveComponent(400, 400, 5);
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
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void MinionRatazana::Update(float dt)
{
	GetComponent<RenderComponent>("RenderComponent")->Update(dt);
	GetComponent<BoxColliderComponent>("BoxColliderComponent")->Update(dt);
	GetComponent<HealthComponent>("HealthComponent")->Update(dt);
}
