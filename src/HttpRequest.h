/*
 * HttpRequest.h
 *
 *  Created on: 20.02.2016
 *      Author: philgras
 */

#ifndef SRC_HTTPREQUEST_H_
#define SRC_HTTPREQUEST_H_

#include "Url.h"
#include <map>
#include <string>
#include <vector>

namespace Peak {

class HttpRequest {
public:

	typedef std::multimap< std::string, std::string> HeaderMap;
	typedef std::pair<HeaderMap::const_iterator, HeaderMap::const_iterator> HeaderRange;

	HttpRequest():
	mUrl(),mHeaderFields(){}
	~HttpRequest(){}


	template<typename StringT>
	void addHeader(StringT&& header, StringT&& value){
		mHeaderFields.insert(std::make_pair(std::forward<StringT>(header),
											std::forward<StringT>(value)));
	}

	/**
	 *
	 */
	HeaderRange getHeaderValues(const std::string& header) const{
		return mHeaderFields.equal_range(header);
	}

	/**
	 *
	 * @param  header - string reference that represents the name of the header field
	 * @return A pointer to the string value of the header field will be returned.
	 * 		   If no header field has the given name, nullptr is the returned value.
	 * 		   Hence, make sure you check for nullptr value!
	 * 		   If the header field has more than one value, it is undefined which value will be returned.
	 */
	const std::string* getHeaderValue(const std::string& header) const{
		auto iter = mHeaderFields.find(header);
		if(iter == mHeaderFields.end()){
			return nullptr;
		}else{
			return &(iter->second);
		}
	}

	const Url& getUrl()const{
		return mUrl;
	}


private:

	Url mUrl;
	HeaderMap mHeaderFields;
};

} /* namespace Peak */

#endif /* SRC_HTTPREQUEST_H_ */
