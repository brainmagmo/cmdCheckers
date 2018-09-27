#include "pch.h"
#include "Board.h"


Board::Board(int size)
{
	width = size;
	height = size;
	spaces[height][width] = ' ';
}

Board::Board(int w, int h)
{
	width = w;
	height = h;
	spaces[height][width] = ' ';
}

const int Board::Area()
{
	return width*height;
}

const int Board::NumOfEmptySpc()
{
	int count = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j <  width; j++)
		{
			if (spaces[i][j] == ' ') { count++; }
		}
	}
	return count;
}

const int Board::NumOfOccupied()
{
	int count = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (spaces[i][j] != ' ') { count++; }
		}
	}
	return count;
}



void Board::addPiece(int row, int column, char piece)
{
	/*if (0 > row || 0 > column || row >= height || column >= width)
	{
		throw "Out of range!";
	}
	if (spaces[row][column] != ' ')
	{
		throw "Space is occupied or invalid!";
	}*/
	spaces[row][column] = piece;

}

void Board::removePiece(int row, int column)
{
	/*
	if (0 > row || 0 > column || row >= height || column >= width)
	{
		throw "Out of range!";
	}
	if (spaces[row][column] == ' ')
	{
		throw "Space is already empty!";
	}
	*/
	spaces[row][column] = ' ';
}

void Board::movePiece(int start[], int end[])
{
	char piece = spaces[start[0]][start[1]];
	removePiece(start[0], start[1]);
	addPiece(end[0], end[1], piece);
}
