/*
 * Service.h
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#ifndef SRC_SERVICE_H_
#define SRC_SERVICE_H_

#include "Service.h"
#include <list>

namespace Peak {

class Service {
public:
	Service();
	~Service();

	void start();

	void stop();

	const std::string& getName() const {return mName;}

	void addConnection(const Connection& connection){
		mConnectionList.push_back(connection);
	}

	void removeConnection(){
		mConnectionList.erase(mConnectionList.begin());
	}



private:

	std::string mName;
	Socket mListener;
	std::list<Connection> mConnectionList;

};

} /* namespace Peak */

#endif /* SRC_SERVICE_H_ */
