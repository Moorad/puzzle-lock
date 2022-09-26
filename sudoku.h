struct cursor {
	int x;
	int y;
};

class sudokuBoard {
	private:
		int _cells[9][9];
		cursor cursorPos = {0,0};
	
	public:
		sudokuBoard();
		sudokuBoard(int cells[9][9]);

		int getCell(int x, int y) { return _cells[x][y]; }
		void setCell(int x, int y, int val) {_cells[x][y] = val; }
		
		cursor getCursor() { return cursorPos; }
		void setCursor(int x, int y) { cursorPos.x = x; cursorPos.y = y; }
		
		bool checkInputValidity(int x, int y, int val);
};

sudokuBoard getBoardExample1();

void draw(sudokuBoard brd);