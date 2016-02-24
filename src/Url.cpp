/*
 * Url.cpp
 *
 *  Created on: 20.02.2016
 *      Author: philgras
 */

#include "Url.h"


namespace Peak {


void Url::parse(Buffer::const_iterator begin, Buffer::const_iterator end){

	Buffer::const_iterator iter = begin;
	std::string parameter , value;

	bool parsingParameter = true;

	for(;*iter != '?' && iter != end; ++iter);

	mPath.assign(begin,iter);

	if(iter != end){

		Buffer::const_iterator firstLetter = ++iter;
		for(;iter != end; ++iter){
			if(parsingParameter){
				if(*iter == '='){
					parameter.assign(firstLetter,iter);
					parsingParameter = false;
					firstLetter = iter+1;
				}
			}else{
				if(*iter == '&'){
					value.assign(firstLetter, iter);

					mParameters.insert(
							std::make_pair(std::move(parameter),
									std::move(value)));

					parsingParameter = true;
					firstLetter = iter + 1;
				}
			}
		}

		if (!parsingParameter) {
			value.assign(firstLetter, iter);
			mParameters.insert(
					std::make_pair(std::move(parameter), std::move(value)));
		}

	}

}

}
