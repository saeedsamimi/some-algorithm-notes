project(MathDriver)

file(GLOB OBJ_LIB_FILES lib/*)

add_executable(MathDriver main.cpp ${OBJ_LIB_FILES})
