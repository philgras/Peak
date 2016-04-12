/*
 * Service.cpp
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#include "Service.h"
#include "Server.h"

namespace Peak {

void Service::removeConnection(Connection& connection){

	Server::getInstance().getEventObserver().removeObservable(connection);
	mConnectionMap.erase(connection.getFileDescriptor().getDescriptor());

}

void Service::handleEvents(int eventTypes){

	if((eventTypes | Observable::EVENT_HANG_UP ) || (eventTypes | Observable::EVENT_ERROR)){
		//TODO: try to restart
	}else if(eventTypes | Observable::EVENT_IN){
		std::vector<Socket> newSockets = mSocket.acceptAll();
		for(auto iter = newSockets.begin(); iter != newSockets.end();++iter){

			std::unique_ptr<Connection> connectionPtr(new Connection(Connection(std::move(*iter),*this)));

			Server::getInstance().getEventObserver().addObservable(*connectionPtr);

			mConnectionMap.insert(std::make_pair(connectionPtr->getFileDescriptor().getDescriptor(),
												 std::move(connectionPtr)));
		}
	}

}

} /* namespace Peak */
