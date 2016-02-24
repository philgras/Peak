/*
 * HttpRequest.h
 *
 *  Created on: 20.02.2016
 *      Author: philgras
 */

#ifndef SRC_HTTPREQUEST_H_
#define SRC_HTTPREQUEST_H_

#include "Buffer.h"
#include <map>
#include <string>
#include <vector>

namespace Peak {

class HttpRequest {
public:

	typedef std::pair<const char*,const char*> HttpBodyRange;

	HttpRequest(): http_header(),mBody(){}
	~HttpRequest(){}

private:

	std::map< std::string, std::vector<std::string> > http_header;
	HttpBodyRange mBody;
};

} /* namespace Peak */

#endif /* SRC_HTTPREQUEST_H_ */
