/*
* Client.cpp
*
*  Created on: Mar 29, 2017
*      Author: patrick
*/

#include "Client.h"

using namespace std;

const string DIR_NAME = "client";

Client::Client() {

}
 
void Client::establish_connection(Server* server) {
	if (!is_connected) {
		string response = "";
		server->connect(&response);
		if (response == "ACK") {
			is_connected = true;
		}
	}
}

bool Client::get_file(Server* server, string filename) {
	if (is_connected && server->connection_established()) {
		if (server->does_file_exist(filename)) {
			string response = "";
			ifstream src;
			try {
				src = server->get_file(filename, &response);
				ofstream dest((DIR_NAME + "/" + filename).c_str(), std::ios::binary);
				dest << src.rdbuf();
				response = "ACK";
				src.close();
				dest.close();
			}
			catch (exception& e) {
				src.close();
			}
			if (response == "ACK") {
				return true;
			}
		}
	}
	return false;
}

bool Client::connection_established() {
	return is_connected;
}
