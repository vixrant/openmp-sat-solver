add_library(serial_impl serial/solver.cc)
add_library(dimacs_parser parser/parser.cc)

add_executable(serialsat cli/main.cc)
target_link_libraries(serialsat PRIVATE serial_impl dimacs_parser)


