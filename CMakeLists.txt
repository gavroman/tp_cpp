cmake_minimum_required(VERSION 3.10)

project(gtests.out)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")

include_directories(project/include)
set(SRCS_DIR project/src)
set(TEST_SRC_DIR tests/src)

set(LIB_SOURCE_FILES project/src/task.c)
add_library(task_library STATIC ${LIB_SOURCE_FILES})

add_executable(main.out ${SRCS_DIR}/main.c)
target_link_libraries(main.out task_library)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(gtests.out tests/src/gtests.cpp)

target_link_libraries(gtests.out ${GTEST_LIBRARIES})
target_link_libraries(gtests.out pthread)
target_link_libraries(gtests.out task_library)
