#include "sudoku.h"
#include "colour.h"
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;

sudokuBoard::sudokuBoard() {
	numOfClues = rand() % 8 + 28;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			setCell(j, i, 0);
		}
	}
}

void sudokuBoard::place(int x, int y, int val) {
	if (isModifiable(x, y)) {
		_cells[y][x].val = val;
	}
}

bool sudokuBoard::isSafe(int x, int y, int val) {
	for (int i = 0; i < 9; i++) {
		if (getCell(i, y).val == val  && i != x) {
			return false;
		}

		if (getCell(x, i).val == val && i != y) {
			return false;
		}

		int boxX = (i % 3) + (3 * (x / 3));
		int boxY =(i / 3) + (3 * (y / 3));
		if (getCell(boxX, boxY).val == val && boxX != x && boxY != y) {
			return false;
		}
	}

	return true;
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
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (!isSafe(j, i, getCell(j, i).val)) {
				return false;
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
		if (!isSafe(currEmpty.x, currEmpty.y, *it)) {
			possibilities.erase(it++);
			found = true;
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
}

sudokuBoard generateRandomBoard() {
	// Min of 17 otherwise cant be unique
	srand(time(NULL));

	sudokuBoard randomBoard = defaultBoard();
	int intBoard[9][9];

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			intBoard[i][j] = randomBoard.getCell(j, i).val; 
		}
	}

	int groups[] = {0,1,2};
	int currentOrder[] = {0,1,2};


	random_shuffle(begin(groups), end(groups));
	int index = 0;
	int nextIndex;
	int correct = 0;
	int maxCorrect = 3;
	
	while (correct < maxCorrect) {
		nextIndex = (index + 1) % 3;
		if (currentOrder[index] == groups[index]) {
			correct ++;
			index = nextIndex;
			continue;
		}

		
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 9; k++) {
				swap(intBoard[j + (index * 3)][k],  intBoard[j + (nextIndex * 3)][k]);
			}	
		}

		swap(currentOrder[index], currentOrder[nextIndex]);
		index = nextIndex;
		correct = 0;
	}

	for (int i = 0; i < 3; i++) {
		random_shuffle(begin(groups), end(groups));
		int currentOrder[] = {0,1,2};
		index = 0;
		nextIndex;
		correct = 0;
		while (correct < maxCorrect) {
			nextIndex = (index + 1) % 3;

			if (groups[index] == currentOrder[index]) {
				correct ++;
				index = nextIndex;
				continue;
			}

			for (int k = 0; k < 9; k++) {
				swap(intBoard[(i * 3) + index][k],  intBoard[(i * 3) + nextIndex][k]);
			}

			swap(currentOrder[index], currentOrder[nextIndex]);
			index = nextIndex;
			correct = 0;
		}
	}

	int clueCount = 81;
	int randomNum;
	int x;
	int y;
	while(clueCount > randomBoard.getNumbOfClues()) {
		randomNum = rand() % 81;
		int x = randomNum % 9;
		int y = randomNum / 9;

		intBoard[y][x] = 0;
		clueCount --;
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			randomBoard.setCell(j, i, intBoard[i][j]);
		}
	}

	return randomBoard;
}

sudokuBoard defaultBoard() {
	sudokuBoard brd;
	int board[9][9] = {
		{6,8,5,1,3,2,4,7,9},
		{7,3,4,5,9,8,1,6,2},
		{2,1,9,7,6,4,5,3,8},
		{9,2,6,8,7,1,3,4,5},
		{8,5,1,3,4,9,7,2,6},
		{4,7,3,2,5,6,8,9,1},
		{5,6,8,4,2,7,9,1,3},
		{3,4,2,9,1,5,6,8,7},
		{1,9,7,6,8,3,2,5,4}
	};

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			brd.setCell(j, i, board[i][j]);
		}
	}

	return brd;
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