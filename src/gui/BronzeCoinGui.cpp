#include <string>
#include <sstream>
#include "BronzeCoinGui.h"
#include "../database/CoinDB.h"
#include "../components/CoinComponent.h"
#include "../managers/EntityManager.h"

/*************************************************************
 *
 * Construtor coloca o gui da medalha de bronze na tela e
 * o texto associado a ela dizendo quantas moedas daquele
 * tipo o player tem
 *
 *************************************************************/
BronzeCoinGui::BronzeCoinGui():
coinSp("img/global/coins/bronze_coin_32x32.png"),
text("font/font_test.ttf",
	 18,Text::TextStyle::SOLID," ",
	 SDL_Color(),0,0)
{
	std::ostringstream ss;
	ss << CoinDB::bronzeCoin;
	text.SetText(ss.str());
	BronzeCoinGui::Display(1);
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
BronzeCoinGui::~BronzeCoinGui()
{

}

/*************************************************************
 *
 * Update muda a quantidade de moedas dependendo de eventos
 * fora dessa classe
 *
 *************************************************************/
void BronzeCoinGui::Update(float dt)
{
	BronzeCoinGui::Display(EntityManager::GetInstance().GetEntityByName("Player")->
		GetComponent<CoinComponent>("CoinComponent")->bronzeCoins);
}

/*************************************************************
 *
 * Render
 *
 *************************************************************/
void BronzeCoinGui::Render()
{
	coinSp.Render(960,10);
	text.Render(995,8);
}

/*************************************************************
 *
 * Display
 *
 *************************************************************/
void BronzeCoinGui::Display(float num)
{
	coinSp.SetClip(0,0,coinSp.GetWidth(),coinSp.GetHeight());
	std::ostringstream ss;
	ss << CoinDB::bronzeCoin;
	text.SetText(ss.str());
}

