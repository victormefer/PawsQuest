#include "Message.h"

unsigned int Message::nextId = 0;

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
Message::Message(MessageType type,Entity* entity)
{
	Message::SetOwner(entity);
	this->id = nextId;
	nextId++;
	this->type = type;
}

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
Message::Message(MessageType type, Entity* entity, Entity* entity2)
{
	Message::SetOwner(entity);
	Message::SetReceiver(entity2);
	this->id = nextId;
	nextId++;
	this->type = type;
}

/*************************************************************
 *
 * GetId
 *
 *************************************************************/
unsigned int& Message::GetId()
{
	return id;
}

/*************************************************************
 *
 * GetOwner
 *
 *************************************************************/
Entity* Message::GetOwner()
{
	return owner;
}

/*************************************************************
 *
 * SetOwner
 *
 *************************************************************/
void Message::SetOwner(Entity* e)
{
	this->owner = e;
}

/*************************************************************
 *
 * GetReceiver
 *
 *************************************************************/
Entity* Message::GetReceiver()
{
	return receiver;
}

/*************************************************************
 *
 * SetReceiver
 *
 *************************************************************/
void Message::SetReceiver(Entity* e)
{
	this->receiver = e;
}
