#include <iostream>
#include <libgen.h>
#include <fstream>
#include <tar.h> // may come in handy
#include "../header/ftp/ftp.h"
#include "../header/tcp/socket.h"
#include <cstring>
#include <cstdlib>
#include <vector>

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
		reader.seekg(0, ios::beg);

		string line;
		while (getline(reader, line)){
			char* cline = (char*)line.c_str();
			cout << line << endl;
			cat(buffer, cline); // cat the two strings
		}
		
		reader.close();

	} else {
		cerr << "File is not open" << endl;
		return NULL;
	}
	
	buffer[size+1] = '\0'; // null terminator

	// debugging purposes
	cout << "Buffer: " << buffer << endl;

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
	char* title = basename(path);
	cout << "Title: " << title << endl;
	
	// read the file and send its contents
	cout << "Path: " << path << endl;
	char* buffer = this->readFile(path);
	cout << "Buffer: " << buffer << endl;

	if ( this->sends(title) != 0)
		return 1;

	if ( this->sends(buffer) != 0)
		return 1;

	return 0;
}

void ftp::Ftp::closes(){
	Socket::closes(); // call parent close
}
