#pragma once

#ifndef NETWORKSPROJECT_TASK4_SERVER_HPP_
#define NETWORKSPROJECT_TASK4_SERVER_HPP_

#include <iostream>
#include <fstream>

class Server {
public:
	// connect with client
	void connect(std::string * response, std::string request);
	// send file to client
	std::ifstream send_file(std::string filename);
	// connection established accessor
	bool connection_established();
	// receive file acknowledgement from client
	void received_file(std::string);

private:
	bool is_connected = false;
};




#endif /* NETWORKSPROJECT_TASK4_SERVER_HPP_ */