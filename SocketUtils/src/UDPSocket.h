/*
 * UDPSocket.h
 *
 *  Created on: Apr 3, 2017
 *      Author: user
 */

#ifndef SRC_UDPSOCKET_H_
#define SRC_UDPSOCKET_H_
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include <netdb.h>
#include <netinet/in.h>
#include <iostream>
#include "Socket.h"
using namespace std;


using namespace std;
namespace networkingLab
{

class UDPSocket:public Socket
{
private:
	string ip;
	int port;

public:
	virtual ~UDPSocket();
	/**
	 * initialize a UDP socket and binds it on the given port. if no
	port is specified a default port 9999 is set. This UDP socket can be used both for
	server socket and client socket
	 */

	UDPSocket(int port = 9999);

	/**
	 *  - reads an incoming message from the UDP
	socket. the message is copied into the given buffer up to the specified length.
	*/

	int read(char* buffer, int length);


	/**
	 *  - reply to an incoming message, this method will send the
	given message as a UDP message to the peer from which the last message was
	received.
	 */

	int reply(string msg);

	/**
	 * return the sender IP of the last received message.
	 */

	string fromAddr();

};

} /* namespace networkingLab */

#endif /* SRC_UDPSOCKET_H_ */
