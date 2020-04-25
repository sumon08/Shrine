cmake_minimum_required(VERSION 2.8.9)
project (test_exe)

#For the static library:
set ( PROJECT_LINK_LIBS libgtest.a libgtest_main.a  )
link_directories( /usr/lib )

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -pthread")

#Bring the headers
include_directories(.)
file(GLOB SOURCES_THIS "*.cpp")
add_executable(test_exe ${SOURCES_THIS})

target_link_libraries(test_exe ${PROJECT_LINK_LIBS} )

message("CMAKE_CXX_FLAGS is ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")