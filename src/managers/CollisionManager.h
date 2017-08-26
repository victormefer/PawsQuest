#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

#include "../entities/Entity.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	static void ManageCollision();
	static bool Grounded(Entity*);
	static void Ascending(Entity*);
};

#endif
