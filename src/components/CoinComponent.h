#ifndef COINCOMPONENT_H_
#define COINCOMPONENT_H_

#include "Component.h"

class CoinComponent: public Component
{
public:
	CoinComponent();
	~CoinComponent();
	void Update(float dt);
	int goldCoins;
	int silverCoins;
	int bronzeCoins;
private:
	void ModifyCurrentCoins();
};

#endif
