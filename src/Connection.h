/*
 * Connection.h
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#ifndef SRC_CONNECTION_H_
#define SRC_CONNECTION_H_

#include "Observable.h"
#include "Common.h"
#include "Socket.h"

namespace Peak {

class Service;

class Connection : public Observable{
public:
	Connection(Socket&& socket, Service& service)
	:Observable(),mSocket(std::move(socket)),mService(service),mBuffer(){

	}

	Connection(Connection&& c)
	:Observable(),mSocket(std::move(c.mSocket)),mService(c.mService),mBuffer(std::move(c.mBuffer)){}

	virtual ~Connection() = default;
	virtual void handleEvents(int eventTypes) final;

	virtual FileDescriptor& getFileDescriptor() {return mSocket;}

	virtual int getEventTypes() {
		return Observable::EVENT_IN | Observable::EVENT_OUT |
			   Observable::EVENT_PEER_CLOSED | Observable::EVENT_EDGE_TRIGGERED;
	}

	const Service& getService() const { return mService; }

protected:

	virtual void receiveMessage() = 0;
	virtual void sendMessage() = 0;

private:
	Socket mSocket;
	Service& mService;
	Buffer mBuffer;
};

} /* namespace Peak */

#endif /* SRC_CONNECTION_H_ */
