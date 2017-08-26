#include "GuiSprite.h"
#include "../managers/ResourceManager.h"

GuiSprite::GuiSprite()
{
	this->name = "default_name";
	texture = NULL;
	scaleX = 1;
	scaleY = 1;
	width = 64;
	height = 64;
}

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
GuiSprite::GuiSprite(std::string file,std::string name)
{
	this->name = name;
	texture = NULL;
	Open(file);
	scaleX=1;
	scaleY=1;
}

/*************************************************************
 *
 * Open
 *
 *************************************************************/
void GuiSprite::Open(std::string file){
	 //texture = ResourceManager::GetImage(file);
	 texture = IMG_LoadTexture ( Game::GetInstance().GetRenderer() , file.c_str() );
	 if(texture == NULL)
	  std::cout<< "ERRO:" << SDL_GetError();

	 SDL_QueryTexture(texture,NULL,NULL,&width,&height);
	 SetClip(0, 0, width, height);
}

/*************************************************************
 *
 * SetClip
 *
 *************************************************************/
void GuiSprite::SetClip(int x, int y, int width, int height){
	 clipRect.x = x;
	 clipRect.y = y;
	 clipRect.w = width;
	 clipRect.h = height;
}

/*************************************************************
 *
 * Render
 *
 *************************************************************/
void GuiSprite::Render(int x, int y,float angle){
	 SDL_Rect dstrect;
	 dstrect.x = x;
	 dstrect.y = y;
	 dstrect.w = clipRect.w*scaleX;
	 dstrect.h = clipRect.h*scaleY;
	 SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),
			 texture,
			 &clipRect,
			 &dstrect,
			 angle ,
			 NULL,
			 SDL_FLIP_NONE);

}

/*************************************************************
 *
 * GetWidth
 *
 *************************************************************/
int GuiSprite::GetWidth() {
	return width*scaleX;
}

/*************************************************************
 *
 * GetHeight
 *
 *************************************************************/
int GuiSprite::GetHeight() {
	return height*scaleY;
}

/*************************************************************
 *
 * IsOpen
 *
 *************************************************************/
bool GuiSprite::Isopen(){
	return !(texture == NULL);
}

/*************************************************************
 *
 * SetScaleX
 *
 *************************************************************/
 void GuiSprite::SetScaleX(float scale){
	 scaleX = scale;
 }

 /*************************************************************
  *
  * SetScaleY
  *
  *************************************************************/
 void GuiSprite::SetScaleY(float scale){
	 scaleY = scale;
 }

