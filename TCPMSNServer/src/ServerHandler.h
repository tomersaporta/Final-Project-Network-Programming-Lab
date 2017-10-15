/*
 * ServerHandler.h
 *
 *  Created on: Jul 7, 2017
 *      Author: user
 */

#ifndef SRC_SERVERHANDLER_H_
#define SRC_SERVERHANDLER_H_
#include "TCPSocket.h"

namespace networkingLab {

class ServerHandler{
public:
	virtual void handleConnectedPeer(TCPSocket* peer)=0;
	virtual ~ServerHandler(){};
};

} /* namespace networkingLab */

#endif /* SRC_SERVERHANDLER_H_ */
