#include "pch.h"
#include <iostream>
#include <string>
#include <locale>

using namespace std;

// position of the X's and O's in TTT
char posTTT[3][3] = {	' ',' ',' ',
						' ',' ',' ',
						' ',' ',' ' };

void displayGrid()
{
	system("cls");
	// Display the grid
	cout << "     0   1   2" << endl
		<< "    ___________" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << i << "  |";
		for (int j = 0; j < 3; j++)
		{
			cout << " " << posTTT[i][j] << " |";
		}
		cout << endl;
		if (i < 2)
		{
			cout << "   |-----------|" << endl;
		}
	}
	cout << endl;
}


bool isFull(char board[3][3])		//check if board is full
{
	int space = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == ' ')
			{
				space++;
			}
		}
	}
	if (space == 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool isBlank(char board[3][3], int row, int col)	// only allow input in blank spot
{
	if (board[row][col] == ' ')
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool checkMove(string move)	// only allow valid input for board coordinate
{
	if (move.length() > 4 || move.substr(1, 1) != "," || isalpha(move[0]) || isalpha(move[2]))
	{
		return true;
	}
	else if (stoi(move.substr(0, 1)) < 3 && stoi(move.substr(2, 1)) < 3)
	{
		return false;
	}
}




//  0 = tie
//  1 = X win
// -1 = O win
int gameState(char board[3][3])
{
	
	for (int i = 0; i < 3; i++)		
	{
		// check each row for X win or O win
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
		{
			if (board[i][0] == 'X')
			{
				return 1;
			}
			else if (board[i][0] == 'O')
			{
				return -1;
			}
				
		}
		

		// check each column for X win or O win
		else if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
		{
			if (board[0][i] == 'X')
			{
				return 1;
			}
			else if (board[0][i] == 'O')
			{
				return -1;
			}
				
		}
	}
	// check diagonals
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
	{
		if (board[0][0] == 'X')
		{
			return 1;
		}
		else if (board[0][0] == 'O')
		{
			return -1;
		}
			
	}
	else if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
	{
		if (board[0][2] == 'X')
		{
			return 1;
		}
		else if (board[0][2] == 'O')
		{
			return -1;
		}
			
	}
	else
	{
		return 0;
	}
	
}

void handleTurn(char currentPlayer, string currentMove) {
	cout << ">> " << currentPlayer << " move: ";
	cin >> currentMove;
	while (checkMove(currentMove))
	{
		cout << "Use correct syntax! (Ex: 0,0): ";
		cin >> currentMove;
	}
	int x = stoi(currentMove.substr(0, 1));
	int y = stoi(currentMove.substr(2, 1));
	while (!isBlank(posTTT, x, y)) {
		cout << "Invalid. Please try again!" << endl;
		cout << ">> " << currentPlayer << " move: ";
		cin >> currentMove;
		while (checkMove(currentMove))
		{
			cout << "Use correct syntax! (Ex: 0,0): ";
			cin >> currentMove;
		}
		x = stoi(currentMove.substr(0, 1));
		y = stoi(currentMove.substr(2, 1));

	}
	posTTT[x][y] = currentPlayer;
}


int main()
{
	char player;
	char opponent;
	string playerMove, oppMove;

	cout << "______________________________\n|   Welcome to Tic Tac Toe   |\n| you already know the rules |" << endl;
	cout << "  Pick X or O: ";
	cin >> player;
	while (toupper(player) != 'X' && toupper(player) != 'O')
	{
		cout << "Pick X or O: ";
		cin >> player;
	}
	player = toupper(player);
	if (player == 'X')
	{
		opponent = 'O';
	}
	else if (player == 'O')
	{
		opponent = 'X';
	}

	int turn;
	char temp;
	cout << "Who go first (X or O): ";
	cin >> temp;
	while (toupper(temp) != 'X' && toupper(temp) != 'O')
	{
		cout << "Seriously, who go first?: ";
		cin >> temp;
	}
	if (toupper(temp) == player)
	{
		turn = 1;
	}
	else
	{
		turn = 0;
	}

	displayGrid();
	cout << "Make your move by typing: \"row,column\"" << endl;
	while (gameState(posTTT) != 1 && gameState(posTTT) != -1 && !isFull(posTTT))
	{
		
		switch (turn)
		{
		case 0:
		{
			handleTurn(opponent, oppMove);

			if (gameState(posTTT) == 1 || gameState(posTTT) == -1 || isFull(posTTT))
			{
				break;
			}
			else {
				turn = 1 - turn;
				displayGrid();
			}
			
			
		}
		case 1:
		{
			handleTurn(player, playerMove);

			if (gameState(posTTT) == 1 || gameState(posTTT) == -1 || isFull(posTTT))
			{
				break;
			}
			else {
				turn = 1 - turn;
				displayGrid();
			}
		}

		}
	}

	displayGrid();
	int result = gameState(posTTT);
	if (result == 1)
	{
		cout << endl << ">> X win! <<" << endl;
	}
	else if (result == -1)
	{
		cout << endl << ">> O win! <<" << endl;
	}
	else if (result == 0)
	{
		cout << endl << ">> Tie <<" << endl;
	}
	system("Pause");
}
