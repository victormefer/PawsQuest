#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <exception>

#include "Game.h"
 /*
#include "states/StageState.h"
int main (int argc, char** argv)
{
	Game game("Paws Quest", 1024, 576);
	try
	{
		StageState* stage = new StageState();
		Game::GetInstance().Push(stage);
		Game::GetInstance().Run();
	}
	catch (std::exception& ex)
	{
		std::cout << "Excecao nao tratada: " << ex.what() << std::endl;
	}
	return 0;
}*/

#include "states/CutScene.h"
#include "states/StartMenu.h"

/*************************************************************
 *
 * Main
 *
 *************************************************************/
int main (int argc, char** argv)
{
	Game game("Paws Quest", 1024, 576);
	try
	{
		Game::GetInstance().Push(new StartMenu());
		// Game::GetInstance().Push(new CutScene("img/cutscene",2,1,Music(
		// 	"audio/3_jogando_a_bolinha/jogando_a_bolinha.ogg"),-1));
		Game::GetInstance().Run();
	}
	catch (std::exception& ex)
	{
		std::cout << "Excecao nao tratada: " << ex.what() << std::endl;
	}
	return 0;
}
