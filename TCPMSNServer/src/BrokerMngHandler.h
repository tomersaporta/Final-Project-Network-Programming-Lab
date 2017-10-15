/*
 * BrokerMngHandler.h
 *
 *  Created on: Jul 7, 2017
 *      Author: user
 */

#ifndef SRC_BROKERMNGHANDLER_H_
#define SRC_BROKERMNGHANDLER_H_

namespace networkingLab {

class BrokerMngHandler{
public:
	virtual void handleReturnedPeer(TCPSocket* peer,string userName)=0;
	virtual void addToHighScore(string userName, int userScore)=0;
	virtual void removePeer(TCPSocket* peer)=0;
	virtual ~BrokerMngHandler(){};
};


} /* namespace networkingLab */

#endif /* SRC_BROKERMNGHANDLER_H_ */
