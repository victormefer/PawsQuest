#ifndef GOLDCOINGUI_H_
#define GOLDCOINGUI_H_

#include "SDL.h"
#include "SDL_image.h"
#include "GuiSprite.h"
#include "../text/Text.h"

class GoldCoinGui
{
public:
	GoldCoinGui();
	~GoldCoinGui();
	void Update(float dt);
	void Render();
	void Display(int num);
	GuiSprite coinSp;
	Text text;
private:
};

#endif
