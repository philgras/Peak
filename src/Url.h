/*
 * Url.h
 *
 *  Created on: 20.02.2016
 *      Author: philgras
 */

#ifndef SRC_URL_H_
#define SRC_URL_H_

#include "Buffer.h"
#include <map>
#include <string>

namespace Peak {


class Url{

public:

	typedef std::pair<std::multimap<std::string,std::string>::const_iterator,
					  std::multimap<std::string,std::string>::const_iterator> range;

	Url():mParameters(),mPath(){}
	~Url(){}

	/**
	 * @returns Boolean value that indicates if the url data is valid.
	 * 			If it is not the Url object can be reused for another call.
	 */
	void parse(Buffer::const_iterator begin, Buffer::const_iterator end);

	const range getParameterValues(const std::string& parameter)const{
		return mParameters.equal_range(parameter);
	}

	const std::string* getParameterValue(const std::string& parameter)const{
		auto iter = mParameters.find(parameter);
		if(iter == mParameters.end()){
			return nullptr;
		}else{
			return &(iter->second);
		}
	}

	const std::string& getPath()const { return mPath; }


private:
	std::multimap<std::string,std::string> mParameters;
	std::string mPath;
};

}

#endif /* SRC_URL_H_ */
