#pragma once
#include <vector>
#include "data.h"
#include "Player.h"
#include "PlayerAI.h"
#include <windows.h>
#include "Graphon.h"


class World
{
public:
	World() {
		   oldCursor.setXY(0,0);
	};
	int init(HWND window);
	int drawWorld();
	void draw();

	void moveDataCell(int indSrc, int indDst);
	void moveFig(void);
	inline int getIndex(int x, int y) {	 return (y<<3)+x; };
	void getXY(int index)
	{
		xFromIndex = index % 8;
		xFromIndex = xFromIndex * 50 + 50;
		yFromIndex = index / 8;
		yFromIndex = yFromIndex * 50 + 50;
	};
	int getPath(void);
	int checkEnd(int);
	void stepAI();
	int  nextStep(int indexCurPlayerAI);
	void moveFigAI(int x, int y);
	void moveDataCellAI(int x, int y,int index);
	int  CheckLastPos(void);
	int  StepRight(int x, int y, int index,  int numCall);
	int StepBottom(int x, int y, int index,  int numCall);
	int StepTop(int x, int y, int index, int numCall);
	int StepLeft(int x, int y, int index, int numCall);
	int getFreeCell(void);
	int nextStepToEnd(int x,int y,int indexCurPlayerAI);
	int  getIndexCurPlayerAI(int indexCurPlayerAI);
	int checkWinWhite();
	int checkWinBlack();
	void StepRight(int dx);
	void StepLeft(int dx);
	void StepBot(int ddy);
	void StepTop(int dy);
	void reInit();

	std::vector<dataCell> cells;   // [64] ;
	int currentCursorIndex=0; 
	point oldCursor;
	int oldIndex = 0;
	int cntPress = 0;
	int currentCursorIndexAI = 0;  
	point oldCursorAI;
	int oldIndexAI = 0;

	int indexStepAI = 5;
	HWND window;
	Graphon graf;
	
	std::vector<Player> players;
	std::vector<PlayerAI> playersAI;

	int xMouse=0,xCur=0;
	int yMouse=0,yCur=0;
	int numPlayerWhite = 0;
	int numPlayerBlack = 0;
	int modeStep = 0;
	int placesEnd[9] = {45,46,47,53,54,55,61,62,63};
	int placesStart[9] = { 0,1,2,8,9,10,16,17,18 };
	int freeCell = 63;
	int xFromIndex = 0;
	int yFromIndex = 0;
	
};

