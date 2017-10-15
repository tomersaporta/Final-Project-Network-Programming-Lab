/*
 * UDPSocket.cpp
 *
 *  Created on: Apr 3, 2017
 *      Author: user
 */

#include "UDPSocket.h"


using namespace std;


namespace networkingLab {


networkingLab::UDPSocket::UDPSocket(int port):Socket(SOCK_DGRAM) {
	this->port=0;
	this->ip="";
	if(port!=9999)
		bind(port);
}
UDPSocket::~UDPSocket()
{
	// TODO Auto-generated destructor stub
}


/**
 * 	- reply to an incoming message,
 * 	this method will send the given message as a UDP
 * 	message to the peer from which the last message was received.
 *
 */

int UDPSocket::reply(string msg){
	int rec;
	bzero((char *) &s_remote, sizeof(s_remote));
	s_remote.sin_family = AF_INET;
	s_remote.sin_addr.s_addr = inet_addr(this->ip.data());
	s_remote.sin_port = htons(this->port);
	socklen_t fromSize = sizeof(s_remote);
	//rec=::write(msg, msg.length());
	rec = sendto(socket_fd, msg.data() ,msg.length(), 0,(struct sockaddr *)&s_remote, fromSize);
	if (rec <0)
		perror("Error reply ");
return rec;
	}

int networkingLab::UDPSocket::read(char* buffer, int length) {

	int n=Socket::read(buffer, length);
	this->ip=inet_ntoa(this->s_remote.sin_addr);
	this->port=ntohs(s_remote.sin_port);

	return n;
}

string networkingLab::UDPSocket::fromAddr(){
	return inet_ntoa(this->s_remote.sin_addr);
}

} /* namespace networkingLab */

