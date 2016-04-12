/*
 * Log.h
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#ifndef SRC_LOG_H_
#define SRC_LOG_H_

#include <string>
#include <iostream>
#include <fstream>
#include <mutex>
#include <ctime>

#define LOG_DEBUG(log, msg) 	log.trace(Peak::LogLevel::DEBUG, msg,		\
									__FILE__, __func__ , __LINE__)

#define LOG_INFO(log, msg)  	log.trace(Peak::LogLevel::INFO, msg,		\
									__FILE__, __func__ , __LINE__)

#define LOG_WARNING(log, msg) 	log.trace(Peak::LogLevel::WARNING, msg,		\
									__FILE__, __func__ , __LINE__)

#define LOG_ERROR(log, msg) 	log.trace(Peak::LogLevel::ERROR,msg,		\
									__FILE__, __func__ , __LINE__)

#define LOG_FATAL(log, msg) 	log.trace(Peak::LogLevel::FATAL,msg,		\
									__FILE__, __func__ , __LINE__)


namespace Peak {

enum class LogLevel{
		FATAL = 0,
		ERROR = 1,
		WARNING = 2,
		INFO = 3,
		DEBUG = 4
	};

const char *const LogLevelStrings[] = {

		"FATAL",
		"ERROR",
		"WARNING",
		"INFO",
		"DEBUG"
};

class Log {
public:

	Log(const std::string& fileName, LogLevel level = LogLevel::DEBUG)
	:mLevel(level),mFileName(fileName),mLogOutput(fileName),mLogMutex(){

	}

	~Log(){
		close();
	}

	void setLogLevel(LogLevel level){
		mLevel = level;
	}

	LogLevel getLogLevel() const {
		return mLevel;
	}

	void trace(LogLevel level, const char* msg, const char* sourceFile,
							const char* function, int line){

		if(level <= mLevel){
			std::lock_guard<std::mutex> guard(mLogMutex);

			std::cout	<<"["<<LogLevelStrings[static_cast<int>(level)]<<"] "
						<<" Timestamp: "<<time(NULL)
						<<" File: "<<sourceFile
						<<" Line: "<<line
						<<" Message: "<<msg<<'\n';
			mLogOutput.flush();
		}

	}


	void trace(LogLevel level, const std::string& msg, const char* sourceFile,
			const char* function, int line){
		trace(level,msg.c_str(),sourceFile,function,line);
	}

	void close(){
		if(mLogOutput.is_open()){
			mLogOutput.flush();
			mLogOutput.close();
		}
	}


private:

	LogLevel mLevel;
	std::string mFileName;
	std::ofstream mLogOutput;
	std::mutex mLogMutex;

};

} /* namespace Peak */

#endif /* SRC_LOG_H_ */
