#include "Gui.h"
#include "../database/CoinDB.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
Gui::Gui():
bartholomeu("img/global/gui/gui_bartholomeu_158x128.png")
{
	energyBar = new EnergyBar();
	healthBar = new HealthBar();
	CoinDB::Load();
	goldCoin = new GoldCoinGui();
	silverCoin = new SilverCoinGui();
	bronzeCoin = new BronzeCoinGui();
	//bartholomeu->Open("img/global/gui/gui_bartholomeu_158x128.png");
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
Gui::~Gui()
{

}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void Gui::Update(float dt)
{
	energyBar->Update(dt);
	healthBar->Update(dt);
	goldCoin->Update(dt);
	silverCoin->Update(dt);
	bronzeCoin->Update(dt);
}

/*************************************************************
 *
 * Render
 *
 *************************************************************/
void Gui::Render()
{
	bartholomeu.Render(0,32);
	energyBar->Render();
	healthBar->Render();
	goldCoin->Render();
	silverCoin->Render();
	bronzeCoin->Render();
}
