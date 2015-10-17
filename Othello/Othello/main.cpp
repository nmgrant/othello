#include "OthelloExceptions.h"
#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {

	// Initialization
	OthelloBoard board; // the state of the game board
	OthelloView v(&board); // a View for outputting the board via operator<<
	string userInput; // a string to hold the user's command choice
	vector<OthelloMove *> possMoves; // a holder for possible moves
	bool quit = false;

	// Main loop
	do {
		// Print the game board using the OthelloView object
		cout << v << endl;

		(board.GetNextPlayer() == OthelloBoard::Player::BLACK) ?
		 (cout << "Black's move" << endl << endl) :
		 (cout << "White's move" << endl << endl);

		// Print all possible moves
		board.GetPossibleMoves(&possMoves);

		cout << endl << "Possible moves: " << endl;
		for (OthelloMove *move : possMoves) {
			cout << move->operator std::string() << " ";
		}

		cout << endl << endl;
		for (OthelloMove *m : possMoves) {
			delete m;
		}
		possMoves.clear();

		// Ask to input a command
		// Command loop:
		// move (r,c)
		// undo n
		// showValue
		// showHistory
		// quit
		do {
			cout << endl << "Enter a command: ";

			getline(cin,userInput);

			if (userInput.find("showValue") == 0) {
				cout << endl << "Board value: " << board.GetValue() << endl;
			}

			else if (userInput.find("showHistory") == 0) {
				
				cout << endl;
				auto hist = board.GetMoveHistory();
				char currentPlayer = board.GetNextPlayer();

				for (auto itr = hist->rbegin(); itr != hist->rend(); itr++) {

					if (currentPlayer == OthelloBoard::Player::BLACK) {
						cout << "White: " << (*itr)->operator std::string() << endl;
					}

					else {
						cout << "Black: " << (*itr)->operator std::string() << endl;
					}

					currentPlayer = -currentPlayer;

				}

			}

			else if (userInput.find("move") == 0) {

				bool isValid = false;
				OthelloMove *move = board.CreateMove();

				try {

					*move = userInput.substr(5, userInput.size() - 5);

					board.GetPossibleMoves(&possMoves);

					for (OthelloMove *m : possMoves) {
						if ( *move == *m ) {
							isValid = true;
						}
					}

					cout << endl << endl;
					for (OthelloMove *m : possMoves) {
						delete m;
					}
					possMoves.clear();

					if (isValid) {
						board.ApplyMove(move);
						break;
					}
					else {
						cout << endl << "Not a valid move." << endl;
						delete move;
					}

				} catch (OthelloException& e) {
					cout << endl << e.what() << endl << endl;
					delete move;
				}

			}

			else if (userInput.find("undo") == 0) {
				
				istringstream iss;
				int undoMoves;

				iss.str(userInput.substr(5, userInput.size() - 5));
				iss >> undoMoves;

				while (undoMoves != 0 && board.GetMoveCount() != 0) {
					board.UndoLastMove();
					undoMoves--;
				}

				break;

			}

			else if (userInput.find("quit") == 0) {
				quit = true;
			}

			else {
				cout << endl << "Invalid input.";
			}

		} while (!quit);

	} while (!board.IsFinished() && !quit); 

	int value = board.GetValue();
	(value > 0) ? (cout << endl << "Game over. Black wins!") << endl :
	 (value < 0) ? (cout << endl << "Game over. White wins!") << endl :
	 (cout << endl << "Game over. We have a tie!" << endl);

}