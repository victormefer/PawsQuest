#include <exception>
#include "BoxColliderComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "../managers/EntityManager.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
BoxColliderComponent::BoxColliderComponent(Rect position,Point scale)
{
	SetName("BoxColliderComponent");
	this->position = position;
	this->scale = scale;
}

/*************************************************************
 *
 * Updeita baseado na posicao do owner
 *
 *************************************************************/
void BoxColliderComponent::Update(float dt) {
	try {
		BoxColliderComponent::SetPosition(
			this->GetOwner()->GetComponent<TransformComponent>
			("TransformComponent")->GetPosition()
		);
	} catch (std::exception& ex) {
		std::cout << "Excecao nao tratada: " << ex.what() << std::endl;
	}
}

/*************************************************************
 *
 * Retorna se 2 rects estao ou nao colidindo
 *
 *************************************************************/
bool BoxColliderComponent::IsColliding(const Rect& a, const Rect& b) {

	float A[] = { a.x, a.x + a.w, a.y, a.y + a.h };
	float B[] = { b.x, b.x + b.w, b.y, b.y + b.h };

	if(((A[0] < B[0] &&  B[0] < A[1] ) ||
		(A[0] < B[1] &&  B[1] < A[1])  ||
		(B[0] < A[0] &&  A[0] < B[1] ) ||
		(B[0] < A[1] &&  A[1] < B[1])  ||
		(A[0] == B[0]))
	     &&
	    ((A[2] < B[2] &&  B[2] < A[3] ) ||
	    (A[2] < B[3] &&  B[3] < A[3])   ||
	    (B[2] < A[2] &&  A[2] < B[3] )  ||
	    (B[2] < A[3] &&  A[3] < B[3] )  ||
	    (A[3] == B[3]) ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*************************************************************
 *
 * GetPosition
 *
 *************************************************************/
Rect BoxColliderComponent::GetPosition() {
	return position;
}

/*************************************************************
 *
 * GetScale
 *
 *************************************************************/
Point BoxColliderComponent::GetScale() {
	return scale;
}

/*************************************************************
 *
 * SetPosition
 *
 *************************************************************/
void BoxColliderComponent::SetPosition(Rect position) {
	this->position = position;
}

/*************************************************************
 *
 * SetScale
 *
 *************************************************************/
void BoxColliderComponent::SetScale(int sx,int sy) {
	this->scale.setX(sx);
	this->scale.setY(sy);
}
