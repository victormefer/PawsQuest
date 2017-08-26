#ifndef STARTMENU_H_
#define STARTMENU_H_

#include <string>
#include <vector>
#include "State.h"
#include "../gui/GuiSprite.h"
#include "../audio/Music.h"

class StartMenu: public State {
public:
	StartMenu();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
	void Main();
	void NewGame();
	void Play();
	void Store();
	void Zones();
	void Options();
	void Exit();
	void Key_Instruction();
	void Sound_Volume();
	GuiSprite GetSelected();
	void SetBossDead();
	void InitBossPhase();
	void SetPlayerDead();
	void StopMusic();
private:
	GuiSprite bg;
	GuiSprite new_game;
	GuiSprite play;
//	GuiSprite store;
//	GuiSprite zones;
	GuiSprite options;
	GuiSprite exit;
	GuiSprite key_instruction;
	GuiSprite sound_volume;
	GuiSprite back;
	GuiSprite new_game_selected;
	GuiSprite play_selected;
//	GuiSprite store_selected;
//	GuiSprite zones_selected;
	GuiSprite options_selected;
	GuiSprite exit_selected;
	GuiSprite key_instruction_selected;
	GuiSprite sound_volume_selected;
	GuiSprite back_selected;
	GuiSprite selected;
	GuiSprite key_instruction_clicked;
	std::vector <GuiSprite> mainVec, optionsVec, key_instructionVec, sound_volumeVec;
	int currentSelection;
	bool mainSection, optionsSection, key_instructionSection, sound_volumeSection;
	Music music;
	bool playingIntro;
};

#endif
