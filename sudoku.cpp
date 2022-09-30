#include "sudoku.h"
#include "colour.h"
#include <iostream>
using namespace std;

sudokuBoard::sudokuBoard() {
}

bool sudokuBoard::checkInputValidity(int x, int y, int val) {
	if (val > 9 || val < 1) {
		return false;
	}

	if (x > 8 || x < 0 ||
		y > 8 || y < 0) {
			return false;
	}

	// if (getCell(x, y) != -1) {
	// 	return false;
	// }

	return true;
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

// Will be used for generating the solution later
	// sudokuBoard defaultBrd;

	// for (int i = 0; i < 9; i++) {
	// 	for (int j = 0; j < 9; j++) {
	// 		if (getCell(j, i).modifiable) {
	// 			defaultBrd.setCell(j, i, 0);
	// 		} else {
	// 			defaultBrd.setCell(j, i, getCell(j, i).val);
	// 		}
	// 	}
	// }

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
		{6,3,2,5,7,1,4,9,3},
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