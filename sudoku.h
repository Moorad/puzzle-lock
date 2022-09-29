struct cursor {
	int x;
	int y;
};

class sudokuBoard {
	private:
		int _cells[9][9];
		bool modifiableCells[9][9];
		cursor cursorPos = {0,0};
	
	public:
		sudokuBoard();
		sudokuBoard(int cells[9][9]);

		int getCell(int x, int y) { return _cells[y][x]; }
		void setCell(int x, int y, int val) {
			_cells[y][x] = val;

			if (val == -1) modifiableCells[y][x] = true;
			else modifiableCells[y][x] = false;	
		}

		bool isModifiable(int x, int y) { return modifiableCells[y][x]; }
	
		cursor getCursor() { return cursorPos; }
		void setCursor(int x, int y) { cursorPos.x = x; cursorPos.y = y; }
		
		void place(int x, int y, int val);
		
		bool checkInputValidity(int x, int y, int val);
};

sudokuBoard getBoardExample1();

void draw(sudokuBoard brd);