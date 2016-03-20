/*
 * AddressLookup.h
 *
 *  Created on: 20.03.2016
 *      Author: philgras
 */

#ifndef ADDRESSLOOKUP_H_
#define ADDRESSLOOKUP_H_

#include <netdb.h>

namespace Peak {


/**
 * Wrapper for getaddrinfo()
 */
class AddressLookup {

public:

	AddressLookup()
	:mResultList(nullptr),mIter(nullptr){}

	~AddressLookup(){
		freeResultList();
	}

	/**
	 * finds address to bind or connect sockets
	 * If lookup has already been called before, the old result list will be freed.
	 * @param host - IPv4, IPv6 or hostname
	 * @param service - protocol or port
	 * @param aiFamily - address family AF_INET AF_INET6 or AF_UNSPEC
	 * @param sockType - SOCK_STREAM or SOCK_DGRAM
	 * @param aiFlags - flags or 0
	 * @throws system-error
	 * TODO: find a more appropriate exception class
	 */
	void lookup(const char* host, const char* service, int aiFamily, int sockType, int aiFlags);

	/**
	 * @returns the next addrinfo in the result list or nullptr
	 */
	const struct addrinfo* getNextResult() const;

private:

	void freeResultList(){
		if( mResultList!= nullptr ){
			freeaddrinfo(mResultList);
			mResultList = nullptr;
		}
	}

	struct addrinfo * mResultList;
	struct addrinfo* mIter;

};

} /* namespace Peak */

#endif /* ADDRESSLOOKUP_H_ */
