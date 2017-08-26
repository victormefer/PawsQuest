#ifndef SAVE_H_
#define SAVE_H_

#include"Game.h"
#include "physics/Point.h"
class Save
{
public:
	static void SetCheckPoint(Entity* entity);
	static Point CheckPoint;
	static int fase;
};

#endif
