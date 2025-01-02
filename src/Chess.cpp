#include "Chess.h"
#include "Square.h"
#include <iostream>

// Set up the game by configuring the Squares in the chessboard (array of Squares) so they are organized like a real chessboard
void Chess::initializeBoard()
{
  // Iterate through all the Squares on the chessboard and set the variables for each Square
  for (int i = 0; i < 8; i++) //rank
  {
    for (int j = 0; j < 8; j++) //file
    {
        chessboard[i][j].setFile('a' + j); // sets File value between 'a' and 'h'
        chessboard[i][j].setRank(1 + i); // sets Rank value between 1 and 8
        chessboard[i][j].setColor((((i + j) % 2) == 0) ? ' ' : '+'); // alternately color squares "+" for white squares and " " for black squares for clean printing
        chessboard[i][j].setOccupant(' '); // all Squares are empty at the beginning
    }
  }
}

void Chess::printBoard()
{
  // Set style for chessboard here
  const std::string WHITE_ROW_SPACER = " |+++++     +++++     +++++     +++++     | ";
  const std::string BLACK_ROW_SPACER = " |     +++++     +++++     +++++     +++++| ";
  const std::string FILE_LABLES =    "    a    b    c    d    e    f    g    h    ";
  const std::string BORDER = "  ----------------------------------------";

  // Print file labels and gameboard border
  std::cout << FILE_LABLES << std::endl << BORDER << std::endl;
  // Print rows/ranks two at a time (since they alternate starting with black and white squares), higher ranks/rows on top
  for (int rank = 7; rank  >= 0; rank -= 2)
  {
    std::cout << WHITE_ROW_SPACER << std::endl;
    std::cout << rank + 1 << "|";
    // Print files/columns for row starting with white, two at a time (since they alternate between black and white squares)
    for (int file = 0; file < 8; file += 2)
    {
        // Print white square
        std::cout << "++" << (chessboard[rank][file].isOccupied() ? chessboard[rank][file].getOccupant() : chessboard[rank][file].getColor()) << "++";
        // Print black square
        std::cout << "  " << (chessboard[rank][file + 1].isOccupied() ? chessboard[rank][file + 1].getOccupant() : chessboard[rank][file + 1].getColor()) << "  ";
    }
    std::cout << "|" << rank + 1 << std::endl << WHITE_ROW_SPACER << std::endl;

    std::cout << BLACK_ROW_SPACER << std::endl;
    std::cout << rank << "|";
    
    // Print files/columns for row starting with black, two at a time (since they alternate between black and white squares)
    for (int file = 0; file < 8; file += 2)
    {
        // Print black square
        std::cout << "  " << (chessboard[rank - 1][file].isOccupied() ? chessboard[rank - 1][file].getOccupant() : chessboard[rank - 1][file].getColor()) << "  ";
        // Print white square
        std::cout << "++" << (chessboard[rank - 1][file + 1].isOccupied() ? chessboard[rank - 1][file + 1].getOccupant() : chessboard[rank - 1][file + 1].getColor()) << "++";
    }
    std::cout << "|" << rank << std::endl << BLACK_ROW_SPACER << std::endl;
  }
  // Print bottom labels and border
  std::cout << BORDER << std::endl << FILE_LABLES << std::endl;
}