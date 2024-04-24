project(matrix)

add_executable(matrix main.cpp)

add_library(libmatrix lib/Matrix.hpp lib/Matrix.cpp
        lib/MatrixExcepts.hpp lib/MatrixExcepts.cpp)

include_directories(matrix PRIVATE lib)
target_link_libraries(matrix PRIVATE libmatrix)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(MatrixTestExec test.cpp)
target_link_libraries(MatrixTestExec PRIVATE gtest gtest_main libmatrix)
add_test(MatrixTest MatrixTestExec)
