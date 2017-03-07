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
ftp::Ftp::Ftp() : Socket() { }
ftp::Ftp::Ftp(int sockd) : Socket(sockd) {  }

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

void ftp::Ftp::writeFile(char* path, char* data){

	ofstream out;
	out.open(path);
	streampos beg, end;
	
	if (out.is_open()){
	
		beg = out.tellg();
		out.seekg(0, ios::end);
		end = out.tellg();
		int size = end-beg;

		out.write(data, sizeof(data)); // this may not work
		out.close();
	} else { out.close(); return NULL };
}

int ftp::Ftp::recvFile(char* path){
	
	if (!this->isConnected())
		return 1; // error enountered

	char* data = this->reads(); // read the file form the socket

}


