#ifndef CHESS_H
#define CHESS_H

#include "Square.h"

class Chess
{
  public:
  
  // Data fields
  inline static Square chessboard[8][8]; // chessboard[rank][file]
  
  // Functions
  static void initializeBoard();
  static void printBoard();
};

#endif

/*
NOTES:

1) The "static" keyword means the class memeber is associated with the class as a whole, 
not each instances of a class.  Remember Chess is an abstract class and we do not intend
to instantiante any Chess objects.  It's just a container class for Chess-related variables
and functions. In other words, there on only one chessboard[][] array--we are not going to 
instantiate multiple Chess objects, each with their own chessboard[][] array.  Similarly, 
with respect to funcitons, we are NOT going invoke the initializeBoard() function on 
instantianted Chess objects (e.g. chessGame1.initializeBoard()) since there are no
instantinated Chess objects.  Instead we are going to invoke it similarly to the way
we would a regular function except that we need to specify that it came from the Chess class.
Invoke it like this: Chess::initializeBoard();

2) The inline keyword means the line of code will be run as if it were outside a class definition.
In this case, it means that the chessboard[][] array will actually be initialized in memory rather
than just being defined as part of a class definition.  If we did not use the inline keyword here 
in the class definition, we could need to exlictly declare the variable in a source file (either
main.cpp or Chess.cpp), which is easy, but it's cleaner to just do it here. If we were to remove 
the inline keyword here, we could just add "Square Chess::chessboard[8][8];" to one of the source
files and it would compile.
*/