#include <iostream>
#include "Game.h"
//#include <math.h>
//#include <time.h>
//#include <cstdlib>
#include <string>
using namespace std;

void welcomeMessage();
void goodbyeMessage(int cond);
void movePrompt(Game& game);
int getDimension(string displayed_type);
Game setsize();

int main()
{
	bool gameOver = false;
	/*int iPassedTurns = 0;*/
	welcomeMessage();
	Game b = setsize();
	b.startingPositions();
	int end = b.endCondition();
	if (end == 0)
	{
		do
		{
			b.displayBoard();
			movePrompt(b);
			b.nextTurn();
			end = b.endCondition();
			/*if (iPassedTurns == 2)
			{
				end = -1;
			}*/
			if (end != 0)
			{
				gameOver = true;
			}
		} while (!gameOver);
	}
	goodbyeMessage(end);
	cin.ignore();
	return 0;
}

void welcomeMessage()
{
	string dump;
	cout << endl;
	cout << " * ~ * . . * ~ * ~ * . . * ~ *\n";
	cout << " * ~ * . W E L C O M E . * ~ *\n";
	cout << " * ~ * . . * ~ * ~ * . . * ~ *\n";
	cout << " * ~ * .  T O  .  M Y  . * ~ *\n";
	cout << " * ~ * . . * ~ * ~ * . . * ~ *\n";
	cout << " * ~ *  C H E C K E R S  * ~ *\n";
	cout << " * ~ * . . * ~ * ~ * . . * ~ *\n";
	cout << " * ~ * .  . G A M E .  . * ~ *\n";
	cout << " * ~ * . . * ~ * ~ * . . * ~ *\n";
	cout << " * .Press ENTER to continue. *\n";
	cout << " * ~ * . . * ~ * ~ * . . * ~ *\n";
	getline(cin, dump);
}

void goodbyeMessage(int cond)
{
	if (cond == -1)
	{
		cout << "\n Wow! A draw! Amazing! You both win!";
	}
	else {
		cout << "\n ~ ~ Great game!\n\n The winner was: ";
		if (cond == 1)
		{
			cout << Game::BLACK << endl << " ~ B L A C K ~";
		}
		if (cond == 2)
		{
			cout << Game::RED << endl << " ~ . R E D . ~";
		}
	}
	cout << "\n\n Thanks for playing! \n\n    Goodbye.";
	cout << "\n * ~ * . . * ~ * ~ * . . * ~ * \n";
	cout << "\n  (c) Copyleft: T.J.Kleinstuber 2018. ";
	cout << "\n Free to share. Not for commercial use.";
	cin.ignore();
}

void movePrompt(Game& b)
{
	string input;
	int trycounter = 0;
	while (trycounter <= 20)
	{
		if ((trycounter + 1) % 3 == 0)
		{
			cout << "\n Please Enter A Valid Move or Capture.";
			cout << "\n Valid moves are composed to two coordinates, with no spaces.";
			cout << "\n Coordinates use the indeces around the edge.";
			cout << "\n Type the coordinate of the piece you want to move,";
			cout << "\n followed by the coordinate of the space you wish to move to.";
			cout << "\n You may also \"PASS\".";
		}

		{
			if (b.bBlacksTurn())
			{
				cout << "\n It is black's (" << b.BLACK << ") turn.\n";
			}
			else
			{
				cout << "\n It is red's (" << b.RED << ") turn.\n";
			}
			cout << "\n Please enter a move in the form A1B0: ";
			cin >> input;
		}
		if (input.length() < 4)
		{
			cout << "\n Input is too short.\n";
			++trycounter;
			continue;
		}
		if (input.length() > 4)
		{
			cout << "\n Input is too long.\n";
			++trycounter;
			continue;
		}
		/*if (input == "PASS")
		{
			++iPassedTurns;
			cout << (b.bBlacksTurn() ? "\n Black has passed." : "\n Red has passed.");
			return;
		}*/
		int sx, sy, ex, ey;
		sx = input[0] - 'A';
		sy = input[1] - '0';
		ex = input[2] - 'A';
		ey = input[3] - '0';

		char pcs = b.chspace(sx, sy);
		char pce = b.chspace(ex, ey);

		if ((b.bBlacksTurn() && (pcs == b.RED)) || (b.bRedsTurn() && (pcs == b.BLACK)))
		{
			cout << "\n You cannot move your opponent's pieces.\n";
			++trycounter;
			continue;
		}

		{
			if (b.validMove(sx, sy, ex, ey))
			{
				b.movePiece(sx, sy, ex, ey);
				/*iPassedTurns = 0;*/
				return;
			}
			else if (b.validCapture(sx, sy, ex, ey))
			{
				b.capturePiece(sx, sy, ex, ey);
				/*iPassedTurns = 0;*/
				b.displayBoard();
				cout << "\nNice Capture! Go again!";
				movePrompt(b);
				return;
			}
			else {
				cout << "\n Please Enter A Valid Move or Capture.\n";
				++trycounter;
				continue;
			}
		}
	}
	{
		cout << "\n Too many attempts. Turn is lost.\n";
		return;
	}
}

int getDimension(string t)
{
	string input;
	int w = -1;
	while (w < 0)
	{
		bool test = true;
		cout << "\n Enter " << t << ": ";
		getline(cin, input);
		if (input.size() > 3)
		{
			cout << "\n Too large.";
			test = false;
			continue;
		}
		for (unsigned int i = 0; i < input.size(); ++i)
		{
			if (input[i] < '0' || input[i] > '9')
			{
				cout << "\n Please enter a number.";
				test = false;
				break;
			}
		}
		if (test)
		{
			w = stoi(input);
			return w;
		}
	}
	return 0;
}

Game setsize()
{
	string input;
	bool done = false;
	
	
	cout << "\n Standard Board? ";
	getline(cin, input);
	if (input[0] == 'Y' || input[0] == 'y')
	{
		return Game(10);
	}
	else
	{
		while (!done)
		{
			int w = getDimension("Width");
			int h = getDimension("Height");
			if ( w < 3 || h < 3)
			{
				cout << "\n Such a small game is trival.";
				continue;
			}
			return Game(h, w);
		}
	}
	return Game();
}




/************************************************************
*															*
*				 ~~brainmagmo~~					*
*                . S E P T  .  2 0 1 8 .					*
*															*
*			   A  C h e c k e r s   G a m e					*
*			Or, "My First Solo Project in C++"				*
*				       VERSION 1.1							*
*															*
*	(c) copyleft: free to share and redistribute and modify	*
*		  		 Not for commercial use.					*
*************************************************************/