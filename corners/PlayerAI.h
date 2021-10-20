#pragma once
#include "Player.h"

class PlayerAI :  public Player
{
public:
    PlayerAI() {
        Player();
    };
    //void initPlayerAI();
protected:
    bool calcNextStep();
    bool checkCell(int x, int y);
    void initAI(int num, int offset)
    {

    }

//data
public:
    int curPos_inList=0;
    int bottom_right = 0;  //bottom=0,right=1
    int makeStep = 0;  //1 = step

};

