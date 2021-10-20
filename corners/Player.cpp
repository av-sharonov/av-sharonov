#include "Player.h"

void Player::move(int deltaX, int deltaY)
{

}

void Player::CalcCurPos()
{

}

void Player::draw(Graphon* gr)
{
	//gr->SFMLView->clear();
	gr->SFMLView->draw(*spriteBack);
	spriteBack->setOrigin(32, 32);
	spriteBack->setPosition(curPos.x, curPos.y);
	//gr->SFMLView->display();
}