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
		_cells[y][x] = val;
	}
}

sudokuBoard getBoardExample1() {
	sudokuBoard brd;
	int board[9][9] = {
		{6,-1,-1,1,3,2,4,-1,9},
		{7,3,4,-1,-1,-1,-1,6,-1},
		{2,1,-1,-1,6,-1,-1,-1,8},
		{9,-1,6,8,-1,-1,-1,4,5},
		{8,5,1,3,-1,-1,7,-1,-1},
		{-1,-1,-1,2,-1,-1,-1,-1,1},
		{-1,-1,-1,4,-1,-1,-1,-1,3},
		{3,4,-1,9,-1,5,-1,8,-1},
		{1,9,-1,6,8,-1,-1,5,-1}
	};

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			brd.setCell(j, i, board[i][j]);
		}
	}

	return brd;
}

void draw(sudokuBoard brd) {
	int size = 9;
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
	for (int i = 0; i < size; i++) {
		if (i == 3 || i == 6) {
			cout << " ―  ―  ―   ―  ―  ―   ―  ―  ―\n";
		}

		if (i == cursorY) {
			cout << "ᐳ";
		} else {
			cout << " ";
		}

		for (int j = 0; j < size; j++) {
			if (j == 3 || j == 6) {
				cout << "|";
			}

			int cell = brd.getCell(j, i);

			if (cursorX == j && cursorY == i) {
				if (cell == -1) {
					cout << colourise(" ● ", blue, false);
				} else {
					cout << " " << colourise(to_string(cell), blue, true) << " ";
				}
			} else {
				if (cell == -1) {
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