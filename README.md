# Puzzle Lock
The main idea behind this is to make a program that would lock certain programs from you for a certain period of time so that you can focus on work instead. To add a twist to this the way the program would work is that it creates a set of puzzles (for now its only sudoku puzzles but might add more later) and generate a key from the solution of these puzzles. The program would then lock the files you specify and the only way to unlock them back is to either solve the puzzles and obtain the key from the solutions or wait for the set time to end. The time required to solve the puzzles should supposedly deter you away from trying to unlock the programs and force you to do some work.

## Install

Make sure you have (make)[https://www.gnu.org/software/make/] installed

Compile code:
```
make
```

Run code:
```
./puzzle_lock
```

Clear all .o files:
```
make clean
```

## Usage
None yet

## Todo
Sudoku:
- [x] Display a test board 
- [x] Add a cursor to the board
- [x] Add a simple move cursor system
- [x] Add a simple placing system
- [x] Add a board solution checker
- [x] Implement board solving algorithm
- [ ] Randomly generate boards
- [ ] Figure out a way to generate a key from the set of sudoku boards
- [ ] Save sudoku boards that make up the key in a file
- [ ] Add a config file
- [ ] Encrypt/lock files
- [ ] Add timing system to unlock after a period of time
- [ ] Add a move mode
- [ ] Add a place mode
- [x] Add proper feedback system (including errors)

	Other:
- [ ] Restructure files into folders
