#include "HealthBar.h"
#include "../managers/ResourceManager.h"
#include "../components/HealthComponent.h"
#include "../managers/EntityManager.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
HealthBar::HealthBar():
redBar("img/global/redbar_64x64.png"),
blackBar("img/global/blackbar_104x109.png")//,
//greyBar("img/global/greybar_64x64.png"),
//life("img/global/gui/gui_life_20x4.png")
{
	player = NULL;
	//life.SetScaleX(2);
	//life.SetScaleY(2);
//	if(EntityManager::GetInstance().GetEntityByName("Player") != NULL)
//	{
//		player = EntityManager::GetInstance().GetEntityByName("Player");
//		Display(player->GetComponent<HealthComponent>("HealthComponent")->GetCurrentHealth());
//	}
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
HealthBar::~HealthBar()
{

}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void HealthBar::Update(float dt)
{
	if(player == NULL)
	{
		player = EntityManager::GetInstance().GetEntityByName("Player");
		Display(player->GetComponent<HealthComponent>("HealthComponent")->GetCurrentHealth());
	}
	player = EntityManager::GetInstance().GetEntityByName("Player");
	Display(player->GetComponent<HealthComponent>("HealthComponent")->GetCurrentHealth());

}

/*************************************************************
 *
 * Render
 *
 *************************************************************/
void HealthBar::Render()
{
	//greyBar.Render(28,28);
	blackBar.Render(0,85);
	redBar.Render(0,85);
	//life.Render(40,85);
}

/*************************************************************
 *
 * Display
 *
 *************************************************************/
void HealthBar::Display(float percentage)
{
	redBar.SetClip(0,0,112*(percentage/(float)100),8);
	blackBar.SetClip(0,0,112,8);
	//greyBar.SetClip(0,0,136,16);
	//life.SetClip(0,0,20,4);
}
