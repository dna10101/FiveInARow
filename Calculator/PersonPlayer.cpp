#include "stdafx.h"
#include "PersonPlayer.h"


PersonPlayer::PersonPlayer(char who, class ChessBoard *board)
{
	this->name = who;
	this->cBoard = board;
}


PersonPlayer::~PersonPlayer()
{
}

boolean PersonPlayer::SetChess(int & x, int & y)
{
	return this->cBoard->SetChess(x,y,this);
}
