/*
 * Buffer.h
 *
 *  Created on: 20.02.2016
 *      Author: philgras
 */

#ifndef SRC_BUFFER_H_
#define SRC_BUFFER_H_

#include <vector>
#include <cassert>

namespace Peak {

class Buffer {
public:

	typedef std::vector<char>::iterator iterator;
	typedef std::vector<char>::const_iterator const_iterator;

	explicit Buffer(size_t capacity)
	:mBuffer(capacity),mBeginOfData(mBuffer.cbegin()),mEndOfData(mBeginOfData){

	}

	Buffer(Buffer&& buf)
	:mBuffer(std::move(buf.mBuffer)),mBeginOfData(buf.mBeginOfData),mEndOfData(buf.mEndOfData){

	}

	~Buffer(){}


	/**
	 * Stores the a data range at the end of the buffer. If there is unused storage in the buffer the range will be stored.
	 * Otherwise, new memory will be allocated.
	 * Consider that calling load will invalidate all returned iterators!
	 *
	 * @param 	begin, end describe a range of data that should be inserted
	 * 			begin, end must not point to a range contained by the buffer
	 */
	template<typename InputIterator>
	void load(InputIterator begin, InputIterator end){

		size_t distance = std::distance(begin, end);

		//check if there are unused data blocks before the current reading position
		if(distance > std::distance(mEndOfData,mBuffer.cend())
			&& std::distance(mBuffer.cbegin(),mBeginOfData) > 0){

			auto beginOfBuffer = mBuffer.begin();
			for(;mBeginOfData!= mEndOfData; ++mBeginOfData, ++beginOfBuffer){
				*beginOfBuffer = *mBeginOfData;
			}
			mBeginOfData = mBuffer.cbegin();
			mEndOfData = beginOfBuffer;
		}

		for(;mEndOfData != mBuffer.end() && begin != end; ++mEndOfData, ++begin){
			*mEndOfData = *begin;
		}

		if(begin != end){
			mBuffer.insert(mBuffer.end(),begin, end);
			mEndOfData = mBuffer.end();
		}
	}

	/**
	 * @returns the size of the data block in the buffer
	 */
	size_t getDataSize()const{
		return std::distance(mBeginOfData,mEndOfData);
	}

	/**
	 * @param bytes -
	 * @returns the new begin iterator of the data block in the buffer
	 */
	const_iterator read(size_t bytes){
		assert(bytes <= getDataSize());
		return mBeginOfData+=bytes;
	}

	const_iterator getBeginOfData() const{
		return mBeginOfData;
	}

	const_iterator getEndOfData() const{
		return mEndOfData;
	}

private:

	std::vector<char> mBuffer;
	const_iterator mBeginOfData;
	const_iterator mEndOfData;

};

} /* namespace Peak */

#endif /* SRC_BUFFER_H_ */
