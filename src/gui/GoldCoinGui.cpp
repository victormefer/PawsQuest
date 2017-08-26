#include <string>
#include "GoldCoinGui.h"
#include "../database/CoinDB.h"
#include "../components/CoinComponent.h"
#include "../managers/EntityManager.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
GoldCoinGui::GoldCoinGui():
coinSp("img/global/coins/gold_coin_32x32.png"),
text("font/font_test.ttf",
	 18,Text::TextStyle::SOLID," ",
	 SDL_Color(),0,0)
{
	std::ostringstream ss;
	ss << CoinDB::goldCoin;
	text.SetText(ss.str());
	GoldCoinGui::Display(1);
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
GoldCoinGui::~GoldCoinGui()
{

}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void GoldCoinGui::Update(float dt)
{
	GoldCoinGui::Display(EntityManager::GetInstance().GetEntityByName("Player")->
		GetComponent<CoinComponent>("CoinComponent")->goldCoins);
}

/*************************************************************
 *
 * Render
 *
 *************************************************************/
void GoldCoinGui::Render()
{
	coinSp.Render(840,10);
	text.Render(875,8);
}

/*************************************************************
 *
 * Display
 *
 *************************************************************/
void GoldCoinGui::Display(int num)
{
	coinSp.SetClip(0,0,coinSp.GetWidth(),coinSp.GetHeight());
	std::ostringstream ss;
	ss << CoinDB::goldCoin;
	text.SetText(ss.str());
}
