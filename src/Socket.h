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
#include <cstdint>
#include <unistd.h>


namespace Peak {

class Socket {
public:

	typedef int SocketDescriptor;

	static const SocketDescriptor INVALID_SOCKET {-1};
	static const char * DEFAULT_IP;
	static const uint16_t DEFAULT_PORT {0};

	Socket()
	:mDescriptor(INVALID_SOCKET), mIsListening(false),
	 mIp(DEFAULT_IP),mPort(DEFAULT_PORT){

	}

	Socket(Socket&& socket)
	:mDescriptor(socket.mDescriptor), mIsListening(socket.mIsListening),
	 mIp(socket.mIp),mPort(socket.mPort){

		socket.mDescriptor 	= INVALID_SOCKET;
		socket.mIsListening = false;
		socket.mIp 			= DEFAULT_IP;
		socket.mPort 		= DEFAULT_PORT;

	}

	~Socket(){
		close();
	}

	void operator=(Socket&&);

	void enableNonBlocking();

	void write(const std::vector&);

	std::vector read();

	void bind(const std::string& port, const std::string& ip);
	void bind(const std::string& port);

	Socket&& accept();

	void listen();

	void close();

	std::uint16_t getPort() const { return mPort; }

	const std::string& getIp() const { return mIp; }

	SocketDescriptor getSocketDescriptor() { return mDescriptor; }

	bool isListening() const { return mIsListening; }

	DISALLOW_COPY_AND_ASSIGN(Socket);

private:

	static void closeSocketDescriptor(SocketDescriptor socket){
		::close(socket);
	}

	SocketDescriptor mDescriptor;
	bool mIsListening;
	std::string mIp;
	std::uint16_t mPort;

};




} /* namespace Peak */

#endif /* SRC_SOCKET_H_ */
