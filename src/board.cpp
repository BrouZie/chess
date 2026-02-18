#include "board.h"
#include <iostream>

Board::Board()
{
  int rows_with_pieces[] = { 0, 1, 6, 7 };
  for (int row : rows_with_pieces) {
    for (int col {}; col < 8; ++col) {
      board[row][col] = 1;
    }
  }
};

void Board::printBoard()
{
  for (int i {}; i < 8; ++i) {
    for (int j {}; j < 8; ++j) {
      std::cout << board[i][j] << " ";
    }
    std::cout << '\n';
  }
}
