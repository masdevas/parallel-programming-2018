cmake_minimum_required(VERSION 3.12)
project(MPI_Task2_27)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DCHECK_TIME=1)

find_package(MPI REQUIRED)
find_package(OpenMP)

include_directories(include)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(MPI_Task2_27 main.cpp image.cpp png.cpp)
target_link_libraries(MPI_Task2_27 PUBLIC ${MPI_CXX_LIBRARIES})
if (OPENMP_FOUND)
    target_link_libraries(MPI_Task1_13 PUBLIC ${OpenMP_CXX_LIBRARIES})
endif()


