add_executable(solver)

find_package(OpenMP REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)

target_sources(solver
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/main.cc
    ${CMAKE_CURRENT_LIST_DIR}/parser.cc
    ${CMAKE_CURRENT_LIST_DIR}/solver.cc
    ${CMAKE_CURRENT_LIST_DIR}/instance.cc
    ${CMAKE_CURRENT_LIST_DIR}/model.cc
  )

target_include_directories(solver
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${Boost_INCLUDE_DIR} 
  )

target_link_libraries(solver PRIVATE OpenMP::OpenMP_CXX ${Boost_LIBRARIES})

target_compile_definitions(solver PUBLIC PRINT_LOGS=1)
