/*
 * UDPTest.h
 *
 *  Created on: May 2, 2017
 *      Author: user
 */

#ifndef UDPTEST_H_
#define UDPTEST_H_

#include <iostream>
#include "UDPSocket.h"
#include <string.h>

using namespace std;
namespace networkingLab {

class UDPTest{

public:
	UDPTest();
	virtual ~UDPTest();

	bool test();
};
} /* namespace networkingLab */

#endif /* UDPTEST_H_ */
