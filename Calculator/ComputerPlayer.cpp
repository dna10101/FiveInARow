#include "stdafx.h"
#include "ComputerPlayer.h"


ComputerPlayer::ComputerPlayer(char who, ChessBoard *board,Player *p)
{
	this->name = who;
	this->cBoard = board;
	this->op_p = p;
}


ComputerPlayer::~ComputerPlayer()
{
}

boolean ComputerPlayer::SetChess(int & cx, int & cy)
{
	int x, y, x1, y1;
	int max = 0, max1 = 0;
	int score, score1;
	
	for (int i = 0; i < this->cBoard->GetWidth(); i++)
	{
		for (int j = 0; j <this->cBoard->GetWidth(); j++)
		{
			if (this->cBoard->GetChess(i, j) != 0)
				continue;

			if ((score = this->cBoard->GetScore(i, j, this)) > max)
			{
				x = i;
				y = j;
				max = score;
			}
			if ((score1 = this->cBoard->GetScore(i, j, this->op_p)) > max1)
			{
				x1 = i;
				y1 = j;
				max1 = score1;
			}
		}
	}
	if (max1 == 0 && max == 0)
		return false;
	if (max1 >= max)
	{
		cx = x1;
		cy = y1;
		//this->SetChess(x1, y1);
		
	}
	else
	{
		cx = x;
		cy = y;
		//this->SetChess(x, y);
	}
	return this->cBoard->SetChess(cx, cy, this);
}
