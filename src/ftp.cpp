#include <iostream>
#include <libgen.h>
#include <fstream>
#include <tar.h> // may come in handy
#include "../header/ftp/ftp.h"
#include "../header/tcp/socket.h"
#include <cstring>
#include <cstdlib>

using namespace std;
using namespace tcp;

// a quick little contatanation function
char* cat(char* str1, char* str2){
	char* result = (char*) malloc(strlen(str1)+strlen(str2)+1); // create a string
	strcpy(result, str1);
	strcat(result, str2);
	return result;
}

/* I belive that the problem lies here */

char* ftp::Ftp::readFile(char* path){

	ifstream reader;
	reader.open(path);
	char* buffer;
	int size;

	if (reader.is_open()){
	
		reader.seekg(0, ios::end);
		size = reader.tellg();
		buffer = new char[size];
		reader.read(buffer, size);
		reader.close();
	}
	
	return buffer;
}

void ftp::Ftp::writeFile(char* path, char* data){

	ofstream out;
	out.open(path);
	streampos beg, end;
	
	if (out.is_open()){
		
		out << data; // write data to file

	} else { out.close(); return; };
}

int ftp::Ftp::recvFile(char* dirpath){
	
	if (!Socket::isConnected())
		return 1; // error enountered

	char* title  = this->reads(); // read the title
	char* buffer = this->reads(); // read the buffer
	
	this->writeFile(cat(dirpath, title), buffer); // write the buffer

	return 0;
}

int ftp::Ftp::sendFile(char* path){
	
	// make sure socket is connected
	if (!Socket::isConnected())
		return 1;

	// Send the file's name from the path
	if ( this->sends(basename(path)) != 0 )
		return 1; /* Error sending title */
	
	// read the file and send its contents
	if ( this->sends(this->readFile(path)) != 0)
		return 1; /* Error sending buffer */

	return 0;
}

void ftp::Ftp::closes(){
	Socket::closes(); // call parent close
}
