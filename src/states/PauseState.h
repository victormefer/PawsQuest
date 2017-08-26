#ifndef PAUSESTATE_H_
#define PAUSESTATE_H_

#include "State.h"
#include "../gui/GuiSprite.h"

class PauseState: public State
{
public:
	PauseState();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
	void SetBossDead();
	void InitBossPhase();
	void SetPlayerDead();
	void StopMusic();
private:
	GuiSprite bg;
	GuiSprite resume;
};

#endif
