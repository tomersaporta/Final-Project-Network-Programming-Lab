/*
 * Socket.h
 *
 *  Created on: Jun 3, 2017
 *      Author: user
 */

#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

#include <string.h>
#include <stdlib.h>
#include <iostream>

#include <netdb.h>
#include <netinet/in.h>
#include <iostream>
#include <inttypes.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "FileBase.h"


using namespace std;
namespace networkingLab {

class Socket:public FileBase {

protected:

	struct sockaddr_in s_local;
	struct sockaddr_in s_remote;


public:
	Socket(int type);

	int bind(int port);

	virtual int connect(string ip, int port);

	virtual ~Socket();

};

} /* namespace networkingLab */

#endif /* SRC_SOCKET_H_ */
