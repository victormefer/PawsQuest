#include "CoinComponent.h"
#include "../database/CoinDB.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
CoinComponent::CoinComponent()
{
	SetName("CoinComponent");
	goldCoins = 0;
	silverCoins = 0;
	bronzeCoins = 0;
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
CoinComponent::~CoinComponent()
{

}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void CoinComponent::Update(float dt)
{

}

/*************************************************************
 *
 * Modifica a quantidade de cois no banco de dados
 *
 *************************************************************/
void CoinComponent::ModifyCurrentCoins()
{
	goldCoins = CoinDB::goldCoin;
	silverCoins = CoinDB::silverCoin;
	bronzeCoins = CoinDB::bronzeCoin;
}
