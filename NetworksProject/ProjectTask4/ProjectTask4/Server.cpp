/*
* server.cpp
*
*  Created on: Mar 29, 2017
*      Author: patrick
*/

#include "Server.h"

using namespace std;

const string DIR_NAME = "server";
const string FILE_NAME = "test.txt";

Server::Server() {

}

void Server::connect(string* response) {
	*response = "ACK";
	is_connected = true;
	return;
}

bool Server::does_file_exist(string filename) {
	if (filename == FILE_NAME) {
		return true;
	}
	return false;
}

ifstream Server::get_file(string filename, string * response) {
	try {
		ifstream file((DIR_NAME + "/" + filename).c_str(), std::ios::binary);
		*response = "ACK";
		return file;
	}
	catch (std::exception& e) {
		return ifstream();
	}
}

bool Server::connection_established() {
	return is_connected;
}
