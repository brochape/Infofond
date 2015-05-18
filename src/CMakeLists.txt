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

add_executable(projet-v2
        scheduler-v2/Data.hpp
        scheduler-v2/Data.cpp

        minisat/Global.hpp
        minisat/Heap.hpp

        scheduler-v2/Main.cpp

        scheduler-v2/Parser.hpp
        scheduler-v2/Parser.cpp

        scheduler-v2/ScheduleSolver.hpp
        scheduler-v2/ScheduleSolver.cpp

        minisat/Solver.cpp
        minisat/Solver.hpp

        minisat/SolverTypes.hpp
        minisat/Sort.hpp
        minisat/VarOrder.hpp
)

add_executable(projet-v3
        scheduler-v3/Data.hpp
        scheduler-v3/Data.cpp

        minisat/Global.hpp
        minisat/Heap.hpp

        scheduler-v3/Main.cpp

        scheduler-v3/Parser.hpp
        scheduler-v3/Parser.cpp

        scheduler-v3/ScheduleSolver.hpp
        scheduler-v3/ScheduleSolver.cpp

        minisat/Solver.cpp
        minisat/Solver.hpp

        minisat/SolverTypes.hpp
        minisat/Sort.hpp
        minisat/VarOrder.hpp
)

add_executable(projet-v9
        scheduler-v9/Data.hpp
        scheduler-v9/Data.cpp

        minisat/Global.hpp
        minisat/Heap.hpp

        scheduler-v9/Main.cpp

        scheduler-v9/Parser.hpp
        scheduler-v9/Parser.cpp

        scheduler-v9/ScheduleSolver.hpp
        scheduler-v9/ScheduleSolver.cpp

        minisat/Solver.cpp
        minisat/Solver.hpp

        minisat/SolverTypes.hpp
        minisat/Sort.hpp
        minisat/VarOrder.hpp
)

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")