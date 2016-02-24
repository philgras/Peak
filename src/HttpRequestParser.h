/*
 * HttpRequestParser.h
 *
 *  Created on: 19.02.2016
 *      Author: philgras
 */

#ifndef HTTPREQUESTPARSER_H_
#define HTTPREQUESTPARSER_H_

#include "../libs/http-parser/http_parser.h"


namespace Peak {

class HttpRequestParser {
public:
	HttpRequestParser();
	~HttpRequestParser();

	void setCurrentRequest(HttpRequest& request){
		mCurrentRequest = request;
		mIsDone = false;
	}

	bool isDone() const{
		return mIsDone;
	}


private:

	struct http_parser mInternalParser;
	HttpRequest& mCurrentRequest;
	bool mIsDone;
};

} /* namespace Peak */

#endif /* HTTPREQUESTPARSER_H_ */
