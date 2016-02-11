/*
 * Module.h
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#ifndef SRC_MODULE_H_
#define SRC_MODULE_H_

namespace Peak {

class Module {
public:

	virtual ~Module(){}

	virtual void init() = 0;
	virtual void execute() = 0;
	virtual void cleanup() = 0;

};

} /* namespace Peak */

#endif /* SRC_MODULE_H_ */
