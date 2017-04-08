#ifndef ASYNCSOCKET_H
#define ASYNCSOCKET_H 1

#include <threadpp/runner.h>
#include "../socket.h"
#include <queue>

using namespace std;
using namespace tcp;

class AsyncSocket : public Socket
{

private:
	queue<char*> outgoing; // messages to be sent
	queue<char*> incoming; // inbox for incoming messages
	Runner       sendd;    // sends data
	Runner       recvd;    // reads data

public:
	// all of the base constructors
	AsyncSocket(); 
	AsyncSocket(int sockd);
	AsyncSocket(char* host, int port);
	
	// getters
	queue<char*> getOutgoing(){ return this->outgoing; }
	queue<char*> getIncoming(){ return this->incoming; }

	// adds values to the outgoing queue
	void pushOutgoing(char* msg){ outgoing.push(msg); }
	void pushIncoming(char* msg){ incoming.push(msg); }
	
	// returns the top value from incoming and outgoing
	char* popIncoming();
	char* popOutgoing();

	// send asynchronously
	int   asends(char* buffer);
	//int   asends(int ii);
	
	// recieve asynchronously
	char* areads();
	//int   areadi();

};

#endif // ASYNCSOCKET_H
