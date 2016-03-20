/*
 * AddressLookup.cpp
 *
 *  Created on: 20.03.2016
 *      Author: philgras
 */

#include "AddressLookup.h"
#include <cstring>

namespace Peak {

void AddressLookup::lookup(const char* host, const char* service, int aiFamily, int sockType, int aiFlags){

	freeResultList();

	struct addrinfo hints;
	int rc = 0;

	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((rc = ::getaddrinfo(host,service,&hints,&mResultList)) != 0) {
		mResultList = nullptr;
		mIter = nullptr;

		//change exception type
		throw std::system_error(std::error_code(), gai_strerror(rc));
	}

}

const struct addrinfo* AddressLookup::getNextResult() const{

	struct addrinfo* next = nullptr;

	if(mIter != nullptr && mResultList != nullptr){
		next = mIter;
		mIter = mIter->ai_next;
	}

	return next;
}

} /* namespace Peak */
