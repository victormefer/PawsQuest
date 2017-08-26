#include "EnergyComponent.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
EnergyComponent::EnergyComponent(int maxEnergy)
{
	SetName("EnergyComponent");
	this->maxEnergy = maxEnergy;
	this->currentEnergy = 0;
}

/*************************************************************
 *
 * Pega a energia atual da entidade
 *
 *************************************************************/
int EnergyComponent::GetCurrentEnergy()
{
	return currentEnergy;
}

/*************************************************************
 *
 * Pega a energia maxima da entidade
 *
 *************************************************************/
int EnergyComponent::GetMaxEnergy()
{
	return maxEnergy;
}

/*************************************************************
 *
 * Update
 *
 *************************************************************/
void EnergyComponent::Update(float dt)
{

}

/*************************************************************
 *
 * Modifica a energia atual da entidade
 *
 *************************************************************/
void EnergyComponent::ModifyCurrentEnergy(char sign, int modify)
{
	if(sign == '+')
		if(currentEnergy+modify > maxEnergy)
			this->currentEnergy = maxEnergy;
		else
			this->currentEnergy += modify;
	else if(sign == '-')
		this->currentEnergy -= modify;
	else
		std::cout << "HealthComponent::modifyCurrentEnergy recebeu um sign invalido" << std::endl;
}
