/***********************************************************************
* Program:
*    Lesson 08, Tic-Tac-Toe
* Summary:
*    This program reads, displays, and writes a Tic-Tac-Toe board
************************************************************************/

#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

#define P1_CHAR 'X'
#define P2_CHAR 'O'
#define EMPTY_CHAR '.'
#define BOARD_SIZE 3

bool read(char board[][BOARD_SIZE], const char* fileName);
bool write(const char board[][BOARD_SIZE], const char* fileName);
void display(const char board[][BOARD_SIZE]);
bool didWin(const char board[][BOARD_SIZE], char turn);

/**********************************************************************
 * Keeps the data and calles the read/display/write functions
 ***********************************************************************/
int main()
{
	char board[BOARD_SIZE][BOARD_SIZE];

	// read the board
	char fileName[256];
	cout << "Enter source filename: ";
	cin >> fileName;
	if (!read(board, fileName))
	{
		cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
		return 1;
	}

	// display the board
	display(board);

	// write the board to a file
	cout << "Enter destination filename: ";
	cin >> fileName;
	if (!write(board, fileName))
	{
		cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
		return 1;
	}

	return 0;
}

/**************************************************************
 * READ
 * Read the board from the specified filename
 *************************************************************/
bool read(char board[][BOARD_SIZE], const char* fileName)
{
	assert(*fileName);

	// open the file
	ifstream fin(fileName);
	if (fin.fail())
		return false;

	// read 9 symbols, hopefully they are . X O
	for (int r = 0; r < BOARD_SIZE; r++)
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			fin >> board[r][c];
			assert(!fin.fail());
			assert(board[r][c] == P1_CHAR ||
				board[r][c] == P2_CHAR ||
				board[r][c] == EMPTY_CHAR);
		}

	// close the file
	fin.close();
	return true;
}

/**********************************************************
 * WRITE
 * Write to fileName the board data
 *********************************************************/
bool write(const char board[][BOARD_SIZE], const char* fileName)
{
	assert(fileName[0] != '\0');

	// open the file
	ofstream fout(fileName);
	if (fout.fail())
		return false;

	// write my 9 symbols
	for (int r = 0; r < BOARD_SIZE; r++)
		for (int c = 0; c < BOARD_SIZE; c++)
			fout << board[r][c] << (c == 2 ? '\n' : ' ');

	// close it!
	fout.close();
	cout << "File written\n";
	return true;
}

/*******************************************************
 * DISPLAY
 * Display the contents the the screen
 *****************************************************/
void display(const char board[][BOARD_SIZE])
{
	// loop through each row
	for (int r = 0; r < BOARD_SIZE; r++)
	{
		// only the first row is not preceeded with the --+-- magic
		if (r != 0)
			cout << "---+---+---\n";

		// now, on each row, do the column stuff
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			// display a space for the dot
			if (board[r][c] == '.')
				cout << "   ";
			else
				cout << " " << board[r][c] << " ";

			// end with a | or a newline
			cout << (c == 2 ? '\n' : '|');
		}
	}

	// display who won
	if (didWin(board, P1_CHAR))
		cout << P1_CHAR << " won!\n";
	if (didWin(board, P2_CHAR))
		cout << P2_CHAR << " won!\n";

	return;
}

/********************************************
 * DID WIN
 * Did a given player (determined by the "turn"
 * variable) win the game?
 *******************************************/
bool didWin(const char board[][BOARD_SIZE], char turn)
{
	// check column wins
	for (int r = 0; r < BOARD_SIZE; r++)
	{
		int inACol = 0;
		for (int c = 0; c < BOARD_SIZE; c++)
			if (board[r][c] == turn)
				inACol++;

		if (inACol >= BOARD_SIZE)
			return true;
	}
	// check row wins
	for (int c = 0; c < BOARD_SIZE; c++)
	{
		int inARow = 0;
		for (int r = 0; r < BOARD_SIZE; r++)
			if (board[r][c] == turn)
				inARow++;

		if (inARow >= BOARD_SIZE)
			return true;
	}
	// check \ diagnal
	int inDiagBack = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		int thisChar = board[i][i];
		if (thisChar == turn)
			inDiagBack++;
		if (inDiagBack >= BOARD_SIZE)
			return true;
	}
	// check / diagnal
	int inDiagFront = 0;
	for (int i = BOARD_SIZE; i >= 0; i--)
	{
		if (board[i][i] == turn)
			inDiagFront++;
		if (inDiagFront >= BOARD_SIZE)
			return true;
	}
	return false;
}
