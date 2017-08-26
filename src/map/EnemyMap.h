#ifndef ENEMYMAP_H_
#define ENEMYMAP_H_

#include "../entities/Entity.h"

#include <vector>
#include <string>

class EnemyMap
{
public:
	EnemyMap(std::string);
	void Load(std::string);
	void Render();
	int GetNumEnemy();
	int GetPhase();
private:
	Component* ia;
	int numEnemy;
	int phase;
};

#endif
