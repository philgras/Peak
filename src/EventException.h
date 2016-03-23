/*
 * EventException.h
 *
 *  Created on: 23.03.2016
 *      Author: philip
 */

#ifndef SRC_EVENTEXCEPTION_H_
#define SRC_EVENTEXCEPTION_H_


#include "BaseException.h"


namespace Peak{

class EventException : public BaseException{

public:
    EventException(const char* errorMsg, const char* file, const char* function, unsigned int line)
    :BaseException(errorMsg,file,function,line){

    }

};

}

#endif /* SRC_EVENTEXCEPTION_H_ */
