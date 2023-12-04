cmake_minimum_required(VERSION 3.23)
project(TicTacToe3c C)

set(CMAKE_C_STANDARD 11)

add_executable(TicTacToe3c main.c server.c client.c game_logic.c game_logic.h)
