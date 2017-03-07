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
#include "../header/tcp/socket.h"
#include "../header/tcp/server.h"

using namespace std;

tcp::Server::Server(){

	// creates the server socket
	server = socket(AF_INET, SOCK_STREAM, 0);
	if (server < 0){
		cerr << "Error creating listening socket" << endl;
	}

}

tcp::Server::Server(int _port){

	// creates the socket
	server = socket(AF_INET, SOCK_STREAM, 0);
	if (server < 0){
		cerr << "Error creating listening socket" << endl;
	}

	// sets local variables
	port = _port;
}

int tcp::Server::binds(){

	if (isBound){
		cerr << "Server already bound" << endl;
		return 1;
	} else {
		cerr << "Host and port not set: use other bind func" << endl;
		return 1;
	}

	// set up the address
	addr.sin_family      = AF_INET;
	addr.sin_port        = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ( bind(server, (struct sockaddr*)&addr, sizeof(addr)) < 0 ){
		cerr << "Error listening socket" << endl;
		return 1;
	}

	return 0;
}

int tcp::Server::binds(int _port){

	if (isBound){
		cerr << "Server already bound" << endl;
		return 1;
	}

	// set up the address
	addr.sin_family      = AF_INET;
	addr.sin_port        = htons(_port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ( bind(server, (struct sockaddr*)&addr, sizeof(addr)) < 0 ){
		cerr << "Error listening socket" << endl;
		return 1;
	}

	return 0;
}

tcp::Socket* tcp::Server::accepts(){

	listen(server, 10); // sets the server to listen
	conn = accept(server, (struct sockaddr*)NULL, NULL);
	if (conn < 0){
		cerr << "Error accepting connection" << endl;
		return nullptr;
	}

	tcp::Socket* temp = new tcp::Socket(conn);

	return temp;

}

int tcp::Server::acceptfd(){

	listen(server, 10); // sets the server to listen
	conn = accept(server, (struct sockaddr*)NULL, NULL);
	if (conn < 0){
		cerr << "Error accepting connection" << endl;
		return 0;
	}

}

void tcp::Server::closes(){
	close(conn);
	close(server);
}
