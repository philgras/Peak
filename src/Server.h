/*
 * Server.h
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#ifndef SRC_SERVER_H_
#define SRC_SERVER_H_

#include "Connection.h"
#include "Service.h"
#include <map>
#include <utility>
#include <string>
#include <thread>
#include <vector>

namespace Peak {

class Server {
public:

	~Server();

	int start();
	int shutdown();

	Module& getModuleByName(const std::string& name){
		return mModuleMap.at(name);
	}

	Service& getServiceByName(const std::string& name){
		return mServiceMap.at(name);
	}

	Service& addService(Service& service){
		return *(mServiceMap.insert(std::pair<std::string,Service>(service.getName(),service)).first);
	}

	static Server& getInstance(){ return mServer; }

private:
	Server();

	void loadServicesIntoMap();
	void startServices();

	Server mServer;
	std::map<std::string,Service> mServiceMap;
	std::map<std::string,Module> mModuleMap;
	std::vector<std::thread> mThreadList;

};

} /* namespace Peak */

#endif /* SRC_SERVER_H_ */
