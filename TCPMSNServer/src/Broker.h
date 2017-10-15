/*
 * Broker.h
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#ifndef SRC_BROKER_H_
#define SRC_BROKER_H_
#include "TCPSocket.h"
#include "MThread.h"
#include "BrokerMng.h"
#include "MultipleTCPSocketsListener.h"
#include "User.h"
#include <sstream>
#include <iostream>
#include "ServerProtocol.h"

namespace networkingLab {

class BrokerMng;

class Broker: public MThread {
private:
	BrokerMng* parent;

	User* user1;
	User* user2;
	MultipleTCPSocketsListener * tcpListen;
	bool stop;
	int sendCommand(TCPSocket* destPeer,int cmd, const char* buff);
	void openSessionCommand();

public:

	Broker(User* user1, User* user2, BrokerMng* parent);
	Broker(TCPSocket* peer1, TCPSocket* peer2, BrokerMng* parent);
	void run();
	void handlePeer(TCPSocket* peer);
	string getIpPort(TCPSocket* peer);
	string getPort(string ipPort);
	void sendUsersIpPort();
	virtual ~Broker();

};

} /* namespace networkingLab */

#endif /* SRC_BROKER_H_ */
