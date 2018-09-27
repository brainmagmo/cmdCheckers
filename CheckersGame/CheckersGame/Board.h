#pragma once
class Board
{
public:
	int width;
	int height;
private:
	char* spaces[];
public:
	Board(int size);
	Board(int w, int h);
	/*~Board();*/
	const int Area();
	const int NumOfEmptySpc();
	const int NumOfOccupied();
	//const void DisplayBoard();
	void addPiece(int x, int y, char pc);
	void removePiece(int x, int y);
	void movePiece(int start[], int end[]);
};

