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

add_executable(main_naive.out project/main_naive.c)
target_link_libraries(main_naive.out naive_library)

add_executable(main_parallel.out project/main_parallel.c)
target_link_libraries(main_parallel.out parallel_library)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(gtests.out project/test/gtests.cpp)
target_link_libraries(gtests.out ${GTEST_LIBRARIES})
target_link_libraries(gtests.out pthread)
target_link_libraries(gtests.out naive_library)
target_link_libraries(gtests.out parallel_library ${CMAKE_DL_LIBS})