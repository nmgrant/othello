const int BOARD_SIZE = 8;

void PrintBoard(char board[BOARD_SIZE][BOARD_SIZE]);
bool InBounds(int row, int col);
bool IsValidMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);
void GetMove(int *row, int *col);
void ApplyMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, 
 char currentPlayer);
int GetValue(char board[BOARD_SIZE][BOARD_SIZE]);