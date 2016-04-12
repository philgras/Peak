/*
 * Connection.cpp
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#include "Connection.h"
#include "Service.h"

namespace Peak {

void Connection::handleEvents(int eventTypes){


	if((eventTypes | Observable::EVENT_HANG_UP ) || (eventTypes | Observable::EVENT_ERROR)){
		mService.removeConnection(*this);
		return;
	}

	if(){

	}


	if (eventTypes | Observable::EVENT_OUT){
		sendMessage();
	}

	if(eventTypes | Observable::EVENT_IN){
		receiveMessage();
	}

	//all events are handled --> send recv loop

	while(mSocket.getTrafficStatus() == Socket::TrafficStatus::NOT_SET){

		receiveMessage();
		sendMessage();

	}

}

} /* namespace Peak */
