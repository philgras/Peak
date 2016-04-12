/*
 * DynamicArray.h
 *
 *  Created on: 24.03.2016
 *      Author: philgras
 */

#ifndef SRC_DYNAMICARRAY_H_
#define SRC_DYNAMICARRAY_H_

#include <utility>
#include <algorithm>
#include <cstddef>

namespace Peak {


template<typename T>
class DynamicArray {
public:

	typedef T* iterator;
	typedef const T* const_iterator;
	typedef T& reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef long difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T value_type;

	DynamicArray()
	:mArray(nullptr),mSize(0){}

	explicit DynamicArray(size_type size)
	:mArray(size == 0 ? nullptr : new T[size]),mSize(size){}

	DynamicArray(const DynamicArray<T>& array)
	:DynamicArray(array.mSize){
		if(mArray != nullptr)
			std::copy_n(array.mArray,mSize,mArray);
	}

	DynamicArray(DynamicArray<T>&& array)
	:DynamicArray(){
		swap(array);
	}

	DynamicArray<T>& operator=(const DynamicArray<T>& array){
		//copy and swap principle
		DynamicArray newArray(array);
		swap(newArray);
		return *this;
	}

	void operator=(DynamicArray<T>&& array){
		swap(array);
	}

	virtual ~DynamicArray(){
		if(mArray != nullptr)
			delete [] mArray;

	}

	iterator begin(){
		return mArray;
	}

	const_iterator cbegin()const{
		return mArray;
	}

	iterator end(){
		return mArray + mSize;
	}

	const_iterator cend()const {
		return mArray;
	}

	size_type size()const{
		return mSize;
	}

	bool empty()const{
		return mSize == 0;
	}

	void swap(DynamicArray<T>& array){
		std::swap(mArray,array.mArray);
		std::swap(mSize,array.mSize);
	}

	reference operator[](size_type z){
		return mArray[z];
	}

	const_reference operator[](size_type z) const{
		return mArray[z];
	}

	void resize(size_type size){
		if(size != mSize){
			pointer newArray = size == 0 ? nullptr : new T[size];
			if(mArray != nullptr){
				if(newArray != nullptr){
					std::copy_n(mArray, size < mSize ? size : mSize, newArray);
				}
				delete [] mArray;
			}
			mArray = newArray;
			mSize = size;
		}
	}

	pointer getStorage(){
		return mArray;
	}


	const_pointer getConstStorage()const{
		return mArray;
	}


private:


	pointer mArray;
	size_type mSize;

};

} /* namespace Peak */

#endif /* SRC_DYNAMICARRAY_H_ */
