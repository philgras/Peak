/*
 * BufferUnitTest.cpp
 *
 *  Created on: 20.03.2016
 *      Author: philgras
 */


#include "Buffer.h"
#include "gtest/gtest.h"
#include "iterator"

using namespace Peak;

TEST(BufferUnitTest,StoragePreparation){

    constexpr size_t BYTES = 10;

    Buffer buffer;
    Buffer::iterator writingPosition;
    Buffer::const_iterator readingPosition;

    //[-,-,-,-,-,-,-,-,-,-]
    writingPosition = buffer.prepareStorage(BYTES);
    ASSERT_EQ(buffer.getCapacity(),BYTES);
    ASSERT_EQ(buffer.getCapacityUsed(),0);

    //[1,2,3,-,-,-,-,-,-,-]
    *writingPosition++ =  '1';
    *writingPosition++ =  '2';
    *writingPosition   =  '3';
    buffer.wrote(3);
    readingPosition = buffer.getReadingPosition();
    ASSERT_EQ(buffer.getCapacityUsed(),3);
    ASSERT_EQ(*readingPosition, '1');
    ASSERT_EQ(*(readingPosition+1), '2');
    ASSERT_EQ(*(readingPosition+2), '3');
    ASSERT_EQ(buffer.getCapacityUsed(),3);

    //[1,2,3,-,-,-,-,-,-,-]
    //       ^
    buffer.read(3);
    auto readingPositionNew = buffer.getReadingPosition();
    ASSERT_EQ(std::distance(readingPosition,readingPositionNew),3);
    ASSERT_EQ(buffer.getCapacityUsed(), 0);


    size_t capacity = buffer.getCapacity();
    writingPosition = buffer.prepareStorage(BYTES);
    ASSERT_EQ(buffer.getCapacity(),capacity);
    ASSERT_EQ(buffer.getCapacityUsed(), 0);
    ASSERT_EQ(*(buffer.getReadingPosition()),'1');

    //[2,3,-,-,-,-,-,-,-,-,-,-]
    buffer.wrote(3);
    buffer.read(1);
    writingPosition = buffer.prepareStorage(BYTES);
    ASSERT_EQ(buffer.getCapacityUsed(), 2);
    ASSERT_EQ(buffer.getCapacity(),BYTES + 2);
    ASSERT_EQ(*(buffer.getReadingPosition()),'2');

}
