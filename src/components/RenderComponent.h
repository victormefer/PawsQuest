#ifndef RENDERCOMPONENT_H_
#define RENDERCOMPONENT_H_

#include "Component.h"
#include "TransformComponent.h"
#include "../Camera.h"
#include "SDL.h"
#include "SDL_image.h"
#include <memory>

class RenderComponent:public Component
{
public:
	RenderComponent(std::string file, int frameCount = 1, float frameTime = 1 );
	~RenderComponent();
	void Open(std::string file, bool ends = false);
	void SetClip(int x, int y, int w, int h);
	void Update(float dt);
	void Render(TransformComponent* transformComponent, bool flip = false);
	int GetFrameWidth();
	int GetWidth();
	int GetHeight();
	bool IsOpen();
	int GetFrameCount();
	float GetFrameTime();
	bool GetFacingLeft();
	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
	void SetFacingLeft(bool facingLeft);
	std::string path;
	std::shared_ptr<SDL_Texture> texture;
private:
	SDL_Rect clipRect;
	int width;
	int height;
	int frameCount, currentFrame;
	float timeElapsed, frameTime;
	bool ends;
	bool facingLeft = false;
};

#endif
