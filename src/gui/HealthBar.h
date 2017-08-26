#ifndef HEALTHBAR_H_
#define HEALTHBAR_H_

#include "SDL.h"
#include "SDL_image.h"
#include "GuiSprite.h"
#include "../entities/Entity.h"

class HealthBar
{
public:
	HealthBar();
	~HealthBar();
	void Update(float dt);
	void Render();
	void Display(float percentage);
private:
	GuiSprite redBar;
	GuiSprite blackBar;
	//GuiSprite greyBar;
	//GuiSprite life;
	Entity* player;
};

#endif
