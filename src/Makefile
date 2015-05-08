G++ = g++ -Wall  -g

sudosat: Main.o Sudoku.o Solver.o
	$(G++) *.o -o sudosat

Solver.o: Solver.cpp Solver.hpp SolverTypes.hpp Global.hpp Heap.hpp
	$(G++) -c Solver.cpp 

Main.o: Main.cpp Sudoku.hpp Sudoku.cpp Solver.hpp 
	$(G++) -c Main.cpp

Sudoku.o: Sudoku.hpp Sudoku.cpp
	$(G++) -c Sudoku.cpp

clean:
	$(RM) *.o sudosat
