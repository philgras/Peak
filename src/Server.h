/*
 * Server.h
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#ifndef SRC_SERVER_H_
#define SRC_SERVER_H_

#include "Connection.h"
#include "EventObserver.h"
#include "Service.h"
#include "Log.h"
#include "Module.h"
#include <map>
#include <utility>
#include <string>
#include <thread>
#include <vector>
#include <atomic>

namespace Peak {


class Server {
public:

	static Server& getInstance(){ return sServer; }

	~Server()=default;

	void start();
	void shutdown();

//	Module& getModuleByName(const std::string& name){
//		return mModuleMap.at(name);
//	}
//
//	Service& getServiceByName(const std::string& name){
//		return mServiceMap.at(name);
//	}
//
//	Service& addService(Service& service){
//		return *(mServiceMap.insert(std::pair<std::string,Service>(service.getName(),service)).first);
//	}

	std::string getInfo();

	bool isRunning() const{
		return mIsRunning.load();
	}

	EventObserver& getEventObserver(){return mObserver;}


private:
	static void workerRoutine();
	static Server sServer;

	Server()
	:mIsRunning(false),mLog("PeakServerLog.log"),mObserver(),
	 mServiceMap(),mModuleMap(),mThreadList(){

	}

	void loadServicesIntoMap();
	void startServices();

	std::atomic_bool mIsRunning;
	Log mLog;
	EventObserver mObserver;
	std::map<std::string,Service> mServiceMap;
	std::map<std::string,std::string> mModuleMap;
	std::vector<std::thread> mThreadList;

};

} /* namespace Peak */

#endif /* SRC_SERVER_H_ */
