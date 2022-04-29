add_library(solver)

find_package(OpenMP REQUIRED)

target_sources(solver
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/parser.cc
    ${CMAKE_CURRENT_LIST_DIR}/instance.cc
    ${CMAKE_CURRENT_LIST_DIR}/model.cc
    ${CMAKE_CURRENT_LIST_DIR}/solver.cc
  )

target_include_directories(solver
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_compile_options(solver PRIVATE -Wall ${OpenMP_CXX_FLAGS})
target_link_libraries(solver PRIVATE ${OpenMP_CXX_FLAGS})
