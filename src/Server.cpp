/*
 * Server.cpp
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#include "Server.h"
#include "Socket.h"
#include "Connection.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/error/en.h"
#include <sstream>
#include <cstdio>

using namespace rapidjson;

namespace Peak {

Server Server::sServer;

std::string Server::getInfo(){

	std::stringstream sstream;

	sstream<<"Running: "<< isRunning()<<"\n"
			<<"Threads: 1 + "<<mThreadList.size()<<"\n"
			<<"Services: "<< mServiceMap.size()<<"\n"
			<<"####################################\n";
	for(auto iter = mServiceMap.begin(); iter != mServiceMap.end(); ++iter){
		sstream<<"Name: "<<iter->second.getName()<<" Port: "<<iter->second.getPort()<<"\n";
	}

	sstream<<"####################################\n";

	return sstream.str();
}

void Server::start(){

	//TODO: catch exceptions and handle failure

	LOG_INFO(mLog,"Starting the event observer...");
	mObserver.start();


	LOG_INFO(mLog,"Loading services...");
	loadServicesIntoMap();
	startServices();

	sServer.mIsRunning.store(true);

	LOG_INFO(mLog,"Running thread(s)...");
	unsigned int concurrency = std::thread::hardware_concurrency();
	if(concurrency == 0){

		LOG_WARNING(mLog,"Unable to detect the number of concurrent threads. Starting in single thread mode...");
		concurrency = 1;

		Server::workerRoutine();

	}else{


		for(unsigned int i = 0; i < concurrency-1; ++i){
			mThreadList.push_back(std::thread(Server::workerRoutine));
		}
	}
}

void Server::shutdown(){
	if(isRunning()){

		LOG_INFO(mLog,"Shutting server down...");

		LOG_INFO(mLog,"Terminating the event loop...");
		sServer.mIsRunning.store(false);
		mObserver.stop();

		LOG_INFO(mLog,"Stopping services...");
		mServiceMap.clear();

		LOG_INFO(mLog,"Joining threads...");
		for(std::thread& thread : mThreadList){
			if(thread.get_id() != std::this_thread::get_id()){
				thread.join();
			}
		}
		mThreadList.clear();
		LOG_INFO(mLog,"All threads terminated...");


	}else{
		LOG_INFO(mLog,"Failed to shutdown the server because it is not running...");
	}
}


void Server::startServices(){

	for(auto iterator = mServiceMap.begin(); iterator!= mServiceMap.end();++iterator){

		Service& service = iterator->second;

		if(service.isActive()){
			try{

				Socket socket;
				socket.bind("127.0.0.1",service.getPort());
				socket.enableNonBlockingMode();
				socket.listen(20);
				service.setListenerSocket(std::move(socket));
				mObserver.addObservable(service);

			}catch(const BaseException& exception){
				LOG_ERROR(mLog,exception.getErrorMessage());
			}
		}
	}

}


void Server::loadServicesIntoMap(){

	const char* SERVICES_JSON_FILE = "../services.json";
	const char* JSON_SERVICE_NAME = "name";
	const char* JSON_SERVICE_DESC = "description";
	const char* JSON_SERVICE_DIRECTORY = "directory-path";
	const char* JSON_SERVICE_URL_PATTERN = "url-pattern";
	const char* JSON_SERVICE_PORT = "port";
	const char* JSON_SERVICE_ACTIVE = "active";

	std::stringstream errorStream;
	std::FILE* file =std::fopen(SERVICES_JSON_FILE, "rb");

	if(!file){
		errorStream<<"Failed to open JSON-file " << SERVICES_JSON_FILE <<".";
		LOG_ERROR(mLog, errorStream.str());
	}else{

		char buffer[1024];
		FileReadStream inputStream(file,buffer, sizeof(buffer));
		Document d;
		d.ParseStream<0, UTF8<>,FileReadStream>(inputStream);

		if(d.HasParseError() || ! d.IsArray()){

			errorStream<<"Error while parsing " << SERVICES_JSON_FILE<<": "<<GetParseError_En(d.GetParseError())<<".";
			LOG_ERROR(mLog, errorStream.str());

		}else{
			bool errors = false;

			for(Value::ConstValueIterator iter = d.GetArray().Begin();
					iter != d.GetArray().End();++iter){

				if(iter->IsObject()
				&& iter->HasMember(JSON_SERVICE_NAME) 		 && (*iter)[JSON_SERVICE_NAME].IsString()
				&& iter->HasMember(JSON_SERVICE_DESC) 		 && (*iter)[JSON_SERVICE_DESC].IsString()
				&& iter->HasMember(JSON_SERVICE_DIRECTORY) 	 && (*iter)[JSON_SERVICE_DIRECTORY].IsString()
				&& iter->HasMember(JSON_SERVICE_URL_PATTERN) && (*iter)[JSON_SERVICE_URL_PATTERN].IsString()
				&& iter->HasMember(JSON_SERVICE_PORT) 		 && (*iter)[JSON_SERVICE_PORT].IsString()
				&& iter->HasMember(JSON_SERVICE_ACTIVE) 	 && (*iter)[JSON_SERVICE_ACTIVE].IsBool()){

					Service service((*iter)[JSON_SERVICE_NAME].GetString(),(*iter)[JSON_SERVICE_DESC].GetString(),
							(*iter)[JSON_SERVICE_URL_PATTERN].GetString(), (*iter)[JSON_SERVICE_DIRECTORY].GetString(),
							(*iter)[JSON_SERVICE_PORT].GetString(),(*iter)[JSON_SERVICE_ACTIVE].GetBool());

					mServiceMap.insert(std::make_pair((*iter)[JSON_SERVICE_NAME].GetString(),std::move(service)));

				}else{
					errors = true;
				}
			}

			if(errors){
				LOG_WARNING(mLog,"Not all services could be loaded correctly due to parsing errors.");
			}
		}
	}
}

void Server::workerRoutine(){

	std::stringstream errorStream;
	DynamicArray<EventObserver::Event> events(10);
	size_t number = 0;

	try{

		while(sServer.isRunning()){

				number = sServer.mObserver.observeForEvents(events);

				for(size_t i = 0; i < number; ++i){
					static_cast<Observable*>(events[i].data.ptr)->handleEvents(events[i].events);
				}

		}

	}catch(const EventException& exception){
		errorStream<<"Stopped Peak server because of an event error: "<<exception.getErrorMessage();
		LOG_FATAL(sServer.mLog,errorStream.str());
		sServer.shutdown();
	}catch(const NetworkException& exception){
		errorStream<<"Stopped Peak server because of a not handled network error: "<<exception.getErrorMessage();
		LOG_FATAL(sServer.mLog,errorStream.str());
		sServer.shutdown();
	}catch(const std::exception& exception){
		errorStream<<"Stopped Peak server because of an unexpected error: "<<exception.what();
		LOG_FATAL(sServer.mLog,errorStream.str());
		sServer.shutdown();
	}
}


} /* namespace Peak */
