add_executable(test_serial main.cc)
target_link_libraries(test_serial PRIVATE serial_impl dimacs_parser)
