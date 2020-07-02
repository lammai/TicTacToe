#include "pch.h"
#include <iostream>
#include <string>
#include <locale>
#include <algorithm>

using namespace std;
int computations;
char player;	// The user
char opponent;	// AI
bool isInit;	// is the game at an initial state?

// store position of the X's and O's in TTT
char posTTT[3][3];

// set the board to an empty state
void setGame() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			posTTT[i][j] = ' ';
		}
	}
	computations = 0;
	isInit = true;
}

void displayGrid() {
	system("cls");
	// Display the board with row/ column indicators
	cout << "     0   1   2" << endl
		<< "               " << endl;
	for (int i = 0; i < 3; i++){
		cout << i << "  |";
		for (int j = 0; j < 3; j++){
			cout << " " << posTTT[i][j] << " |";
		}
		cout << endl;
		if (i < 2){
			cout << "   |-----------|" << endl;
		}
	}
	cout << endl;
}

//check if board is full
bool isFull(char board[3][3]) {		
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (board[i][j] == ' '){
				return false;
			}
		}
	}
	return true;
}

// only allow input in blank spot
bool isBlank(char board[3][3], int row, int col) {	
	if (board[row][col] == ' '){
		return true;
	}
	else{
		return false;
	}

}

// only allow valid input for board coordinate
bool checkMove(string move) {	
	if (move.length() > 4 || move.substr(1, 1) != "," || isalpha(move[0]) || isalpha(move[2])){
		return true;
	}
	else if (stoi(move.substr(0, 1)) < 3 && stoi(move.substr(2, 1)) < 3){
		return false;
	}
}




//  0 = tie
//  1 = AI winning
// -1 = player winning
int gameState(char board[3][3]){
	
	for (int i = 0; i < 3; i++){
		// check each row for X win or O win
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2]){
			if (board[i][0] == opponent){
				return 1;
			}
			else if (board[i][0] == player){
				return -1;
			}
		}

		// check each column for X win or O win
		else if (board[0][i] == board[1][i] && board[1][i] == board[2][i]){
			if (board[0][i] == opponent){
				return 1;
			}
			else if (board[0][i] == player){
				return -1;
			}
		}
	}
	// check diagonals
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2]){
		if (board[0][0] == opponent){
			return 1;
		}
		else if (board[0][0] == player){
			return -1;
		}
	}
	else if (board[0][2] == board[1][1] && board[1][1] == board[2][0]){
		if (board[0][2] == opponent){
			return 1;
		}
		else if (board[0][2] == player){
			return -1;
		}
	}
	else{
		return 0;
	}
	
}

// AI function, implementing minimax algorithm
int minimax(char board[3][3], int depth, bool isMaxPlayer) {
	computations++;
	if (gameState(board) == 1 || gameState(board) == -1)
		return gameState(board);
	if (isFull(board))
		return 0;
	if (isMaxPlayer) {		// maximizing for AI
		int bestVal = -9999;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == ' ') {
					board[i][j] = opponent;
					bestVal = max(bestVal, minimax(board, depth + 1, !isMaxPlayer));

					board[i][j] = ' ';
				}
			}
		}
		return bestVal;
	}
	else {					// minimizing for player
		int bestVal = 9999;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == ' ') {
					board[i][j] = player;
					bestVal = min(bestVal, minimax(board, depth + 1, !isMaxPlayer));

					board[i][j] = ' ';
				}
			}
		}
		return bestVal;
	}
}

pair<int, int> findBestMove(char board[3][3]) {
	pair<int, int> bestMove = make_pair(-1, -1);
	int bestVal = -9999;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == ' ') {
				board[i][j] = opponent;
				int moveVal = minimax(board, 0, false);

				board[i][j] = ' ';

				if (moveVal > bestVal) {
					bestMove.first = i;
					bestMove.second = j;
					bestVal = moveVal;
				}
			}
		}
	}
	return bestMove;
}

// start the game
void playGame() {
	setGame();
	int turn;
	char temp;
	cout << "Who go first (X or O): ";
	cin >> temp;
	while (toupper(temp) != 'X' && toupper(temp) != 'O') {
		cout << "Please try again, who go first?: ";
		cin >> temp;
	}
	if (toupper(temp) == player) {
		turn = 1;
	}
	else {
		turn = 0;
	}

	displayGrid();
	cout << "Make your move by typing: \"row #,column #\"" << endl;

	// Game loop
	while (gameState(posTTT) != 1 && gameState(posTTT) != -1 && !isFull(posTTT)) {
		switch (turn) {
		case 0:	// AI turn
		{
			if (isInit)	// if this is the first move for AI, move randomly
				posTTT[rand() % 3][rand() % 3] = opponent;
			else {
				pair<int, int> aiMove = findBestMove(posTTT);
				posTTT[aiMove.first][aiMove.second] = opponent;
				isInit = false;
			}
			if (gameState(posTTT) == 1 || gameState(posTTT) == -1 || isFull(posTTT)) {
				break;
			}
			else {
				turn = 1 - turn;
				displayGrid();
				cout << "CPU calculated " << computations << " steps" << endl;
			}
		}
		case 1:	// player turn
		{
			string currentMove;
			cout << ">> " << player << " move: ";
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
				cout << ">> " << player << " move: ";
				cin >> currentMove;
				while (checkMove(currentMove))
				{
					cout << "Use correct syntax! (Ex: 0,0): ";
					cin >> currentMove;
				}
				x = stoi(currentMove.substr(0, 1));
				y = stoi(currentMove.substr(2, 1));

			}
			posTTT[x][y] = player;
			isInit = false;
			if (gameState(posTTT) == 1 || gameState(posTTT) == -1 || isFull(posTTT)) {
				break;
			}
			else {
				turn = 1 - turn;
				displayGrid();
			}
		}
		}
	}
}

int main() {
	string playAgain = "Y";

	// Intro
	cout << "______________________________\n|   Welcome to Tic Tac Toe   |\n| you already know the rules |" << endl;
	cout << "  Pick X or O: ";
	cin >> player;
	while (toupper(player) != 'X' && toupper(player) != 'O') {
		cout << "Pick X or O: ";
		cin >> player;
	}
	player = toupper(player);
	if (player == 'X') {
		opponent = 'O';
	}
	else if (player == 'O') {
		opponent = 'X';
	}

	while (playAgain == "Y") {
		playGame();
		displayGrid();
		int result = gameState(posTTT);
		if (result == 1) {
			cout << endl << ">> " << opponent << " win! <<" << endl;
		}
		else if (result == -1) {
			cout << endl << ">> " << player << " win! <<" << endl;
		}
		else if (result == 0) {
			cout << endl << ">> Tie <<" << endl;
		}

		cout << "Play again? (Y/N)" << endl;
		cin >> playAgain;
		playAgain = toupper(playAgain[0]);
	}
	system("Pause");
}
