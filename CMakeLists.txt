cmake_minimum_required(VERSION 3.6)
project(tictactoe_cl)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES board.c tictactoe.h main.c tictactoe.c)
add_executable(tictactoe_cl ${SOURCE_FILES})

set(TEST_SOURCE_FILES test_runner.c)
add_executable(test_runner ${TEST_SOURCE_FILES})
