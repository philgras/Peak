/*
 * Buffer.h
 *
 *  Created on: 20.02.2016
 *      Author: philgras
 */

#ifndef SRC_BUFFER_H_
#define SRC_BUFFER_H_

#include <cassert>
#include <cstddef>
#include <vector>


namespace Peak {

class Buffer {
public:
    typedef unsigned char byte;
	typedef std::vector<byte>::iterator iterator;
	typedef std::vector<byte>::const_iterator const_iterator;

	Buffer()
	:mBuffer(),mReadingPosition(mBuffer.cbegin()),mEndOfData(mBuffer.begin()){

	}

	Buffer(Buffer&& buf)
	:mBuffer(std::move(buf.mBuffer)),mReadingPosition(buf.mReadingPosition),
	 mEndOfData(buf.mEndOfData){

	}

	~Buffer(){}


	/**
     * TODO: make it a InpuIterator instead of a RandomAccessIterator
     */
    iterator prepareStorage(size_t bytes);


    /**
     * Stores the a data range at the end of the buffer. If there is unused storage in the buffer the range will be stored.
     * Otherwise, new memory will be allocated.
     * Consider that calling load will invalidate all returned iterators!
     *
     * @param   begin, end describe a range of data that should be inserted
     *          begin, end must not point to a range contained by the buffer
     */
    template<typename InputIterator>
    void load(InputIterator begin, InputIterator end){

        size_t distance = std::distance(begin, end);
        auto iter = prepareStorage(std::distance(begin,end));

        assert(std::distance(iter,mBuffer.end()) >= std::distance(begin,end));

        for(;begin != end; ++begin, ++iter){
            *iter = *begin;
        }

        mEndOfData = iter;
    }

    /**
     * @param bytes -
     * @returns the new begin iterator of the data block in the buffer
     */
    const_iterator read(size_t bytes){
        assert(bytes <= getCapacityUsed());
        return mReadingPosition+=bytes;
    }

    /**
     *
     */
    iterator wrote(size_t bytes){
       assert(bytes <= static_cast<size_t>(std::distance(mEndOfData,mBuffer.end())));
       return mEndOfData+=bytes;
    }

    /**
     * @returns the size of the data block in the buffer
     */
    size_t getCapacityUsed()const{
        return std::distance(mReadingPosition,const_iterator(mEndOfData));
    }

    size_t getCapacity() const{
        return mBuffer.size();
    }

    const_iterator getReadingPosition() const{
        return mReadingPosition;
    }


private:


	std::vector<byte> mBuffer;
	const_iterator mReadingPosition;
	iterator mEndOfData;

};

} /* namespace Peak */

#endif /* SRC_BUFFER_H_ */
