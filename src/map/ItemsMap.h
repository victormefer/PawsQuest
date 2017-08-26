#ifndef ENERGYMAP_H_
#define ENERGYMAP_H_

#include "../entities/Entity.h"

#include <vector>
#include <string>

class ItemsMap
{
public:
	ItemsMap(std::string);
	void Load(std::string);
	void Render();
	int GetNumItems();
	int GetPhase();
private:
	int numItems;
	int phase;
};

#endif
