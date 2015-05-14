#Déclaration du projet

project(InfoFond)

#Déclaration de l'exécutable

add_executable(projet-v0
        scheduler-v0/Data.hpp
        scheduler-v0/Data.cpp

        minisat/Global.hpp
        minisat/Heap.hpp

        scheduler-v0/Main.cpp

        scheduler-v0/Parser.hpp
        scheduler-v0/Parser.cpp

        scheduler-v0/ScheduleSolver.hpp
        scheduler-v0/ScheduleSolver.cpp

        minisat/Solver.cpp
        minisat/Solver.hpp

        minisat/SolverTypes.hpp
        minisat/Sort.hpp
        minisat/VarOrder.hpp
)

add_executable(projet-v1
        scheduler-v1/Data.hpp
        scheduler-v1/Data.cpp

        minisat/Global.hpp
        minisat/Heap.hpp

        scheduler-v1/Main.cpp

        scheduler-v1/Parser.hpp
        scheduler-v1/Parser.cpp

        scheduler-v1/ScheduleSolver.hpp
        scheduler-v1/ScheduleSolver.cpp

        minisat/Solver.cpp
        minisat/Solver.hpp

        minisat/SolverTypes.hpp
        minisat/Sort.hpp
        minisat/VarOrder.hpp
)

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")