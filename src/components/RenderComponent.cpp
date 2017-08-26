#include "RenderComponent.h"
#include "../Game.h"
#include "../managers/ResourceManager.h"

/*************************************************************
 *
 * Construtor exige que pelo menos o path da imagem seja
 * especificado
 *
 *************************************************************/
RenderComponent::RenderComponent(std::string file, int frameCount, float frameTime)
{
	SetName("RenderComponent");
	this->texture = NULL;
	this->frameCount = frameCount;
	this->frameTime = frameTime;
	this->currentFrame = 0;
	this->timeElapsed = 0;
	path = file;
	Open(file);
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
RenderComponent::~RenderComponent()
{

}

/*************************************************************
 *
 * Open garante que a texture seja carregada
 *
 *************************************************************/
void RenderComponent::Open(std::string file, bool ends)
{
	texture = ResourceManager::GetImage(file);
	SDL_QueryTexture(texture.get(), NULL, NULL, &width, &height);
	SetClip(0, 0, width / frameCount, height);
	timeElapsed = 0.0;
	currentFrame = 0;
	this->ends = ends;
}

/*************************************************************
 *
 * SetClip
 *
 *************************************************************/
void RenderComponent::SetClip(int x, int y, int w, int h)
{
	this->clipRect.x = x;
	this->clipRect.y = y;
	this->clipRect.w = w;
	this->clipRect.h = h;
}

/*************************************************************
 *
 * Render renderiza de acordo com a posicao (transform) do
 * owner do componente
 *
 *************************************************************/
void RenderComponent::Render(TransformComponent* transformComponent, bool flip)
{
	if(IsEnable())
	{
		SDL_Rect dstrect;
		dstrect.x = transformComponent->GetPosition().x - Camera::pos.getX();
		dstrect.y = transformComponent->GetPosition().y - Camera::pos.getY();
		dstrect.w = clipRect.w * transformComponent->GetScale().getX();
		dstrect.h = clipRect.h * transformComponent->GetScale().getY();

		SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstrect,
			transformComponent->GetRotation(), NULL, RenderComponent::GetFacingLeft() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	}
}

/*************************************************************
 *
 * GetWidth
 *
 *************************************************************/
int RenderComponent::GetWidth()
{
	return width/frameCount;
}

/*************************************************************
 *
 * GetFrameWidth
 *
 *************************************************************/
int RenderComponent::GetFrameWidth()
{
	return width/frameCount;
}

/*************************************************************
 *
 * GetHeight
 *
 *************************************************************/
int RenderComponent::GetHeight()
{
	return height;
}

/*************************************************************
 *
 * IsOpen retorna se existe uma texture associada a variavel
 *
 *************************************************************/
bool RenderComponent::IsOpen()
{
	if (texture != NULL) return true;
	else return false;
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void RenderComponent::Update(float dt)
{
	if((currentFrame + 1 == frameCount) && ends){
	}else{

		timeElapsed += dt;
		if (timeElapsed >= frameTime)
		{
			SetFrame(currentFrame + 1);
			timeElapsed = 0.0;
		}
	}
}

/*************************************************************
 *
 * GetFrameCount
 *
 *************************************************************/
int RenderComponent::GetFrameCount()
{
	return frameCount;
}

/*************************************************************
 *
 * GetFrameTime
 *
 *************************************************************/
float RenderComponent::GetFrameTime()
{
	return frameTime;
}

/*************************************************************
 *
 * GetFacingLeft
 *
 *************************************************************/
bool RenderComponent::GetFacingLeft()
{
	return facingLeft;
}

/*************************************************************
 *
 * SetFrame
 *
 *************************************************************/
void RenderComponent::SetFrame(int frame)
{
	currentFrame = frame % frameCount;
	timeElapsed = 0.0;
	SetClip( currentFrame * width / frameCount, 0, width / frameCount, height );
}

/*************************************************************
 *
 * SetFrameCount
 *
 *************************************************************/
void RenderComponent::SetFrameCount(int frameCount)
{
	this->frameCount = frameCount;
}

/*************************************************************
 *
 * SetFrameTime
 *
 *************************************************************/
void RenderComponent::SetFrameTime(float frameTime)
{
	this->frameTime = frameTime;
}

/*************************************************************
 *
 * SetFacingLeft
 *
 *************************************************************/
void RenderComponent::SetFacingLeft(bool facingLeft)
{
	this->facingLeft = facingLeft;
}
