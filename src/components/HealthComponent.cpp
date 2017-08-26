#include "HealthComponent.h"
#include "../Save.h"
#include "../managers/EntityManager.h"
#include "../entities/StillAnimation.h"
#include "../entities/Ratazana.h"
#include "../entities/MinionRatazana.h"
#include "../audio/Sound.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
HealthComponent::HealthComponent(int maxHealth)
{
	SetName("HealthComponent");
	this->currentHealth = maxHealth;
	this->maxHealth = maxHealth;
}

/*************************************************************
 *
 * GetCurrentHealth
 *
 *************************************************************/
int HealthComponent::GetCurrentHealth()
{
	return currentHealth;
}

/*************************************************************
 *
 * GetMaxHealth
 *
 *************************************************************/
int HealthComponent::GetMaxHealth()
{
	return maxHealth;
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void HealthComponent::Update(float dt){
	HealthComponent::IsDead();
}

/*************************************************************
 *
 * Modifica a vida atual da entidade
 *
 *************************************************************/
void HealthComponent::ModifyCurrentHealth(char sign, int modify)
{
	if(sign == '+')
		if(currentHealth+modify > maxHealth)
			this->currentHealth = maxHealth;
		else
			this->currentHealth += modify;
	else if(sign == '-')
		this->currentHealth -= modify;
	else
		std::cout << "HealthComponent::modifyCurrentEnergy recebeu um sign invalido" << std::endl;
}

/*************************************************************
 *
 * IsDead
 *
 *************************************************************/
void HealthComponent::IsDead()
{
	if(currentHealth <= 0)
	{
		/*************************************************************
		 *
		 * Player
		 *
		 *************************************************************/
		if(this->GetOwner()->tag == "Player")
		{
				Game::GetInstance().GetCurrentState().SetPlayerDead();
		}
		/*************************************************************
		 *
		 * Enemy
		 *
		 *************************************************************/
		if(this->GetOwner()->tag == "Enemy")
		{
			/*************************************************************
			 *
			 * Quais sons ativar para cada inimigo diferente
			 *
			 *************************************************************/
			if(this->GetOwner()->GetName() == "Calopsita")
			{
				Sound* sound = new Sound("audio/sons/calopsita/morrendo.ogg");
				sound->Play(0);
			}
			else if(this->GetOwner()->GetName() == "Crocodilo")
			{
				Sound* sound = new Sound("audio/sons/crocodilo/death.ogg");
				sound->Play(0);
			}
			else if(this->GetOwner()->GetName() == "Pombo" ||
			   this->GetOwner()->GetName() == "PomboTopete")
			{
				Sound* sound = new Sound("audio/sons/pombo/morte.ogg");
				sound->Play(0);
			}
			else
			{
				Sound* sound = new Sound("audio/sons/morte_outros_inimigos/death.ogg");
				sound->Play(0);
			}

			/*************************************************************
			 *
			 * Remove o inimigo e coloca a animacao posterior a morte dele
			 *
			 *************************************************************/

			int x = this->GetOwner()->GetComponent<TransformComponent>
					("TransformComponent")->GetPosition().x;
			int y = this->GetOwner()->GetComponent<TransformComponent>
					("TransformComponent")->GetPosition().y;

			this->GetOwner()->Delete();

			EntityManager::GetInstance().addEntity(new StillAnimation(
				x, y, 0, "Enemy", "img/fumaca_697x67.png", 12, 0.2, 2.4, true
			));
		}

		/*************************************************************
		 *
		 * Boss
		 *
		 *************************************************************/
		if(this->GetOwner()->tag == "Boss")
		{
			if(this->GetOwner()->GetName() == "Ratazana")
			{
				//tocar musica para morte do boss
				this->GetOwner()->Delete();
			}
			if(this->GetOwner()->GetName() == "MinionRatazana")
			{
				int x = this->GetOwner()->GetComponent<TransformComponent>
					("TransformComponent")->GetPosition().x;
				int y = this->GetOwner()->GetComponent<TransformComponent>
					("TransformComponent")->GetPosition().y;
				//tirar do vetor da ratazana
				// for(int i = 0  ;
				// 	i  < dynamic_cast<Ratazana*>(EntityManager::GetInstance().GetEntityByName("Ratazana"))->minionArray.size();
				// 	i++){
				// 	if(dynamic_cast<Ratazana*>(EntityManager::GetInstance().GetEntityByName("Ratazana"))->minionArray[i]->GetId() == this->GetOwner()->GetId())
				// 		dynamic_cast<Ratazana*>(EntityManager::GetInstance().GetEntityByName("Ratazana"))->minionArray.erase(
				// 			dynamic_cast<Ratazana*>(EntityManager::GetInstance().GetEntityByName("Ratazana"))->minionArray.begin() + i);
				// }
				
				//mandando o outro atacar
				// if(!dynamic_cast<Ratazana*>(EntityManager::GetInstance().GetEntityByName("Ratazana"))->minionArray.empty())
				// {
				// 	dynamic_cast<MinionRatazana*>(dynamic_cast<Ratazana*>(EntityManager::GetInstance().
				// 		GetEntityByName("Ratazana"))->minionArray.begin())->attacking = true;
				// }

				//tocar musica para morte do boss
				this->GetOwner()->Delete();
				EntityManager::GetInstance().addEntity(new StillAnimation(
				x, y, 0, "Enemy", "img/fumaca_697x67.png", 12, 0.2, 2.4, true
			));
			}
		}
	}
}