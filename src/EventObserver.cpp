/*
 * EventObserver.cpp
 *
 *  Created on: 23.03.2016
 *      Author: philip
 */

#include "EventObserver.h"
#include "EventException.h"

#include <cassert>
#include <cstring>
#include <cerrno>

#include <sys/epoll.h>
#include <unistd.h>

#define HXS_MAXEVENTS 1

namespace Peak {

void EPollDescriptor::acquire(){
	close();
	mDescriptor = ::epoll_create1(0);
	if(mDescriptor == INVALID_DESCRIPTOR){
		THROW_EXCEPTION(EventException, std::strerror(errno));
	}
}


void EventObserver::addObservable(Observable& observable){

	int rc = 0;

	Event epoll_event;

	epoll_event.data.ptr = &observable;
	epoll_event.events = observable.getEventTypes();

	rc = ::epoll_ctl(mEpollDescriptor.getDescriptor(), EPOLL_CTL_ADD,
			  observable.getFileDescriptor().getDescriptor(), &epoll_event);

	if(rc == -1){
		THROW_EXCEPTION(EventException, std::strerror(errno));
	}

}

void EventObserver::removeObservable(Observable& o){
	Event dummy; //for compatibility with kernel 2.6.9
	int rc = ::epoll_ctl(mEpollDescriptor.getDescriptor(),EPOLL_CTL_DEL,o.
						getFileDescriptor().getDescriptor(),&dummy);
	if(rc == -1){
		THROW_EXCEPTION(EventException,std::strerror(errno));
	}
}

size_t EventObserver::observeForEvents(DynamicArray<Event>& events, int timeout){

	assert(events.empty() == false);
	int n = ::epoll_wait(mEpollDescriptor.getDescriptor(), events.getStorage(), events.size(), timeout);
	if(n == -1){
		THROW_EXCEPTION(EventException, strerror(errno));
	}

	return n;

}


} /* namespace Peak */
