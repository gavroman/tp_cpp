cmake_minimum_required(VERSION 3.10)

project(gtests.out)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage -ftest-coverage")
set(CMAKE_C_FLAGS "--coverage -ftest-coverage")

include_directories(project/naive project/parallel)

set(NAIVE_DIR project/naive)
set(PARALLEL_DIR project/parallel)

set(NAIVE_LIB_SOURCE_FILES ${NAIVE_DIR}/naive.c)
add_library(naive_library STATIC ${NAIVE_LIB_SOURCE_FILES})

set(PARALLEL_LIB_SOURCE_FILES ${PARALLEL_DIR}/parallel.c)
add_library(parallel_library SHARED ${PARALLEL_LIB_SOURCE_FILES})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(gtests.out project/test/gtests.cpp)
target_link_libraries(gtests.out ${GTEST_LIBRARIES})
target_link_libraries(gtests.out pthread)
target_link_libraries(gtests.out naive_library)
target_link_libraries(gtests.out parallel_library)