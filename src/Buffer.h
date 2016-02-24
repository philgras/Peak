/*
 * Buffer.h
 *
 *  Created on: 20.02.2016
 *      Author: philgras
 */

#ifndef SRC_BUFFER_H_
#define SRC_BUFFER_H_

#include <vector>

namespace Peak {

class Buffer {
public:

	typedef std::vector<char>::iterator::pointer iterator;
	typedef std::vector<char>::const_iterator::pointer const_iterator;

	Buffer();
	~Buffer();




private:

	std::vector<char> mBuffer;

};

} /* namespace Peak */

#endif /* SRC_BUFFER_H_ */
