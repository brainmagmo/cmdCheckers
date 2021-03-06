#include <iostream>
#include <pch>
using namespace std;

int algToSpc(char cn[]);
int spcToDsp(int spc);
int between(int s, int n);
void fillBaseBoard(char brd[]);
void displayBoard(char brd[]);
bool isValidMove(int s, int n, char spc[]);
bool isValidCapture(int s, int n, char spc[]);
//void updateDisplay(char pcl[], char[]);
void executeMove(int s, int n, char pcl[], char brd[]);
void placePieces(char brd[], char pcl[]);
void executeMove(int s, int n, char pcl[], char brd[]);
void executeCapture(int s, int n, char pcl[], char brd[]);

//takes a space in the form "B3" and converts it into an index for Spaces array
int algToSpc(char space[])
{
	int out = 0;
	int row = space[0] - 'A';
	int column = space[1] - '0';
	if (column == 0) { column += 10; }
	out += row * 5;
	out += (column - 1) / 2;

	return out;
}

//takes an index for a space and gives an index for the display
int spcToDsp(int space)//takes an index for spaces and converts to an index for displayboard
{
	int row = space / 5;
	int column = space % 5;
	int out = 23;
	out += row * 44;
	out += column * 4;
	if (row % 2 == 0)
	{
		out += 2;
	}
	return out;
}

//takes two spaces indeces and returns the space halfway between them
int between(int theStart, int theEnd)
{
	int d = theEnd - theStart;
	int e = (theStart / 5) % 2;
	int x = 0;


	if (e == 1) //odd rows
	{
		switch (d)
		{
		case (11): x = 5;
		case (9): x = 4;
		case (-9): x = -5;
		case (-11): x = -6;
		}
	}
	else { //even rows
		switch (d)
		{
		case (-11): x = -5;
		case (-9): x = -4;
		case (9): x = 5;
		case (11): x = 6;
		}
	}
	return (x + theStart);
}

//initializes borders and pattern
void fillBaseBoard(char BOARD[])
{
	for (int i = 0; i < 22 * 21; i++)
	{
		BOARD[i] = ' ';
	}
	for (int i = 0; i < 22 * 21; i++)
	{

		i % 22 == 0 && i != 0 ? i = i + 22 : i = i;
		BOARD[i] = (i % 2 == 0 ? '+' : '-');
	}
	for (int i = 22; i < 22 * 21; i += 1)
	{
		i % 44 == 0 ? i = i + 22 : i = i;
		if (i % 2 == 0)
		{
			BOARD[i] = '|';
		}
		else if (((i / 22) + 1) % 4 == 0)
		{
			if ((i + 1) % 4 == 0)
			{
				BOARD[i] = '#';
			}
		}
		else if (((i / 22) + 3) % 4 == 0)
		{
			if ((i + 3) % 4 == 0)
			{
				BOARD[i] = '#';
			}
		}
	}

	for (int i = 21; i < 22 * 21; i = i + 1)
	{
		if ((i + 1) % 22 == 0)
		{
			BOARD[i] = '\n';
		}
	}
}

//sends display board to cout
void displayBoard(char thisBoard[])
{
	for (int i = 0; i < 22 * 21; i++)
	{
		if (i % 22 == 0)
		{
			if ((i + 22) % 44 == 0)
			{
				cout << static_cast<char>((i + 22) / 44 + 64);
			}
			else {
				cout << ' ';
			}
		}
		cout << thisBoard[i];
	}
	cout << "  1 2 3 4 5 6 7 8 9 0\n";
};

//checks if target space is empty and one space away and there is a piece to move
bool isValidMove(int moveStart, int moveEnd, char thePieces[])
{
	bool checkPlease = false;
	if (moveStart >= 0 && moveStart < 50 && moveEnd >= 0 && moveEnd < 50) //bounds check
	{
		char s = thePieces[moveStart];

		if (thePieces[moveEnd] == '#' && (s == 'X' || s == 'O'))
		{
			int d = moveStart - moveEnd;
			int e = (moveStart / 5) % 2;  // even and odd rows require separate checks

			if (d == 5 || d == -5)
			{
				checkPlease = true;
			}
			else if (e == 1)
			{
				if (d == 6 || d == -4)
				{
					checkPlease = true;
				}
			}
			else
			{
				if (d == 4 || d == -6)
				{
					checkPlease = true;
				}
			}

		}

	}

	return checkPlease;
}

//checks if target space two away is empty and if an enemy piece is between 
//starting friendly piece and target empty square
bool isValidCapture(int moveStart, int moveEnd, char thePieces[])
{
	bool checkCapt = false;
	int d = moveStart - moveEnd;
	if (d == 9 || d == -9 || d == 11 || d == -11)
	{
		char n = thePieces[moveEnd];
		if (n == '#')
		{
			char s = thePieces[moveStart];
			char b = thePieces[between(moveStart, moveEnd)];
			if (
				(s == 'O' && b == 'X') ||
				(s == 'X' && b == 'O')
				)
			{
				checkCapt = true;
			}
		}
	}


	return checkCapt;
}

//copies piece data only display. !!!unused
/*
void updateDisplay(char Pieces[], char Board[]) { //unused...
	for (int i = 0; i < 50; i++)
	{
		Board[spcToDsp(i)] = Pieces[i];
	}
}
*/

//changes starting and ending chars in piece array and on display
void executeMove(int theStart, int theEnd, char thePieces[], char dispBoard[])
{

	char piece = thePieces[theStart];
	thePieces[theStart] = '#';
	thePieces[theEnd] = piece;

	//updateDisplay(thePieces, dispBoard);
	dispBoard[spcToDsp(theStart)] = '#';
	dispBoard[spcToDsp(theEnd)] = piece;

}

//changes the starting, target, and between chars as appropriate
//!!! inputting "G0E8" does not erase middle piece !!!
void executeCapture(int theStart, int theEnd, char thePieces[], char dispBoard[])
{
	char piece = thePieces[theStart];

	int btw = between(theStart, theEnd);
	thePieces[theStart] = '#';
	thePieces[theEnd] = piece;
	thePieces[btw] = '#';

	//updateDisplay(thePieces, dispBoard);
	dispBoard[spcToDsp(theStart)] = '#';
	dispBoard[spcToDsp(theEnd)] = piece;
	dispBoard[spcToDsp(btw)] = '#';
}

//initializes starting pieces on both arrays.
//!!! has two extra pieces for error testing.
//!!! inputting "G0E8" does not erase middle piece !!!
void placePieces(char drawingBoard[], char pieceLocs[])
{
	for (int i = 0; i < 15; i++)
	{
		pieceLocs[i] = 'X';
		pieceLocs[i + 35] = 'O';
		drawingBoard[spcToDsp(i)] = 'X';
		drawingBoard[spcToDsp(i + 35)] = 'O';
	}
	for (int i = 15; i < 35; i++)
	{
		pieceLocs[i] = '#';
	}
	//test//
	pieceLocs[34] = 'X';
	pieceLocs[29] = 'O';

	//FOR DEBUG: !!!
	drawingBoard[spcToDsp(34)] = 'X';
	drawingBoard[spcToDsp(29)] = 'O';

}

//checks for an abscence of 'O' in pieces
bool isXWinner(char piecesLoc[])
{
	bool Xwinner_ = true;
	for (int i = 0; i < 50; i++)
	{
		if (piecesLoc[i] == 'O') { Xwinner_ = false; }
	}
	return Xwinner_;
}

//checks for an abscence of 'X' in pieces
bool isOWinner(char piecesLoc[])
{
	bool Owinner_ = true;
	for (int i = 0; i < 50; i++)
	{
		if (piecesLoc[i] == 'X') { Owinner_ = false; }
	}
	return Owinner_;
}
int main()
{
	char mainBOARD[22 * 21]; //holds visual board
	char piecesL[50]; //5 per row, 10 rows, stores which piece is on location. 0, 1, 2, 3, 4 is a1, a3, a5, a7, a9
	fillBaseBoard(mainBOARD); //draw the lines
	placePieces(mainBOARD, piecesL); //add X and O pieces

	char move[100]; //to hold input
	char from[2], toward[2];
	int fromI, towardI;
	displayBoard(mainBOARD);
	char g[] = "G0";
	cout << "Welcome to this " << "checkers " << "game.\n"
		<< "Moves are in this form: A1B2.\n";
	do {
		cout << "Please Enter a Move:\n";
		cin.getline(move, 100);
		from[0] = move[0]; from[1] = move[1];
		toward[0] = move[2]; toward[1] = move[3];
		fromI = algToSpc(from); towardI = algToSpc(toward);
		if (isValidMove(fromI, towardI, piecesL)) {
			executeMove(fromI, towardI, piecesL, mainBOARD);
		}
		else if (isValidCapture(fromI, towardI, piecesL)) {
			executeCapture(fromI, towardI, piecesL, mainBOARD);
		}
		else { cout << "Please enter a valid move.\n"; }
		//updateDisplay(piecesL, mainBOARD);
		displayBoard(mainBOARD);
	} while (!(isXWinner(piecesL) ^ isOWinner(piecesL)));
	if (isOWinner(piecesL))
	{
		cout << "You Win!\n";
	}
	else if (isXWinner(piecesL))
	{
		cout << "You Lose.\n";
	}
	else
	{
		cout << "You broke the game!";
		//how did you get here?
	}
}

/************************************************************
*    T R E V O R  .  J O H N . K L E I N S T U B E R	    *
*                . S E P T  .  2 0 1 8 .                    *
*             A  C h e c k e r s   G a m e	                *
*           Or, "My First Solo Project in C++"              *
*   (c) copyleft: free to share and redistribute and modify *
*		  		 Not for commercial use.                    *
*************************************************************/
