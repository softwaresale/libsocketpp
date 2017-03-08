#ifndef FTP_H
#define FTP_H 1

#include <iostream>
#include <fstream>
#include "../tcp/socket.h"

using namespace std;
using namespace tcp;

/* @author Charlie Sale
 * This file is a collection of classes that
 * are built off of the TCP socket system
 * earlier written to handle file transfer (FTP) .*/

/* This struct contains data about a file
 * Note: This struct has to be sterilized to
 *       be written over a socket */

typedef struct {

	char* title;   // title of file
	char* buffer;  // file buffer

} FtpFile_t;

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
	
	/* Sterilizes a file struct
	 * @param file -- file structure to be parsed
	 * @return     -- returns an integer containing
	 *                all of the struct's data */
	char*   serialize(FtpFile_t file);
	
	/* Calls the readint() to read an integer and
	 *     create a struct
	 * @param data -- data to be parsed into a struct
	 * @return     -- instantiated FtpFile_t struct */
	FtpFile_t readFileStruct(char* data);

protected:

public:
	// call the Socket's constructors
	Ftp(char* host, int port) : Socket(host, port) { }
	Ftp() : Socket() { }
	Ftp(int sockd) : Socket(sockd) { }

	/* This class should use all of the Socket functions */

	/* Write a file 
	 * @param path -- file path */
	int sendFile(char* path);
	
	/* Downloading a file to path
	 * @param dirpath -- download directory path */
	int recvFile(char* dirpath);
	
	/* Closes the ftp connection */
	void closes();
};

}


#endif // FTP_H
