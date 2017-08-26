#include "TransformComponent.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
TransformComponent::TransformComponent(Rect position, float rotation, Point scale)
{
	SetName("TransformComponent");
	this->position.x = position.x;
	this->position.y = position.y;
	this->position.w = position.w * scale.getX();
	this->position.h = position.h * scale.getY();
	this->rotation = rotation;
	this->scale = scale;
}

/*************************************************************
 *
 * GetPosition
 *
 *************************************************************/
Rect TransformComponent::GetPosition()
{
	return position;
}

/*************************************************************
 *
 * GetRotation
 *
 *************************************************************/
float TransformComponent::GetRotation()
{
	return rotation;
}

/*************************************************************
 *
 * GetScale
 *
 *************************************************************/
Point TransformComponent::GetScale()
{
	return scale;
}

/*************************************************************
 *
 * SetPosition
 *
 *************************************************************/
void TransformComponent::SetPosition(Rect p)
{
	this->position = p;
}

/*************************************************************
 *
 * SetRotation
 *
 *************************************************************/
void TransformComponent::SetRotation(float r)
{
	this->rotation = r;
}

/*************************************************************
 *
 * SetScale
 *
 *************************************************************/
void TransformComponent::SetScale(Point s)
{
	this->scale.x = s.x;
	this->scale.y = s.y;
}

/*************************************************************
 *
 * AddToPos add a posicao atual
 *
 *************************************************************/
void TransformComponent::AddToPos(Point pos)
{
	this->position = this->position + pos;
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void TransformComponent::Update(float dt)
{

}
