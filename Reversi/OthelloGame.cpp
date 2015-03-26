#include <iostream>
#include "OthelloGame.h"

using namespace std;

void PrintBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
	
	cout << endl;
	cout << "- 0 1 2 3 4 5 6 7" << endl;
	
	for (int r = 0; r < BOARD_SIZE; r++) {
		cout << r << " ";
		for (int c = 0; c < BOARD_SIZE; c++) {
			if (board[r][c] == 1) {
				cout << "B ";
			}
			else if (board[r][c] == -1) {
				cout << "W ";
			}
			else {
				cout << ". ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

bool IsValidMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
	return ((InBounds(row,col) && board[row][col] == 0)
	 || (row == -1 && col == -1)) ? (true) : (false);
}

bool InBounds(int row, int col) {
	return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) ? 
	 (true) : (false);
}

void GetMove(int *row, int *col) {
	 char buffer;
	 cin >> buffer >> *row >> buffer >> *col >> buffer;
}

int GetValue(char board[BOARD_SIZE][BOARD_SIZE]) {
	int value = 0;
	for (int r = 0; r < BOARD_SIZE; r++) {
		for (int c = 0; c < BOARD_SIZE; c++) {
			value += board[r][c];
		}
	}
	return value;
}

void ApplyMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col,
 char currentPlayer) {
	board[row][col] = currentPlayer;
	int r = row;
	int c = col;
	bool canCapture;
	for (int rD = -1; rD <= 1; rD++) {
		for (int cD = -1; cD <= 1; cD++) {
			
			canCapture = false;

			while (InBounds(r + rD, c + cD) && (board[r + rD][c + cD] != 0 && 
			 board[r + rD][c + cD] != currentPlayer)) {
					r += rD; 
					c += cD;
			}

			if (board[r + rD][c + cD] == currentPlayer) {
				canCapture = true;
			}

			while (r != row || c != col) {
				if (canCapture) {
					board[r][c] = currentPlayer;
				} 
				r -= rD;
				c -= cD;
			}
		}
	}
}