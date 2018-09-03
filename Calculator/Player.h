#pragma once
#include"ChessBoard.h"

class Player
{
protected:
	char name;
	class ChessBoard *cBoard;
public:
	Player(){}
	Player(char who);
	Player(char who, class ChessBoard *board);
	~Player();
	virtual boolean SetChess(int &cx, int &cy);
	char GetName();
	void SetName(char name);
};

