#pragma once
#define ARRAY_SIZE 64
#define ARRAY_PLAYERS_SIZE 9
#define WIDTH_CELL 50
#define HEIGHTH_CELL 50
#define ORIGIN_DESK_X 50
#define ORIGIN_DESK_Y 50

struct cell
{
	int empty;
	int black_white;  //черные==1, белые==1
	int cursor;
	int x, y;   //xCell,yCell
} typedef cell;
struct point
{
	point() { x = 0; y = 0; };
	point(int X, int Y)
	{
		x = X;  y = Y;
	}
	int x;
	int y;
	void setXY(int X,int Y)
	{
		x = X;  y = Y;
	}
} typedef point;

class dataCell
{
public:
	dataCell(void)
	{
		_cell.empty=0;		_cell.black_white = 0;		_cell.cursor = 0;
		_cell.x = 0;		_cell.y = 0;
		pointOldCursor.setXY(0,0);
	}

	void clearCell(void)
	{
		_cell.empty = 0;		_cell.black_white = 0;		_cell.cursor = 0;
		_cell.x = 0;		_cell.y = 0;
		pointOldCursor.setXY(0, 0);
	}
	void setXY(int x,int y)
	{
		_cell.x = x;		_cell.y = y;
	}
	void moveDataCell(dataCell* dest)
	{
		dest->_cell.black_white = _cell.black_white;
		dest->_cell.empty = 1;   dest->_cell.cursor = 1;
		_cell.empty = 0;  _cell.black_white = 0;

	}
	inline int checkFig() { 
		return _cell.empty;
	};
	inline void setCursor(void) { _cell.cursor = 1; };
	inline void fillCell(int x, int y, int empty, int black_white) {
		setXY(x, y);  _cell.empty = empty; _cell.black_white = black_white;	};
//data
	cell _cell;
	point pointOldCursor;
	int numPlayerWhite = 0;
	int numPlayerBlack = 0;
};

