#Déclaration du projet

project(InfoFond)

#Déclaration de l'exécutable

add_executable(question4
        question-4/Data.hpp
        question-4/Data.cpp

        minisat/Global.hpp
        minisat/Heap.hpp

        question-4/Main.cpp

        question-4/Parser.hpp
        question-4/Parser.cpp

        question-4/ScheduleSolver.hpp
        question-4/ScheduleSolver.cpp

        minisat/Solver.cpp
        minisat/Solver.hpp

        minisat/SolverTypes.hpp
        minisat/Sort.hpp
        minisat/VarOrder.hpp
)

add_executable(question5
        question-5/Data.hpp
        question-5/Data.cpp

        minisat/Global.hpp
        minisat/Heap.hpp

        question-5/Main.cpp

        question-5/Parser.hpp
        question-5/Parser.cpp

        question-5/ScheduleSolver.hpp
        question-5/ScheduleSolver.cpp

        minisat/Solver.cpp
        minisat/Solver.hpp

        minisat/SolverTypes.hpp
        minisat/Sort.hpp
        minisat/VarOrder.hpp
)

add_executable(question6
        question-6/Data.hpp
        question-6/Data.cpp

        minisat/Global.hpp
        minisat/Heap.hpp

        question-6/Main.cpp

        question-6/Parser.hpp
        question-6/Parser.cpp

        question-6/ScheduleSolver.hpp
        question-6/ScheduleSolver.cpp

        minisat/Solver.cpp
        minisat/Solver.hpp

        minisat/SolverTypes.hpp
        minisat/Sort.hpp
        minisat/VarOrder.hpp
)

add_executable(question7
        question-7/Data.hpp
        question-7/Data.cpp

        minisat/Global.hpp
        minisat/Heap.hpp

        question-7/Main.cpp

        question-7/Parser.hpp
        question-7/Parser.cpp

        question-7/ScheduleSolver.hpp
        question-7/ScheduleSolver.cpp

        minisat/Solver.cpp
        minisat/Solver.hpp

        minisat/SolverTypes.hpp
        minisat/Sort.hpp
        minisat/VarOrder.hpp
)

add_executable(question10-1
        question-10-1/Data.hpp
        question-10-1/Data.cpp

        minisat/Global.hpp
        minisat/Heap.hpp

        question-10-1/Main.cpp

        question-10-1/Parser.hpp
        question-10-1/Parser.cpp

        question-10-1/ScheduleSolver.hpp
        question-10-1/ScheduleSolver.cpp

        minisat/Solver.cpp
        minisat/Solver.hpp

        minisat/SolverTypes.hpp
        minisat/Sort.hpp
        minisat/VarOrder.hpp
)

add_executable(question9
        question-9/Data.hpp
        question-9/Data.cpp

        minisat/Global.hpp
        minisat/Heap.hpp

        question-9/Main.cpp

        question-9/Parser.hpp
        question-9/Parser.cpp

        question-9/ScheduleSolver.hpp
        question-9/ScheduleSolver.cpp

        minisat/Solver.cpp
        minisat/Solver.hpp

        minisat/SolverTypes.hpp
        minisat/Sort.hpp
        minisat/VarOrder.hpp
)

add_executable(question10-2
        question-10-2/Data.hpp
        question-10-2/Data.cpp

        minisat/Global.hpp
        minisat/Heap.hpp

        question-10-2/Main.cpp

        question-10-2/Parser.hpp
        question-10-2/Parser.cpp

        question-10-2/ScheduleSolver.hpp
        question-10-2/ScheduleSolver.cpp

        minisat/Solver.cpp
        minisat/Solver.hpp

        minisat/SolverTypes.hpp
        minisat/Sort.hpp
        minisat/VarOrder.hpp
)


set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")