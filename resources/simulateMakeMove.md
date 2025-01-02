# simulateMakeMove()

After you implement the Chess::makeMove() function in Lab 4, you will need to write tests to verify the functionality of your code.  Since you will want to repeat tests without having to repeatedly type in moves as the user, it with be useful to have a function that simulates a user entering in a move. This is the purpose of simulateMakeMove(). 

## Code

```
void simulateMakeMove(char origFile, int origRank, char destFile, int destRank) {
                std::stringstream dest{};
                dest << origFile << origRank << destFile << destRank;
                std::istringstream simulatedEntry(dest.str());
                std::cin.rdbuf(simulatedEntry.rdbuf());
                Chess::makeMove();
            }
```

## How it works

The simulateMakeMove function is designed to simulate a chess move by accepting the string representation of a move, like "b2c3" directly from code rather than from a real user. It constructs the move string using the 4 function arguments, places it in the same memory buffer that std::cin reads from, and then calls your makeMove() function. This allows your Chess::makeMove() method to execute using the simulated input as if it were entered by a user. The function is useful for testing or automating moves in a chess program without manual input.

## How to use

Copy the function to your app test code file and include the `<sstream>` library.  In your test code, everywhere you would normally call makeMove(), call simulateMakeMove() instead and provide the move that you want the simulated user to enter into cin. For example, instead of using the below code and manually enterign moves:

```
Chess::initializeBoard();
while(true) // Loop for game play
{
  Chess::printBoard();
  Chess::makeMove();
}
```

try this instead:

```
Chess::initializeBoard();
Chess::printBoard();
simulateMakeMove('a',2,'a',4);
Chess::printBoard();
simulateMakeMove('a',7,'a',5);
// and so on.....
```

