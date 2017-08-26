#include "MoveComponent.h"
#include "PlayerStateComponent.h"
#include "../Game.h"

/*************************************************************
 *
 * Construtor que precisa necessariamente receber qual a
 * velocidade de movimento quando a entidade anda, quando ela
 * corre e qual sua aceleracao
 *
 *************************************************************/
MoveComponent::MoveComponent(float walkSpeed, float runSpeed, float acceleration)
{
	SetName("MoveComponent");
	this->walkSpeed = walkSpeed;
	this->runSpeed = runSpeed;
	this->acceleration = acceleration;
	this->minVerticalSpeed= 450;
	this->verticalSpeed= 450;
	this->currentSpeed = 0;
	this->currentVerticalSpeed = 0;
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void MoveComponent::Update(float dt)
{

}

/*************************************************************
 *
 * WalkLeft
 *
 *************************************************************/
void MoveComponent::WalkLeft()
{
	currentSpeed = -walkSpeed* Game::GetInstance().GetDeltaTime();
	if(this->GetOwner()->GetName() == "Player")
	{
		this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(currentSpeed, 0) );
		if(!IsInside(Rect(Camera::pos.x, Camera::pos.y, 1024, 600), this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center()))
		{
			this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(-currentSpeed, 0) );
		}
	}
	else
	{
		this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(currentSpeed, 0) );
	}
}

/*************************************************************
 *
 * WalkRight
 *
 *************************************************************/
void MoveComponent::WalkRight()
{
	currentSpeed = walkSpeed* Game::GetInstance().GetDeltaTime();
	if(this->GetOwner()->GetName() == "Player")
	{
		this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(currentSpeed, 0) );
		if(!IsInside(Rect(Camera::pos.x, Camera::pos.y, 1024, 600), this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center()))
		{
			this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(-currentSpeed, 0) );
		}
	}
	else
	{
		this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(currentSpeed, 0) );
	}
}

/*************************************************************
 *
 * WalkUp
 *
 *************************************************************/
void MoveComponent::WalkUp()
{
	this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(0, -walkSpeed * Game::GetInstance().GetDeltaTime()) );
}

/*************************************************************
 *
 * WalkDown
 *
 *************************************************************/
void MoveComponent::WalkDown()
{
	this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(0, walkSpeed * Game::GetInstance().GetDeltaTime()) );
}

/*************************************************************
 *
 * RunLeft
 *
 *************************************************************/
void MoveComponent::RunLeft()
{
	if (currentSpeed >= 0)
		currentSpeed = -walkSpeed * Game::GetInstance().GetDeltaTime();
	else if (currentSpeed > -runSpeed * Game::GetInstance().GetDeltaTime())
		currentSpeed -= acceleration * Game::GetInstance().GetDeltaTime();
	else
		currentSpeed = -runSpeed * Game::GetInstance().GetDeltaTime();

	if(this->GetOwner()->GetName() == "Player")
	{
		this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(currentSpeed, 0) );
		if(!IsInside(Rect(Camera::pos.x, Camera::pos.y, 1024, 600), this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center()))
		{
			this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(-currentSpeed, 0) );
		}
	}
	else
	{
		this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(currentSpeed, 0) );
	}
}

/*************************************************************
 *
 * RunRight
 *
 *************************************************************/
void MoveComponent::RunRight()
{
	if (currentSpeed <= 0)
		currentSpeed = walkSpeed * Game::GetInstance().GetDeltaTime();
	else if (currentSpeed < runSpeed * Game::GetInstance().GetDeltaTime())
		currentSpeed += acceleration * Game::GetInstance().GetDeltaTime();
	else
		currentSpeed = runSpeed * Game::GetInstance().GetDeltaTime();

	if(this->GetOwner()->GetName() == "Player")
	{
		this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(currentSpeed, 0) );
		if(!IsInside(Rect(Camera::pos.x, Camera::pos.y, 1024, 600), this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center()))
		{
			this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(-currentSpeed, 0) );
		}
	}
	else
	{
		this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(currentSpeed, 0) );
	}
}

/*************************************************************
 *
 * Jump
 *
 *************************************************************/
void MoveComponent::Jump()
{
	if (currentVerticalSpeed <= 0)
		currentVerticalSpeed = minVerticalSpeed * Game::GetInstance().GetDeltaTime() ;
	else if (currentVerticalSpeed < verticalSpeed * Game::GetInstance().GetDeltaTime() )
		currentVerticalSpeed += 100 * Game::GetInstance().GetDeltaTime();
	else
		currentVerticalSpeed = verticalSpeed * Game::GetInstance().GetDeltaTime();
	this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(0, -currentVerticalSpeed) );
}

/*************************************************************
 *
 * Falling
 *
 *************************************************************/
void MoveComponent::Falling()
{
	if (currentVerticalSpeed <= 0 ){
		currentVerticalSpeed = -450 * Game::GetInstance().GetDeltaTime();
		if(this->GetOwner()->GetName() == "Player")
			if((this->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() != PlayerStateComponent::DAMAGED &&
				this->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() != PlayerStateComponent::SPECIAL))
				this->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->SetState(PlayerStateComponent::FALLING);
	}
	else
	{
		if (currentVerticalSpeed > 0 )
			currentVerticalSpeed -= 40 * Game::GetInstance().GetDeltaTime();
	}
	this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(0, -currentVerticalSpeed) );
}

/*************************************************************
 *
 * SetFalling
 *
 *************************************************************/
void MoveComponent::SetFalling()
{
	currentVerticalSpeed = -1;
}

/*************************************************************
 *
 * GetVerticalSpeed
 *
 *************************************************************/
float MoveComponent::GetVerticalSpeed()
{
	return currentVerticalSpeed;
}

/*************************************************************
 *
 * GetSpeed
 *
 *************************************************************/
float MoveComponent::GetSpeed(){
	return currentSpeed;
}


/*************************************************************
 *
 * Bounce
 *
 *************************************************************/
void MoveComponent::Bounce()
{
	MoveComponent::Jump();
	currentVerticalSpeed = 1200 * Game::GetInstance().GetDeltaTime();
}

/*************************************************************
 *
 * SetWalkSpeed
 *
 *************************************************************/
void MoveComponent::SetWalkSpeed(float walkSpeed)
{
	this->walkSpeed = walkSpeed;
}

/*************************************************************
 *
 * SetRunSpeed
 *
 *************************************************************/
void MoveComponent::SetRunSpeed(float runSpeed)
{
	this->runSpeed = runSpeed;
}

/*************************************************************
 *
 * SetAcceleration
 *
 *************************************************************/
void MoveComponent::SetAcceletarion(float acceleration)
{
	this->acceleration = acceleration;
}

/*************************************************************
 *
 * WalkTo
 *
 *************************************************************/
void MoveComponent::WalkTo(Point position, float speed ){

	Rect currentPosition = this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition();
	float dt = Game::GetInstance().GetDeltaTime();
	Point frameSpeed;

	float ang;
	if(position.x > currentPosition.x && currentPosition.y > position.y){//1
		ang = atan((currentPosition.y - position.y)/(position.x - currentPosition.x));
	}
	if(currentPosition.x > position.x && currentPosition.y > position.y){//2
		ang = 180- atan((currentPosition.y - position.y)/(currentPosition.x - position.x));
	}
	if(currentPosition.x > position.x && position.y > currentPosition.y){//3
		ang = 180 + atan((position.y - currentPosition.y)/(currentPosition.x - position.x)) ;
	}
	if(position.x > currentPosition.x && position.y > currentPosition.y){//4
		ang = 360- atan((position.y - currentPosition.y)/(position.x - currentPosition.x));
	}

	frameSpeed.x = cos(ang)*speed;
	frameSpeed.y = sin(ang)*speed;

	this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(frameSpeed.x * dt,frameSpeed.x * dt) );
	currentPosition.x += frameSpeed.x * dt;
	currentPosition.y += frameSpeed.y * dt;

	if(( currentPosition.x  > position.x - 120 * dt  && currentPosition.x  < position.x + 120 * dt )
		&& ( currentPosition.y  > position.y - 120 * dt && currentPosition.y  < position.y + 120 * dt ))
	{
		this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->SetPosition(
			Rect(
				position.x,
				position.y,
				currentPosition.w,
				currentPosition.h
				)
			);
	}
}

/*************************************************************
 *
 * WalkTo
 *
 *************************************************************/
void MoveComponent::WalkToVertical(float position, float speed ){

	Rect currentPosition = this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition();
	float dt = Game::GetInstance().GetDeltaTime();

	float movement = 0;
	if(position > currentPosition.y)
	{
		movement += speed * dt;
	}
	else
	{
		movement -= speed * dt;
	}

	this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(0,movement) );

	if ( currentPosition.y  > position- 120 * dt  && currentPosition.y  < position + 120 * dt )
	{
		this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->SetPosition(
			Rect(
				currentPosition.x,
				position,
				currentPosition.w,
				currentPosition.h
				)
			);
	}
}

/*************************************************************
 *
 * WalkTo
 *
 *************************************************************/
void MoveComponent::WalkToHorizontal(float position, float speed ){

	Rect currentPosition = this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition();
	float dt = Game::GetInstance().GetDeltaTime();

	float movement = 0;
	if(position > currentPosition.x)
	{
		movement += speed * dt;
	}
	else
	{
		movement -= speed * dt;
	}

	this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->AddToPos( Point(movement,0) );

	if ( currentPosition.x  > position- 120 * dt  && currentPosition.x  < position + 120 * dt )
	{
		this->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->SetPosition(
			Rect(
				position,
				currentPosition.y,
				currentPosition.w,
				currentPosition.h
				)
			);
	}
}

