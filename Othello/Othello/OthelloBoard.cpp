#include <vector>
#include "OthelloBoard.h"

OthelloBoard::OthelloBoard() : mValue(0), mNextPlayer(BLACK), mPassCount(0) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			mBoard[i][j] = 0;	
		}
	}
	mBoard[3][3] = WHITE;
	mBoard[3][4] = BLACK;
	mBoard[4][3] = BLACK;
	mBoard[4][4] = WHITE;
 }

 void OthelloBoard::ApplyMove(OthelloMove *move) {
	
	mHistory.push_back(move);

	if ( move->IsPass() ) {
		mPassCount++;
	}
	else {
	
	mPassCount = 0;
	mBoard[move->mRow][move->mCol] = mNextPlayer;
	mValue += mNextPlayer;

		for (int rD = -1; rD <= 1; rD++) {
			for (int cD = -1; cD <= 1; cD++) {
				
				int r = move->mRow;
				int c = move->mCol;	
				int flipped = 0;

				while (InBounds(r + rD, c + cD) && (mBoard[r + rD][c + cD] != 0 && 
				 mBoard[r + rD][c + cD] != mNextPlayer)) {
					r += rD; 
					c += cD;
				}

				if (InBounds(r + rD, c+ cD) && mBoard[r + rD][c + cD] ==
				 mNextPlayer && (r != move->mRow || c != move->mCol)) {
					while (r != move->mRow || c != move->mCol) {
						mBoard[r][c] = mNextPlayer;
						flipped++;
						mValue += 2*mNextPlayer; 
						r -= rD;
						c -= cD;
					}
					move->AddFlipSet(OthelloMove::FlipSet(flipped, rD, cD));
				}

			}
		}
	}

	(mNextPlayer == WHITE) ? mNextPlayer = BLACK : mNextPlayer = WHITE;

}

void OthelloBoard::GetPossibleMoves(std::vector<OthelloMove *> *list) const {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			
			bool possibleMove = false;

			if ( mBoard[i][j] == 0 ) {
				
				for (int rD = -1; rD <= 1; rD++) {
					for (int cD = -1; cD <= 1; cD++) {
						
						int row = i;
						int col = j;

						if (!(rD == 0 && cD == 0 )) {
							
							while (InBounds(row + rD, col + cD) && 
							 (mBoard[row + rD][col + cD] != 0 && 
							 mBoard[row + rD][col + cD] != mNextPlayer)) {
								row += rD;
								col += cD;
							}

							if (InBounds(row + rD, col + cD) && 
							 mBoard[row + rD][col + cD] == mNextPlayer 
							 && (row != i || col != j)) {
								possibleMove = true;
								break;		
							}

						}
					}

					if (possibleMove) {
						OthelloMove *move = CreateMove();
						move->mRow = i;
						move->mCol = j;
						list->push_back(move);
						break;
					}

				}
			}
		}
	}

	if (list->size() == 0) {
		list->push_back(CreateMove());
	}

}

void OthelloBoard::UndoLastMove() {

	if ( mHistory.back()->IsPass() ) {
		mPassCount--;
	}

	else {

		auto flips = mHistory.back()->mFlips;
		mValue -= mBoard[mHistory.back()->mRow][mHistory.back()->mCol];
		mBoard[mHistory.back()->mRow][mHistory.back()->mCol] = 0;

		for (auto itr = flips.begin(); itr != flips.end(); itr++) {
			
			int flipped = itr->switched;
			int r = mHistory.back()->mRow;
			int c = mHistory.back()->mCol;

			while (flipped != 0) {
				r += itr->rowDelta;
				c += itr->colDelta;
				mBoard[r][c] = -mBoard[r][c];
				mValue += 2*mBoard[r][c];
				flipped--;
			}

		}

	}

	mNextPlayer = -mNextPlayer;
	delete mHistory.back();
	mHistory.pop_back();
}
