#include "pch.h"
#include "Game.h"

#include <math.h>
#include <time.h>
#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;

Game::Game()
{
	width = 0;
	height = 0; for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			spaces[i*width + j] = blank(i, j); //should replace arithmatic with a func that returns a pointer
		}
	}
}

Game::Game(int s)
{
	width = s;
	height = s;
	//assumes spaces holds at least width*height
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			spaces[i*width + j] = blank(i, j); //should replace arithmatic with a func that returns a pointer
		}
	}

}

Game::Game(int h, int w)
{
	width = w;
	height = h;
	//assumes spaces holds at least width*height
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			spaces[i*width + j] = blank(i, j); //i should abstract the board and use a pointer here
		}
	}
}

Game::~Game() // do I need this?
{
	//delete  spaces;
}

int Game::area() const
{
	return width * height;
}

int Game::numOfEmptySpc() const
{
	int count = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (isEmptySpc(i, j))
			{
				count++;
			}
		}
	}
	return count;
}
int Game::numOfOccupied() const
{
	int count = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (!isEmptySpc(i, j))
			{
				count++;
			}
		}
	}
	return count;
}
void Game::startingPositions()
{
	char pc = RED;
	for (int i = 0; i < height; i++)
	{
		if (i == ((height + 1) / 3)) { pc = '.'; }  //i want to abstract this <
		if (i == (height - ((height + 1) / 3))) { pc = BLACK; }
		for (int j = 0; j < width; j++)
		{
			if (!static_cast<bool>((i + j) % 2))
			{
				spaces[i*width + j] = pc;
			}
		}
	}
}
void Game::startingPositionsRand()
{
	srand(time(0));
	for (int i = 1; i < height; i++)
	{
		for (int j = 1; j < width; j++)
		{
			if (!static_cast<bool>((i + j) % 2))
			{
				int I = ((i - 1) % height);
				int J = ((j - 1) % width);
				if ((rand() % 9 == 0) && isEmptySpc(i,j) && isEmptySpc(I,J))
				{ spaces[i*width + j] = BLACK;
					spaces[(I * width) + J] = RED;
				}
			}
		}
	}
}

char Game::blank(int x, int y) const
{
	if (static_cast<bool>((x + y) % 2))
	{
		return ' ';
	}
	else {
		return '.';
	}
}
bool Game::isEmptySpc(int x, int y) const
{
	char c = chspace(x, y);
	return (c == ' ' || c == '.');
}

bool Game::validMove(int sx, int sy, int ex, int ey) const
{
	bool r = false;
	if (isEmptySpc(ex, ey) && !isEmptySpc(sx, sy))
	{
		int dx = sx - ex;
		int dy = sy - ey;
		if ((dx == 1 || dx == -1) && (dy == -1 || dy == 1))
		{
			r = true;
		}
	}
	return r;
}

bool Game::validCapture(int sx, int sy, int ex, int ey) const
{
	int dx = ex - sx;
	int dy = ex - sx;
	return (
		(dx == 2 || dx == -2) && (dy == 2 || dy == -2)
		);
}

// returns -1 if the board is empty (a draw)
// returns 0 if red and black are still on the board
// returns 1 if Black won 
// returns 2 if Red won
int Game::endCondition() const
{
	int redPcs = 0;
	int blkPcs = 0;
	int ret = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (!isEmptySpc(i, j))
			{
				chspace(i, j) == BLACK ? blkPcs++ : redPcs++;

				if (blkPcs > 0 && redPcs > 0)
				{
					break;
				}
			}
		}
	}
	if (blkPcs == 0 && redPcs == 0) { ret = -1; }
	if (blkPcs > 0 && redPcs == 0) { ret = 1; }
	if (blkPcs == 0 && redPcs > 0) { ret = 2; }
	return ret;
}

char Game::chspace(int x, int y) const
{
	return spaces[x*width + y];
}

void Game::displayBoard() const
{
	cout << endl;
	for (int i = 0; i < height; i++)       //for each row
	{
		for (int j = 0; j < width; j++)    //decorate a horizontal line
		{
			cout << '+' << '-';
			if (width > 10)
			{
				cout << "--";
			}
		}
		cout << '+' << endl << '|';

		for (int j = 0; j < width; j++)    // populate vertical separated characters/blanks
		{
			if (width > 10)
			{
				cout << ' ';
			}
			cout << chspace(i, j);
			if (width > 10)
			{
				cout << ' ';
			}
			cout << '|';
		}
		cout << (char)('A' + i) << endl; // row index

	}
	for (int j = 0; j < width; j++) // bottom line
	{
		cout << '+' << '-';
		if (width > 10)
		{
			cout << "--";
		}
	}
	cout << '+' << endl;

	for (int j = 0; j < width; j++) // column index
	{
		if (width > 10)
		{
			cout << setw(4)  << j;
		}
		else {
			cout << setw(2) << j;
		}
	}
	cout << endl;
}

void Game::nextTurn()
{
	blkTurn = !blkTurn;
}

bool Game::bBlacksTurn() const
{
	return blkTurn;
}

bool Game::bRedsTurn() const
{
	return !blkTurn;
}

void Game::setPiece(int row, int column, char piece)
{
	if (isEmptySpc(row, column))
	{
		spaces[row*width + column] = piece;
	}

}

void Game::popPiece(int row, int column)
{
	if (!isEmptySpc(row, column))
	{
		spaces[row*width + column] = blank(row, column);
	}
}

void Game::movePiece(int sx, int sy, int ex, int ey)
{
	if (!isEmptySpc(sx, sy) && isEmptySpc(ex, ey))
	{
		setPiece(ex, ey, chspace(sx, sy));
		popPiece(sx, sy);
	}
}

void Game::capturePiece(int sx, int sy, int ex, int ey)
{
	movePiece(sx, sy, ex, ey);
	popPiece(sx + ((ex - sx) / 2), sy + ((ey - sy) / 2));
}
