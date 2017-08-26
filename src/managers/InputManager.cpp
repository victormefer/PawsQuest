#include"SDL.h"
#include "InputManager.h"

/*************************************************************
 *
 * GetInstance singleton
 *
 *************************************************************/
InputManager& InputManager::GetInstance(){
	static InputManager instance;
	return instance;
}

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
InputManager::InputManager(){
	quitRequested = false;
	updateCounter = 0;
	mouseY = 0;
	mouseX = 0;
	for(int i=1;i<6;i++){
		mouseState[i]=false;
		mouseUpdate[i]=false;
	}
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
InputManager::~InputManager(){

}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void InputManager::Update(){
	 SDL_Event event;
	 quitRequested = false;
	 updateCounter++;
	 SDL_GetMouseState(&mouseX, &mouseY);

	 while (SDL_PollEvent(&event))
		 if(event.key.repeat != 1){
			 if(event.type == SDL_QUIT) {
				 quitRequested = true;
			 }
			 if(event.type == SDL_MOUSEBUTTONDOWN){
				 mouseState[event.button.button] = true;
				 mouseUpdate[event.button.button] = updateCounter;
			 }
			 if(event.type == SDL_MOUSEBUTTONUP){
				 mouseState[event.button.button] = false;
				 mouseUpdate[event.button.button] = updateCounter;
			 }
			 if(event.type == SDL_KEYDOWN){
				 keyState[event.key.keysym.sym] = true;
				 keyUpdate[event.key.keysym.sym] = updateCounter;
			 }
			 if(event.type == SDL_KEYUP){
				 keyState[event.key.keysym.sym] = false;
				 keyUpdate[event.key.keysym.sym] = updateCounter;
			 }

		 }
}

/*************************************************************
 *
 * KeyPress verifica se a key foi clicada
 *
 *************************************************************/
bool InputManager::KeyPress (int key){
	return  (keyState[key] && (keyUpdate[key] == updateCounter));
}

/*************************************************************
 *
 * KeyRelease verifica se a key foi solta
 *
 *************************************************************/
bool InputManager::KeyRelease (int key){
	return  (!keyState[key] && (keyUpdate[key] == updateCounter));
}

/*************************************************************
 *
 * IsKeyDown verifica se a key esta sendo pressionada
 *
 *************************************************************/
bool InputManager::IsKeyDown (int key){
	return keyState[key];
}

/*************************************************************
 *
 * MousePress verifica se o mouse foi clicado
 *
 *************************************************************/
bool InputManager::MousePress (int button){
	return (mouseState[button] && (mouseUpdate[button] == updateCounter));
}

/*************************************************************
 *
 * MouseRelease verifica se o mouse foi solto
 *
 *************************************************************/
bool InputManager::MouseRelease (int button){
	return (!mouseState[button]&& (mouseUpdate[button] == updateCounter));
}

/*************************************************************
 *
 * IsMouseDown verifica se o mouse esta sendo pressionado
 *
 *************************************************************/
bool InputManager::IsMouseDown (int button){
	return mouseState[button];
}

/*************************************************************
 *
 * GetMouseX
 *
 *************************************************************/
int InputManager::GetMouseX(){
	return mouseX;
}

/*************************************************************
 *
 * GetMouseY
 *
 *************************************************************/
int InputManager::GetMouseY(){
	return mouseY;
}

/*************************************************************
 *
 * QuitRequested verifica se desejamos sair do jogo
 *
 *************************************************************/
bool InputManager::QuitRequested(){
	return quitRequested;
}
