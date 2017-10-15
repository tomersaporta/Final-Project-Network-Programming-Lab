/*
 * User.cpp
 *
 *  Created on: Sep 1, 2017
 *      Author: user
 */

#include "User.h"

namespace networkingLab {


User::User(TCPSocket *peer, string name) {
	this->peer = peer;
	this->name=name;

}
string User::getName(){
	return name;
}
TCPSocket* User:: getPeer(){
	return peer;
}

User::~User() {
	// TODO Auto-generated destructor stub
}


} /* namespace networkingLab */
