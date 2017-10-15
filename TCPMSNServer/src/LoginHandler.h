/*
 * LoginHandler.h
 *
 *  Created on: Aug 27, 2017
 *      Author: user
 */

#ifndef SRC_LOGINHANDLER_H_
#define SRC_LOGINHANDLER_H_

#include "TCPSocket.h"

namespace networkingLab {

class LoginHandler {
public:


	virtual void handleLoginPeer(TCPSocket * peer, string user_name)=0;
	virtual ~LoginHandler(){};
};

}/* namespace networkingLab */

#endif /* SRC_LOGINHANDLER_H_ */
