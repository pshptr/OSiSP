cmake_minimum_required(VERSION 3.23)
project(TicTacToe2c C)

set(CMAKE_C_STANDARD 11)

add_executable(TicTacToe2c main.c client.c server.c client.h server.h)
