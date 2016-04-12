/*
 * Service.h
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#ifndef SRC_SERVICE_H_
#define SRC_SERVICE_H_

#include "Common.h"

#include "FileDescriptor.h"
#include "Socket.h"
#include "Observable.h"

#include <unordered_map>
#include <memory>
#include <string>

namespace Peak {

class Connection;

class Service : public Observable {
public:

	Service(const char* name, const char* desc, const char* pattern,
			const char* directoryPath, const char* port, bool active)

	:Observable(),
	 mSocket(),
	 mName(name),
	 mDescription(desc),
	 mUrlPattern(pattern),
	 mDirectoryPath(directoryPath),
	 mPort(port),
	 mActive(active),
	 mConnectionMap(){


	}

	Service(const std::string& name, const std::string& desc, const std::string& pattern,
			const std::string& directoryPath, const std::string& port, bool active)

	:Observable(),
	 mSocket(),
	 mName(name),
	 mDescription(desc),
	 mUrlPattern(pattern),
	 mDirectoryPath(directoryPath),
	 mPort(port),
	 mActive(active),
	 mConnectionMap(){


	}


	Service(Service&& s)
	:Observable(),
	 mSocket(std::move(s.mSocket)),
	 mName(std::move(s.mName)),
	 mDescription(std::move(s.mDescription)),
	 mUrlPattern(std::move(s.mUrlPattern)),
	 mDirectoryPath(std::move(s.mDirectoryPath)),
	 mPort(std::move(s.mPort)),
	 mActive(s.mActive),
	 mConnectionMap(std::move(s.mConnectionMap)){}


	virtual ~Service() = default;

	virtual void handleEvents(int eventTypes);

	virtual FileDescriptor& getFileDescriptor(){return mSocket;}
	virtual int getEventTypes(){
		return  Observable::EVENT_IN | Observable::EVENT_EDGE_TRIGGERED;
	}


	//TODO: rethink this function design because the connection object is invalidated after this invocation
	void removeConnection(Connection& connection);

	void setListenerSocket(Socket&& socket){ mSocket = std::move(socket);}
	bool isActive()const{return mActive;}
	const std::string& getName() const {return mName;}
	const std::string& getPort() const {return mPort;}

	DISALLOW_COPY_AND_ASSIGN(Service);

private:

	Socket mSocket;
	std::string mName;
	std::string mDescription;
	std::string mUrlPattern;
	std::string mDirectoryPath;
	std::string mPort;
	bool mActive;
	std::unordered_map<Socket::Descriptor,std::unique_ptr<Connection>> mConnectionMap;

};

} /* namespace Peak */

#endif /* SRC_SERVICE_H_ */
