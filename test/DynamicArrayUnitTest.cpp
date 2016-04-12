/*
 * DynamicArrayUnitTest.cpp
 *
 *  Created on: 28.03.2016
 *      Author: philgras
 */

#include <gtest/gtest.h>

#include "DynamicArray.h"
#include <iterator>


TEST(DynamicArrayUnitTest, constructors){

	Peak::DynamicArray<int> standardArray;
	Peak::DynamicArray<int> presizedArray1(10);
	Peak::DynamicArray<int> presizedArray2(20);

	ASSERT_EQ(standardArray.size(),0);
	ASSERT_EQ(presizedArray1.size(),10);
	ASSERT_EQ(presizedArray2.size(),20);

	//copy constructor
	presizedArray1[0] = 1;
	Peak::DynamicArray<int> copiedArray(presizedArray1);
	ASSERT_EQ(presizedArray1[0],copiedArray[0]);
	copiedArray[0] = 2;
	ASSERT_NE(presizedArray1[0],copiedArray[0]);

	ASSERT_EQ(copiedArray.size(),10);
	ASSERT_EQ(presizedArray1.size(),10);
	ASSERT_EQ(copiedArray.size(),	std::distance(copiedArray.begin(),copiedArray.end()));
	ASSERT_EQ(presizedArray1.size(),std::distance(presizedArray1.begin(),presizedArray1.end()));

	//move constructor
	auto dataptr = presizedArray1.getStorage();
	Peak::DynamicArray<int> moveArray(std::move(presizedArray1));
	ASSERT_EQ(moveArray.size(),10);
	ASSERT_EQ(presizedArray1.size(),0);
	ASSERT_EQ(moveArray[0],1);
	ASSERT_EQ(moveArray.getStorage(),dataptr);
	ASSERT_EQ(presizedArray1.getStorage(),nullptr);

}

TEST(DynamicArrayUnitTest, assigning){

	Peak::DynamicArray<int> array1(10);
	Peak::DynamicArray<int> array2(5);

	array1[0]=1;
	array2[0]=2;

	array2 = array1;

	ASSERT_EQ(true,true);

}

TEST(DynamicArrayUnitTest, behaviorWhenEmpty){

	Peak::DynamicArray<int> array1;
	Peak::DynamicArray<int> array2(0);

	EXPECT_EQ(array1.size(),0);
	EXPECT_EQ(array2.size(),0);

	EXPECT_EQ(array1.empty(),true);
	EXPECT_EQ(array2.empty(),true);

	EXPECT_EQ(array1.cbegin(),array1.cend());
	EXPECT_EQ(array2.cbegin(),array2.cend());

	EXPECT_EQ(array1.begin(),array1.end());
	EXPECT_EQ(array2.begin(),array2.end());

	EXPECT_EQ(array1.getStorage(),nullptr);
	EXPECT_EQ(array2.getStorage(),nullptr);

	Peak::DynamicArray<int> moveArray(std::move(array1));
	EXPECT_EQ(array1.getStorage(),nullptr);
	EXPECT_EQ(moveArray.getStorage(),nullptr);

}



TEST(DynamicArrayUnitTest, resizing){

	Peak::DynamicArray<int> array;
	ASSERT_EQ(true,true);

}
