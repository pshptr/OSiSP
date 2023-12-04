cmake_minimum_required(VERSION 3.23)
project(TicTac4 C)

set(CMAKE_C_STANDARD 99)

add_executable(TicTac4 main.c game_logic.c game_logic.h play_game_client.c play_game_server.c)
