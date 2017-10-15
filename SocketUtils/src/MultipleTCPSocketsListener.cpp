

#include "MultipleTCPSocketsListener.h"

using namespace std;


namespace networkingLab{

/*
 * Add the given socket to the socket list to be listen on
 */
void MultipleTCPSocketsListener::addSocket(TCPSocket* socket){

	vector<TCPSocket*>::iterator iterator;
	iterator = this->sockets.begin();
	this->sockets.insert(iterator,socket);

	//??
	//this->sockets.push_back(socket);

}

/*
 * Set the given sockets to the socket list to be listen on
 */
void MultipleTCPSocketsListener::addSockets(vector<TCPSocket*> socketVec){
	//TODO: set the given sockets as the socket list to select from
	vector<TCPSocket*>::iterator iterator , newBegin, newEnd;
	iterator= this->sockets.begin();
	newBegin = socketVec.begin();
	newEnd = socketVec.end();
	this->sockets.insert(iterator, newBegin,newEnd);

	//??
	//this->sockets = socketVec;
	//??
	//this->sockets.swap(socketVec);
}

/*
 * This method checks to see if any of the previous given sockets are ready for reading
 * It returns one of the Sockets that are ready.
 */
TCPSocket* MultipleTCPSocketsListener::listenToSocket(){

	//create local set for the select function (fd_set)
	//struct timeval tv;
	socketVector::iterator begin, end;
	begin = this->sockets.begin();
	end = this->sockets.end();

	fd_set fds;
	int  highestFile=0;

	//Clear all entries from the set.
	FD_ZERO(&fds);

	//fill the set with file descriptors from the socket list using (FD_SET macro)
	while ( begin != end){
		if((*begin)->socket_fd > highestFile){
			//find the highest sock_fd in the TCPSocket vector
			highestFile = (*begin)->socket_fd;
		}
		//Add fd to the set
		FD_SET((*begin)->socket_fd , &fds);
		begin++;
	}

	//perform the select  don't care about writefds, exceptfds and timeout
	int returned = select(highestFile +1 ,&fds,NULL,NULL, NULL);

	//check the returned value from the select to find the socket that is ready
	if (returned !=0){
		//return the iterator to beginning
		begin = sockets.begin();
		//if select return a valid socket return the matching TCPSocket object otherwise return NULL
		while (begin != end){
			if (FD_ISSET((*begin)->socket_fd,&fds)){
				return (*begin);
			}
			begin++;
		}
	}

	return NULL;
}
int MultipleTCPSocketsListener::removeSocket(TCPSocket* socket) {
	int sock_fd = socket->socket_fd;
	socketVector::iterator begin = sockets.begin();
	for (; begin != this->sockets.end(); begin++) {
		TCPSocket* sock = *begin;
		int temp_fd = sock->socket_fd;
		if (temp_fd == sock_fd) {
			sockets.erase(begin);
			return 1;
		}

	}
	return -1;

}

TCPSocket* MultipleTCPSocketsListener::searchSocket(int port, string ip) {
	socketVector::iterator begin = sockets.begin();
		for (; begin != this->sockets.end(); begin++) {
			TCPSocket* sock = *begin;
			if (ip.compare(sock->getRemotedSocketIP())==0 && port == sock->getRemotedSocketPort())
				return sock;
		}
		return NULL;
}
string MultipleTCPSocketsListener::getPeerList() {
	string list;
	char buffer[10];
	socketVector::iterator begin = sockets.begin();
			for (; begin != this->sockets.end(); begin++) {
				TCPSocket* sock = *begin;
				list+=sock->getRemotedSocketIP();
				sprintf(buffer, ":%d",sock->getRemotedSocketPort());
				list+=buffer;
				list+="\n";
			}
			return list;
	}

} /* namespace networkingLab */


