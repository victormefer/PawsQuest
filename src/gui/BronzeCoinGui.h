#ifndef BRONZECOINGUI_H_
#define BRONZECOINGUI_H_

#include "SDL.h"
#include "SDL_image.h"
#include "GuiSprite.h"
#include "../text/Text.h"

class BronzeCoinGui
{
public:
	BronzeCoinGui();
	~BronzeCoinGui();
	void Update(float dt);
	void Render();
	void Display(float num);
private:
	GuiSprite coinSp;
	Text text;
};

#endif
