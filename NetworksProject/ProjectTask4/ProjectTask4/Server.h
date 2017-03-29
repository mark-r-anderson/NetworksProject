/*
* Server.h
*
*  Created on: Mar 29, 2017
*      Author: patrick
*/

#pragma once

#ifndef NETWORKSPROJECT_TASK4_SERVER_HPP_
#define NETWORKSPROJECT_TASK4_SERVER_HPP_

#include <iostream>
#include <fstream>

class Server {
public:
	Server();
	//~Server();

	void connect(std::string * response);
	//void disconnect(std::string);
	bool does_file_exist(std::string filename);
	std::ifstream get_file(std::string filename, std::string * response);
	bool connection_established();

private:
	bool is_connected = false;
};




#endif /* NETWORKSPROJECT_TASK4_SERVER_HPP_ */