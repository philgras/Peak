/*
 * FileDescriptor.h
 *
 *  Created on: 05.04.2016
 *      Author: philgras
 */

#ifndef SRC_FILEDESCRIPTOR_H_
#define SRC_FILEDESCRIPTOR_H_

#include "Common.h"
#include <unistd.h>

namespace Peak{


class FileDescriptor{

public:

	typedef int Descriptor;

	static constexpr int INVALID_DESCRIPTOR = -1;

	FileDescriptor()
	:mDescriptor(INVALID_DESCRIPTOR){
	}

	FileDescriptor(FileDescriptor&& f)
	:mDescriptor(f.mDescriptor){
		f.mDescriptor = INVALID_DESCRIPTOR;
	}

	virtual ~FileDescriptor(){
		close();
	}

	void operator=(FileDescriptor&& f){
		mDescriptor = f.mDescriptor;
		f.mDescriptor = INVALID_DESCRIPTOR;
	}

	void close(){
		if(mDescriptor != INVALID_DESCRIPTOR){
			::close(mDescriptor);
			mDescriptor = INVALID_DESCRIPTOR;
		}
	}

	Descriptor getDescriptor() const{return mDescriptor;}

	DISALLOW_COPY_AND_ASSIGN(FileDescriptor);

protected:

	Descriptor mDescriptor;

};

}



#endif /* SRC_FILEDESCRIPTOR_H_ */
