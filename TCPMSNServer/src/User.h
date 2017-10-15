/*
 * User.h
 *
 *  Created on: Sep 1, 2017
 *      Author: user
 */

#ifndef SRC_USER_H_
#define SRC_USER_H_


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "TCPSocket.h"

using namespace std;

namespace networkingLab {

class User {
private:
	string name;
	TCPSocket* peer;
public:
	User(TCPSocket* peer, string name);
	string getName();
	TCPSocket* getPeer();
	virtual ~User();
};


} /* namespace networkingLab */

#endif /* SRC_USER_H_ */
