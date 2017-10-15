/*
 * TCPSocket.cpp
 *
 *  Created on: Apr 24, 2017
 *      Author: user
 */

#include "TCPSocket.h"

namespace networkingLab {




TCPSocket::~TCPSocket() {
	// TODO Auto-generated destructor stub
}

TCPSocket::TCPSocket(size_t port) :Socket(SOCK_STREAM){


	socket_fd = socket (AF_INET,SOCK_STREAM ,0);
	if (socket_fd < 0){
			cerr<<"Error opening channel"<<endl;
			close();
	}

	int optval = 1;
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

	bind(port);

}

TCPSocket::TCPSocket(string peerIp, size_t port):Socket(SOCK_STREAM) {

	socket_fd =socket(AF_INET, SOCK_STREAM,0);
	if(socket_fd <0){
		cerr<<"Error opening channel"<<endl;
		close();
	}

	connect(peerIp, port);

}

TCPSocket::TCPSocket(int connected_sock, struct sockaddr_in new_local_addr,	struct sockaddr_in new_remote_addr):Socket(SOCK_STREAM){

	socket_fd = connected_sock;
	s_local = new_local_addr;
	s_remote = new_remote_addr;
}

TCPSocket* TCPSocket::listenAndAccept(){

	 // Listening for Connection Request
	  listen(socket_fd, 1);

	  unsigned int len = sizeof(this->s_remote);
	  // Accepting a connection request
	  int connect_sock = accept(socket_fd, (struct sockaddr *)&s_remote, &len);
	  if (connect_sock<=0){
		  cerr<<"Error accept connection field"<<endl;
		  return NULL;
	  }

	  return new TCPSocket(connect_sock, this->s_local, this->s_remote);
}
string TCPSocket::getRemotedSocketIP() {
	return(string)inet_ntoa(this->s_remote.sin_addr);
}


int TCPSocket::getRemotedSocketPort() {
	return htons(this->s_remote.sin_port);
}


} /* namespace networkingLab */


