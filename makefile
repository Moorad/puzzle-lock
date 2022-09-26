puzzle_lock: puzzle_lock.o sudoku.o colour.o
	g++ puzzle_lock.o sudoku.o colour.o -o puzzle_lock

puzzle_lock.o: puzzle_lock.cpp
	g++ -c puzzle_lock.cpp

sudoku.o: sudoku.cpp
	g++ -c sudoku.cpp

colour.o: colour.cpp
	g++ -c colour.cpp

clean:
	rm *.o puzzle_lock
