#include <iostream>
#include <stdlib.h>
#include "sudoku.h"
#include "colour.h"
using namespace std;

int main(void) {
	system("clear");

	sudokuBoard brd = getBoardExample2();
	struct Cursor pos = {0,0};
	int value;

	string error = "";	
	string lastOperation = "Type your values to get started, use \n\"value: 0\" for moving cursor without placing.";

	while (true) {
		if (brd.checkFullBoard()) {
			cout << "Solution is valid = " << brd.checkSolution() << "\n";
			return 0;
		}

		cout << "Sudoku puzzle 1:\n";
		if (error != "") {
			cout << colourise(error, red, true) << "\n";
			error = "";
		} else if (lastOperation != "") {
			cout << colourise(colourise(lastOperation, white, true), black, false) << "\n";
		}

		draw(brd);

		cout << "x position: ";
		cin >> pos.x;
		cout << "y position: ";
		cin >> pos.y;
		cout << "value: ";
		cin >> value;

		if (pos.x > 8 || pos.x < 0 || pos.y > 8 || pos.y < 0) {
			error = "Position is invalid.";
		} else if (value != 0 && (value < 1 || value > 9)) {
			error = "Value is not valid.";
		} else {
			brd.setCursor(pos.x, pos.y);

			if (value >= 1 && value <= 9) {
				brd.place(pos.x, pos.y, value);

				if (brd.isModifiable(pos.x, pos.y)) {
					lastOperation = "Placed " + to_string(value) + " at (" + to_string(pos.x) + ", " + to_string(pos.y) + ").";
				} else {
					lastOperation = "Moved cursor to (" + to_string(pos.x) + ", " + to_string(pos.y) + ").";
				}
			} else {	
				lastOperation = "Moved cursor to (" + to_string(pos.x) + ", " + to_string(pos.y) + ").";
			}

		}

		system("clear");
	}
	return 0;
}