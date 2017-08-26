#ifndef ENERGYBAR_H_
#define ENERGYBAR_H_

#include "SDL.h"
#include "SDL_image.h"
#include "GuiSprite.h"
#include "../entities/Entity.h"
#include "../entities/Player.h"

class EnergyBar
{
public:
	EnergyBar();
	~EnergyBar();
	void Update(float dt);
	void Render();
	void Display(float percentage);
private:
	GuiSprite blueBar;
	GuiSprite blackBar;
	//GuiSprite greyBar;
	//GuiSprite energy;
	Entity* player;
};

#endif
