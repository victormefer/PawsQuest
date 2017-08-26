#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "../entities/Entity.h"

class Message
{
public:
	enum MessageType{COLLISION_DETECTED};
	unsigned int &GetId();
	Entity* GetOwner();
	void SetOwner(Entity*);
	Entity* GetReceiver();
	void SetReceiver(Entity*);
	unsigned int id;
	static unsigned int nextId;
	MessageType type;
	Message(MessageType, Entity*);
	Message(MessageType, Entity*, Entity*);
private:
	Entity *owner, *receiver;
};

#endif
