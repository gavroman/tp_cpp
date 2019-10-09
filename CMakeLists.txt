cmake_minimum_required(VERSION 3.0)

project(Task_manager)

set(SRCS_DIR project/src)

SET(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_C_STANDART 99)
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_COMPILER_VERSION -std = 11)

include_directories(project/include)

set(SRCS ${SRCS_DIR}/main.c ${SRCS_DIR}/task.c)

add_executable(main.out ${SRCS})
