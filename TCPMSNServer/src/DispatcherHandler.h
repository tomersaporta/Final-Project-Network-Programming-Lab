/*
 * DispatcherHandler.h
 *
 *  Created on: Jul 7, 2017
 *      Author: user
 */

#ifndef SRC_DISPATCHERHANDLER_H_
#define SRC_DISPATCHERHANDLER_H_
#include "TCPSocket.h"
#include "User.h"

namespace networkingLab {

class DispatcherHandler {
public:
	virtual void manageGameSession(User* user1, User* user2)=0;
	virtual string getName(string ip)=0;
	virtual string getIP(string name)=0;
	virtual string getRandomName()=0;
	virtual string getNames()=0;
	virtual string getHighScoreList()=0;
	virtual void removeUserFromMap(string ipPort,string name)=0;


	virtual ~DispatcherHandler() {
	}
	;

};

} /* namespace networkingLab */

#endif /* SRC_DISPATCHERHANDLER_H_ */
