/*
 * Url.h
 *
 *  Created on: 20.02.2016
 *      Author: philgras
 */

#ifndef SRC_URL_H_
#define SRC_URL_H_

#include <iterator>
#include <type_traits>
#include <vector>
#include <map>
#include <string>

namespace Peak {

/*
 * TODO: simplify the interface --> no ranges
 */
class Url{

public:

	typedef std::multimap<std::string,std::string> ParameterMap;
    typedef std::pair<ParameterMap::const_iterator,ParameterMap::const_iterator> ParameterRange;


	Url():mParameters(),mPath(){}
	~Url(){}


	/*
	 * TODO: implement a template function for InputIterator traits
	 */

	/**
	 *
	 */
	void parse(const std::string& str){
		parseInternal(&(*str.begin()), &(*str.end()));
	}

	/**
	 *
	 */
	void parse(const std::vector<char>& vec){
		parseInternal(&(*vec.begin()), &(*vec.end()));

	}



	/**
	 *
	 * @param  parameter - string reference that represents the name of the parameter
	 * @returns Pair of constant map iterators to parameter name and parameter value.
	 * 		   Pair.first is equivalent to begin and Pair.second to end.
	 */
	const ParameterRange getParameterValues(const std::string& parameter)const{
		return mParameters.equal_range(parameter);
	}

	/**
	 *
	 * @param  parameter - string reference that represents the name of the parameter
	 * @returns A string pointer to the value of the parameter will be returned.
	 * 		   If no parameter has the given name, nullptr is the returned value.
	 * 		   Hence, make sure you check for nullptr value!
	 * 		   If the parameter has more than one value, it is undefined which value will be returned.
	 */
	const std::string* getParameterValue(const std::string& parameter)const{
		auto iter = mParameters.find(parameter);
		if(iter == mParameters.end()){
			return nullptr;
		}else{
			return &(iter->second);
		}
	}

	/**
	 * @returns URL path as string
	 */
	const std::string& getPath()const { return mPath; }

	const ParameterMap getAllParameterValues()const{
	        return mParameters;
	}


private:
	void parseInternal(const char* begin, const char* end);
	ParameterMap mParameters;
	std::string mPath;
};

}

#endif /* SRC_URL_H_ */
