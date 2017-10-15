/*
 * FileInterface.cpp
 *
 *  Created on: Jun 5, 2017
 *      Author: user
 */

#include "FileInterface.h"

namespace networkingLab {

FileInterface::FileInterface() {
	// TODO Auto-generated constructor stub

}


FileInterface::~FileInterface() {
	// TODO Auto-generated destructor stub
}

int networkingLab::FileInterface::read(char* msg, int len) {
	return ::read(socket_fd, msg, len);
}

int networkingLab::FileInterface::write(const char* msg, int len) {
	return ::write(socket_fd, msg, len);
}

void networkingLab::FileInterface::close() {
	shutdown(socket_fd, SHUT_RDWR);
	::close(socket_fd);
}
} /* namespace networkingLab */
