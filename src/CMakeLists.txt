#Déclaration du projet

project(InfoFond)

#Déclaration de l'exécutable

add_executable(projet
        Data.hpp
        Data.cpp

        Global.hpp
        Heap.hpp

        Main.cpp

        Parser.hpp
        Parser.cpp

        ScheduleSolver.hpp
        ScheduleSolver.cpp

        Solver.cpp
        Solver.hpp

        SolverTypes.hpp
        Sort.hpp
        VarOrder.hpp
)

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")