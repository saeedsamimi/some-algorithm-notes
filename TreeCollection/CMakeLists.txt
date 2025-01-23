add_executable(treecollection main.cpp)

set(GTEST_OUTPUT "${CMAKE_BINARY_DIR}/test-reports/")

file(GLOB TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test/*.test.cc")
add_executable(treecollection_test ${TEST_FILES})

target_link_libraries(treecollection_test GTest::gmock_main)
