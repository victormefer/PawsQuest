#ifndef GAME_H_
#define GAME_H_

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "states/State.h"
#include "managers/ResourceManager.h"
#include <stack>
#include <cstdlib>
#include <ctime>
#include <memory>

#include <iostream>

 #define FPS 60

class Game
{
	public:
		Game(std::string Title, int width, int height);
		~Game();
		void Run();
		void Push(State* state);
		SDL_Renderer* GetRenderer();
		State& GetCurrentState();
		static Game& GetInstance();
		float GetDeltaTime();
	private:
		void CalculateDeltaTime();
		static Game* instance;
		SDL_Window* window;
		SDL_Renderer* renderer;
		std::stack<std::unique_ptr<State>> stateStack;
		State* storedState;
		int frameStart;
		float dt;
};

#endif
