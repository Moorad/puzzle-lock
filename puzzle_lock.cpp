#include <iostream>
#include <stdlib.h>
#include "sudoku.h"
#include "colour.h"
using namespace std;

int main(void) {
	system("clear");

	sudokuBoard brd = getBoardExample1();
	struct cursor pos = {0,0};
	int value;

	while (true) {
		cout << "Sudoku puzzle 1:\n";
		
		if (!brd.checkInputValidity(pos.x, pos.y, value)) {
			cout << colourise("Input was invalid\n", red, true);
		} else {
			brd.setCursor(pos.x, pos.y);
		}

		draw(brd);

		cout << "x position: ";
		cin >> pos.x;
		cout << "y position: ";
		cin >> pos.y;
		cout << "value: ";
		cin >> value;

		

		system("clear");
	}
	return 0;
}