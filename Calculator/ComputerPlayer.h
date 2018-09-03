#pragma once
#include "Player.h"
class ComputerPlayer :
	public Player
{
protected:
	class Player *op_p;
public:
	ComputerPlayer(char who,ChessBoard *board,class Player *p);
	~ComputerPlayer();
	virtual boolean SetChess(int &cx, int &cy);
};

