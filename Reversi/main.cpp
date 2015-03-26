#include <iostream>
#include "OthelloGame.h"

using namespace std;

int main(int argc, char* argv[]) {
	const int BOARD_SIZE = 8;
	int row, col;
	bool pass, playerBlack;
	bool blackPass = false;
	bool whitePass = false;
	char currentPlayer = 1;
	
	char board[BOARD_SIZE][BOARD_SIZE] = {
		{0, 0, 0, 0, 0, 0, 0, 0},	
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, -1, 1, 0, 0, 0},
		{0, 0, 0, 1, -1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
	};

	while (!(whitePass && blackPass)) {
			
			PrintBoard(board);

			if (currentPlayer == 1) {
				playerBlack = true;
				cout << "Black's turn." << endl;
			}
			else {
				playerBlack = false;
				cout << "White's turn." << endl;
			}
			
			do {
				cout << "Please enter a valid move: " << endl;
				GetMove(&row, &col);
			} while (!IsValidMove(board,row,col));
			
			if (!(row == -1 && col == -1)) {
				ApplyMove(board, row, col, currentPlayer);
				pass = false;
			}
			else {
				pass = true;
			}

			currentPlayer = (playerBlack ? (-1) : (1));
			playerBlack ? (blackPass = pass) : (whitePass = pass);

	}
	if (GetValue(board) > 0) {
		cout << "Black wins!" << endl;
	}
	else if (GetValue(board) < 0) {
		cout << "White wins!" << endl;
	}
	else {
		cout << "Tie game!" << endl;
	}
}