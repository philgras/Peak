/*
 * UrlUnitTest.cpp
 *
 *  Created on: 20.02.2016
 *      Author: philgras
 */


#include "../src/Url.h"
#include "gtest/gtest.h"
#include <iterator>

TEST(UrlUnitTest, parsingTest){

	const char urlString[] = "/test/path/to/nothing3?number=1";

	Peak::Url urlObject;

	urlObject.parse(std::begin(urlString),std::end(urlString));

	ASSERT_STREQ(urlObject.getParameterValue("number")->c_str(),"1");

}

