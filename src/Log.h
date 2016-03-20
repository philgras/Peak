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
		FATAL,
		ERROR,
		WARNING,
		INFO,
		DEBUG
	};

const char* LogLevelStrings[]{

		"FATAL",
		"ERROR",
		"WARNINGS",
		"INFO",
		"DEBUG"
};

class Log {
public:

	Log(const std::string& fileName, LogLevel level = LogLevel::DEBUG)
	:mLevel(level),mFileName(fileName),mLogOutput(fileName){

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
			mLogOutput	<<"["<<LogLevelStrings[level]<<"] "
						<<" Timestamp: "<<time(NULL)
						<<" Message: "<<msg
						<<" File: "<<sourceFile
						<<" Line: "<<line<<'\n';
		}

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

};

} /* namespace Peak */

#endif /* SRC_LOG_H_ */
