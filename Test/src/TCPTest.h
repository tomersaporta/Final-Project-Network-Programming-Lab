/*
 * TCPTest.h
 *
 *  Created on: May 2, 2017
 *      Author: user
 */

#ifndef TCPTEST_H_
#define TCPTEST_H_

#include "MThread.h"
#include "TCPSocket.h"
#include <iostream>
#include <string.h>

#define TCPTEST_PORT 4321

namespace networkingLab {

class TCPTest : public MThread {
public:
	TCPTest();
	virtual ~TCPTest();
	bool test();
	void run();
};

} /* namespace networkingLab */

#endif /* TCPTEST_H_ */
