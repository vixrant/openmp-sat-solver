find_package(OpenMP REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)

################################
# Serial Solver implementation

add_executable(serial_solver)

target_sources(serial_solver
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/main.cc
    ${CMAKE_CURRENT_LIST_DIR}/parser.cc
    ${CMAKE_CURRENT_LIST_DIR}/solver.cc
    ${CMAKE_CURRENT_LIST_DIR}/instance.cc
    ${CMAKE_CURRENT_LIST_DIR}/model.cc
  )

target_include_directories(serial_solver
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${Boost_INCLUDE_DIR} 
  )

target_link_libraries(serial_solver
  PRIVATE
    OpenMP::OpenMP_CXX
    ${Boost_LIBRARIES}
  )

if(PRINT_LOGS)
  target_compile_definitions(serial_solver PRIVATE PRINT_LOGS=1)
endif(PRINT_LOGS)

target_compile_definitions(serial_solver PRIVATE ROW_STRIP=0 COL_STRIP=0)

##################################
# Parallel Solver implementation
# Row-striped

add_executable(row_parallel_solver)

target_sources(row_parallel_solver
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/main.cc
    ${CMAKE_CURRENT_LIST_DIR}/parser.cc
    ${CMAKE_CURRENT_LIST_DIR}/solver.cc
    ${CMAKE_CURRENT_LIST_DIR}/instance.cc
    ${CMAKE_CURRENT_LIST_DIR}/model.cc
  )

target_include_directories(row_parallel_solver
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${Boost_INCLUDE_DIR} 
  )

target_link_libraries(row_parallel_solver
  PRIVATE
    OpenMP::OpenMP_CXX
    ${Boost_LIBRARIES}
  )

if(PRINT_LOGS)
  target_compile_definitions(row_parallel_solver PRIVATE PRINT_LOGS=1)
endif(PRINT_LOGS)

target_compile_definitions(row_parallel_solver PRIVATE ROW_STRIP=1 COL_STRIP=0)

##################################
# Parallel Solver implementation
# Column-striped

add_executable(col_parallel_solver)

target_sources(col_parallel_solver
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/main.cc
    ${CMAKE_CURRENT_LIST_DIR}/parser.cc
    ${CMAKE_CURRENT_LIST_DIR}/solver.cc
    ${CMAKE_CURRENT_LIST_DIR}/instance.cc
    ${CMAKE_CURRENT_LIST_DIR}/model.cc
  )

target_include_directories(col_parallel_solver
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${Boost_INCLUDE_DIR} 
  )

target_link_libraries(col_parallel_solver
  PRIVATE
    OpenMP::OpenMP_CXX
    ${Boost_LIBRARIES}
  )

if(PRINT_LOGS)
  target_compile_definitions(col_parallel_solver PRIVATE PRINT_LOGS=1)
endif(PRINT_LOGS)

target_compile_definitions(col_parallel_solver PRIVATE ROW_STRIP=0 COL_STRIP=1)

##################################
# Parallel Solver implementation
# Blocked

add_executable(block_parallel_solver)

target_sources(block_parallel_solver
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/main.cc
    ${CMAKE_CURRENT_LIST_DIR}/parser.cc
    ${CMAKE_CURRENT_LIST_DIR}/solver.cc
    ${CMAKE_CURRENT_LIST_DIR}/instance.cc
    ${CMAKE_CURRENT_LIST_DIR}/model.cc
  )

target_include_directories(block_parallel_solver
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${Boost_INCLUDE_DIR} 
  )

target_link_libraries(block_parallel_solver
  PRIVATE
    OpenMP::OpenMP_CXX
    ${Boost_LIBRARIES}
  )

if(PRINT_LOGS)
  target_compile_definitions(block_parallel_solver PRIVATE PRINT_LOGS=1)
endif(PRINT_LOGS)

target_compile_definitions(block_parallel_solver PRIVATE ROW_STRIP=0 COL_STRIP=1)
