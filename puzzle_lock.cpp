#include <iostream>
#include <stdlib.h>
#include "sudoku.h"
#include "colour.h"
using namespace std;

int main(void) {
	system("clear");

	sudokuBoard brd = getBoardExample2();
	string error = "";
	struct cursor pos = {0,0};
	int value;

	while (true) {
		cout << "Sudoku puzzle 1:\n";
		if (error != "") {
			cout << colourise(error, red, true);
			error = "";
		}

		draw(brd);

		cout << "x position: ";
		cin >> pos.x;
		cout << "y position: ";
		cin >> pos.y;
		cout << "value: ";
		cin >> value;

		if (!brd.checkInputValidity(pos.x, pos.y, value)) {
			error = "Position is invalid\n";
		} else {
			brd.setCursor(pos.x, pos.y);
		}

		if (value >= 1 && value <= 9) {
			brd.place(pos.x, pos.y, value);

			if (brd.checkFullBoard()) {
				cout << brd.checkSolution() << "\n";
				return 0;
			}
		} else if (value != -1) {
			error = "Value is invalid\n";
		}
		

		system("clear");
	}
	return 0;
}