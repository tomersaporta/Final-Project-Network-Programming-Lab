/*
 * MultipleTCPSocketsListenerTester.h
 *
 *  Created on: May 22, 2017
 *      Author: Tomer Saporta
 */

#ifndef MULTIPLETCPSOCKETSLISTENERTESTER_H_
#define MULTIPLETCPSOCKETSLISTENERTESTER_H_
#include "MultipleTCPSocketsListener.h"
#include "MThread.h"
#include "Socket.h"
#include "TCPSocket.h"

#define MTCPSL_PORT 6667

// the number of open sockets to test simultaneously
#define TEST_SIZE 10

/**
 * This is a multiple TCP sockets server
 * it opens TEST_SIZE TCP server sockets, wait for incoming connection on all of them,
 * once there is an incoming connection it perform the following:
 * 	1. connects to it
 * 	2. read the received message
 * 	3. validate the the message is correct (equal to the global message var)
 * 	4. send a new message (also update the global message var so the client will be able to verify it)
 * 	5. close the session socket
 * 	6. wait for the next connection (do this loop TEST_SIZE times after that terminate the server)
 */



namespace networkingLab {

class MultipleTCPSocketsListenerTester :MThread {

	string message; // the message sent
	bool testFail;  // flag that mark if the test pass or not

	vector<TCPSocket*> serverSockets; // vector to hold all the sockets

private :
	void createClientAndSendRecvMsg(int port);
public:
	MultipleTCPSocketsListenerTester();
	virtual ~MultipleTCPSocketsListenerTester();
	void run();
	bool test();
};

} /* namespace networkingLab */

#endif /* MULTIPLETCPSOCKETSLISTENERTESTER_H_ */
