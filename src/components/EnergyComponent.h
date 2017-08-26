#ifndef ENERGYCOMPONENT_H_
#define ENERGYCOMPONENT_H_

#include "Component.h"

class EnergyComponent: public Component
{
public:
	EnergyComponent(int);
	int GetCurrentEnergy();
	int GetMaxEnergy();
	void ModifyCurrentEnergy(char,int);
	void Update(float);
private:
	int currentEnergy;
	int maxEnergy;
};

#endif
