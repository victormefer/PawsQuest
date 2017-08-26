#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>
#include "MessageManager.h"
#include "EntityManager.h"
#include "../Save.h"
#include "../entities/Entity.h"
#include "../entities/Esquilo.h"
#include "../entities/Nut.h"
#include "../components/EnergyComponent.h"
#include "../components/HealthComponent.h"
#include "../components/TransformComponent.h"
#include "../components/PlayerStateComponent.h"
#include "../components/EdgeCooldownComponent.h"
#include "../components/MoveComponent.h"
#include "../components/HatTimerComponent.h"
#include "../components/HidranteTimerComponent.h"
#include "../components/HangingComponent.h"
#include "../components/AttachableComponent.h"
#include "../messages/Message.h"
#include "../database/CoinDB.h"
#include "../managers/EntityManager.h"
#include "../database/SaveDB.h"
#include "../states/TutorialState.h"
#include "../states/FirstPhaseState.h"
#include "../states/SecondPhaseState.h"
#include "../audio/Sound.h"

MessageManager* MessageManager::instance = NULL;
std::map<int,Message*> MessageManager::messageMap;

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
MessageManager::MessageManager()
{
	if (instance != NULL){			}
	else{ instance = this; }
}

/*************************************************************
 *
 * GetInstance
 *
 *************************************************************/
MessageManager& MessageManager::GetInstance()
{
	return *instance;
}

/*************************************************************
 *
 * HandleMessaging busca no mapa de mensagens e trata elas
 * naquele frame, comportamentos diferentes serao ativados
 * dependendo do tipo de mensagem e de quem transmitiu a
 * mensagem. Junto a ela teremos a entidade que esta interessada
 * em receber a mensagem
 *
 *************************************************************/
void MessageManager::HandleMessaging()
{
	if(!messageMap.empty())
	{
		for (auto it=messageMap.begin();
			it!=messageMap.end();
			++it)
		{
			/*************************************************************
			 *
			 * O tipo de mensagem esta relacionado a Colisao
			 *
			 *************************************************************/
			if(it->second->type == Message::COLLISION_DETECTED)
			{
				/*************************************************************
				 *
				 * Se o dono da mensagem for o Player
				 *
				 *************************************************************/
				if (it->second->GetOwner()->tag == "Player")
				{
					/*************************************************************
					 *
					 * Colisao com itens
					 *
					 *************************************************************/
					if (it->second->GetReceiver()->tag == "Item")
					{
						if(it->second->GetReceiver()->GetName() == "Energy")
						{
							Sound* sound = new Sound("audio/sons/osso/osso.ogg");
							sound->Play(0);
							EntityManager::GetInstance().GetEntityByName("Player")->
									GetComponent<EnergyComponent>("EnergyComponent")->
									ModifyCurrentEnergy('+',25);
							EntityManager::GetInstance().removeEntity(
								it->second->GetReceiver()->GetId());
						}
						else if(it->second->GetReceiver()->GetName() == "Health")
						{
							Sound* sound = new Sound("audio/sons/racao/recuperandovida.ogg");
							sound->Play(0);
							EntityManager::GetInstance().GetEntityByName("Player")->
									GetComponent<HealthComponent>("HealthComponent")->
									ModifyCurrentHealth('+',25);
							EntityManager::GetInstance().removeEntity(
								it->second->GetReceiver()->GetId());
						}
						else if(it->second->GetReceiver()->GetName() == "GoldCoin")
						{
							Sound* sound = new Sound("audio/sons/coins/gold.ogg");
							sound->Play(0);
							CoinDB::Add('G');
							CoinDB::Load();
							EntityManager::GetInstance().removeEntity(
								it->second->GetReceiver()->GetId());
						}
						else if(it->second->GetReceiver()->GetName() == "SilverCoin")
						{
							Sound* sound = new Sound("audio/sons/coins/silver.ogg");
							sound->Play(0);
							CoinDB::Add('S');
							CoinDB::Load();
							EntityManager::GetInstance().removeEntity(
							it->second->GetReceiver()->GetId());
						}
						else if(it->second->GetReceiver()->GetName() == "BronzeCoin")
						{
							Sound* sound = new Sound("audio/sons/coins/bronze.ogg");
							sound->Play(0);
							CoinDB::Add('B');
							CoinDB::Load();
							EntityManager::GetInstance().removeEntity(
							it->second->GetReceiver()->GetId());
						}
						else if(it->second->GetReceiver()->GetName() == "Save")
						{

							if(it->second->GetReceiver()->HaveComponent("HidranteTimerComponent"))
							{
								it->second->GetReceiver()->GetComponent<HidranteTimerComponent>
								("HidranteTimerComponent")->StartAnimation();
							}
							Save::SetCheckPoint(it->second->GetReceiver());
						}
						else if(it->second->GetReceiver()->GetName() == "Hat")
						{
							it->second->GetOwner()->AddComponent(new HatTimerComponent());
							it->second->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->
								SetState(PlayerStateComponent::SPECIAL);
							EntityManager::GetInstance().removeEntity(
							it->second->GetReceiver()->GetId());
							Game::GetInstance().GetCurrentState().StopMusic();
						}
						else if(it->second->GetReceiver()->GetName() == "BossPhase0")
						{
							Game::GetInstance().GetCurrentState().InitBossPhase();
							EntityManager::removeEntity(it->second->GetReceiver()->GetId());
						}
						else if(it->second->GetReceiver()->GetName() == "BossPhase1")
						{
							Game::GetInstance().GetCurrentState().InitBossPhase();
							EntityManager::removeEntity(it->second->GetReceiver()->GetId());
						}
						else if(it->second->GetReceiver()->GetName() == "BossPhase2")
						{
							Game::GetInstance().GetCurrentState().InitBossPhase();
							EntityManager::removeEntity(it->second->GetReceiver()->GetId());
						}
						else if(it->second->GetReceiver()->GetName() ==  "Almofadinha")
						{
							std::cout << "deu ruim" << std::endl;
							it->second->GetReceiver()->GetComponent<AttachableComponent>
							("AttachableComponent")->Attach(it->second->GetOwner());
							std::cout << "oi" << std::endl;
							Game::GetInstance().GetCurrentState().InitBossPhase();
						}
					}
					/*************************************************************
					 *
					 * Colisao com chao
					 *
					 *************************************************************/
					else if (it->second->GetReceiver()->tag == "Ground")
					{
						if (it->second->GetReceiver()->GetName() == "Spike" || it->second->GetReceiver()->GetName() == "Nut")
						{
							Sound* sound = new Sound("audio/sons/dog/quando_o_dog_pisa_num_spike.ogg");
							sound->Play(0);
							it->second->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->
								SetState(PlayerStateComponent::DAMAGED);
						}
						if(it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x <
							it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
						{
							EntityManager::GetInstance().GetEntityById(it->second->GetOwner()->GetId())->
							GetComponent<TransformComponent>("TransformComponent")->
							SetPosition(Rect(
								it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
								GetPosition().x - it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
								GetPosition().w,
								it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
								it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
								it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h)
							);
						}
						if(it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x >
							it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
						{
							EntityManager::GetInstance().GetEntityById(it->second->GetOwner()->GetId())->
									GetComponent<TransformComponent>("TransformComponent")->
							SetPosition(
								Rect(
									it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
									GetPosition().x + it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
									GetPosition().w,
									it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
									it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
									it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h
								)
							);
						}
					}
					/*************************************************************
					 *
					 * Colisao com enemy
					 *
					 *************************************************************/
					else if (it->second->GetReceiver()->tag == "Enemy")
					{
						if(it->second->GetOwner()->GetComponent<PlayerStateComponent>
							("PlayerStateComponent")->GetState() == PlayerStateComponent::SPECIAL)
						{
							if(it->second->GetOwner()->HaveComponent("HealthComponent"))
							{
								it->second->GetReceiver()->GetComponent<HealthComponent>("HealthComponent")
								->ModifyCurrentHealth('-',100);

							}
						}
						else
						{
							it->second->GetOwner()->GetComponent<PlayerStateComponent>
							("PlayerStateComponent")->SetState(PlayerStateComponent::DAMAGED);

							if(it->second->GetReceiver()->GetName() == "Calopsita")
							{
								Sound* sound = new Sound("audio/sons/calopsita/atacando.ogg");
								sound->Play(1);
							}
							if(it->second->GetReceiver()->GetName() == "Crocodilo")
							{
								Sound* sound = new Sound("audio/sons/crocodilo/jacare_ataque_acertou_o_dog.ogg");
								sound->Play(0);
							}

						}
					}
					/*************************************************************
					 *
					 * Colisao com Boss
					 *
					 *************************************************************/
					else if(it->second->GetReceiver()->tag == "Boss")
					{
						if (it->second->GetReceiver()->GetName() == "Ratazana")
						{
							it->second->GetOwner()->GetComponent<PlayerStateComponent>
							("PlayerStateComponent")->SetState(PlayerStateComponent::DAMAGED);
						}
						else if (it->second->GetReceiver()->GetName() == "MinionRatazana")
						{
							it->second->GetOwner()->GetComponent<PlayerStateComponent>
							("PlayerStateComponent")->SetState(PlayerStateComponent::DAMAGED);
						}
					}
					/*************************************************************
					 *
					 * Colisao com Edge
					 *
					 *************************************************************/
					else if(it->second->GetReceiver()->tag == "Edge")
					{
						it->second->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->SetState(PlayerStateComponent::DEAD);
						it->second->GetOwner()->GetComponent<GravityComponent>("GravityComponent")->Disable();
						it->second->GetOwner()->GetComponent<RenderComponent>("RenderComponent")->Disable();
						it->second->GetOwner()->GetComponent<EdgeCooldownComponent>("EdgeCooldownComponent")->Start();
						it->second->GetOwner()->GetComponent<HealthComponent>("HealthComponent")->ModifyCurrentHealth('+',100);
						Sound* sound = new Sound("audio/sons/dog/cachorro_morrendo_porque_caiu_no_abismo.ogg");
						sound->Play(0);
						for (;
							it!=messageMap.end();
							++it)
						{
							MessageManager::RemoveMessage(it->first);
						}
						return;
					}

					/*************************************************************
					 *
					 * Colisao com hanger
					 *
					 *************************************************************/
					else if (it->second->GetReceiver()->tag == "Hanger" && it->second->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() == PlayerStateComponent::FALLING)
					{
						// it->second->GetOwner()->GetComponent<PlayerStateComponent>
							// ("PlayerStateComponent")->SetState(PlayerStateComponent::HANGING);
						it->second->GetOwner()->GetComponent<HangingComponent>("HangingComponent")->SetHanging(true, it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center());
					}



					/*************************************************************
					 *
					 * Colisao com Pushable (GAMBIARRA!!)
					 *
					 *************************************************************/
					else if (it->second->GetReceiver()->tag == "Pushable")
					{
						if (it->second->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() != PlayerStateComponent::JUMPING && it->second->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->GetState() != PlayerStateComponent::FALLING)
						{
							it->second->GetOwner()->GetComponent<PlayerStateComponent>("PlayerStateComponent")->SetState(PlayerStateComponent::PUSHING);
						}
						// EMPURRA PUSHABLE
						if(it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x <
							it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
						{	// Player a esquerda do pushable
							it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
							SetPosition(Rect(
								it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
								GetPosition().x + it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
								GetPosition().w,
								it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
								it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
								it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h)
							);
						}
						else if(it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x >
							it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
						{	// Player a direita do pushable
							it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
							SetPosition(Rect(
								it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
								GetPosition().x - it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
								GetPosition().w,
								it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
								it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
								it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h)
							);
						}

						// CHECA COLISAO PUSHABLE COM GROUND
						for (auto kt = EntityManager::mapEntity["Ground"].begin(); kt != EntityManager::mapEntity["Ground"].end(); ++kt)
						{
							if(IsInside(Rect(Camera::pos.x, Camera::pos.y, 1024, 600), kt->second->GetComponent<TransformComponent>
								("TransformComponent")->GetPosition().Center()))
							{
								if(it->second->GetReceiver()->GetComponent<BoxColliderComponent>("BoxColliderComponent")->IsColliding(
									it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition(),
									kt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition()))
								{
									// COLIDIU, VOLTA POSICAO DO PUSHABLE
									if(it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x <
										kt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
									{	// Pushable a esquerda do ground
										it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
										SetPosition(Rect(
											kt->second->GetComponent<TransformComponent>("TransformComponent")->
											GetPosition().x - it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
											GetPosition().w,
											it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
											it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
											it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h)
										);
									}
									else if(it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x >
										kt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
									{
										it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
										SetPosition(Rect(
											kt->second->GetComponent<TransformComponent>("TransformComponent")->
											GetPosition().x + kt->second->GetComponent<TransformComponent>("TransformComponent")->
											GetPosition().w,
											it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
											it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
											it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h)
										);
									}
									// VOLTA PLAYER
									if(it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x <
										it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
									{	// Player a esquerda do pushable
										it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
										SetPosition(Rect(
											it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
											GetPosition().x - it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
											GetPosition().w,
											it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
											it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
											it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h)
										);
									}
									else if(it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x >
										it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
									{	// Player a direita do pushable
										it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
										SetPosition(Rect(
											it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
											GetPosition().x + it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
											GetPosition().w,
											it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
											it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
											it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h)
										);
									}
									break;
								}
							}
						}

						// CHECA COLISAO COM OUTRO PUSHABLE
						for (auto jt = EntityManager::mapEntity["Pushable"].begin(); jt != EntityManager::mapEntity["Pushable"].end(); ++jt)
						{
							if(jt->second != it->second->GetReceiver()/* && IsInside(Rect(Camera::pos.x, Camera::pos.y, 1024, 600), jt->second->
								GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center())*/)
							{
								if(it->second->GetReceiver()->GetComponent<BoxColliderComponent>("BoxColliderComponent")->
									IsColliding(
										it->second->GetReceiver()->
										GetComponent<TransformComponent>("TransformComponent")->GetPosition(),
										jt->second->
										GetComponent<TransformComponent>("TransformComponent")->GetPosition()
										))
								{
									// COLIDIU, EMPURRA SEGUNDO PUSHABLE
									if(it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x <
										jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
									{	// Pushable a esquerda do segundo pushable
										jt->second->GetComponent<TransformComponent>("TransformComponent")->
										SetPosition(Rect(
											it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
											GetPosition().x + it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
											GetPosition().w,
											jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
											jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
											jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h)
										);
									}
									else if(it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x >
										jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
									{	// Pushable a direita do segundo pushable
										jt->second->GetComponent<TransformComponent>("TransformComponent")->
										SetPosition(Rect(
											it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
											GetPosition().x - jt->second->GetComponent<TransformComponent>("TransformComponent")->
											GetPosition().w,
											jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
											jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
											jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h)
										);
									}


									// CHECA COLISAO SEGUNDO PUSHABLE COM GROUND
									for (auto kt = EntityManager::mapEntity["Ground"].begin(); kt != EntityManager::mapEntity["Ground"].end(); ++kt)
									{
										if(IsInside(Rect(Camera::pos.x, Camera::pos.y, 1024, 600), kt->second->GetComponent<TransformComponent>
											("TransformComponent")->GetPosition().Center()))
										{
											if(jt->second->GetComponent<BoxColliderComponent>("BoxColliderComponent")->IsColliding(
												jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition(),
												kt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition()))
											{
												// COLIDIU, VOLTA POSICAO DO SEGUNDO PUSHABLE
												if(jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x <
													kt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
												{	// Pushable a esquerda do ground
													jt->second->GetComponent<TransformComponent>("TransformComponent")->
													SetPosition(Rect(
														kt->second->GetComponent<TransformComponent>("TransformComponent")->
														GetPosition().x - it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
														GetPosition().w,
														jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
														jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
														jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h)
													);
												}
												else if(jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x >
													kt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
												{
													jt->second->GetComponent<TransformComponent>("TransformComponent")->
													SetPosition(Rect(
														kt->second->GetComponent<TransformComponent>("TransformComponent")->
														GetPosition().x + kt->second->GetComponent<TransformComponent>("TransformComponent")->
														GetPosition().w,
														jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
														jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
														jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h)
													);
												}
												// VOLTA POSICAO DO PRIMEIRO PUSHABLE
												if(it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x <
													jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
												{	// Pushable a esquerda do ground
													it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
													SetPosition(Rect(
														jt->second->GetComponent<TransformComponent>("TransformComponent")->
														GetPosition().x - it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
														GetPosition().w,
														it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
														it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
														it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h)
													);
												}
												else if(it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x >
													jt->second->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
												{
													it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
													SetPosition(Rect(
														jt->second->GetComponent<TransformComponent>("TransformComponent")->
														GetPosition().x + jt->second->GetComponent<TransformComponent>("TransformComponent")->
														GetPosition().w,
														it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
														it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
														it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h)
													);
												}
												// VOLTA PLAYER
												if(it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x <
													it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
												{	// Player a esquerda do pushable
													it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
													SetPosition(Rect(
														it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
														GetPosition().x - it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
														GetPosition().w,
														it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
														it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
														it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h)
													);
												}
												else if(it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x >
													it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().x)
												{	// Player a direita do pushable
													it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->
													SetPosition(Rect(
														it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
														GetPosition().x + it->second->GetReceiver()->GetComponent<TransformComponent>("TransformComponent")->
														GetPosition().w,
														it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().y,
														it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().w,
														it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition().h)
													);
												}
												break;
											}
										}
									}
									break;
								}
							}
						}
					}
					/*************************************************************
					 *
					 * Final da gambiarra
					 *
					 *************************************************************/

					MessageManager::RemoveMessage(it->first);
				}
				/*************************************************************
				 *
				 * Se o dono da mensagem for o inimigo
				 *
				 *************************************************************/
				else if (it->second->GetOwner()->tag == "Enemy")
				{
					if(it->second->GetOwner()->HaveComponent("IA_WalkForwardComponent"))
					{
						EntityManager::GetInstance().removeEntity(it->second->GetOwner()->GetId());
					}

					if(it->second->GetReceiver()->tag == "Prefab")
					{
						if(it->second->GetOwner()->HaveComponent("HealthComponent"))
						{
							it->second->GetOwner()->GetComponent<HealthComponent>("HealthComponent")
									->ModifyCurrentHealth('-',100);
							it->second->GetReceiver()->Delete();
						}
					}
					MessageManager::RemoveMessage(it->first);
				}
				/*************************************************************
				 *
				 * Se o dono da mensagem for o NUT
				 *
				 *************************************************************/
				else if ( it->second->GetOwner()->GetName() == "Nut" && it->second->GetOwner()->tag == "Ground")
				{
					if(it->second->GetReceiver()->GetName() == "Arvore_esquilo" )
					{
						Rect nut;
						nut = it->second->GetOwner()->GetComponent<TransformComponent>("TransformComponent")->GetPosition();

						if(nut.x > (27650) && nut.x < (27800))
						{
							dynamic_cast<Esquilo*>(dynamic_cast<Nut*>(it->second->GetOwner())->boss)->Fall();
						}
					}
					MessageManager::RemoveMessage(it->first);
				}
			}
		}
	}
}

/*************************************************************
 *
 * AddMessage
 *
 *************************************************************/
void MessageManager::AddMessage(Message* message)
{
	messageMap[message->GetId()] = message;
}

/*************************************************************
 *
 * RemoveMessage
 *
 *************************************************************/
void MessageManager::RemoveMessage(int id)
{
	messageMap.erase(messageMap.find(id));
}

/*************************************************************
 *
 * Size
 *
 *************************************************************/
int MessageManager::Size()
{
	return messageMap.size();
}
