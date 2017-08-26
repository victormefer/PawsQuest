#include "PauseState.h"
#include "../managers/InputManager.h"

PauseState::PauseState():
bg("img/menu/pause_1024x576.png"),
resume("img/menu/resume_selected_192x64.png")
{

}

void PauseState::Update(float dt)
{
	if(InputManager::GetInstance().QuitRequested())
		quitRequested = true;

	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY))
		popRequested = true;

	if(InputManager::GetInstance().KeyPress(SPACE_KEY))
		popRequested = true;


}

void PauseState::Render()
{
	bg.Render(0,0,0);
	resume.Render(416,302);
}

void PauseState::Pause()
{

}

void PauseState::Resume()
{

}

void PauseState::SetBossDead()
{

}

void PauseState::InitBossPhase()
{

}

void PauseState::SetPlayerDead()
{

}

void PauseState::StopMusic()
{

}
