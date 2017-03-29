#include "Server.h"
#include "Client.h"

using namespace std;

int main(int argc, const char* argv) {
	// create client and server objects
	Client client;
	Server* server = new Server();

	// client establishes connection with server
	client.establish_connection(server);
	if (client.connection_established()) {
		// request file
		client.request_file(server, "test.txt");
	}
	
	system("pause");
}
