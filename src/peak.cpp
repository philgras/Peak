/*
 * peak.cpp
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#include "Server.h"

using namespace Peak;

int main(int n, char** c){


	Server& server = Server::getInstance();

	return server.start();

}



