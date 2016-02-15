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

	std::list<Connection>::const_iterator&
	getLocator() const {
		return mLocator;
	}

	const Socket& getSocket() const{ return mSocket; }


private:

	Socket mSocket;
	Service& mService;
	std::list<Connection>::const_iterator mLocator;

};

} /* namespace Peak */

#endif /* SRC_CONNECTION_H_ */
