cmake_minimum_required(VERSION 2.8)

project(Task_manager)

set(SRCS_DIR project/src)

include_directories(project/include)

set(SRCS ${SRCS_DIR}/main.c ${SRCS_DIR}/task.c)
set(HEADERS task.h)

add_executable(main.out ${SRCS})
