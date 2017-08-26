#ifndef SILVERCOINGUI_H_
#define SILVERCOINGUI_H_

#include "SDL.h"
#include "SDL_image.h"
#include "GuiSprite.h"
#include "../text/Text.h"

class SilverCoinGui
{
public:
	SilverCoinGui();
	~SilverCoinGui();
	void Update(float dt);
	void Render();
	void Display(float num);
private:
	GuiSprite coinSp;
	Text text;
};

#endif
