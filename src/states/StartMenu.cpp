#include "StartMenu.h"
#include "../managers/InputManager.h"
#include "../Game.h"
#include "CutScene.h"
#include "TutorialState.h"
#include "FirstPhaseState.h"
#include "../database/CoinDB.h"
#include "../audio/Sound.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
StartMenu::StartMenu():
 bg("img/menu/start_menu_bg_1024x576.png","bg"),
 new_game("img/menu/new_game_192x64.png","new_game"),
 play("img/menu/play_192x64.png","play"),
// store("img/menu/store_192x64.png","store"),
// zones("img/menu/zones_192x64.png","zones"),
 options("img/menu/options_192x64.png","options"),
 exit("img/menu/exit_192x64.png","exit"),
 key_instruction("img/menu/key_instruction_192x64.png","key_instruction"),
 sound_volume("img/menu/sound_volume_192x64.png","sound_volume"),
 back("img/menu/back_192x64.png","back"),
 new_game_selected("img/menu/selected_192x64.png"),
 play_selected("img/menu/selected_192x64.png"),
// store_selected("img/menu/store_selected_192x64.png"),
// zones_selected("img/menu/zones_selected_192x64.png"),
 options_selected("img/menu/options_selected_192x64.png"),
 exit_selected("img/menu/exit_selected_192x64.png"),
 key_instruction_selected("img/menu/key_instruction_selected_192x64.png"),
 sound_volume_selected("img/menu/sound_volume_selected_192x64.png"),
 back_selected("img/menu/back_selected_192x64.png"),
 selected("img/menu/new_game_192x64.png","new_game"),
 key_instruction_clicked("img/menu/key_all_1064x576.png")
{
	music = Music("audio/1_title_theme/title_theme_intro.ogg");
	mainSection = true;
	optionsSection = false;
	key_instructionSection = false;
	sound_volumeSection = false;
	currentSelection = 0;
	mainVec.push_back(new_game);
	mainVec.push_back(play);
//	mainVec.push_back(store);
//	mainVec.push_back(zones);
	mainVec.push_back(options);
	mainVec.push_back(exit);
	optionsVec.push_back(key_instruction);
	optionsVec.push_back(sound_volume);
	optionsVec.push_back(back);
	key_instructionVec.push_back(back);
	sound_volumeVec.push_back(back);
	music.Play(0);
	playingIntro = true;
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void StartMenu::Update(float dt) {

std::cout << "0" << std::endl;
	if (InputManager::GetInstance().IsKeyDown(SDLK_ESCAPE))
	{
		if(mainSection) {quitRequested = true; 			  }
		if(optionsSection) { StartMenu::Main(); 		  }
		if(key_instructionSection){ StartMenu::Options(); }
		if(sound_volumeSection){ StartMenu::Options();	  }
	}
std::cout << "1" << std::endl;
	if (InputManager::GetInstance().QuitRequested())
	{
		quitRequested = true;
	}
std::cout << "2" << std::endl;
	if (InputManager::GetInstance().KeyPress(SDLK_KP_ENTER) ||
		InputManager::GetInstance().KeyPress(SDLK_SPACE))
	{
		if(mainSection)
		{
			if(selected.name == new_game.name){ StartMenu::NewGame(); 		}
			if(selected.name == play.name){ StartMenu::Play(); 				}
//			else if(selected.name == store.name){ StartMenu::Store(); 		}
//			else if(selected.name == zones.name){ StartMenu::Zones(); 		}
			else if(selected.name == options.name) { StartMenu::Options(); 	}
			else if(selected.name == exit.name){ StartMenu::Exit(); 		}
			// else { std::cout << "Error:StartMenu::Update" << std::endl; 	}
		}
		else if(optionsSection)
		{
			if(selected.name == key_instruction.name){ StartMenu::Key_Instruction(); }
			else if(selected.name == sound_volume.name){ StartMenu::Sound_Volume();  }
			else if(selected.name == back.name)
			{
				Sound* sound = new Sound("audio/sons/menu/descelecionar.ogg");
				sound->Play(0);
				StartMenu::Main();
			}
			// else { std::cout << "Error:StartMenu::Update" << std::endl; 			 }
		}
		else if(key_instructionSection)
		{
			if(selected.name == back.name)
			{
				Sound* sound = new Sound("audio/sons/menu/descelecionar.ogg");
				sound->Play(0);
				StartMenu::Options();
			}
			// else { std::cout << "Error:StartMenu::Update" << std::endl; }
		}
		else if(sound_volumeSection)
		{
			if(selected.name == back.name)
			{
				Sound* sound = new Sound("audio/sons/menu/descelecionar.ogg");
				sound->Play(0);
				StartMenu::Options();
			}
			// else { std::cout << "Error:StartMenu::Update" << std::endl; }
		}
	}

	if (InputManager::GetInstance().KeyPress(SDLK_DOWN))
	{
		if(mainSection)
		{
			if((unsigned)(currentSelection+1) < mainVec.size())
			{ selected = mainVec[currentSelection+1]; currentSelection++; }
		}
		if(optionsSection)
		{
			if((unsigned)(currentSelection+1) < optionsVec.size())
			{ selected = optionsVec[currentSelection+1]; currentSelection++; }
		}
		if(key_instructionSection)
		{
			if((unsigned)(currentSelection+1) < key_instructionVec.size())
			{ selected = key_instructionVec[currentSelection+1]; currentSelection++; }
		}
		if(sound_volumeSection)
		{
			if((unsigned)(currentSelection+1) < sound_volumeVec.size())
			{ selected = sound_volumeVec[currentSelection+1]; currentSelection++; }
		}
		Sound* sound = new Sound("audio/sons/menu/selecionar.ogg");
		sound->Play(0);
	}

	if (InputManager::GetInstance().KeyPress(SDLK_UP))
	{
		if(mainSection)
		{
			if((currentSelection-1) > -1)
			{ selected = mainVec[currentSelection-1]; currentSelection--;}
		}
		if(optionsSection)
		{
			if((currentSelection-1) > -1)
			{ selected = optionsVec[currentSelection-1]; currentSelection--;}
		}
		if(key_instructionSection)
		{
			if((currentSelection-1) > -1)
			{ selected = key_instructionVec[currentSelection-1]; currentSelection--;}
		}
		if(sound_volumeSection)
		{
			if((currentSelection-1) > -1)
			{ selected = sound_volumeVec[currentSelection-1]; currentSelection--;}
		}
		Sound* sound = new Sound("audio/sons/menu/selecionar.ogg");
		sound->Play(0);
	}

	if (playingIntro)
	{
		if (!music.IsPlaying())
		{
			music = Music("audio/1_title_theme/title_theme_loop.ogg");
			music.Play(-1);
			playingIntro = false;
		}
	}
}

/*************************************************************
 *
 * Render
 *
 *************************************************************/
void StartMenu::Render() {
	bg.Render(0, 0, 0);
	//O SELECIONADO É RENDERIZADO DIFERENTE DOS DEMAIS
	if(mainSection)
	{
		if(selected.name != new_game.name){ new_game.Render(800,236,0); 	 }
		else{ selected.Open("img/menu/new_game_selected_192x64.png"); selected.Render(800,236,0); }
		if(selected.name != play.name){	play.Render(800,302,0); 			 }
		else{ selected.Open("img/menu/play_selected_192x64.png"); selected.Render(800,302,0); }
//		if(selected.name != store.name){ store.Render(800,236,0); 			 }
//		else{ selected.Open("img/menu/store_selected_192x64.png"); selected.Render(800,236,0); }
//		if(selected.name != zones.name){ zones.Render(800,302,0); 			 }
//		else{ selected.Open("img/menu/zones_selected_192x64.png"); selected.Render(800,302,0); }
		if(selected.name != options.name) { options.Render(800,368,0); 		 }
		else{ selected.Open("img/menu/options_selected_192x64.png"); selected.Render(800,368,0); }
		if(selected.name != exit.name){ exit.Render(800,434,0); 			 }
		else{ selected.Open("img/menu/exit_selected_192x64.png"); selected.Render(800,434,0); }
	}
	if(optionsSection)
	{
		if(selected.name != key_instruction.name){ key_instruction.Render(800,304,0); }
		else{ selected.Open("img/menu/key_instruction_selected_192x64.png"); selected.Render(800,304,0); 		  }
		if(selected.name != sound_volume.name){ sound_volume.Render(800,368,0); 	  }
		else{ selected.Open("img/menu/sound_volume_selected_192x64.png"); selected.Render(800,368,0); 		  }
		if(selected.name != back.name) { back.Render(800,434,0); 					  }
		else{ selected.Open("img/menu/back_selected_192x64.png"); selected.Render(800,434,0); 	      }
	}
	if(key_instructionSection)
	{
		key_instruction_clicked.Render(10,10,0);
		if(selected.name != back.name){ back.Render(420,500,0); 		 }
		else{ selected.Open("img/menu/back_selected_192x64.png"); back.Render(420,500,0); }
	}
	if(sound_volumeSection)
	{
		// std::cout << "DEVERIA DAR CERTO" << std::endl;
		if(selected.name != back.name){ back.Render(420,500,0); 		 }
		else{ selected.Open("img/menu/selected_192x64.png"); back.Render(420,500,0); }
	}
}

/*************************************************************
 *
 * Pause
 *
 *************************************************************/
void StartMenu::Pause() {

}

/*************************************************************
 *
 * Resume
 *
 *************************************************************/
void StartMenu::Resume() {

}

/*************************************************************
 *
 * Main
 *
 *************************************************************/
void StartMenu::Main()
{
	mainSection = true;
	optionsSection = false;
	key_instructionSection = false;
	sound_volumeSection = false;
	currentSelection = 0;
	selected = new_game;
}

/*************************************************************
 *
 * NewGame
 *
 *************************************************************/
void StartMenu::NewGame()
{
	Sound* sound = new Sound("audio/sons/menu/selecao_final.ogg");
	sound->Play(0);
	CoinDB::Delete();
	Game::GetInstance().Push(new CutScene("img/cutscene_0",31,0.1,Music(
			"audio/3_jogando_a_bolinha/jogando_a_bolinha.ogg"),0));
}

/*************************************************************
 *
 * Play
 *
 *************************************************************/
void StartMenu::Play()
{
	Sound* sound = new Sound("audio/sons/menu/selecao_final.ogg");
	sound->Play(0);
	Game::GetInstance().Push(new FirstPhaseState());
}

/*************************************************************
 *
 * Store
 *
 *************************************************************/
void StartMenu::Store()
{

}

/*************************************************************
 *
 * Zones
 *
 *************************************************************/
void StartMenu::Zones()
{

}

/*************************************************************
 *
 * Options
 *
 *************************************************************/
void StartMenu::Options()
{
	mainSection = false;
	optionsSection = true;
	key_instructionSection = false;
	sound_volumeSection = false;
	currentSelection = 0;
	selected = key_instruction;
}

/*************************************************************
 *
 * Exit
 *
 *************************************************************/
void StartMenu::Exit()
{
	quitRequested = true;
}

/*************************************************************
 *
 * Key_Instruction
 *
 *************************************************************/
void StartMenu::Key_Instruction()
{
	mainSection = false;
	optionsSection = false;
	key_instructionSection = true;
	sound_volumeSection = false;
	currentSelection = 0;
	selected = back;
}

/*************************************************************
 *
 * Sound_Volume
 *
 *************************************************************/
void StartMenu::Sound_Volume()
{
	mainSection = false;
	optionsSection = false;
	key_instructionSection = false;
	sound_volumeSection = true;
	currentSelection = 0;
	selected = back;
}

/*************************************************************
 *
 * GetSelected
 *
 *************************************************************/
GuiSprite StartMenu::GetSelected()
{
	return selected;
}

/*************************************************************
 *
 * SetBossDead
 *
 *************************************************************/
void StartMenu::SetBossDead()
{

}

/*************************************************************
 *
 * InitBossPhase
 *
 *************************************************************/
void StartMenu::InitBossPhase()
{

}

/*************************************************************
 *
 * SetPlayerDead
 *
 *************************************************************/
void StartMenu::SetPlayerDead()
{

}

/*************************************************************
 *
 * StopMusic
 *
 *************************************************************/
void StartMenu::StopMusic()
{
	music.Stop();
}
