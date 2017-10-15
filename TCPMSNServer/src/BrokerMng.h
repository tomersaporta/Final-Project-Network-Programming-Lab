/*
 * BrokerMng.h
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#ifndef SRC_BROKERMNG_H_
#define SRC_BROKERMNG_H_

#include "TCPSocket.h"
#include "Broker.h"
#include "BrokerMngHandler.h"
#include "User.h"

namespace networkingLab {


class BrokerMng {

public:
	BrokerMngHandler* handler;
	BrokerMng(BrokerMngHandler* handler);
	void rleasePeer(TCPSocket* peer,string user_name);
	void createGameBroker(User* user1, User* user2);
	void saveUsersScore(string userName, int userScore);

	virtual ~BrokerMng();
};

} /* namespace networkingLab */

#endif /* SRC_BROKERMNG_H_ */
