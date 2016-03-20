/*
 * PeakCommon.h
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_


#define DISALLOW_COPY_AND_ASSIGN(class_name) 				\
		class_name(const class_name&) = delete; 			\
		class_name& operator=(const class_name&) = delete

#define THROW_EXCEPTION(class_name,msg)	\
		throw class_name((msg),__FILE__, __func__ , __LINE__)

#endif /* SRC_COMMON_H_ */
