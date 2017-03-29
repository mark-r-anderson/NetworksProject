#include "Server.h"

using namespace std;

const string DIR_NAME = "server";
const string FILE_NAME = "test.txt";

// connect with client
void Server::connect(string* response, string request) {
	if (request == "HELLO") {
		cout << "SERVER: Request received. Sending acknowledgement." << endl;

		// send acknowledgement to client
		*response = "ACK";
		is_connected = true;
	}
	return;
}

// send file to client
ifstream Server::send_file(string filename) {
	if (filename == FILE_NAME) {
		try {
			cout << "SERVER: Request received. Sending file." << endl;

			// send file from server directory to client
			ifstream file((DIR_NAME + "/" + filename).c_str(), std::ios::binary);
			return file;
		}
		catch (std::exception& e) {
			return ifstream();
		}
	}
	return ifstream();
}

// connection established accessor
bool Server::connection_established() {
	return is_connected;
}

// receive file acknowledgement from client
void Server::received_file(string response) {
	if (response == "ACK") {
		cout << "SERVER: Received acknowledgement." << endl;
	}
}
