/*
 * Socket.cpp
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#include "Socket.h"
#include "AddressLookup.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <fcntl.h>



namespace Peak {


void Socket::operator =(Socket&& socket){

	this->mDescriptor 	= socket.mDescriptor;
	socket.mDescriptor 	= INVALID_SOCKET;

}

void Socket::connect(const std::string& host, const std::string& service){
	AddressLookup addressLookup;
	const struct addrinfo* addressInfo = nullptr;
	int errorCode;

	addressLookup.lookup(host.c_str(),service.c_str(),
							AF_UNSPEC, SOCK_STREAM, 0);

	while((addressInfo = addressLookup.getNextResult())!= nullptr){

		mDescriptor = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
		if (mDescriptor == INVALID_SOCKET) {

			errorCode = errno;
			//TODO: log

			continue;
		}


		if (::connect(mDescriptor, addressInfo->ai_addr, addressInfo->ai_addrlen) == -1) {
			errorCode = errno;
			//TODO: log

			this->close();
			continue;

		}
	}

	//if the socket could not connect to any address throw an exception
	if(mDescriptor == INVALID_SOCKET){
		THROW_EXCEPTION(NetworkException,strerror(errorCode));
	}
}


void Socket::bind(const std::string& host, const std::string& service ){

	AddressLookup addressLookup;
	const struct addrinfo* addressInfo = nullptr;
	int yes = 1;
	int errorCode;

	addressLookup.lookup(host.c_str(),service.c_str(),
							AF_INET,SOCK_STREAM,AI_PASSIVE);

	while((addressInfo = addressLookup.getNextResult())!= nullptr){
		//get the descriptor
		mDescriptor = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
		if (mDescriptor == INVALID_SOCKET) {
			errorCode = errno;

			//TODO: log

			continue;
		}

		//setsockopt
		if (::setsockopt(mDescriptor, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))	== -1) {
			errorCode = errno;
			this->close();
			THROW_EXCEPTION(NetworkException,strerror(errno));
		}

		//bind it
		if (::bind(mDescriptor, addressInfo->ai_addr, addressInfo->ai_addrlen) == -1) {
			errorCode = errno;

			//TODO: log

			this->close();
			continue;
		}
	}

	//if the socket could not be bind to any address throw an exception
	if(mDescriptor == INVALID_SOCKET){
		THROW_EXCEPTION(NetworkException,strerror(errorCode));
	}

}


void Socket::enableNonBlockingMode(){

	int flags;

	flags = ::fcntl(mDescriptor, F_GETFL, 0);
	if (flags == -1) {
		THROW_EXCEPTION(NetworkException,strerror(errno));
	}

	flags |= O_NONBLOCK;
	if (::fcntl(mDescriptor, F_SETFL, flags) == -1) {
		THROW_EXCEPTION(NetworkException,strerror(errno));
	}
}




std::vector<Socket> Socket::acceptAll(){
	std::vector<Socket> acceptedSockets;
	int descriptor;

	while(true){
		if((descriptor = ::accept(mDescriptor,NULL,NULL)) == INVALID_SOCKET){
			if(errno == EAGAIN || errno == EWOULDBLOCK){
				break;
			}else{
				THROW_EXCEPTION(NetworkException,strerror(errno));
			}
		}else{
			acceptedSockets.push_back(Socket(descriptor));
		}
	}
	return acceptedSockets;
}




Socket Socket::acceptSingle(){
	int descriptor;
	if((descriptor = ::accept(mDescriptor,NULL,NULL)) == INVALID_SOCKET){
		THROW_EXCEPTION(NetworkException,strerror(errno));
	}
	return Socket(descriptor);
}




void Socket::send(Buffer& buf){

    int rc;

    while(buf.getCapacityUsed()>0){
        rc = ::send(mDescriptor, &(*buf.getReadingPosition()), static_cast<int>(buf.getCapacityUsed()) ,0);
        if(rc == -1){
            if(errno == EAGAIN || errno == EWOULDBLOCK){

                mStatus = SEND_WAIT;
                break;

            }else{

                THROW_EXCEPTION(NetworkException,strerror(errno));

            }

        }

        buf.read(rc);

    }

}

void Socket::receive(Buffer& buffer){


    auto iter = buffer.prepareStorage(BUFFER_SIZE);

    int rc = ::recv(mDescriptor, &(*(iter)) ,static_cast<int>(BUFFER_SIZE),0);
    if(rc == -1){
        if(errno == EAGAIN || errno == EWOULDBLOCK){

            mStatus = RECV_WAIT;
            rc = 0;

        }else{

            THROW_EXCEPTION(NetworkException,strerror(errno));

        }
    }else if(rc == 0){

        mStatus = CLOSED_BY_PEER;

    }

    buffer.wrote(rc);

}

} /* namespace Peak */
