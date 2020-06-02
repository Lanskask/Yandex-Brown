cmake_minimum_required(VERSION 3.15)
project(Yandex_Brown)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-long-long -pedantic")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")

add_subdirectory(W2_NAMESPACES_THIS)
add_subdirectory(W3_SMART_POINTERS)
add_subdirectory(W1_ASOC_CONTAINERS)
add_subdirectory(W4_SHARED_WEAK_POINTERS)

add_executable(little_tests little_tests.cpp)