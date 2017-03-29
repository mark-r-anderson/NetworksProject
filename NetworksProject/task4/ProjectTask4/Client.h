#pragma once

#ifndef NETWORKSPROJECT_TASK4_CLIENT_HPP_
#define NETWORKSPROJECT_TASK4_CLIENT_HPP_

#include <iostream>
#include "Server.h"

class Client {
public:
	void establish_connection(Server* server); // establish connection with the server
	bool connection_established(); // connection accessor
	void request_file(Server* server, std::string filename); // request a file from server
	void received_file(Server* server); // send file received acknowledgement to server

private:
	bool is_connected = false;
};

#endif /* NETWORKSPROJECT_TASK4_CLIENT_HPP_ */
