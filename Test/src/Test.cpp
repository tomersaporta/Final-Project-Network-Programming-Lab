/*
 * Test.cpp
 *
 *  Created on: May 2, 2017
 *      Author: user
 */


#include <iostream>
#include "UDPTest.h"
#include "TCPTest.h"
#include "MultipleTCPSocketsListenerTester.h"
#include "FileTest.h"
using namespace std;
using namespace networkingLab;

int main() {
	cout << "!!!Hello Testing !!!" << endl; // prints !!!Hello World!!!
// UDP Test
	UDPTest * testUDP = new UDPTest();
	bool res1 = testUDP->test();
	if (res1==true){
		cout<<"\n***TEST UDP PASS***\n"<<endl;
	}else{
		cout <<"TEST UDP FAIL!!!"<<endl;
	}


//TCP Test
	TCPTest *testTCP = new TCPTest();
	bool res2 = testTCP->test();
	if (res2 == true){
		cout<<"\n***TEST TCP PASS***\n"<<endl;
	}else{
		cout <<"TEST TCP FAIL!!!"<<endl;
	}


//MultipleTCPSocketsListener Test

	MultipleTCPSocketsListenerTester *multiTCPSocketTest = new MultipleTCPSocketsListenerTester();
	if(multiTCPSocketTest->test()){
		cout<<"\n***Multiple TCP Sockets Listener Tester PASS\***\n"<<endl;
	}
	else{
		cout<<"Multiple TCP Sockets Listener Tester FAIL!!!"<<endl;
	}

//File Test

	FileTest * fileTest = new FileTest();
	if(fileTest->test()){

		cout<<"\n***File Tester PASS\***\n"<<endl;
		}
		else{
			cout<<"File Tester FAIL!!!"<<endl;
		}

	return 0;
}
