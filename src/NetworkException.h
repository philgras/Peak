/*
 * NetworkException.h
 *
 *  Created on: 22.03.2016
 *      Author: philip
 */

#ifndef SRC_NETWORKEXCEPTION_H_
#define SRC_NETWORKEXCEPTION_H_

#include "BaseException.h"


namespace Peak{

class NetworkException : public BaseException{

public:
    NetworkException(const char* errorMsg, const char* file, const char* function, unsigned int line)
    :BaseException(errorMsg,file,function,line){

    }

};


}



#endif /* SRC_NETWORKEXCEPTION_H_ */
