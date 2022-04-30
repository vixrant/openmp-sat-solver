cmake_minimum_required(VERSION 3.15)
project(psat LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
option(PRINT_LOGS "Enables logging of algorithm logic" OFF)

add_subdirectory(./src/)
