#include "stdafx.h"
#include "ChessBoard.h"

#define		FIVE	100000
#define		ALIVE4	50000
#define		DIE4A	250
#define		DIE4B	300
#define		DIE4C	260
#define		ALIVE3	300
#define		jALIVE3	200
#define		DIE3A	50
#define		DIE3B	80
#define		DIE3C	60
#define		DIE3D	55
#define		DIE3E	45
#define		DIE3F	20
#define		ALIVE2	65
#define		OTHER	10


ChessBoard::ChessBoard(int N,int five)
{
	this->width = N;
	this->five = five;
	this->board = new char*[N]();
	for (int i = 0; i < N; i++)
	{
		this->board[i] = new char[N]();
	}
}


ChessBoard::~ChessBoard()
{
	for (int i = 0; i < this->width; i++)
	{
		delete[]this->board[i];
	}
	delete[]this->board;
}

boolean ChessBoard::Judge(int cx, int cy, Player * p)
{
	int left = 0, right = 0;
	char currentChar = this->board[cx][cy];
	int x = cx,y=cy;
	//横线情况 —
	while (--x>= 0)
	{
		if (this->board[x][y] == currentChar)
		{
			left++;
		}
		else
		{
			break;
		}
	}
	x = cx;
	while (++x < this->width)
	{
		if (this->board[x][y] == currentChar)
		{
			right++;
		}
		else
		{
			break;
		}
	}
	if (right + left + 1 >= this->five)
	{
		return 1;
	}

	//   对角线情况 '\'
	left = right = 0;
	x = cx;
	y = cy;
	while ((--x)>= 0 && (++y) < this->width)
	{
		if (this->board[x][y] == currentChar)
		{
			left++;
		}
		else
		{
			break;
		}
	}
	x = cx;
	y = cy;
	while ((++x < this->width) && (--y>=0))
	{
		if (this->board[x][y] == currentChar)
		{
			right++;
		}
		else
		{
			break;
		}
	}
	if (right + left + 1 >= this->five)
	{
		return 1;
	}

	//竖线情况 |
	left = right = 0;
	x = cx;
	y = cy;
	while ((--y) >= 0)
	{
		if (this->board[x][y] == currentChar)
		{
			left++;
		}
		else
		{
			break;
		}
	}
	y = cy;
	while ((++y) <= this->width)
	{
		if (this->board[x][y] == currentChar)
		{
			right++;
		}
		else
		{
			break;
		}
	}
	if (left + right + 1 >= this->five)
	{
		return 1;
	}

	//对角线情况 ‘/’
	left = right = 0;
	x = cx;
	y = cy;	
	while ((--x)>= 0 && (--y)>=0)
	{
		if (this->board[x][y] == currentChar)
		{
			left++;
		}
		else
		{
			break;
		}
	}
	x = cx;
	y = cy;
	while ((++x <this->width) && (++y <this->width))
	{
		if (this->board[x][y] == currentChar)
		{
			right++;
		}
		else
		{
			break;
		}
	}
	if (right + left + 1 >= this->five)
	{
		return 1;
	}

	return 0;
}

boolean ChessBoard::SetChess(int x, int y, Player *p)
{
	if (x < 0 || y < 0 || x >= this->width || y >=this->width)
		return false;
	if (this->board[x][y] == 0)
	{
		this->board[x][y] = p->GetName();
		this->step++;
		return true;
	}
	return false;
}

char ChessBoard::GetChess(int x, int y)
{
	if (x<0 || x>this->width || y<0 || y>this->width)
		return -1;
	return this->board[x][y];
}

void ChessBoard::CLeanChessBoard()
{
	for (int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->width; j++)
			this->board[i][j] = 0;
	}
	
}

int ChessBoard::GetScore(int X, int Y, Player * p)
{

	int maxScore;
	int count;
	int left = 0, right = 0;
	int x = X;
	int y = Y;
	//横线
	while (--x>=0)
	{
		if (this->board[x][y] == p->GetName())
		{
			left++;
		}
		else
		{
			break;
		}
	}
	x = X;
	while (++x < this->width)
	{
		if (this->board[x][y] == p->GetName())
		{
			right++;
		}
		else
		{
			break;
		}
	}
	x = X;

	count = left + right + 1;
	switch (count)
	{
	case 4:
		maxScore = ALIVE4;
		break;
	case 3:
		maxScore = ALIVE3;
		break;
	case 2:
		maxScore = ALIVE2;
		break;
	case 1:
		maxScore = OTHER;
		break;
	default:
		maxScore = FIVE;
		break;
	}

	left = right = 0;
	//竖线
	while (--y>=0)
	{
		if (this->board[x][y] == p->GetName())
		{
			left++;
		}
		else
		{
			break;
		}
	}
	y = Y;
	while (++y <this->width)
	{
		if (this->board[x][y] == p->GetName())
		{
			right++;
		}
		else
		{
			break;
		}
	}
	y = Y;

	count = left + right + 1;
	switch (count)
	{
	case 4:
		maxScore += ALIVE4;
		break;
	case 3:
		maxScore += ALIVE3;
		break;
	case 2:
		maxScore += ALIVE2;
		break;
	case 1:
		maxScore += OTHER;
		break;
	default:
		maxScore += FIVE;
		break;
	}

	left = right = 0;
	//斜线\*
	while (--x>=0 && --y>=0)
	{
		if (this->board[x][y] == p->GetName())
		{
			left++;
		}
		else
		{
			break;
		}
	}
	x = X;
	y = Y;
	while (++x <this->width && ++y <this->width)
	{
		if (this->board[x][y] == p->GetName())
		{
			right++;
		}
		else
		{
			break;
		}
	}
	x = X;
	y = Y;

	count = left + right + 1;
	switch (count)
	{
	case 4:
		maxScore += ALIVE4;
		break;
	case 3:
		maxScore += ALIVE3;
		break;
	case 2:
		maxScore += ALIVE2;
		break;
	case 1:
		maxScore += OTHER;
		break;
	default:
		maxScore += FIVE;
		break;
	}

	//
	left = right = 0;
	//斜线/*
	while (++x <this->width && --y>=0)
	{
		if (this->board[x][y] == p->GetName())
		{
			left++;
		}
		else
		{
			break;
		}
	}
	x = X;
	y = Y;
	while (--x > 0 && ++y <= this->width)
	{
		if (this->board[x][y] == p->GetName())
		{
			right++;
		}
		else
		{
			break;
		}
	}
	x = X;
	y = Y;

	count = left + right + 1;
	switch (count)
	{
	case 4:
		maxScore += ALIVE4;
		break;
	case 3:
		maxScore += ALIVE3;
		break;
	case 2:
		maxScore += ALIVE2;
		break;
	case 1:
		maxScore += OTHER;
		break;
	default:
		maxScore += FIVE;
		break;
	}
	return maxScore;
}

int ChessBoard::GetWidth()
{
	return this->width;
}
