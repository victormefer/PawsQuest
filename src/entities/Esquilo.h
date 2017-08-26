#ifndef ESQUILO_H_
#define ESQUILO_H_

#include "Entity.h"
#include "../Timer.h"
#include "../physics/Rect.h"

class Esquilo: public Entity
{
public:
	Esquilo(int x, int y);
		void Update(float dt);
		void Fall();
		void Damage();
		enum EsquiloState { THROWING, DOWN, CLIMBING, WALKINGTOTREE, WALKINGONTREE, FALLING};
		EsquiloState state;
		Timer timer;
		bool thowing;
		int randomize = 0;
		Rect tree_position;
		int phase;
};

#endif
