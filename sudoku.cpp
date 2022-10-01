#include "sudoku.h"
#include "colour.h"
#include <set>
#include <iostream>
using namespace std;

sudokuBoard::sudokuBoard() {
}

void sudokuBoard::place(int x, int y, int val) {
	if (isModifiable(x, y)) {
		_cells[y][x].val = val;
	}
}

bool sudokuBoard::checkFullBoard() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (getCell(j, i).val == 0) {
				return false;
			}
		}
	}

	return true;
}

bool sudokuBoard::checkSolution() {
	// Checking 
	
	for (int i = 0; i < 9; i++) {
		bool seen[9] = {false};
		for (int j = 0; j < 9; j++) {
			 if (seen[getCell(j, i).val - 1] == false) {
				seen[getCell(j, i).val - 1] = true;
			} else {
				return false;
			}
		}
	}

	// Checking columns
	for (int i = 0; i < 9; i++) {
		bool seen[9] = {false};
		for (int j = 0; j < 9; j++) {
			 if (seen[getCell(i, j).val - 1] == false) {
				seen[getCell(i, j).val - 1] = true;
			} else {
				return false;
			}
		}
	}

	// Check 3x3s
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			bool seen[9] = {false};
			for (int k = 0; k < 9; k++) {
				int currX = (k % 3) + (3 * j);
				int currY = (k / 3) + (3 * i);
				if (seen[getCell(currX, currY).val - 1] == false) {
					seen[getCell(currX, currY).val - 1] = true;
				} else {
					return false;
				}
			}
		}
	}

	return true;
}

// Backtracking algorithm
// https://en.wikipedia.org/wiki/Sudoku_solving_algorithms
bool sudokuBoard::solveBoard() {
	set<int> possibilities = {1,2,3,4,5,6,7,8,9};

	Cursor currEmpty;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (getCell(j, i).val == 0) {
				currEmpty = {j, i};
				goto endloop;
			}
		}
	}

	return true;

endloop:
	// Horizontal, Vertical and 3x3 check possibilities
	for (auto it = possibilities.begin(); it != possibilities.end();) {
		bool found = false;
		for (int i = 0; i < 9; i++) {
			if (getCell(i, currEmpty.y).val == *it) {
				possibilities.erase(it++);
				found = true;
				break;
			}

			if (getCell(currEmpty.x, i).val == *it) {
				possibilities.erase(it++);
				found = true;
				break;
			}

			int multiX = currEmpty.x / 3;
			int multiY = currEmpty.y / 3;
			if (getCell((i % 3) + (3 * multiX), (i / 3) + (3 * multiY)).val == *it) {
				possibilities.erase(it++);
				found = true;
				break;
			}
		}

		if (!found) {
			++it;
		}
	}

	for (auto it = possibilities.begin(); it != possibilities.end(); ++it) {
		place(currEmpty.x, currEmpty.y, *it);

		if (solveBoard()) {
			return true;
		} else {
			place(currEmpty.x, currEmpty.y, 0);
		}
	}
	
	return false;

// Vertical

// 3x3
}

sudokuBoard getBoardExample1() {
	sudokuBoard brd;
	int board[9][9] = {
		{6,0,0,1,3,2,4,0,9},
		{7,3,4,0,0,0,0,6,0},
		{2,1,0,0,6,0,0,0,8},
		{9,0,6,8,0,0,0,4,5},
		{8,5,1,3,0,0,7,0,0},
		{0,0,0,2,0,0,0,0,1},
		{0,0,0,4,0,0,0,0,3},
		{3,4,0,9,0,5,0,8,0},
		{1,9,0,6,8,0,0,5,0}
	};

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			brd.setCell(j, i, board[i][j]);
		}
	}

	return brd;
}

sudokuBoard getBoardExample2() {
	sudokuBoard brd;
	int board[9][9] = {
		{4,0,5,2,6,9,7,8,1},
		{6,8,2,5,7,1,4,9,3},
		{1,9,7,8,3,4,5,6,2},
		{8,2,6,1,9,5,3,4,7},
		{3,7,4,6,8,2,9,1,5},
		{9,5,1,7,4,3,6,2,8},
		{5,1,9,3,2,6,8,7,4},
		{2,4,8,9,5,7,1,3,6},
		{7,6,3,4,1,8,2,5,9}
	};

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			brd.setCell(j, i, board[i][j]);
		}
	}

	return brd;
}

void draw(sudokuBoard brd) {
	int cursorX = brd.getCursor().x;
	int cursorY = brd.getCursor().y;

	// Draw pointer top
	cout << " "; // left margin

	for (int k = 0; k < cursorX; k++) {
		if (k == 2 || k == 5) {
			cout << " ";
		} 
		cout << "   ";
	}
	cout << " ᐯ \n";

	// Draw board
	for (int i = 0; i < 9; i++) {
		if (i == 3 || i == 6) {
			cout << " ―  ―  ―   ―  ―  ―   ―  ―  ―\n";
		}

		if (i == cursorY) {
			cout << "ᐳ";
		} else {
			cout << " ";
		}

		for (int j = 0; j < 9; j++) {
			if (j == 3 || j == 6) {
				cout << "|";
			}

			int cell = brd.getCell(j, i).val;

			if (cursorX == j && cursorY == i) {
				if (cell == 0) {
					cout << colourise(" ● ", blue, false);
				} else {
					cout << " " << colourise(to_string(cell), blue, true) << " ";
				}
			} else {
				if (cell == 0) {
					cout << "   ";
				} else {
					if (brd.isModifiable(j, i)) {
						cout << " " << colourise(colourise(to_string(cell), white, true), black, false)<< " ";
					} else {
						cout << " " << cell << " ";
					}
				}
			}
		}
		cout << "\n";
	}
}