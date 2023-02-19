cmake_minimum_required(VERSION 3.24)
project(khw1)

set(CMAKE_CXX_STANDARD 23)

add_executable(khw1 main.cpp sorters.h sorters.cpp heapsort.h sort_tester.cpp sort_tester.h)
