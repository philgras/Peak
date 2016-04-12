/*
 * Observable.h
 *
 *  Created on: 04.04.2016
 *      Author: philgras
 */

#ifndef SRC_OBSERVABLE_H_
#define SRC_OBSERVABLE_H_

#include "FileDescriptor.h"
#include "Common.h"
#include <sys/epoll.h>

namespace Peak{

struct Observable{


	enum EventTypes{
		EVENT_IN = EPOLLIN,
		EVENT_OUT = EPOLLOUT,
		EVENT_PEER_CLOSED = EPOLLRDHUP,
		EVENT_HANG_UP = EPOLLHUP,
		EVENT_ERROR = EPOLLERR,
		EVENT_EDGE_TRIGGERED = EPOLLET
	};

	Observable() = default;
	virtual ~Observable() = default;

	/**
	 * event could be set to EPOLLIN EPOLLOUT EPOLLHUP EPOLLRDHUP EPOLLERR
	 */
	virtual void handleEvents(int eventTypes) = 0;


	virtual FileDescriptor& getFileDescriptor() = 0;
	virtual int getEventTypes() = 0;

	DISALLOW_COPY_AND_ASSIGN(Observable);

};

}

#endif /* SRC_OBSERVABLE_H_ */
