project(GraphCycles)

add_executable(GraphCycles Cycles.cpp)
configure_file(test.txt ${CMAKE_CURRENT_BINARY_DIR}/test.txt COPYONLY)