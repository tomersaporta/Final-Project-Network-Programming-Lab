/*
 * FileTest.cpp
 *
 *  Created on: Jun 5, 2017
 *      Author: user
 */

#include "FileTest.h"

namespace networkingLab {

FileTest::FileTest() {
	// TODO Auto-generated constructor stub

}

FileTest::~FileTest() {
	// TODO Auto-generated destructor stub
}

bool FileTest::test() {

	string path = "MyFileTest6.txt";
	//int mode =1;
	File *file = new File(path, O_RDWR| O_CREAT);

	string msg ="Hello Tomer Test6!!";
	//char msg[100] = "Hello Tomer Test3";
	char buff[100];
	file->write(msg.data(), sizeof(msg));
	cout << "write to file path: " << path << " : " << msg << endl;
	file->close();

	File *file2 = new File(path, O_RDONLY);
	file2->read(buff, sizeof(buff));
	file2->close();
	cout << "read from file path: " << path << " : " << buff << endl;
	if (strcmp(msg.c_str(), buff) == 0) {
		return true;
	}
	return false;

}

void FileTest::run() {

}

} /* namespace networkingLab */
