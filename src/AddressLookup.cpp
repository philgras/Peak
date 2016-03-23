/*
 * AddressLookup.cpp
 *
 *  Created on: 20.03.2016
 *      Author: philgras
 */

#include "AddressLookup.h"
#include "Common.h"
#include "NetworkException.h"
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

		THROW_EXCEPTION(NetworkException, gai_strerror(rc));
	}

	mIter = mResultList;

}

const struct addrinfo* AddressLookup::getNextResult(){

	struct addrinfo* next = nullptr;

	if(mIter != nullptr && mResultList != nullptr){
		next = mIter;
		mIter = mIter->ai_next;
	}

	return next;
}

} /* namespace Peak */
