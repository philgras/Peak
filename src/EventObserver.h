/*
 * EventObserver.h
 *
 *  Created on: 23.03.2016
 *      Author: philip
 */

#ifndef SRC_EVENTOBSERVER_H_
#define SRC_EVENTOBSERVER_H_


#include "DynamicArray.h"
#include "FileDescriptor.h"
#include "TerminationDescriptor.h"
#include "Observable.h"
#include <sys/epoll.h>

namespace Peak {


class EPollDescriptor : public FileDescriptor{

public:

	EPollDescriptor()
	:FileDescriptor(){}

	~EPollDescriptor() = default;

	void acquire();

	DISALLOW_COPY_AND_ASSIGN(EPollDescriptor);

};


//TODO: for windows and bsd --> template<typename EventDescriptorType, typename ObservationStrategy>
class EventObserver {
public:

    typedef struct epoll_event Event;

    static constexpr int INFINITE_TIMEOUT = -1;

    EventObserver()
    :mEpollDescriptor(),mTerminationDescriptor(){}

    ~EventObserver() = default;

    void start(){
    	mEpollDescriptor.acquire();
    	mTerminationDescriptor.acquire();
    	addObservable(mTerminationDescriptor);
    }
    void stop(){
    	mTerminationDescriptor.writeTerminationEvent();
    	mEpollDescriptor.close();
    }

    void addObservable(Observable&);
    void removeObservable(Observable&);

    size_t observeForEvents(DynamicArray<Event>& events  ,int timeout = INFINITE_TIMEOUT);


private:

    EPollDescriptor mEpollDescriptor;
    TerminationDescriptor mTerminationDescriptor;

};

} /* namespace Peak */

#endif /* SRC_EVENTOBSERVER_H_ */
