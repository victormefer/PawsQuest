#ifndef GUI_H_
#define GUI_H_

#include "EnergyBar.h"
#include "HealthBar.h"
#include "GoldCoinGui.h"
#include "SilverCoinGui.h"
#include "BronzeCoinGui.h"
#include "GuiSprite.h"

class Gui
{
public:
	Gui();
	~Gui();
	void Update(float dt);
	void Render();
	EnergyBar* energyBar;
	HealthBar* healthBar;
	GoldCoinGui* goldCoin;
	SilverCoinGui* silverCoin;
	BronzeCoinGui* bronzeCoin;
	GuiSprite bartholomeu;
};

#endif
