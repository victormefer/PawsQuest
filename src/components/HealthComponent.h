#ifndef HEALTHCOMPONENT_H_
#define HEALTHCOMPONENT_H_

#include "Component.h"

class HealthComponent: public Component
{
public:
	HealthComponent(int);
	int GetCurrentHealth();
	int GetMaxHealth();
	void ModifyCurrentHealth(char,int);
	void Update(float);
	void IsDead();
private:
	int currentHealth;
	int maxHealth;
};

#endif
