/*
* main.cpp
*
*  Created on: Mar 29, 2017
*      Author: patrick
*/

#include "Server.h"
#include "Client.h"

using namespace std;

int main(int argc, const char* argv) {
	Client client;
	Server* server = new Server();

	client.establish_connection(server);
	if (client.connection_established()) {
		client.get_file(server, "test.txt");
	}
	return 0;
}
