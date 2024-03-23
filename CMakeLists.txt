cmake_minimum_required(VERSION 3.29)
project(Quera)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_CXX_FLAGS "-O0 -static-libstdc++ -static-libgcc")
add_subdirectory(Bellman-Ford)
add_subdirectory(ShortestPath2D)
add_subdirectory(Dijkstra)
add_subdirectory(TopologicalSort)
add_subdirectory(GraphComponents)
add_subdirectory(GraphCycles)
add_subdirectory(TreeShortestPath)