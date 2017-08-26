#include <string>
#include <sstream>
#include "SilverCoinGui.h"
#include "../database/CoinDB.h"
#include "../components/CoinComponent.h"
#include "../managers/EntityManager.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
SilverCoinGui::SilverCoinGui():
coinSp("img/global/coins/silver_coin_32x32.png"),
text("font/font_test.ttf",
	 18,Text::TextStyle::SOLID," ",
	 SDL_Color(),0,0)
{
	std::ostringstream ss;
	ss << CoinDB::silverCoin;
	text.SetText(ss.str());
	SilverCoinGui::Display(1);
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
SilverCoinGui::~SilverCoinGui()
{

}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void SilverCoinGui::Update(float dt)
{
	SilverCoinGui::Display(EntityManager::GetInstance().GetEntityByName("Player")->
		GetComponent<CoinComponent>("CoinComponent")->silverCoins);
}

/*************************************************************
 *
 * Render
 *
 *************************************************************/
void SilverCoinGui::Render()
{
	coinSp.Render(900,10);
	text.Render(935,8);
}

/*************************************************************
 *
 * Display
 *
 *************************************************************/
void SilverCoinGui::Display(float num)
{
	coinSp.SetClip(0,0,coinSp.GetWidth(),coinSp.GetHeight());
	std::ostringstream ss;
	ss << CoinDB::silverCoin;
	text.SetText(ss.str());
}





