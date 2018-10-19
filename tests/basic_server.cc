
#include <tcp/socket.h>
#include <tcp/server.h>
#include <inet/addr.h>
#include <iostream>
#include <memory>
#include <thread>
#include <future>

int client(void)
{
	lsock::inet::Addr addr("127.0.0.1", 8888);
	lsock::tcp::Socket sock;
	int ret = sock.connect(&addr);
	if (ret < 0) {
		std::cerr << "client: error connecting" << std::endl;
		return 1;
	}

	sock << "Hello World from Client" << std::endl;

	return 0;
}

int main()
{
	lsock::inet::Addr addr("default-host", 8888);
	lsock::tcp::Server serv;

	std::future<int> cli_ret = std::async(std::launch::async, client);

	int ret = serv.connect(&addr);
	if (ret < 0) {
		std::cerr << "server: error connecting" << std::endl;
    		return 1;
	}

	auto sock = serv.accept();
	char *buf = new char[30];
	sock->get(buf, 30);
	std::clog << buf << std::endl;
	std::string bufstr(buf);
	if (bufstr != "Hello World from Client") {
		std::cerr << "server: error reading from client" << std::endl;
		return 2;
	}
	delete[] buf;
	sock->disconnect();

	int cliret_val = cli_ret.get();
	std::clog << "server: cli ret: " << cliret_val << std::endl;
	if (cliret_val) {
		std::cerr << "server: client failed" << std::endl;
		return 3;
	}

	return 0;
}
