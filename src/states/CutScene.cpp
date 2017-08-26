#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "CutScene.h"
#include "../Game.h"
#include "StartMenu.h"
#include "../managers/InputManager.h"
#include "TutorialState.h"
#include "FirstPhaseState.h"
#include "SecondPhaseState.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
CutScene::CutScene(std::string path,int num, float cd, Music music, int phase):
bg("img/menu/start_menu_bg_1024x576.png")
{
	this->path = path;
	this->num = num;
	this->phase = phase;
	this->cd = cd;
	this->music = music;
	this->music.Play(2);

	for(int i=0; i<num; i++)
	{
		opened.push_back(false);
	}
}

/*************************************************************
 *
 * Update vai dando update no tempo e chamando novas imagens
 * da cutscene ate que acabe. Quando acaba chama uma nova state
 *
 *************************************************************/
void CutScene::Update(float dt)
{
	time.Update(dt);
	if(time.Get() < cd*num)
	{
		for(int i=0; i<num; i++)
		{
			if(time.Get() >= (cd*i) && time.Get() < (cd*(i+1)))
			{
				if(opened[i])
				{

				}
				else
				{
					std::stringstream sstm;
					sstm << path << "/cutscene" << i+1 << ".png";
					std::string result = sstm.str();
					bg.Open(result);
					opened[i]=true;
				}
			}
		}
	}
	else
	{
		//Game::GetInstance().Push(new TutorialState());
		popRequested = true;
		if(phase == -1)
		{
			std::cout << "oi " << std::endl;
			Game::GetInstance().Push(new StartMenu());
		}
		if(phase == 0)
			Game::GetInstance().Push(new TutorialState());
		if(phase == 1)
			Game::GetInstance().Push(new FirstPhaseState());
		if(phase == 2)
			Game::GetInstance().Push(new SecondPhaseState());
		//Game::GetInstance().Push(new SecondPhaseState());
	}

	if (InputManager::GetInstance().IsKeyDown(SDLK_ESCAPE))
	{
		quitRequested = true;
	}
	if (InputManager::GetInstance().QuitRequested())
	{
		quitRequested = true;
	}
	/////////////////////////////////////////////////////////////////
	//            !!!!!!!!!!!TIRAR ISSO DEPOIS!!!!!!!!!!!
	/////////////////////////////////////////////////////////////////
	if(InputManager::GetInstance().KeyPress(SPACE_KEY))
	{
		popRequested = true;
		if(phase == -1)
		{
			std::cout << "oi " << std::endl;
			Game::GetInstance().Push(new StartMenu());
		}
		if(phase == 0)
			Game::GetInstance().Push(new TutorialState());
		if(phase == 1)
			Game::GetInstance().Push(new FirstPhaseState());
		if(phase == 2)
			Game::GetInstance().Push(new SecondPhaseState());
	}

}

/*************************************************************
 *
 * Render
 *
 *************************************************************/
void CutScene::Render()
{
	bg.Render(0,0,0);
}

/*************************************************************
 *
 * Pause
 *
 *************************************************************/
void CutScene::Pause()
{

}

/*************************************************************
 *
 * Resume
 *
 *************************************************************/
void CutScene::Resume()
{

}

/*************************************************************
 *
 * Resume
 *
 *************************************************************/
void CutScene::SetBossDead()
{

}

/*************************************************************
 *
 * Resume
 *
 *************************************************************/
void CutScene::InitBossPhase()
{

}

/*************************************************************
 *
 * Resume
 *
 *************************************************************/
void CutScene::SetPlayerDead()
{

}

/*************************************************************
 *
 * StopMusic
 *
 *************************************************************/
void CutScene::StopMusic()
{
	music.Stop();
}
