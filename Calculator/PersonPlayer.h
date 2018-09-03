#pragma once
#include "Player.h"
class PersonPlayer :
	public Player
{
public:
	PersonPlayer(char who, class ChessBoard *board);
	~PersonPlayer();
	virtual boolean SetChess(int &x,int &y);
};

