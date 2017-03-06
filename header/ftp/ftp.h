#ifndef FTP_H
#define FTP_H 1

#include <iostream>
#include <fstream>
#include "../tcp/socket"

using namespace std;
using namespace tcp;

/* @author Charlie Sale
 * This file is a collection of classes that
 * are built off of the TCP socket system
 * earlier written to handle file transfer (FTP) .*/

namespace ftp
{

class Ftp: public Socket {

	/* This class inherits the Socket class to use its
	 * basic network functionality */

private:
	// some file handleing methods

	/* Reads a file and returns the contents
	 * @param path -- path to file */
	char* readFile(char* path);
	
	/* Writes a file
	 * @param path -- path to file
	 * @param data -- data to be written to file */
	void  writeFile(char* path, char* data);

protected:

public:
	// call the Socket's constructor
	Ftp(char* host, int port) : Socket(char* host, int port) { }
	
	/* This class should use all of the Socket functions */

	/* Write a file 
	 * @param path -- file path */
	void sendFile(char* path);
	
	/* Downloading a file to path
	 * @param path -- download file path */
	void recvFile(char* path);
};

}


#endif // FTP_H
