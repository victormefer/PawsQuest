#include "EnergyBar.h"
#include "../managers/ResourceManager.h"
#include "../managers/EntityManager.h"

/*************************************************************
 *
 * Construtor cria todas as barras associadas a barra de
 * energia pegando o path das imagens
 *
 *************************************************************/
EnergyBar::EnergyBar():
blueBar("img/global/bluebar_104x109.png"),
blackBar("img/global/blackbar_104x109.png")//,
//greyBar("img/global/greybar_64x64.png"),
//energy("img/global/gui/gui_energy_34x4.png")
{
	player = NULL;
	//energy.SetScaleX(2);
	//energy.SetScaleY(2);
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
EnergyBar::~EnergyBar()
{

}

/*************************************************************
 *
 * Update updeita a barra de energia baseado na energia do
 * player
 *
 *************************************************************/
void EnergyBar::Update(float dt)
{
	if(player == NULL)
	{
		player = EntityManager::GetInstance().GetEntityByName("Player");
		Display(player->GetComponent<EnergyComponent>("EnergyComponent")->GetCurrentEnergy());
	}
	Display(player->GetComponent<EnergyComponent>("EnergyComponent")->GetCurrentEnergy());
}

/*************************************************************
 *
 * Render
 *
 *************************************************************/
void EnergyBar::Render()
{
	//greyBar.Render(28,56);
	blackBar.Render(0,105);
	blueBar.Render(0,105);
	//energy.Render(32,104);
}

/*************************************************************
 *
 * Display
 *
 *************************************************************/
void EnergyBar::Display(float percentage)
{
	//greyBar.SetClip(0,0,136,16);
	blueBar.SetClip(0,0,112*(percentage/(float)100),8);
	blackBar.SetClip(0,0,112,8);
	//energy.SetClip(0,0,34,4);
}
