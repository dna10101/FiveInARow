#include "stdafx.h"
#include "Player.h"


Player::Player(char who)
{
	this->name = who;
	this->cBoard = NULL;
}

Player::Player(char who, class ChessBoard *board)
{
	this->name = who;
	this->cBoard = board;
}


Player::~Player()
{
	this->cBoard = NULL;
}

boolean Player::SetChess(int &x, int &y)
{
	return this->cBoard->SetChess(x, y,this);
}

char Player::GetName()
{
	return this->name;
}

void Player::SetName(char name)
{
	this->name = name;
}

