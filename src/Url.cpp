/*
 * Url.cpp
 *
 *  Created on: 20.02.2016
 *      Author: philgras
 */

#include "Url.h"


namespace Peak {



void Url::parseInternal(const char* begin, const char* end){

	const char* iter = begin;
	std::string parameter , value;
	bool parsingParameter = true;

	mParameters.clear();

	for(;*iter != '?' && iter != end; ++iter);

	mPath.assign(begin,iter);

	if(iter != end){

		const char* firstLetter = ++iter;
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
