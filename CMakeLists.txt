cmake_minimum_required(VERSION 3.27)
# quera project configurations
project(Quera-Practice-Cake-or-Fake C)
project(Quera-Practice-Pairs C)
# university contest configurations
project(linearVillage C)
project(intervalsLength C)
project(cacaoMilk C)
project(helloHelloByeBye C)
# mathematics configurations
project(math-polynomials C)

set(CMAKE_C_STANDARD 23)

# quera practice files
add_executable(Quera-Practice-Cake-or-Fake Quera-Practice/CakeOrFake.c)
add_executable(Quera-Practice-Pairs Quera-Practice/pairs.c)
# contest files
add_executable(linearVillage Contest/linearVillageMain.c)
add_executable(intervalsLength Contest/intervalsLengthMain.c)
add_executable(cacaoMilk Contest/cacaoMilk.c)
add_executable(helloHelloByeBye Contest/HelloHelloGoodByeBye.c)
# mathematics files
add_executable(math-polynomials Mathematics/Polynomials.c)
