/*
 * TerminationDescriptor.h
 *
 *  Created on: 06.04.2016
 *      Author: philgras
 */

#ifndef SRC_TERMINATIONDESCRIPTOR_H_
#define SRC_TERMINATIONDESCRIPTOR_H_

#include "Common.h"

#include "FileDescriptor.h"
#include "Observable.h"
#include "EventException.h"
#include "Server.h"

#include <cstring>
#include <cerrno>

#include <sys/eventfd.h>


namespace Peak{

class TerminationDescriptor : public FileDescriptor, public Observable{

public:

	TerminationDescriptor()
	:FileDescriptor(),Observable(){}

	~TerminationDescriptor() = default;

	void acquire(){
		close();
		mDescriptor = ::eventfd(0, EFD_NONBLOCK);
		if(mDescriptor == INVALID_DESCRIPTOR){
			THROW_EXCEPTION(EventException,strerror(errno));
		}
	}

	virtual void handleEvents(int eventTypes){
		return;
	}

	virtual FileDescriptor& getFileDescriptor(){ return *this;}
	virtual int getEventTypes() {
		return Observable::EVENT_IN ;
	}

	void writeTerminationEvent(){
		::eventfd_write(mDescriptor, 1);
	}

	DISALLOW_COPY_AND_ASSIGN(TerminationDescriptor);


};


}



#endif /* SRC_TERMINATIONDESCRIPTOR_H_ */
