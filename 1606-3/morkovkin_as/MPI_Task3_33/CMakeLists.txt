cmake_minimum_required(VERSION 3.12)
project(MPI_Task3_33)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DCHECK_TIME=1)

find_package(MPI REQUIRED)
find_package(OpenMP)

include_directories(include)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(MPI_Task3_33 main.cpp image.cpp png.cpp pixel.cpp)
target_link_libraries(MPI_Task3_33 PUBLIC ${MPI_CXX_LIBRARIES})
if (OPENMP_FOUND)
    target_link_libraries(MPI_Task3_33 PUBLIC ${OpenMP_CXX_LIBRARIES})
endif()


