project(Polynomial)

add_library(libpolynomial Polynomial.cpp Polynomial.hpp)

add_executable(Polynomial main.cpp)

target_include_directories(Polynomial PRIVATE .)
target_link_libraries(Polynomial PRIVATE polynomial)
