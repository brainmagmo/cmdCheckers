#pragma once
#include <string>
#include <iostream>
using namespace std;
class Game
{
public:
	Game();
	//some of these should be private?
	Game(int s);
	Game(int h, int w);
	int width;
	int height;
	void movePiece(int startx, int starty, int endx, int endy);
	//x is a vertical coord, y is a horizontal coord
	bool isEmptySpc(int x, int y) const;
	char chspace(int x, int y) const;
	char blank(int x, int y) const;
	int area() const;
	int numOfEmptySpc() const;
	int numOfOccupied() const;
	void displayBoard() const;
	//game-specific:
	void nextTurn();
	bool bBlacksTurn() const;
	bool bRedsTurn() const;
	static const char BLACK = '%';
	static const char RED = '@';
	bool validMove(int sx, int sy, int ex, int ey) const;
	bool validCapture(int sx, int sy, int ex, int ey) const;
	int endCondition() const;
	void startingPositions();
	void startingPositionsRand();
	void capturePiece(int sx, int sy, int ex, int ey);
	~Game();
protected:
	bool blkTurn = false;

	void setPiece(int x, int y, char pc);
	void popPiece(int x, int y);
	char spaces[3276] = {};
};

