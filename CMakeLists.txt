cmake_minimum_required(VERSION 3.15)
project(psat LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(./include/)
add_subdirectory(./src/)
add_subdirectory(./test/)
