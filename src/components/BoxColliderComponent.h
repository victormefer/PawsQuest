#ifndef BOXCOLLIDERCOMPONENT_H_
#define BOXCOLLIDERCOMPONENT_H_

#include "Component.h"
#include "../physics/Rect.h"
#include "../physics/Point.h"

class BoxColliderComponent: public Component
{
public:
	BoxColliderComponent(Rect,Point scale);
	void Update(float dt);
	bool IsColliding(const Rect& a, const Rect& b);
	Rect GetPosition();
	Point GetScale();
	void SetPosition(Rect);
	void SetScale(int,int);
private:
	Rect position;
	Point scale;
};

#endif
