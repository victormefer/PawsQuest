#ifndef COLLIDERMAP_H_
#define COLLIDERMAP_H_

#include "../entities/Entity.h"
#include <vector>

class ColliderMap
{
public:
	ColliderMap(std::string);
	void Load(std::string);
	int GetWidth();
	int GetHeight();
private:
	int mapWidth;
	int mapHeight;
};

#endif
