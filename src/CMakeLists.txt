#Déclaration du projet

project(InfoFond)

#Déclaration de l'exécutable

add_executable(test
        Data.cpp
        Global.hpp
        Heap.hpp
        Main.cpp
        Parser.cpp
        ScheduleSolver.cpp
        Solver.cpp
        Solver.hpp
        SolverTypes.hpp
        Sort.hpp
        VarOrder.hpp
)

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")