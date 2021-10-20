#include "World.h"


int World::init(HWND Window)
{
	int ret = 0;
	window = Window;
	graf.init(window);

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		cells.push_back(dataCell());
	}
	int x, y,index;
	int offsetX,  offsetY;
	for (int i = 0; i < ARRAY_PLAYERS_SIZE; i++)
	{

		players.push_back(Player());
		players[i].init(i, 343);
		players[i].spriteBack = std::make_unique<sf::Sprite>(graf.texturesWhite[i]);
		//players[i].SFMLView = std::make_unique<sf::RenderWindow>(window);
		players[i].spriteBack->setOrigin(32, 32);
	
		players[i].spriteBack->setPosition(players[i].curPos.x , players[i].curPos.y );
		x = players[i].curPos.x+7;
		y = players[i].curPos.y + 7;

		offsetX = (x - WIDTH_CELL) / WIDTH_CELL - 1;
		offsetY = (y - WIDTH_CELL) / WIDTH_CELL - 1;
	
		index = getIndex(offsetX, offsetY);
		players[i].number = index;
		cells[index].numPlayerWhite = i;
		//cells[index].x = x;		cells[index].y = y;
		cells[index].fillCell(x,y,1,1);	
			
		playersAI.push_back(PlayerAI());
		playersAI[i].init(i,90);
		playersAI[i].spriteBack = std::make_unique<sf::Sprite>(graf.texturesBlack[i]);

		playersAI[i].spriteBack->setOrigin(33, 33);

		playersAI[i].spriteBack->setPosition(playersAI[i].curPos.x, playersAI[i].curPos.y);
		x = playersAI[i].curPos.x +10;
		y = playersAI[i].curPos.y + 10;

		offsetX = (x - WIDTH_CELL) / WIDTH_CELL - 1;
		offsetY = (y - WIDTH_CELL) / WIDTH_CELL - 1;
	   index = getIndex(offsetX, offsetY);  // offsetY * 8 + offsetX;
	   playersAI[i].number = index;
	   cells[index].numPlayerBlack = i;
	
	   cells[index].fillCell(x, y, 1, 2);
	}

	return ret;
}

void World::reInit()
{
	graf.reInit(window);
	int x, y, index;
	int offsetX, offsetY;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		cells[i].clearCell();
	}
	for (int i = 0; i < ARRAY_PLAYERS_SIZE; i++)
	{
		players[i].init(i, 343);
		//players[i].spriteBack = std::make_unique<sf::Sprite>(graf.texturesWhite[i]);
		players[i].spriteBack->setOrigin(32, 32);

		players[i].spriteBack->setPosition(players[i].curPos.x, players[i].curPos.y);
		x = players[i].curPos.x + 7;
		y = players[i].curPos.y + 7;

		offsetX = (x - WIDTH_CELL) / WIDTH_CELL - 1;
		offsetY = (y - WIDTH_CELL) / WIDTH_CELL - 1;

		index = getIndex(offsetX, offsetY);
		players[i].number = index;
		cells[index].numPlayerWhite = i;

		cells[index].fillCell(x, y, 1, 1);

		playersAI[i].init(i, 90);
		
		playersAI[i].spriteBack->setOrigin(33, 33);

		playersAI[i].spriteBack->setPosition(playersAI[i].curPos.x, playersAI[i].curPos.y);
		x = playersAI[i].curPos.x + 10;
		y = playersAI[i].curPos.y + 10;

		offsetX = (x - WIDTH_CELL) / WIDTH_CELL - 1;
		offsetY = (y - WIDTH_CELL) / WIDTH_CELL - 1;
		index = getIndex(offsetX, offsetY);  // offsetY * 8 + offsetX;
		playersAI[i].number = index;
		cells[index].numPlayerBlack = i;

		cells[index].fillCell(x, y, 1, 2);
	}

}

void World::StepRight(int dx)
{
	if (abs(dx) < 100)
	{
		currentCursorIndex = oldIndex + 1;
		xMouse = oldCursor.x + WIDTH_CELL;
		yMouse = oldCursor.y;
	}
	//определяем индекс клетки "вправо через одну"
		//index = индекс_текущей_клетки + 2
	else
	{
		currentCursorIndex = oldIndex + 1;
		if (cells[currentCursorIndex].checkFig() == 0)
			xMouse = oldCursor.x + WIDTH_CELL;
		else {
			xMouse = oldCursor.x + WIDTH_CELL * 2;
			currentCursorIndex++;
		}
		yMouse = oldCursor.y;
	}
	//ставим на эту клетку фигуру
	moveFig();
	stepAI();
}

void World::StepLeft(int dx)
{
	if (abs(dx) < 100) {
		currentCursorIndex = oldIndex - 1;
		xMouse = oldCursor.x - WIDTH_CELL;
		yMouse = oldCursor.y;
	}
	else {
		//определяем индекс клетки "влево через одну"
			//index = индекс_текущей_клетки - 2 
		currentCursorIndex = oldIndex - 1;
		if (cells[currentCursorIndex].checkFig() == 0)
			xMouse = oldCursor.x - WIDTH_CELL;
		else {
			currentCursorIndex = oldIndex - 2;
			xMouse = oldCursor.x - WIDTH_CELL * 2;
		}
		yMouse = oldCursor.y;
	}
	//ставим на эту клетку фигуру
	moveFig();
	stepAI();
}

void  World::StepBot(int dy)
{
		if (abs(dy) < 100) {
			currentCursorIndex = oldIndex + 8;
			xMouse = oldCursor.x;
			yMouse = oldCursor.y + WIDTH_CELL;
		}
		//определяем индекс клетки "вниз через одну"
		//index = индекс_текущей_клетки + 8
		else {
			currentCursorIndex = oldIndex + 8;
			if (cells[currentCursorIndex].checkFig() == 0)
				yMouse = oldCursor.y + WIDTH_CELL;
			else {
				currentCursorIndex = oldIndex + 16;
				yMouse = oldCursor.y + WIDTH_CELL * 2;
			}
			xMouse = oldCursor.x;
		}
		//ставим на эту клетку фигуру
		moveFig();
		stepAI();
}

void  World::StepTop(int dy)
{
	if (abs(dy) < 100) {
		currentCursorIndex = oldIndex - 8;
		xMouse = oldCursor.x;
		yMouse = oldCursor.y - WIDTH_CELL;
	}
	//определяем индекс клетки "вверх через одну"
		//index = индекс_текущей_клетки - 8
	else {
		currentCursorIndex = oldIndex - 8;
		if (cells[currentCursorIndex].checkFig() == 0)
			yMouse = oldCursor.y - WIDTH_CELL;
		else {
			currentCursorIndex = oldIndex - 16;
			yMouse = oldCursor.y - WIDTH_CELL * 2;
		}
		xMouse = oldCursor.x;
	}
	moveFig();
	stepAI();
}

int World::drawWorld()
{
	cntPress++;
	
	xMouse = xMouse / WIDTH_CELL;
	int indexX = xMouse-1;
	if (indexX < 0 || indexX>7) {
		cntPress=0;
		return 0;
	}
	xMouse = xMouse * WIDTH_CELL;
	yMouse = yMouse / WIDTH_CELL;
	int indexY= yMouse-1;
	if (indexY < 0 || indexY>7) {
		cntPress=0;
		return 0;
	}
	yMouse = yMouse * WIDTH_CELL;
	currentCursorIndex = getIndex(indexX, indexY);
	if (cntPress == 1) {
		if (cells[currentCursorIndex].checkFig()==1)
		{
			graf.spriteFrame.setOrigin(0, 0);
			oldCursor.setXY(xMouse, yMouse);
			oldIndex = currentCursorIndex;
			graf.spriteFrame.setPosition(xMouse, yMouse);
			graf.SFMLView->draw(graf.spriteFrame);
			//надо определить, какой спрайт надо двигать
			//numPlayerWhite
			numPlayerWhite = cells[currentCursorIndex].numPlayerWhite;
		}
		else		{
			cntPress = 0; return 0;
		}
	}
		if (cntPress >= 2) {
			//проверяем...
			if (cells[currentCursorIndex].checkFig() == 0)
			{
				int dx = oldCursor.x - xMouse;
				int dy = oldCursor.y - yMouse;
				int ddx = oldCursor.x / WIDTH_CELL - xMouse / WIDTH_CELL;
				int ddy = oldCursor.y / WIDTH_CELL - yMouse / WIDTH_CELL;
				if ((abs(dx) < 100) && (abs(dy) < 100))
				{
				//рядом пустое место
					if (ddx == ddy)  //по диагонали ходить нельзя...
					{
					cntPress = 1; return 0;
					}
					moveFig();
					stepAI();
				}
				else
				{
					//надо прыгать через фигуру(ы). Пока умеем прыгать только через одну фигуру...
						//определяем направление
					if (ddx < 0) //вправо по X
					{
						StepRight(dx);						return 0;
					}
					if (ddx > 0)   //влево по Х
					{
						StepLeft(dx);							return 0;
					}
					if (ddy < 0)  //вниз
					{
						StepBot(dy);						return 0;
					}
					//if (ddx == 0) {		return 0;		}
						if (ddy > 0) //вверх
							StepTop(dy);
					
				}
			}
		}
		if (checkWinWhite())
		{
			reInit();
			return 1;
		}
		if (checkWinBlack())
		{
			reInit();
			return 2;
		}
		return 0;

}

void World::moveFig(void)
{
	graf.spriteFrame.setOrigin(0, 0);
	cells[currentCursorIndex].numPlayerWhite = numPlayerWhite;
	cells[currentCursorIndex].fillCell(xMouse, yMouse, 1, 1);

	oldCursor.setXY(xMouse, yMouse);
	graf.spriteFrame.setPosition(xMouse, yMouse);
	graf.SFMLView->draw(graf.spriteFrame);
	cntPress = 0;
	numPlayerWhite = cells[currentCursorIndex].numPlayerWhite;
	moveDataCell(0, 0);
		
}


void World::moveDataCell(int indSrc, int indDst)
{
	xMouse = xMouse / WIDTH_CELL;
	int indexX = xMouse - 1;
	xMouse = xMouse * WIDTH_CELL;
	yMouse = yMouse / WIDTH_CELL;
	int indexY = yMouse - 1;
	yMouse = yMouse * WIDTH_CELL;
	int index = getIndex(indexX, indexY);
	cells[oldIndex].moveDataCell(&cells[index]);
	cells[oldIndex].clearCell();
	//надо определить, какой спрайт надо двигать и установить для него новую позицию
	//numPlayerWhite
	players[numPlayerWhite].curPos.setXY(xMouse + 43, yMouse + 43);
	players[numPlayerWhite].spriteBack->setOrigin(32, 32);
	players[numPlayerWhite].spriteBack->setPosition(xMouse + 43, yMouse + 43);
	//cells[indDst] = cells[indSrc];
}

void World::moveFigAI(int x, int y)
{
	x = x / WIDTH_CELL;
	int indexX = x - 1;
	x = x * WIDTH_CELL;
	y = y / WIDTH_CELL;
	int indexY = y - 1;
	y = y * WIDTH_CELL;
	int index = getIndex(indexX, indexY);
	if (index > 63)
		return;
	graf.spriteFrame.setOrigin(0, 0);
	cells[currentCursorIndexAI].numPlayerBlack = numPlayerBlack;
	cells[currentCursorIndexAI].fillCell(x, x, 1, 2);

	oldCursorAI.setXY(x, y);
	graf.spriteFrame.setPosition(x, y);
	graf.SFMLView->draw(graf.spriteFrame);
	//cntPress = 0;
	numPlayerBlack = cells[currentCursorIndexAI].numPlayerBlack;
	moveDataCellAI(x, y,index);

}

void World::moveDataCellAI(int x, int y, int index)
{
	cells[oldIndexAI].moveDataCell(&cells[index]);
	cells[oldIndexAI].clearCell();
	//надо определить, какой спрайт надо двигать и установить для него новую позицию
	//numPlayerWhite
	playersAI[numPlayerBlack].curPos.setXY(x + 43, y + 43);
	playersAI[numPlayerBlack].spriteBack->setOrigin(32, 32);
	playersAI[numPlayerBlack].spriteBack->setPosition(x + 43, y + 43);
	//cells[indDst] = cells[indSrc];
}

int World::checkWinWhite()
{
	int indexX, x,  indexY, y,index,count=0;
	for (int i = 0;i < 9;i++)
	{
		x = players[i].curPos.x / WIDTH_CELL;
		 indexX = x - 1;
		x = x * WIDTH_CELL;
		y = players[i].curPos.y / WIDTH_CELL;
		 indexY = y - 1;
		y = y * WIDTH_CELL;
		 index = getIndex(indexX, indexY);
		if (index > 63)
			return 0;
		for (int j = 0;j < 9;j++)
		{
			if (index == placesStart[j])
			{
				count++;
				break;
			}
		}
	}
	if (count == 9)
		return 1;
	else
		return 0;
}

int World::checkWinBlack()
{
	int indexX, x,  indexY, y, index, count = 0;
	for (int i = 0;i < 9;i++)
	{
		x = playersAI[i].curPos.x / WIDTH_CELL;
		indexX = x - 1;
		x = x * WIDTH_CELL;
		y = playersAI[i].curPos.y / WIDTH_CELL;
		indexY = y - 1;
		y = y * WIDTH_CELL;
		index = getIndex(indexX, indexY);
		if (index > 63)
			return 0;

		for (int j = 0;j < 9;j++)
		{
			if (index == placesEnd[j])
			{
				count++;
				break;
			}
		}
	}
	if (count == 9)
		return 1;
	else
		return 0;
}


void World::stepAI()
{
	int i = 0,count=0;
	int ret = 0;

	while (1)
	{
		//по возможности, ходим вниз-вправо по очереди. После хода отмечаем направление
		//перебираем всех игроков ИИ по очереди, начиная с последнего
		for ( i = indexStepAI; i >= 0; i--)
		{
			//проверяем принципиальную возмохность хода, ходим, если возможности нет, передаем ход следующему
			ret=nextStep(i);
			if (!ret)	//если ход сделан, отмечаем сходившего игрока, выходим
			{
				indexStepAI=i-1;		
				if (indexStepAI < 0)
					indexStepAI = 8;
				return;
			}
			count++;  //тупик
			if (count > 8)
			{
				modeStep = 1;
				return;
			}
		}
		if (count <= 8)
			indexStepAI = 8;  //ни разу не сходили
		else
			return;
	}
}

int  World::getIndexCurPlayerAI(int indexCurPlayerAI)
{
	xCur = playersAI[indexCurPlayerAI].curPos.x / WIDTH_CELL;
	int indexX = xCur - 1;
	if (indexX < 0 || indexX>7)
		return 1;
	xCur = xCur * WIDTH_CELL;
	yCur = playersAI[indexCurPlayerAI].curPos.y / WIDTH_CELL;
	int indexY = yCur - 1;
	if (indexY < 0 || indexY>7)
		return 1;
	yCur = yCur * WIDTH_CELL;
	currentCursorIndexAI = getIndex(indexX, indexY);
	return 0;
}

int  World::nextStep(int indexCurPlayerAI)
{
	if (getIndexCurPlayerAI(indexCurPlayerAI))
		return 1;
	//рисуем курсор
		if (cells[currentCursorIndexAI].checkFig())
		{
			graf.spriteFrame.setOrigin(0, 0);
			oldCursorAI.setXY(xCur, yCur);
			oldIndexAI = currentCursorIndexAI;
			graf.spriteFrame.setPosition(xCur, yCur);
			graf.SFMLView->draw(graf.spriteFrame);
				//надо определить, какой спрайт надо двигать
			numPlayerBlack = cells[currentCursorIndexAI].numPlayerBlack;
		}
		else
		{					//сюда попасть не должно...
			return 1;
		}
			return(nextStepToEnd(xCur, yCur, indexCurPlayerAI));
	
		return 1;
}

int World::getPath(void)
{
	int endIndex = getFreeCell();
	if (endIndex == ARRAY_SIZE)
		return 1;
	else
		getXY(endIndex);
	return 0;
}

int World::checkEnd(int ind)
{
	for (int i = 0;i < 9;i++)
	{
		if (placesEnd[i] == ind)
			return placesEnd[i];
	}
	return 0;
}

int World::nextStepToEnd(int x,int y, int indexCurPlayerAI)
{
	int ret = 0;
	if (getPath())
		return 1;
	int index = getIndex( x/ WIDTH_CELL-1,  y/ WIDTH_CELL-1);
	int difX = xFromIndex - x;
	int difY = yFromIndex - y;
	 ret = checkEnd(index);
	if (ret == 0)
	{
		modeStep = 0;
		if (difX > 0)  //step right
		{
			if (StepRight(x, y, indexCurPlayerAI, 1) == 0)
				return 0;
		}
		else {
			if (!StepLeft(x, y, indexCurPlayerAI, 1))
				return 0;
		}
		if (difY > 0)
		{
			if (!StepBottom(x, y, indexCurPlayerAI, 1))
				return 0;
		}
		else
			ret = StepTop(x, y, indexCurPlayerAI, 1);
		return ret;
	}
	else
	{
		modeStep = 1;
		if (difY > 0)
		{
			if (!StepBottom(x, y, indexCurPlayerAI, 1))
				return 0;
		}
		if (difX > 0)  //step right
		{
			if (StepRight(x, y, indexCurPlayerAI, 1) == 0)
				return 0;
		}
	}
		return 1;
}

int  World::StepBottom(int x, int y, int index,int numCall)
{
	if (getIndexCurPlayerAI(index))
		return 1;
	//пытаемся пойти вниз
	if (currentCursorIndexAI + 8 >= ARRAY_SIZE)
	{
		if (numCall == 2)
			return 1;
		if (StepRight(x, y, index,  2))
		return 1;
		else return 0;
	}
	currentCursorIndexAI += 8;
	if (cells[currentCursorIndexAI ].checkFig() == 0)  //можно
	{
		y = y + WIDTH_CELL;
		if (y > 450)
			return 1;
		
		if(currentCursorIndexAI > 55)
		if (CheckLastPos())
		{
			if(StepRight( x,  y,  index,1))
			return 1;
			else
				return 0;
		}
		if (modeStep == 0)
		if (playersAI[index].bottom_right == 2) //уже ходил вниз
		{
			playersAI[index].bottom_right = 0;
			return 1;
		}
		playersAI[index].bottom_right = 2;
		//currentCursorIndexAI += 8;
		moveFigAI(x, y);
		return 0;
	}
	else
	{		//прыжок?
		currentCursorIndexAI += 8;
		if (currentCursorIndexAI >= ARRAY_SIZE)
			return 1;
		if (cells[currentCursorIndexAI].checkFig() == 0)
		{
			y = y + WIDTH_CELL * 2;					//x = oldCursor.x;
			if (y > 450)
				return 1;
			
			if (currentCursorIndexAI > 47)
			if (CheckLastPos())
			{
				if (StepRight(x, y, index,1))
					return 1;
				else
					return 0;
			}
			if (modeStep == 0)
			if (playersAI[index].bottom_right == 2) //уже ходил вниз
			{
				playersAI[index].bottom_right = 0;
				return 1;
			}
			playersAI[index].bottom_right = 2;
			//currentCursorIndexAI = currentCursorIndexAI + 8;
			moveFigAI(x, y);
			return 0;
		}
		return 1;
	}
}

int  World::StepTop(int x, int y, int index, int numCall)
{
	if (getIndexCurPlayerAI(index))
		return 1;
	if (modeStep == 1)
		return 1;
	//пытаемся пойти вверх
	if (currentCursorIndexAI - 8 <  0)
	{
		//if (numCall == 2)
			return 1;
		//if (StepRight(x, y, index, 2))
		//	return 1;
		//else return 0;
	}
	currentCursorIndexAI -= 8;
	if (cells[currentCursorIndexAI].checkFig() == 0)  //можно
	{
		y = y - WIDTH_CELL;
		if (y <= 50)
			return 1;
		/*
		if (currentCursorIndexAI - 8 > 55)
			if (CheckLastPos())
			{
				if (StepRight(x, y, index, 1))
					return 1;
				else
					return 0;
			}*/
		if (modeStep == 0)
			if (playersAI[index].bottom_right == 3) //уже ходил вверх
			{
				playersAI[index].bottom_right = 0;
				return 1;
			}
		playersAI[index].bottom_right = 3;
		//currentCursorIndexAI -= 8;
		moveFigAI(x, y);
		return 0;
	}
	else
	{		//прыжок?
		currentCursorIndexAI -= 8;
		if (currentCursorIndexAI >= ARRAY_SIZE)
			return 1;
		if (cells[currentCursorIndexAI ].checkFig() == 0)
		{
			y = y - WIDTH_CELL * 2;					
			if (y <= 50)
				return 1;
			/*
			if (currentCursorIndexAI > 47)
				if (CheckLastPos())
				{
					if (StepRight(x, y, index, 1))
						return 1;
					else
						return 0;
				}*/
			if (modeStep == 0)
				if (playersAI[index].bottom_right == 3) //уже ходил вверх
				{
					playersAI[index].bottom_right = 0;
					return 1;
				}
			playersAI[index].bottom_right = 3;
			//currentCursorIndexAI = currentCursorIndexAI - 16;
			moveFigAI(x, y);
			return 0;
		}
		return 1;
	}
}

int  World::StepRight(int x, int y, int index, int numCall)
{
	if (getIndexCurPlayerAI(index))
		return 1;
	//пытаемся пойти вправо
		if (currentCursorIndexAI + 1 >= ARRAY_SIZE)
		{
			if (numCall == 2)
				return 1;
			if (StepBottom(x, y, index,  2))
				return 1;
			else return 0;
		}
		currentCursorIndexAI++;
	if (cells[currentCursorIndexAI].checkFig() == 0)  //можно
	{
		x = x + WIDTH_CELL;
		if (x >= 450)
			return 1;
		
		if (modeStep == 0)
		if (playersAI[index].bottom_right == 1) //уже ходил вправо
		{
			playersAI[index].bottom_right = 0;
			return 1;
		}
		playersAI[index].bottom_right = 1;
		
		moveFigAI(x, y);
		return 0;
	}
	else
	{	//прыжок?
		currentCursorIndexAI++;
		if (currentCursorIndexAI >= ARRAY_SIZE)
			return 1;
		if (cells[currentCursorIndexAI].checkFig() == 0)
		{
			x = x + WIDTH_CELL * 2;					//x = oldCursor.x;x
			if (x >= 450)
				return 1;
			if (modeStep == 0)
			if (playersAI[index].bottom_right == 1) //уже ходил вправо
			{
				playersAI[index].bottom_right = 0;
				return 1;
			}
			playersAI[index].bottom_right = 1;
			//currentCursorIndexAI = currentCursorIndexAI + 2;
			moveFigAI(x, y);

			return 0;
		}
		return 1;
	}
}

int  World::StepLeft(int x, int y, int index, int numCall)
{
	if (getIndexCurPlayerAI(index))
		return 1;
	//пытаемся пойти влево
	if (currentCursorIndexAI -1 < 0)
	{
		//if (numCall == 2)
			return 1;
		//if (StepBottom(x, y, index, 2))
		//	return 1;
		//else return 0;
	}
	currentCursorIndexAI--;
	if (cells[currentCursorIndexAI ].checkFig() == 0)  //можно
	{
		x = x - WIDTH_CELL;
		if (x < 50)
			return 1;
		
		if (modeStep == 0)
			if (playersAI[index].bottom_right == 4) //уже ходил влево
			{
				playersAI[index].bottom_right = 0;
				return 1;
			}
		playersAI[index].bottom_right = 4;
		
		moveFigAI(x, y);
		return 0;
	}
	else
	{	//прыжок?
		currentCursorIndexAI--;
		if (currentCursorIndexAI  >= ARRAY_SIZE)
			return 1;
		if (cells[currentCursorIndexAI ].checkFig() == 0)
		{
			x = x - WIDTH_CELL * 2;					//x = oldCursor.x;x
			if (x < 50)
				return 1;
			if (modeStep == 0)
				if (playersAI[index].bottom_right == 4) //уже ходил вправо
				{
					playersAI[index].bottom_right = 0;
					return 1;
				}
			playersAI[index].bottom_right = 4;
			
			moveFigAI(x, y);

			return 0;
		}
		return 1;
	}
}


int  World::CheckLastPos(void)
{
	if( ( cells[63]. _cell.black_white==2) &&
		(cells[62]._cell.black_white == 2) &&
		( cells[61]._cell.black_white == 2) )
		return 1;
	else return 0;
}

void World::draw()
{
	graf.SFMLView->clear();
	graf.SFMLView->draw(*graf.spriteBack);
	for (int i = 0; i < ARRAY_PLAYERS_SIZE; i++)
	{
		//players[i].spriteBack->setOrigin(players[i].curPos.x + 25, players[i].curPos.y + 25);
		//players[i].spriteBack->setPosition(players[i].spriteBack->getOrigin());
		players[i].draw(&graf);

		//playersAI[i].spriteBack = std::make_unique<sf::Sprite>(graf.texturesBlack[i]);
		//playersAI[i].SFMLView = std::make_unique<sf::RenderWindow>(window);
		playersAI[i].draw(&graf);
	}
	graf.SFMLView->draw(graf.spriteFrame);
	graf.SFMLView->display();
}


int World::getFreeCell(void)
{
	int i = 0;
	for (i = 0;i < 9;i++)
	{
		if (cells[placesEnd[i]].checkFig() == 0)
			break;
	}
	if (i == 9)
		return ARRAY_SIZE;
	return placesEnd[i];
}

