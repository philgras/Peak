/*
 * Socket.h
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

#include "FileDescriptor.h"
#include "Common.h"
#include "NetworkException.h"
#include "Buffer.h"
#include <string>
#include <vector>
#include <cerrno>
#include <cstring>
#include <cstdint>
#include <unistd.h>

#include <sys/socket.h>


namespace Peak {

class Socket : public FileDescriptor{
public:

	static constexpr size_t BUFFER_SIZE = 8192;

	enum TrafficStatus{
	  NOT_SET,
	  SEND_WAIT,
	  RECV_WAIT,
	  CLOSED_BY_PEER
	};

	Socket()
	:FileDescriptor(),mStatus(NOT_SET){}

	Socket(Socket&& socket)
	:FileDescriptor(std::move(socket)),mStatus(socket.mStatus){}

	virtual~Socket(){}

	void operator=(Socket&& socket){
		FileDescriptor::operator =(std::move(socket));
		mStatus = socket.mStatus;
	}

	/**
	 * sets the flag NON_BLOCKING of the socket descriptor
	 * @throws NetworkException, if an error occurs
	 */
	void enableNonBlockingMode();

	/**
	 * connects to an IP or hostname
	 * @param host - hostname or IPv4 , IPv6
	 * @param service - port or protocol
	 * @param throws NetworkException, if an network error occurs or the host cannot be reached
	 */
	void connect(const std::string& host, const std::string& service);

	/**
	 * binds to an IP or hostname
	 * @param host - hostname or IPv4 , IPv6
	 * @param service - port or protocol
	 * @throws NetworkException, if an network error occurs
	 */
	void bind(const std::string& host, const std::string& service);

	/**
	 * listens on the socket descriptor to accept incoming connection
	 * @param backlog - number of connections that will be stored if not accepted immediately
	 * @throws NetworkException, if an network error occurs or the host cannot be reached
	 */
	void listen(int backlog){
		if(::listen(mDescriptor,backlog) == -1){
			THROW_EXCEPTION(NetworkException, strerror(errno));
		}
	}

	/**
	 * Use this only in non-blocking mode!!!
	 * accepts all available connections
	 * @returns accepted sockets
	 * @throws NetworkException, if an network error occurs
	 */
	std::vector<Socket> acceptAll();

	/**
	 * Rather use this in blocking mode
	 * @returns the accepted socket
	 * @throws NetworkException, if an network error occurs
	 */
	Socket acceptSingle();

	void send(Buffer&);

	void receive(Buffer&);

	TrafficStatus getTrafficStatus()const{
	    return mStatus;
	}

	DISALLOW_COPY_AND_ASSIGN(Socket);

private:

	explicit Socket(Descriptor descriptor)
	:FileDescriptor(),mStatus(NOT_SET){
		mDescriptor = descriptor;
	}

	TrafficStatus mStatus;

};




} /* namespace Peak */

#endif /* SRC_SOCKET_H_ */
