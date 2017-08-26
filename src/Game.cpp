#include "Game.h"
#include "managers/EntityManager.h"
#include "entities/Entity.h"
#include "components/TransformComponent.h"
#include "components/RenderComponent.h"
#include "physics/Point.h"
#include "managers/InputManager.h"
#include <iostream>

Game* Game::instance = NULL;

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
Game::Game (std::string Title, int width, int height)
{
//	dt = 0;
//	frameStart = 0;
	if (instance != NULL){ std::cout<< "Instance != NULL" << std::endl; }
	else
	{
		instance = this;

		//SDL_INIT
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0 )
		{
			std::cout<< "SDL_Init falhou: %s \n", SDL_GetError();
			exit(1);
		}
		//IMG_INIT
		if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0)
		{
			std::cout<< "IMG_Init falhou: %s \n", SDL_GetError();
			exit(1);
		}
		// MIX_INIT
		if ( Mix_Init(MIX_INIT_OGG) == 0 )
		{
			std::cout << "Mix_Init falhou: " << Mix_GetError() << std::endl;
			exit(1);
		}
		// MIX_OPENAUDIO
		if ( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0 )
		{
			std::cout << "Mix_OpenAudio falhou: " << Mix_GetError() << std::endl;
			exit(1);
		}
		// TFF_INIT
		if ( TTF_Init() != 0 )
		{
			std::cerr << "TTF_Init falhou: " << TTF_GetError() << std::endl;
			exit(1);
		}

		// JOY STICK
		if (SDL_Init( SDL_INIT_JOYSTICK ) < 0)
		{
			std::cout << "Couldn't initialize SDL:" << SDL_GetError() << std::endl;
			exit(1);
		}
		std::cout << SDL_NumJoysticks() << "joysticks were found" << std::endl;

		window = SDL_CreateWindow(Title.c_str(),SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, width, height, 0);
		if (window == NULL){ std::cout<< "SDL_Window falhou: %s \n", SDL_GetError(); }
		renderer = /*SDL_Renderer**/ SDL_CreateRenderer(window, -1,	SDL_RENDERER_ACCELERATED);
		if (renderer == NULL){ std::cout<< "SDL_Renderer falhou: %s \n", SDL_GetError(); }

		storedState = NULL;
		frameStart = 0;
		dt = 0;
	}

}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
Game::~Game ()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

/*************************************************************
 *
 * Run
 *
 *************************************************************/
void Game::Run()
{
	if (storedState != NULL)
	{
		stateStack.emplace(storedState);
		storedState = NULL;
	}

	while (!stateStack.empty() && !stateStack.top()->QuitRequested())
	{
		CalculateDeltaTime();
		InputManager::GetInstance().Update();

		stateStack.top()->Update(dt);
		stateStack.top()->Render();
		SDL_RenderPresent(renderer);

		if (stateStack.top()->PopRequested())
		{
			stateStack.pop();
			// Destruir todos os recursos carregados
			ResourceManager::ClearImages();
			ResourceManager::ClearMusic();
			ResourceManager::ClearSound();
			ResourceManager::ClearFonts();
			stateStack.top()->Resume();
		}

		if (storedState != NULL)
		{
			stateStack.top()->Pause();
			stateStack.emplace(storedState);
			storedState = NULL;
		}

//		SDL_Delay(33);
		/*
		if(Game::GetDeltaTime() < ((float)1/60))
		{
			SDL_Delay(((((float)1/60)) - Game::GetDeltaTime())*1000);
		}*/
		/*if ( (float)(SDL_GetTicks() - frameStart) < 1000.0 / 60.0 )
			SDL_Delay( (1000.0/60.0) - (frameStart - SDL_GetTicks()) );*/

		float frameEnd = (float)SDL_GetTicks();

		if((frameEnd-frameStart) < (float)(1000.f / FPS))
			while(frameEnd - frameStart <= (1000.f / FPS)){
				frameEnd = (float)SDL_GetTicks();
			}
	}

	// Remover todos os states da pilha
	if (stateStack.top()->QuitRequested())
	{
		while(!stateStack.empty())
			stateStack.pop();

		// Destruir todos os recursos carregados
		ResourceManager::ClearImages();
		ResourceManager::ClearMusic();
		ResourceManager::ClearSound();
		ResourceManager::ClearFonts();
	}
}

/*************************************************************
 *
 * Push
 *
 *************************************************************/
void Game::Push(State* state)
{
	storedState = state;
}

/*************************************************************
 *
 * GetRenderer
 *
 *************************************************************/
SDL_Renderer* Game::GetRenderer()
{
	return renderer;
}

/*************************************************************
 *
 * GetCurrentState
 *
 *************************************************************/
State& Game::GetCurrentState()
{
	return *stateStack.top();
}

/*************************************************************
 *
 * GetInstance
 *
 *************************************************************/
Game& Game::GetInstance()
{
	return *instance;
}

/*************************************************************
 *
 * CalculateDeltaTime
 *
 *************************************************************/
void Game::CalculateDeltaTime()
{
	dt = (float)(SDL_GetTicks() - frameStart)/1000.0;
	frameStart = SDL_GetTicks();
}

/*************************************************************
 *
 * GetDeltaTime
 *
 *************************************************************/
float Game::GetDeltaTime()
{
	return dt;
}
