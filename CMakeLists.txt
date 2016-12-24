cmake_minimum_required(VERSION 3.6)
project(tictactoe_cl)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES board.c tictactoe.h main.c tictactoe.c)
add_executable(tictactoe_cl ${SOURCE_FILES})