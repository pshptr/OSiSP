cmake_minimum_required(VERSION 3.23)
project(untitled5 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled5 main.c, server.c, client.c)

add_executable(untitled5 server.c)

add_executable(untitled5 client.c)