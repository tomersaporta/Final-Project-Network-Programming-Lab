//============================================================================
// Name        : TCPMSNTest.cpp
// Author      : Tomer Saporta
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "SDKTest.h"

using namespace networkingLab;
using namespace std;

int main() {
	cout << "!!!TCPMSNClientTest!!!" << endl;
	TCPMSNClientTest TCPMSNtest;
	bool test = false;
	test = TCPMSNtest.test();
	if(test){
		cout<<"\n***Game Test PASS***\n"<<endl;
	}
	else {
		cout<<"Game Test Failed!!!!"<<endl;
	}
	return 0;
}
