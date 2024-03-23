project(TreeShortestPath)

add_executable(TreeShortestPath tree.cpp)
configure_file(test.txt ${CMAKE_CURRENT_BINARY_DIR}/test.txt COPYONLY)