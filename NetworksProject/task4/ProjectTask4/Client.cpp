#include "Client.h"

using namespace std;

const string DIR_NAME = "client";
 
// establish connection with server
void Client::establish_connection(Server* server) {
	// if not already connecetd
	if (!is_connected) {
		cout << "CLIENT: Requesting connection..." << endl;

		string response = "";
		string request = "HELLO";
		// request connection
		server->connect(&response, request);
		if (response == "ACK") {
			cout << "CLIENT: Connection established." << endl;
			is_connected = true;
		}
	}
}

// request file from server
void Client::request_file(Server* server, string filename) {
	if (is_connected && server->connection_established()) {
		string response = "";
		ifstream src;
		try {
			cout << "CLIENT: Requesting file..." << endl;

			// request file from server
			src = server->send_file(filename);
			// save file to client directory
			ofstream dest((DIR_NAME + "/" + filename).c_str(), std::ios::binary);
			dest << src.rdbuf();
			// file received
			received_file(server);
			src.close();
			dest.close();
		}
		catch (exception& e) {
			src.close();
		}
	}
	return;
}

// send file received acknowledgement to server
void Client::received_file(Server* server) {
	cout << "CLIENT: Received file. Sending acknowledgement." << endl;

	string response = "ACK";
	// send acknowledgement
	server->received_file(response);
}

// connection established accessor
bool Client::connection_established() {
	return is_connected;
}
