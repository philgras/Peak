/*
 * Log.h
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#ifndef SRC_LOG_H_
#define SRC_LOG_H_

#include <string>

namespace Peak {

class Log {
public:

	enum class LogLevel{
		FATAL,
		ERROR,
		WARNING,
		INFO,
		DEBUG
	};


	Log(const std::string& filename);
	~Log();

	void trace(LogLevel logLevel, const char* message, const char* file,
				const char* function_name, int line);

private:



};

} /* namespace Peak */

#endif /* SRC_LOG_H_ */
