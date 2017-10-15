/*
 * FileBase.cpp
 *
 *  Created on: Jun 5, 2017
 *      Author: user
 */

#include "FileBase.h"


namespace networkingLab {

FileBase::FileBase() {
	socket_fd= NULL;

}

FileBase::~FileBase() {
	// TODO Auto-generated destructor stub
}

int FileBase::FileBase::read(char* msg, int len) {
	return ::read(socket_fd, msg, len);
}

int FileBase::FileBase::write(const char* msg, int len) {
	return ::write(socket_fd, msg, len);
}

void FileBase::FileBase::close() {
	//shutdown(socket_fd, SHUT_RDWR);
	::close(socket_fd);
}
} /* namespace networkingLab */

