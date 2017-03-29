/*
* Client.h
*
*  Created on: Mar 29, 2017
*      Author: patrick
*/

#pragma once

#ifndef NETWORKSPROJECT_TASK4_CLIENT_HPP_
#define NETWORKSPROJECT_TASK4_CLIENT_HPP_

#include <iostream>
#include "Server.h"

class Client {
public:
	Client();

	void establish_connection(Server* server);
	bool connection_established();
	bool get_file(Server* server, std::string filename);

private:
	bool is_connected = false;
};




#endif /* NETWORKSPROJECT_TASK4_CLIENT_HPP_ */
