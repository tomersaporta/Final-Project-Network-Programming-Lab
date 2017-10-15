//============================================================================
// Name        : TCPMSNServerTest.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "TCPMSNServer.h"

using namespace networkingLab;
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	TCPMSNServer* s=new TCPMSNServer();
	s->startMSNServer();

	sleep(50);

	return 0;
}
