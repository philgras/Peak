cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
project (Peak C CXX)
find_package(Threads REQUIRED)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU OR
	CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "-Wall -Wfatal-errors -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")

endif()

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/test)

set(CMAKE_BINARY_DIR "bin")

#rapidjson
set(RAPIDJSON_ROOT libs/rapidjson CACHE STRING "Path to rapidJSON.")

add_subdirectory(${RAPIDJSON_ROOT} ${CMAKE_BINARY_DIR}/rapidjson)

include_directories(SYSTEM ${RAPIDJSON_ROOT}/include)

add_library(url src/Url.cpp)
add_library(buffer src/Buffer.cpp)
add_library(socket src/Socket.cpp)
add_library(addressLookup src/AddressLookup.cpp)
add_library(service src/Service.cpp)
add_library(eventObserver src/EventObserver.cpp)
add_library(server src/Server.cpp)

target_link_libraries(socket buffer addressLookup)
target_link_libraries(service socket)
target_link_libraries(server service eventObserver ${CMAKE_THREAD_LIBS_INIT})

enable_testing()

#google test
set(GTEST_ROOT libs/googletest CACHE STRING "Path to the google test/mock framework.")

add_subdirectory(${GTEST_ROOT} ${CMAKE_BINARY_DIR}/gtest)

include_directories(SYSTEM ${GTEST_ROOT}/googletest/include
                           ${GTEST_ROOT}/googlemock/include)


add_executable(PeakTestsMain 
               test/PeakTestsMain.cpp
               test/UrlUnitTest.cpp
               test/BufferUnitTest.cpp
               test/DynamicArrayUnitTest.cpp)

target_link_libraries(PeakTestsMain gmock gmock_main gtest gtest_main)
target_link_libraries(PeakTestsMain url buffer)

add_executable(Peak src/Peak.cpp)
target_link_libraries(Peak server)

add_test(NAME PeakTestsMain COMMAND PeakTestsMain)
