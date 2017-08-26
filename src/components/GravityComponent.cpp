#include "GravityComponent.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
GravityComponent::GravityComponent(float mass)
{
	SetName("GravityComponent");
	this->mass = mass;
	this->isGrounded = false;
	gravityForce = 0;
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void GravityComponent::Update(float dt)
{

}
