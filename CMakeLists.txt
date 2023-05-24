cmake_minimum_required(VERSION 3.25)
project(OS_Ex5 C)

set(CMAKE_C_STANDARD 11)

add_executable(OS_Ex5 queue.c active_object.c queue.h utils.h utils.c pipe_line.c pipe_line.h active_object.h main.c)
