#include "Player.h"

/*************************************************************
 *
 * Construtor do player define todos os componentes utilizados
 * pelo player
 *
 *************************************************************/
Player::Player(int x, int y, int phase) : Entity("Player")
{
	SetTag("Player");

	// ADD STATE
	PlayerStateComponent* state = new PlayerStateComponent();
	state->SetOwner(this);
	AddComponent(state);

	// ADD INPUT
	InputComponent* input = new InputComponent();
	input->SetOwner(this);
	AddComponent(input);

	// ADD RENDER
	if(phase == 2)
	{
		RenderComponent* render = new RenderComponent("img/characters/player/player_parado_oculos_32x32.png", 16, 0.08);
		render->SetOwner(this);
		AddComponent(render);
	}
	else
	{
		RenderComponent* render = new RenderComponent("img/characters/player/player_parado_32x32.png", 16, 0.08);
		render->SetOwner(this);
		AddComponent(render);
	}

	// ADD TRANSFORM
	TransformComponent* transform = new TransformComponent(
			Rect( x, y, GetComponent<RenderComponent>("RenderComponent")->GetWidth(),
			GetComponent<RenderComponent>("RenderComponent")->GetHeight() ), 0, Point(2, 2) );
	transform->SetOwner(this);
	AddComponent(transform);

	// ADD MOVE
	MoveComponent* move = new MoveComponent(200, 400, 5);
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

	// ADD HEALTHCOMPONENT
	HealthComponent* healthComponent = new HealthComponent(100);
	healthComponent->SetOwner(this);
	AddComponent(healthComponent);

	// ADD ENERGYCOMPONENT
	EnergyComponent* energyComponent = new EnergyComponent(100);
	energyComponent->SetOwner(this);
	AddComponent(energyComponent);

	// ADD COINCOMPONENT
	CoinComponent* coinComponent = new CoinComponent();
	coinComponent->SetOwner(this);
	AddComponent(coinComponent);

	// ADD HANGINGCOMPONENT
	HangingComponent* hangComponent = new HangingComponent();
	hangComponent->SetOwner(this);
	AddComponent(hangComponent);

	//ADD EDGECOOLDOWNCOMPONENT
	EdgeCooldownComponent* edgeComponent = new EdgeCooldownComponent();
	edgeComponent->SetOwner(this);
	AddComponent(edgeComponent);
}

/*************************************************************
 *
 * Update chama o update dos componentes do player
 *
 *************************************************************/
//void Player::Update(float dt)
//{
//	GetComponent<InputComponent>("InputComponent")->Update(dt);
//	GetComponent<PlayerStateComponent>("PlayerStateComponent")->Update(dt);
//	GetComponent<RenderComponent>("RenderComponent")->Update(dt);
//	GetComponent<BoxColliderComponent>("BoxColliderComponent")->Update(dt);
//}
