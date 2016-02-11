/*
 * Connection.h
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#ifndef SRC_CONNECTION_H_
#define SRC_CONNECTION_H_

#include "Socket.h"

namespace Peak {

class Service;

class Connection {
public:
	Connection();
	~Connection();

	Service& getService() const { return mService; }


private:

	Socket mSocket;
	Service& mService;
	std::vector<unsigned char> mBuffer;

};

} /* namespace Peak */

#endif /* SRC_CONNECTION_H_ */
