/*
 * Buffer.cpp
 *
 *  Created on: 20.02.2016
 *      Author: philgras
 */

#include "Buffer.h"
#include <iterator>

namespace Peak {

Buffer::iterator Buffer::prepareStorage(size_t bytes){


    /*
     * [--herecomesthedata----] will be transformed to [herecomesthedata------]
     */
    if(std::distance(mBuffer.cbegin(),mReadingPosition) >0){
        auto iterator = mBuffer.begin();
        for(;mReadingPosition != mEndOfData; ++mReadingPosition, ++iterator){
            *iterator = *mReadingPosition;
        }
        mReadingPosition = mBuffer.cbegin();
        mEndOfData = iterator;
    }


    /*
     * [herecomesthedata------] --> [herecomesthedata----------------------]
     */
    assert(std::distance(mEndOfData,mBuffer.end()) >= 0);
    size_t distance = std::distance(mEndOfData,mBuffer.end());
    if(distance < bytes){

       size_t dataSize = getCapacityUsed();

       //just remove this as fast as possible because it is killing performance unnecessarily
       mBuffer.resize(dataSize + bytes);

       mReadingPosition = mBuffer.cbegin();
       mEndOfData = mBuffer.begin() + dataSize;

    }

    return mEndOfData;
}

} /* namespace Peak */
