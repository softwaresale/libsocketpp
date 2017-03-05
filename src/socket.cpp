#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include "../header/socket"

using namespace std;

tcp::Socket::Socket(){

	socketfd = socket(AF_INET, SOCK_STREAM, 0); // creates the new socket
	if (socketfd < 0){
		cerr << "Error creating socket" << endl;
		return;
	}

}

tcp::Socket::Socket(char* _host, int _port){

	host = _host; // sets the class host variable
	port = _port; // sets the class port variable


	socketfd = socket(AF_INET, SOCK_STREAM, 0); // creates the new socket
	if (socketfd < 0){
		cerr << "Error creating socket" << endl;
		return;
	}

}

tcp::Socket::Socket(int sockd){
	socketfd = sockd; // sets the socket descriptor
}

int tcp::Socket::connects(char* _host, int _port){

	addr.sin_family      = AF_INET;         // sets the address's family
	addr.sin_port        = htons(_port);     // sets the address's port
	addr.sin_addr.s_addr = inet_addr(_host); // sets the address's host

	if ( connect(socketfd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
		cerr << "Error connecting to server" << endl;
		return 1;
	}
	return 0;
}

int tcp::Socket::connects(){

	if (host == NULL || port == 0){

		cerr << "Error: host or port not set. Use 'connect(host, port)' instead" << endl;
		return 1;

	}

	addr.sin_family      = AF_INET;          // sets the address's family
	addr.sin_port        = htons(port);      // sets the address's port
	addr.sin_addr.s_addr = inet_addr(host);  // sets the address's host

	if ( connect(socketfd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
		cerr << "Error connecting to host" << endl;
		return 1;
	}

	return 0;
}

int tcp::Socket::sends(char* buffer){

	int bytes;

	/* First, send the size of buffer */
	int datalen = strlen(buffer); // get sizeof buffer
	int len     = htonl(datalen); // reformat

	bytes = send(socketfd, (char*)&len, sizeof(len), 0); // send the size
	if (bytes < 0){
		cerr << "Error sending size of buffer to socket" << endl;
		return 1;
	}

	/* Now acutally send the data */

	bytes = send(socketfd, buffer, datalen, 0);
	if (bytes < 0){
		cerr << "Error writing buffer to socket" << endl;
		return 1;
	}

	cout << bytes << " written" << endl;

	return 0;

}

int tcp::Socket::sends(int ii){

	int bytes;

	char* in = (char*)&ii;

	/* First, send the size of buffer */
	int datalen = strlen(in);     // get sizeof buffer
	int len     = htonl(datalen); // reformat

	bytes = send(socketfd, (char*)&len, sizeof(len), 0); // send the size
	if (bytes < 0){
		cerr << "Error sending size of buffer to socket" << endl;
		return 1;
	}

	/* Now acutally send the data */

	bytes = send(socketfd, in, datalen, 0);
	if (bytes < 0){
		cerr << "Error writing buffer to socket" << endl;
		return 1;
	}

	return 0;
}

char* tcp::Socket::reads(){

	char* buffer;
	int bytes, buflen;

	/* Read the incoming size */
	bytes = recv(socketfd, (char*)&buflen, sizeof(buflen), 0);
	if (bytes < 0){
		cerr << "Error reading size of data" << endl;
		return NULL;
	}
	buflen = ntohl(buflen);

	buffer = new char[buflen+1]; // create a buffer for reading with room for null terminator

	/* Read the data */

	bytes = recv(socketfd, buffer, buflen, 0);
	if (bytes < 0){
		cerr << "Error reading data" << endl;
		return NULL;
	}

	buffer[buflen] = '\0'; // set the null terminator

	return buffer;
}

int tcp::Socket::readint(){

	char* buffer;
	int   bytes, buflen;

	/* Read the incoming size */
	bytes = recv(socketfd, (char*)&buflen, sizeof(buflen), 0);
	if (bytes < 0){
		cerr << "Error reading size of data" << endl;
		return -1;
	}
	buflen = ntohl(buflen);

	buffer = new char[buflen+1]; // create a buffer for reading with room for null terminator

	/* Read the data */

	bytes = recv(socketfd, buffer, buflen, 0);
	if (bytes < 0){
		cerr << "Error reading data" << endl;
		return -1;
	}

	buffer[buflen] = '\0'; // set the null terminator

	int num = atoi(buffer);

	return num;
}

void tcp::Socket::closes(){
	close(socketfd);
}
