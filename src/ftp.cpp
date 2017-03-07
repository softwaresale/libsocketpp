#include <iostream>
#include <fstream>
#include <tar.h> // may come in handy
#include "../header/ftp/ftp.h"
#include "../header/tcp/socket.h"
#include <cstring>

using namespace std;
using namespace tcp;

// a quick little contatanation function
char* cat(char* str1, char* str2){
	char* result = malloc(strlen(str1)+strlen(str2)+1); // create a string
	strcpy(result, str1);
	strcat(result, str2);
	return result;
}

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

char* ftp::Ftp::serialize(FtpFile_t file){

	int titlesize = sizeof(file.title); // get the title's name
	int buffersize = sizeof(file.buffer); // get the buffer's size
	char* data = new char[buffersize + titlesize + 1]; // create a buffer the correct
	                                                   // size
	int i; // counter
	for (i = 0; i < sizeof(title); i++)
		data[i] = file.title[i]; // copy the title into the buffer

	// add a separator. I am using a new line
	data[titlesize + 1] = '\n';
	int j = 0; // temp iterator
	for (i = titlesize+2; i < sizeof(buffersize); i++)
		data[i] = file.buffer[j++]; // copy the buffer into the data

	
	return data; // return the data
}

FtpFile_t ftp::Ftp::readFileStruct(char* data){

	FtpFile_t tmp; // create a temporary file struct
	char ch; // tmp
	int i, j; i = 0; // split up into declaration and initilization. May be useful

	while ((ch = data[i]) != '\n'){
		tmp.title[i] = data[i]; // copy the data
		i++; // iterate
	}

	j = 0;
	while (ch = data[i]){
		tmp.buffer[j++] = data[i];
		i++;
	}

	return tmp; // this may not work at all, but its worth a shot
}

int ftp::Ftp::recvFile(char* dirpath){
	
	if (!this->isConnected())
		return 1; // error enountered

	char* data = this->reads(); // read the file form the socket
	// TODO: do some error handling
	FtpFile_t file = this->readFtpFile(data); // parse the ftp file
	
	this->writeFile(cat(dirpath, file.title), file.buffer); // write the file
	// TODO: make sure this worked
	
	return 0;
}

int ftp::Ftp::sendFile(char* path){

	

}


