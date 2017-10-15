/*
 * FileBase.h
 *
 *  Created on: Jun 5, 2017
 *      Author: user
 */

#ifndef SRC_FILEBASE_H_
#define SRC_FILEBASE_H_

#include <arpa/inet.h>
#include <cstdio>
#include <string>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <netdb.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>




using namespace std;
namespace networkingLab {

class FileBase{
public:

	int socket_fd;

	FileBase();
	virtual ~FileBase();
	virtual int read(char* msg, int len);
	virtual int write(const char* msg, int len);
	virtual void close();

};

} /* namespace networkingLab */

#endif /* SRC_FILEBASE_H_ */
