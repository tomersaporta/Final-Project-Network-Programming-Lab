/*
 * File.cpp
 *
 *  Created on: Jun 5, 2017
 *      Author: user
 */

#include "File.h"


namespace networkingLab {

File::File(string path, int mode) {

	socket_fd = open(path.data(),mode);

}

File::~File() {
	// TODO Auto-generated destructor stub
}

//int File::read(char* msg, int len) {
//
//	   pFile = fopen (path.data(), "r");
//	   if (pFile == NULL){
//		   perror ("Error opening file");
//		   return -1;
//	   }
//	   else
//	   {
//	     while ( ! feof (pFile) )
//	     {
//	       if ( fgets (msg , len , pFile) == NULL )
//	    	   break;
//	       //fputs (buffer , stdout);
//	     }
//	     fclose (pFile);
//	   }
//	   return 1;
//}
//
//int File::write(const char* msg, int len) {
//
//	  pFile = fopen (path.data(),"w");
//	  if (pFile!=NULL)
//	  {
//	    fputs (msg,pFile);
//	    fclose (pFile);
//	    return 1;
//	  }
//	  return -1;
//}
//
//void File::close() {
//}

} /* namespace networkingLab */
