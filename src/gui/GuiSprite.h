#ifndef GUISPRITE_H_
#define GUISPRITE_H_

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

class GuiSprite
{
public:
	GuiSprite();
	GuiSprite(std::string,std::string name="default_name");
	void Open (std::string);
	void SetClip(int,int,int,int);
	void Render(int,int,float angle = 0);
	int GetWidth(void);
	int GetHeight(void);
	bool Isopen(void);
	void SetScaleX(float);
	void SetScaleY(float);
	SDL_Rect clipRect;
	std::string name;
private:
	SDL_Texture* texture;
	int width;
	int height;
	float scaleX;
	float scaleY;
};

#endif
