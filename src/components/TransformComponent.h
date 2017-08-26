#ifndef TRANSFORMCOMPONENT_H_
#define TRANSFORMCOMPONENT_H_

#include "Component.h"
#include "..\physics\Rect.h"

class TransformComponent: public Component
{
public:
	TransformComponent(Rect,float,Point);
	Rect GetPosition();
	float GetRotation();
	Point GetScale();
	void SetPosition(Rect);
	void SetRotation(float);
	void SetScale(Point);
	void AddToPos(Point);
	void Update(float);
private:
	Rect position;
	float rotation;
	Point scale;
};

#endif
