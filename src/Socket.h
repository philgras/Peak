/*
 * Socket.h
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

#include "Common.h"
#include <string>
#include <vector>
#include <exception>
#include <cerrno>
#include <cstring>
#include <cstdint>
#include <unistd.h>

#include <sys/socket.h>


namespace Peak {

class SocketException : std::exception{

public:
	SocketException(const char* errorMsg, const char* file, const char* function, unsigned int line)
	:mErrorMsg(errorMsg),mFile(file),mFunction(function),mLine(line){

	}

	const char* getErrorMessage() const{
		return mErrorMsg;
	}

	const char* getSourceFileName()const{
		return mFile;
	}

	const char* getFunctionName()const{
		return mFunction;
	}

	unsigned int getLineNumber() const{
		return mLine;
	}

private:
	const char* mErrorMsg;
	const char* mFile;
	const char* mFunction;
	unsigned int mLine;

};

class Socket {
public:

	typedef int SocketDescriptor;
	static constexpr SocketDescriptor INVALID_SOCKET {-1};

	Socket()
	:mDescriptor(INVALID_SOCKET){

	}

	Socket(Socket&& socket)
	:mDescriptor(socket.mDescriptor){

		socket.mDescriptor 	= INVALID_SOCKET;


	}

	~Socket(){
		close();
	}

	void operator=(Socket&&);

	/**
	 * sets the flag NON_BLOCKING of the socket descriptor
	 * @throws SocketException, if an error occurs
	 */
	void enableNonBlockingMode();

	/**
	 * connects to an IP or hostname
	 * @param host - hostname or IPv4 , IPv6
	 * @param service - port or protocol
	 * @param throws SocketException, if an network error occurs or the host cannot be reached
	 */
	void connect(const std::string& host, const std::string& service);

	/**
	 * binds to an IP or hostname
	 * @param host - hostname or IPv4 , IPv6
	 * @param service - port or protocol
	 * @throws SocketException, if an network error occurs
	 */
	void bind(const std::string& host, const std::string& service);

	/**
	 * listens on the socket descriptor to accept incoming connection
	 * @param backlog - number of connections that will be stored if not accepted immediately
	 * @throws SocketException, if an network error occurs or the host cannot be reached
	 */
	void listen(int backlog){
		if(::listen(mDescriptor,backlog) == -1){
			THROW_EXCEPTION(SocketException, strerror(errno));
		}
	}

	/**
	 * Use this only in non-blocking mode!!!
	 * accepts all available connections
	 * @returns accepted sockets
	 * @throws SocketException, if an network error occurs
	 */
	std::vector<Socket> acceptAll();

	/**
	 * Rather use this in blocking mode
	 * @returns the accepted socket
	 * @throws SocketException, if an network error occurs
	 */
	Socket acceptSingle();

	void send(const Buffer&);

	void receive(Buffer&);

	void close(){
		if(mDescriptor != INVALID_SOCKET){
			::close(mDescriptor);
			mDescriptor = INVALID_SOCKET;
		}
	}

	DISALLOW_COPY_AND_ASSIGN(Socket);

private:

	explicit Socket(SocketDescriptor descriptor)
	:mDescriptor(descriptor){

	}

	SocketDescriptor mDescriptor;


};




} /* namespace Peak */

#endif /* SRC_SOCKET_H_ */
