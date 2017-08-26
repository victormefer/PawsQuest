#include "Entity.h"
#include  "../managers/MessageManager.h"

unsigned int Entity::nextId = 0;

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
Entity::Entity()
{
	id = nextId;
	nextId++;
	this->name = "default_name";
	this->tag = "default_tag";
	this->toDelete = false;
}

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
Entity::Entity(std::string name)
{
	this->name = name;
	this->tag = "default_tag";
	this->id = nextId;
	nextId++;
	this->toDelete = false;
}

/*************************************************************
 *
 * Destrutor
 *
 *************************************************************/
Entity::~Entity()
{

}

/*************************************************************
 *
 * GetId
 *
 *************************************************************/
unsigned int& Entity::GetId()
{
	return id;
}

/*************************************************************
 *
 * GetName
 *
 *************************************************************/
std::string Entity::GetName()
{
	return name;
}

/*************************************************************
 *
 * Update percorre todos os componentes da entidade e da update
 *
 *************************************************************/
void Entity::Update(float dt)
{
	for (std::map<std::string,Component*>::iterator it=mapComponents.begin(); it!=mapComponents.end(); ++it)
	{
		it->second->Update(dt);
	}
}

/*************************************************************
 *
 * AddComponent
 *
 *************************************************************/
void Entity::AddComponent(Component* component)
{
	component->SetOwner(this);
	mapComponents[component->GetName()] = component;
}

/*************************************************************
 *
 * RemoveComponent
 *
 *************************************************************/
void Entity::RemoveComponent(std::string name)
{
	mapComponents.erase(mapComponents.find(name));
}

/*************************************************************
 *
 * SendMessage envia uma mensagem que tem o owner e o receiver
 *
 *************************************************************/
void Entity::SendMessage(Message* message)
{
	MessageManager::GetInstance().AddMessage(message);
}

/*************************************************************
 *
 * HaveComponent
 *
 *************************************************************/
bool Entity::HaveComponent(std::string componentName)
{

	for (std::map<std::string,Component*>::iterator it=mapComponents.begin(); it!=mapComponents.end(); ++it)
	{
		if(componentName == it->first)
		{
			return true;
		}
	}
	return false;
}

/*************************************************************
 *
 * SetTag
 *
 *************************************************************/
void Entity::SetTag(std::string tag)
{
	this->tag = tag;
}

/*************************************************************
 *
 * Delete
 *
 *************************************************************/
void Entity::Delete()
{
	this->toDelete = true;
}

