cmake_minimum_required(VERSION 3.23)
project(TicTac4 C)

set(CMAKE_C_STANDARD 99)

add_executable(TicTac4 menu.h Network.cpp Network.h GameBoard.cpp GameBoard.h Graphics.cpp Graphics.h Input.cpp Input.h)
