#pragma once
#include "data.h"
#include <SFML\Graphics.hpp>
#include "Graphon.h"


class Player
{
public:
	Player() { 
		curPos.setXY(0, 0); 		oldPos.setXY(0, 0);
		//curStep = 0;  active = false;  number = 0; 
	};
	void init(int num,int offset) {
		curPos.x = offset + (num % 3)* 50;
		curPos.y = offset + (num / 3) * 50;
	};
	void draw(Graphon*gr);
protected:
	void move(int deltaX, int deltaY);  //1,0;0,1;...
	void CalcCurPos();
	point GetCurPos() { return curPos; };
	
//data
public:
	point curPos;
	point oldPos;
	int curStep=0;
	bool active=false;
	int number=0;
	std::unique_ptr<sf::Sprite> spriteBack;
	std::unique_ptr<sf::RenderWindow> SFMLView;
};

