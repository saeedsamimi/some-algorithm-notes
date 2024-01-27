cmake_minimum_required(VERSION 3.27)
# quera project configurations
project(Quera-Practice-Cake-or-Fake C)
project(Quera-Practice-Pairs C)
project(Quera-Practice-Spring-Box C)
# university contest configurations
project(linearVillage C)
project(intervalsLength C)
project(cacaoMilk C)
project(helloHelloByeBye C)
project(allSubsets C)
# mathematics configurations
project(math-polynomials C)
project(math-polynomials-C++ CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

# quera practice files
add_executable(Quera-Practice-Cake-or-Fake Quera-Practice/CakeOrFake.c)
add_executable(Quera-Practice-Pairs Quera-Practice/pairs.c)
add_executable(Quera-Practice-Spring-Box Quera-Practice/springBox.c)
# contest files
add_executable(linearVillage Contest/linearVillageMain.c)
add_executable(intervalsLength Contest/intervalsLengthMain.c)
add_executable(cacaoMilk Contest/cacaoMilk.c)
add_executable(helloHelloByeBye Contest/HelloHelloGoodByeBye.c)
add_executable(allSubsets Contest/allSubsets.c)
# mathematics files
add_executable(math-polynomials Mathematics/Polynomials.c)
add_executable(math-polynomials-C++ Mathematics/Polynomials.cpp Mathematics/Polynomials.h)
