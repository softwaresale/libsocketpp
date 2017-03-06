#include <iostream>
#include <fstream>
#include <tar.h> // may come in handy
#include "../header/ftp/ftp.h"
#include "../header/tcp/socket.h"

using namespace std;
using namespace tcp;

// this is the constructor
// note: this will probably be buggy af
ftp::Ftp::Ftp(char* host, int port) : Socket(char* host, int port){ }


char* ftp::Ftp::readFile(char* path){

	ifstream reader;
	reader.open(path);
	char* buffer;
	streampos beg, end;	

	if (reader.is_open()){
	
		beg = reader.tellg();
		reader.seekg(0, ios::end);
		end = reader.tellg();

		int size = end-beg;
	
		buffer = new char[size];

		reader.read(buffer, size);
		reader.close();
	} else { return NULL; }
	
	return buffer;
}
