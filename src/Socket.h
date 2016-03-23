/*
 * Socket.h
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

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

class Socket {
public:

	typedef int SocketDescriptor;
	static constexpr SocketDescriptor INVALID_SOCKET = -1;
	static constexpr size_t BUFFER_SIZE = 8192;

	enum TrafficStatus{
	  NOT_SET,
	  SEND_WAIT,
	  RECV_WAIT,
	  CLOSED_BY_PEER
	};

	Socket()
	:mDescriptor(INVALID_SOCKET),mStatus(NOT_SET){

	}

	Socket(Socket&& socket)
	:mDescriptor(socket.mDescriptor),mStatus(socket.mStatus){

		socket.mDescriptor 	= INVALID_SOCKET;

	}

	~Socket(){
		close();
	}

	void operator=(Socket&&);

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

	void close(){
		if(mDescriptor != INVALID_SOCKET){
			::close(mDescriptor);
			mDescriptor = INVALID_SOCKET;
		}
	}


	SocketDescriptor getSocketDescriptor() const{
	    return mDescriptor;
	}

	TrafficStatus getTrafficStatus()const{
	    return mStatus;
	}

	DISALLOW_COPY_AND_ASSIGN(Socket);

private:

	explicit Socket(SocketDescriptor descriptor)
	:mDescriptor(descriptor),mStatus(NOT_SET){

	}

	SocketDescriptor mDescriptor;
	TrafficStatus mStatus;

};




} /* namespace Peak */

#endif /* SRC_SOCKET_H_ */
