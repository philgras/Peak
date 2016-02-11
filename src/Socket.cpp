/*
 * Socket.cpp
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#include "Socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <fcntl.h>
#include <system_error>
#include <cerrno>
#include <cstring>

namespace Peak {

void Socket::operator =(Socket&& socket){

	this->mDescriptor 	= socket.mDescriptor;
	this->mIsListening 	= socket.mIsListening;
	this->mIp 			= socket.mIp;
	this->mPort 		= socket.mPort;

	socket.mDescriptor 	= INVALID_SOCKET;
	socket.mIsListening = false;
	socket.mIp 			= DEFAULT_IP;
	socket.mPort 		= DEFAULT_PORT;

}

void Socket::bind(const std::string& port, const std::string& ip ){

	struct addrinfo * res = NULL;
	struct addrinfo hints;
	int yes = 1; //used in the setsockopt()-call
	int rc; //used to get gai_strerror
	SocketDescriptor sfd = INVALID_SOCKET;

	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((rc = ::getaddrinfo(ip? ip.c_str() : NULL , port.c_str(), &hints, &res)) != 0) {
		throw std::system_error(std::error_code(), gai_strerror(rc));
	}

	/*don't return before releasing the allocated resources*/

	for (struct addrinfo* iter = res; iter != NULL; iter = iter->ai_next) {

		//get the descriptor
		sfd = socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol);
		if (sfd == INVALID_SOCKET) {
			//log
			continue;
		}

		//setsockopt
		if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))
				== -1) {
			//log
			Socket::closeSocketDescriptor(sfd);
			sfd = INVALID_SOCKET;
			break;
		}

		//bind it
		if (::bind(sfd, iter->ai_addr, iter->ai_addrlen) == -1) {
			//log
			Socket::closeSocketDescriptor(sfd);
			sfd = INVALID_SOCKET;
			continue;
		}
	}

	freeaddrinfo(res);
}


void Socket::enableNonBlocking(){

	int flags;

	flags = fcntl(mDescriptor, F_GETFL, 0);
	if (flags == -1) {
		throw std::system_error(errno, std::system_category());
	}

	flags |= O_NONBLOCK;
	if (fcntl(mDescriptor, F_SETFL, flags) == -1) {
		throw std::system_error(errno, std::system_category());

	}
}

} /* namespace Peak */
