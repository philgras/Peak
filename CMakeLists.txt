cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
project (Peak C CXX)
find_package(Threads)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU OR
	CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "-Wall -Wfatal-errors -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")

endif()

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/test)

set(CMAKE_BINARY_DIR "bin")

enable_testing()

add_library(url src/Url.cpp)
add_library(buffer src/Buffer.cpp)
add_library(socket src/Socket.cpp)
add_library(addressLookup src/AddressLookup.cpp)


set(GTEST_ROOT libs/googletest CACHE STRING "Path to the google test/mock framework.")

add_subdirectory(${GTEST_ROOT} ${CMAKE_BINARY_DIR}/gtest)

include_directories(SYSTEM ${GTEST_ROOT}/googletest/include
                           ${GTEST_ROOT}/googlemock/include)


add_executable(PeakTestsMain 
               test/PeakTestsMain.cpp
               test/UrlUnitTest.cpp
               test/BufferUnitTest.cpp)

target_link_libraries(PeakTestsMain gmock gmock_main gtest gtest_main)
target_link_libraries(PeakTestsMain url buffer)

#add_executable(Peak src/Peak.cpp)

add_test(NAME PeakTestsMain COMMAND PeakTestsMain)
