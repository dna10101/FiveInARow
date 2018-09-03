#pragma once
#include<vector>
using namespace std;
#include"Player.h"

class ChessBoard
{
private:
	char **board;
	int width;
	int step = 0;
	int five;
public:
	ChessBoard(int N,int five);
	~ChessBoard();
	boolean Judge(int x, int y, class Player *p);
	boolean SetChess(int x, int y,class Player *p);
	char GetChess(int x, int y);
	void CLeanChessBoard();
	int GetScore(int X, int Y, class Player *P);
	int GetWidth();
};

