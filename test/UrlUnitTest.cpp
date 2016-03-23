/*
 * UrlUnitTest.cpp
 *
 *  Created on: 20.02.2016
 *      Author: philgras
 */


#include "Url.h"
#include "gtest/gtest.h"
#include <iterator>
#include <string>
#include <vector>
#include <map>
#include <iostream>



TEST(UrlUnitTest, parsingNormalUrl){

    const std::string urlNormal = "/test/path/to/nothing3?para1=val1&para2=val2&para1=val2";

	/*
	 * Expected parsing results:
	 *
	 * #####urlNormal:
	 *
	 * Path: 		"/test/path/to/nothing3"
	 * Parameters:
	 * 				Name: "para1" 	Value(s): "val1","val2"
	 * 				Name: "para2"	Value(s): "val2"
	 */

	const std::string* single_value = nullptr;
	Peak::Url::ParameterRange multiple_values;
	const std::string path 			= "/test/path/to/nothing3";
	const std::string paraNormal1 	= "para1";
	const std::string paraNormal2 	= "para2";
	const std::string valueNormal1 	= "val1";
	const std::string valueNormal2 	= "val2";
	const std::string random  		= "abcdefghijklmnop";

	Peak::Url url;

	//************check urlNormal*****************

	url.parse(urlNormal);

	//check getPath

	EXPECT_EQ(path, url.getPath());

	//check getParameterValue

	EXPECT_EQ(nullptr,url.getParameterValue(random));

	single_value = url.getParameterValue(paraNormal1);
	EXPECT_TRUE(valueNormal1 == *single_value ||
				valueNormal2 == *single_value);
	EXPECT_EQ(valueNormal2, *url.getParameterValue(paraNormal2));

	//check getParameterValues

	multiple_values = url.getParameterValues(paraNormal1);

	/**
	 * horrible interface
	 * TODO: need redesign
	 */
	auto begin = multiple_values.first;
	EXPECT_TRUE(begin->second == valueNormal1 || begin->second == valueNormal2);
	++begin;
	EXPECT_TRUE(((begin->second == valueNormal1) || (begin->second == valueNormal2) ));
	++begin;
	EXPECT_EQ(begin, multiple_values.second);

	EXPECT_EQ(url.getAllParameterValues().size(),3);

}

TEST(UrlUnitTest, parsingStrangeUrl){

	const std::string urlStrange = "/test/path/to/nothing3?para1=val1=val2==val3&=&&para3=&==&";

	/*
	 * Expected parsing results:
	 *
	 *
	 * #####urlStrange:
	 *
	 * Path: 		"/test/path/to/nothing3"
	 * Parameters:
	 * 				Name: "para1" 	Value(s): "val1=val2==val3"
	 * 				Name: ""		Value(s): "","="
	 * 				Name: "&para3"	Value(s): ""
	 */

	Peak::Url::ParameterRange multiple_values;
	const std::string path 			= "/test/path/to/nothing3";
	const std::string paraStrange1 	= "para1";
	const std::string paraStrange2 	= "";
	const std::string paraStrange3 	= "&para3";
	const std::string valueStrange1 = "val1=val2==val3";
	const std::string valueStrange2 = "=";
	const std::string valueStrange3	= "";
	const std::string random  		= "abcdefghijklmnop";

	Peak::Url url;

	//************check urlStrange****************

	url.parse(urlStrange);

	//check getPath

	EXPECT_EQ(path, url.getPath());

	//check getParameterValue

	EXPECT_EQ(nullptr,url.getParameterValue(random));
	EXPECT_EQ(valueStrange1, *url.getParameterValue(paraStrange1));

	//check getParameterValues

	multiple_values = url.getParameterValues(paraStrange2);
	auto begin = multiple_values.first;
	EXPECT_TRUE(begin->second == valueStrange2 || begin->second == valueStrange3 );
	++begin;
	EXPECT_TRUE(begin->second == valueStrange2 || begin->second == valueStrange3 );
	++begin;
	EXPECT_EQ(begin, multiple_values.second);

	//check getAllParameterValues

	EXPECT_EQ(url.getAllParameterValues().size(),4);

}

