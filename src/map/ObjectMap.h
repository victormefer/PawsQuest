#ifndef OBJECTMAP_H_
#define OBJECTMAP_H_

#include "../entities/Entity.h"
#include "../components/TransformComponent.h"
#include "../components/RenderComponent.h"

#include <vector>
#include <string>
#include <map>

class ObjectMap
{
public:
	ObjectMap(std::string);
	void Load(std::string);
	//void Update(float dt);
	//void RenderLayer(int layer, int cameraX, int cameraY);
	//void RenderBelow(int cameraX, int cameraY);
	int GetnumObjects();
	int GetPhase();
	//static std::map<int,Entity*> mapObject;
private:
	int numObjects;
	int phase;
};

#endif
