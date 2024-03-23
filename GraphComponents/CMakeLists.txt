project(GraphComponents)

add_executable(GraphComponents components.cpp)
configure_file(test.txt ${CMAKE_CURRENT_BINARY_DIR}/test.txt COPYONLY)