/*
 * FileTest.h
 *
 *  Created on: Jun 5, 2017
 *      Author: user
 */

#ifndef FILETEST_H_
#define FILETEST_H_

#include "MThread.h"
#include "FileBase.h"
#include "File.h"




namespace networkingLab {

class FileTest:MThread {

public:
	FileTest();
	virtual ~FileTest();
	bool test();
	void run();

};

} /* namespace networkingLab */

#endif /* FILETEST_H_ */
