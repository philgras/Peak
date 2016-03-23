/*
 * BaseException.h
 *
 *  Created on: 22.03.2016
 *      Author: philgras
 */

#ifndef SRC_BASEEXCEPTION_H_
#define SRC_BASEEXCEPTION_H_

#include <exception>

namespace Peak{

class BaseException : public std::exception{

public:
    BaseException(const char* errorMsg, const char* file, const char* function, unsigned int line)
    :mErrorMsg(errorMsg),mFile(file),mFunction(function),mLine(line){

    }

    const char* getErrorMessage() const{
        return mErrorMsg;
    }

    const char* getSourceFileName()const{
        return mFile;
    }

    const char* getFunctionName()const{
        return mFunction;
    }

    unsigned int getLineNumber() const{
        return mLine;
    }

private:
    const char* mErrorMsg;
    const char* mFile;
    const char* mFunction;
    unsigned int mLine;

};

}



#endif /* SRC_BASEEXCEPTION_H_ */
