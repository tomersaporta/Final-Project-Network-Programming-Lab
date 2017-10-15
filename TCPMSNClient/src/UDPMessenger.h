/*
 * UDPMessenger.h
 *
 *  Created on: Apr 5, 2017
 *      Author: user
 */

#ifndef UDPMESSENGER_H_
#define UDPMESSENGER_H_

#include <string>
#include <iostream>
#include "UDPSocket.h"
#include <string.h>
#include "MThread.h"



using namespace std;

namespace networkingLab {

class TCPMSNClientHandler;

class UDPMessenger : public MThread{

private :
	string destIP;
		int destPort;
		UDPSocket * udp_socket;
		bool isRun;
		TCPMSNClientHandler * handler;
public:



	UDPMessenger(int port, string destIP,int destPort,TCPMSNClientHandler * handler);
	virtual ~UDPMessenger();
	void sendTo(string msg);
	void reply(string msg);
	void close();
	void run();
};

} /* namespace networkingLab */

#endif /* UDPMESSENGER_H_ */
