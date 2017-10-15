/*
 * Server.h
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#ifndef SRC_SERVER_H_
#define SRC_SERVER_H_
#include "TCPSocket.h"
#include "ServerHandler.h"
#include "MThread.h"
namespace networkingLab {

class Server: public MThread {

private:
	int port;
	bool stop;
	ServerHandler* handler;
	TCPSocket * serverSocket;

public:
	Server(int port, ServerHandler* handler);
	void run();
	void startServer();
	void close();
	virtual ~Server();
};

} /* namespace networkingLab */

#endif /* SRC_SERVER_H_ */
