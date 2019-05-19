cmake_minimum_required(VERSION 3.13)
project(Parallel_TBB)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined,address,leak")

find_library(tbb tbb)

include_directories(include)

add_subdirectory(src)
