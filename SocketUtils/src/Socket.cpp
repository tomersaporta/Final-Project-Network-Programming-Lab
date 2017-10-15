/*
 * Socket.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: user
 */

#include "Socket.h"

namespace networkingLab {

Socket::Socket(int type) {
	socket_fd = socket(AF_INET, type, 0);
	if (socket_fd < 0){
		cerr<<"Error opening channel"<<endl;
		close();
	}

}

int Socket::bind(int port){

	bzero(&this->s_local, sizeof(this->s_local));
	this->s_local.sin_family = AF_INET;
	this->s_local.sin_port = htons(port);
	this->s_local.sin_addr.s_addr = htonl(INADDR_ANY);

	if(::bind(socket_fd ,(struct sockaddr*)&this->s_local, sizeof(this->s_local))<0){
		cerr<<"Error naming channel"<<endl;
		close();
		return -1;
	}
	return 1;
}


int Socket::connect(string ip, int port){
	// set the server details
	bzero(&this->s_remote, sizeof(this->s_remote));
	this->s_remote.sin_family = AF_INET;
	this->s_remote.sin_addr.s_addr=inet_addr(ip.c_str());
	this->s_remote.sin_port = htons(port);

	//connect the socket to the server
	if(::connect(socket_fd, (struct sockaddr*)&this->s_remote,sizeof(this->s_remote))<0){
		cerr<<"Error establishing communications"<<endl;
		close();
		return -1;
	}
	return 1;
}


Socket::~Socket() {
	// TODO Auto-generated destructor stub
}


} /* namespace networkingLab */
