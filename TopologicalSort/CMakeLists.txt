project(TopologicalSort)

add_executable(TopologicalSort TopoloSort.cpp)
configure_file(test.txt ${CMAKE_CURRENT_BINARY_DIR}/test.txt COPYONLY)