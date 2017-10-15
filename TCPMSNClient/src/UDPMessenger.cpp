//============================================================================
// Name        : UDPMessenger.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "UDPMessenger.h"
#include "TCPMSNClient.h"
using namespace std;


namespace networkingLab {

networkingLab::UDPMessenger::UDPMessenger(int port, string destIP,int destPort,TCPMSNClientHandler * handler) {
	this->udp_socket = new UDPSocket(port);
	isRun=true;
	this->destIP = destIP;
	this->destPort = destPort;
	this->handler=handler;
	this->start();
}

void networkingLab::UDPMessenger::sendTo(string msg) {
	this->udp_socket->connect(this->destIP, this->destPort);
	int length = htonl(msg.length());
	udp_socket->write((char*) &length, 4);
	udp_socket->write(msg.data(), msg.length());

}

UDPMessenger::~UDPMessenger() {
	this->isRun = false;
	this->udp_socket->close();
}

void UDPMessenger::reply(string msg){
	cout<<"reply"<<endl;
	udp_socket->reply(msg);

}

void UDPMessenger::close(){
	isRun=false;
	//close socket
	cout<<"close"<<endl;
	udp_socket->close();
	this->waitForThread();
	delete udp_socket;

}
void UDPMessenger::run(){



	while(isRun){
		int rec;
		int len;
		udp_socket->read((char *) &len, sizeof(len));
		len = ntohl(len);
		char*buffer = new char[len];
		rec = udp_socket->read(buffer, len);
		if(rec<0)
			break;


		string msg (buffer);



		this->handler->onRecvMsg(buffer);


	}

}

} /* namespace networkingLab */

