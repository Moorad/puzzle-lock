struct Cursor {
	int x;
	int y;
};

struct Cell {
	int val;
	bool modifiable;
};

class sudokuBoard {
	private:
		Cell _cells[9][9];
		Cursor cursorPos = {0,0};
	
	public:
		sudokuBoard();

		Cell getCell(int x, int y) { return _cells[y][x]; }
		void setCell(int x, int y, int val) {
			_cells[y][x].val = val;
			_cells[y][x].modifiable = val == 0;
		}

		bool isModifiable(int x, int y) { return _cells[y][x].modifiable; }
		bool isSafe(int x, int y, int val);
	
		Cursor getCursor() { return cursorPos; }
		void setCursor(int x, int y) { cursorPos.x = x; cursorPos.y = y; }
		
		void place(int x, int y, int val);

		bool checkFullBoard();
		bool checkSolution();
		
		bool solveBoard();
};

sudokuBoard getBoardExample1();
sudokuBoard getBoardExample2();

void draw(sudokuBoard brd);