/*
 * EventObserver.h
 *
 *  Created on: 23.03.2016
 *      Author: philip
 */

#ifndef SRC_EVENTOBSERVER_H_
#define SRC_EVENTOBSERVER_H_

#include "Connection.h"
#include "Common.h"
#include "Event.h"
#include "EventException.h"
#include <vector>
#include <cassert>
#include <sys/epoll.h>

namespace Peak {

class EventObserver {
public:

    typedef int EventDescriptor;

    static constexpr int INVALID_DESCRIPTOR;

    EventObserver();
    ~EventObserver(){
        close();
    }



    void observeConnection(Connection* connection){

        struct epoll_event event;
        int rc = 0;

        event.data.ptr = connection;
        event.events = EPOLLIN | EPOLLOUT | EPOLLET;

        rc = ::epoll_ctl(mEventDescriptor, EPOLL_CTL_ADD,
                  connection->getSocket().getSocketDescriptor(), &event);

        if(rc == -1){
            THROW_EXCEPTION(EventException, strerror(errno));
        }

    }

    void waitForEvents(){



    }

    void close(){
        if(mEventDescriptor != INVALID_DESCRIPTOR){
            ::close(mEventDescriptor);
            mEventDescriptor = INVALID_DESCRIPTOR;
        }
    }

private:

    EventDescriptor mEventDescriptor;

};

} /* namespace Peak */

#endif /* SRC_EVENTOBSERVER_H_ */
