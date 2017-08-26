#ifndef MESSAGEMANAGER_H_
#define MESSAGEMANAGER_H_

#include <map>
#include "../messages/Message.h"

class MessageManager
{
public:
	MessageManager();
	static MessageManager& GetInstance();
	static void HandleMessaging();
	static void AddMessage(Message*);
	static void RemoveMessage(int id);
	static int Size();
private:
	static MessageManager* instance;
	static std::map<int,Message*> messageMap;
};

#endif
