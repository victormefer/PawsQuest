#ifndef COMPONENTS_ATTACHABLECOMPONENT_H_
#define COMPONENTS_ATTACHABLECOMPONENT_H_

#include "../entities/Entity.h"
#include "Component.h"
#include "../physics/Rect.h"
#include "../physics/Point.h"

class AttachableComponent: public Component
{
public:
	AttachableComponent();
	void Update(float dt);
	void Attach(Entity* toAttach);
	Entity* attachedTo;
private:
};

#endif
