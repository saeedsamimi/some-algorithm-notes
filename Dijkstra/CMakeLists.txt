project(Dijkstra)

add_executable(Dijkstra Dijkstra.cpp)
configure_file(test.txt ${CMAKE_CURRENT_BINARY_DIR}/test.txt COPYONLY)