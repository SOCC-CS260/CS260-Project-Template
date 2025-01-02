#define DOCTEST_CONFIG_IMPLEMENT
#define DOCTEST_CONFIG_NO_BREAKS

#ifndef LAB // If LAB value was not passed into main() by the build system...
    #define LAB 2 
#endif

#include <iostream>
#include "doctest.h"

// Main function to execute unit tests
int main(int argc, char** argv) {
        
    // Print the launching message with the lab number
    std::cout << "Launching tests for Lab " << LAB << std::endl;

    doctest::Context context;

    // Apply command-line arguments to the doctest context
    context.applyCommandLine(argc, argv);

    // Run tests and capture the result
    int test_result = context.run();

    if(context.shouldExit()) {  // Important to check
        return test_result;     // to respect --exit command-line flag
    }

    // Clean up or other code following the test run can be placed here

    std::cout << "=======================================" << std::endl;
    std::cout << " End of LAB " << LAB << " Test Results " << std::endl;
    std::cout << "=======================================" << std::endl;

    return 0;
}

// LAB 2 TESTS (Test Functions, Square, Chess, WhitePawn, BlackPawn)
#if LAB >= 2 

    #include "Square.h"
    #include "Chess.h"
    #include "BlackPawn.h"
    #include "WhitePawn.h"

    #pragma region TESTING FUNCTIONS

        // Tracker array to keep track of the board state during testing
        char tracker[8][8]{}; 

        void printTracker(std::string desc = ""){
            std::cout << "------------------" << std::endl;
            std::cout << desc << std::endl << std::endl;
            for (int i = 8; i >= 1; i--) {  // Rank from 8 to 1
                std::cout << i << "| ";
                for (int j = 0; j < 8; j++) {  // File from 'a' to 'h'
                    std::cout << tracker[i - 1][j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "------------------" << std::endl;
            std::cout << "   a b c d e f g h" << std::endl;  // Column labels
        }

            void clearTracker(){
                for (int i = 0; i < 8; i++) { //rank 
                    for (int j = 0; j < 8; j++) { //file
                        tracker[i][j] = ' ';
                    } 
                }
            }
        
        // Clear board function to reset the board for each test. Square occupant data type changes in lab 5 requiring conditional compilation
            
        void clearBoard(){
            for (int i = 0; i < 8; i++) { //rank 
                for (int j = 0; j < 8; j++) { //file
                    #if LAB < 5 // char data type
                    Chess::chessboard[i][j].setOccupant(' ');
                    #else // ptr data type
                    Chess::chessboard[i][j].setOccupant(nullptr);
                    #endif
                } 
            }
        }

        #if LAB >= 4 // makeMove() function not implemented until Lab 4

            void simulateMakeMove(char origFile, int origRank, char destFile, int destRank) {
                std::stringstream dest{};
                dest << origFile << origRank << destFile << destRank;
                std::istringstream simulatedEntry(dest.str());
                std::cin.rdbuf(simulatedEntry.rdbuf());
                std::cout << dest.str() << std::endl;
                Chess::makeMove();
            }

            #if LAB >= 9
                void simulateMakeMove(char origFile, int origRank, char destFile, int destRank, bool whiteTurn) {
                    std::stringstream dest{};
                    dest << origFile << origRank << destFile << destRank;
                    std::istringstream simulatedEntry(dest.str());
                    std::cin.rdbuf(simulatedEntry.rdbuf());
                    Chess::makeMove(whiteTurn);
                }
            #endif
        #endif

        #if LAB >= 5 // Pointers not implemented for square occupants until lab 5
            char checkForOccupant(char file, int rank){
                if ( Chess::chessboard[rank - 1][file -'a'].getOccupant() == nullptr)
                    return ' ';
                else
                    return  Chess::chessboard[rank - 1][file -'a'].getOccupant()->getSymbol();
            }

            // Fake chess piece class (deried from ChessPiece) for testing purposes
            #ifdef CHESS_PIECE_H
                class FakePiece : public ChessPiece {
                public:
                    FakePiece(char file, int rank)
                        : ChessPiece('f', file, rank)
                    {}
                    FakePiece(char symbol, char file, int rank)
                        : ChessPiece(symbol, file, rank)
                    {}
                    bool isMoveLegal(char file, int rank) {
                        return true;
                    }
                };
            #endif
        #endif

        # if LAB >= 6 // setLocation function not implemented until Lab 6
            void resetBoard() {
                
                //Rooks
                #ifdef ROOK_H
                    Square tempR[4];
                    for (int i = 0; i < 2; i++) {
                        Chess::R[i].setLocation(&tempR[i]);
                        Chess::r[i].setLocation(&tempR[i + 2]);
                    }
                    Chess::chessboard[1 - 1]['a' - 'a'].setOccupant(&Chess::R[0]);
                    Chess::R[0].setLocation(&Chess::chessboard[1 - 1]['a' - 'a']);
                    Chess::chessboard[1 - 1]['h' - 'a'].setOccupant(&Chess::R[1]);
                    Chess::R[1].setLocation(&Chess::chessboard[1 - 1]['h' - 'a']);
                    Chess::chessboard[8 - 1]['a' - 'a'].setOccupant(&Chess::r[0]);
                    Chess::r[0].setLocation(&Chess::chessboard[8 - 1]['a' - 'a']);
                    Chess::chessboard[8 - 1]['h' - 'a'].setOccupant(&Chess::r[1]);
                    Chess::r[1].setLocation(&Chess::chessboard[8 - 1]['h' - 'a']);
                #endif

                //Knights
                #ifdef KNIGHT_H
                    Square tempN[4];
                    for (int i = 0; i < 2; i++) {
                        Chess::N[i].setLocation(&tempN[i]);
                        Chess::n[i].setLocation(&tempN[i + 2]);
                    }
                    Chess::chessboard[1 - 1]['b' - 'a'].setOccupant(&Chess::N[0]);
                    Chess::N[0].setLocation(&Chess::chessboard[1 - 1]['b' - 'a']);
                    Chess::chessboard[1 - 1]['g' - 'a'].setOccupant(&Chess::N[1]);
                    Chess::N[1].setLocation(&Chess::chessboard[1 - 1]['g' - 'a']);
                    Chess::chessboard[8 - 1]['b' - 'a'].setOccupant(&Chess::n[0]);
                    Chess::n[0].setLocation(&Chess::chessboard[8 - 1]['b' - 'a']);
                    Chess::chessboard[8 - 1]['g' - 'a'].setOccupant(&Chess::n[1]);
                    Chess::n[1].setLocation(&Chess::chessboard[8 - 1]['g' - 'a']);
                #endif

                //Bishops
                #ifdef BISHOP_H
                    Square tempB[4];
                    for (int i = 0; i < 2; i++) {
                        Chess::B[i].setLocation(&tempB[i]);
                        Chess::b[i].setLocation(&tempB[i + 2]);
                    }
                    Chess::chessboard[1 - 1]['c' - 'a'].setOccupant(&Chess::B[0]);
                    Chess::B[0].setLocation(&Chess::chessboard[1 - 1]['c' - 'a']);
                    Chess::chessboard[1 - 1]['f' - 'a'].setOccupant(&Chess::B[1]);
                    Chess::B[1].setLocation(&Chess::chessboard[1 - 1]['f' - 'a']);
                    Chess::chessboard[8 - 1]['c' - 'a'].setOccupant(&Chess::b[0]);
                    Chess::b[0].setLocation(&Chess::chessboard[8 - 1]['c' - 'a']);
                    Chess::chessboard[8 - 1]['f' - 'a'].setOccupant(&Chess::b[1]);
                    Chess::b[1].setLocation(&Chess::chessboard[8 - 1]['f' - 'a']);
                #endif

                //Queens
                #ifdef QUEEN_H
                    Square tempQ[2];
                    Chess::Q.setLocation(&tempQ[0]);
                    Chess::q.setLocation(&tempQ[1]);

                    Chess::chessboard[1 - 1]['d' - 'a'].setOccupant(&Chess::Q);
                    Chess::Q.setLocation(&Chess::chessboard[1 - 1]['d' - 'a']);
                    Chess::chessboard[8 - 1]['d' - 'a'].setOccupant(&Chess::q);
                    Chess::q.setLocation(&Chess::chessboard[8 - 1]['d' - 'a']);
                #endif

                //Kings
                #ifdef KING_H
                    Square tempK[2];
                    Chess::K.setLocation(&tempK[0]);
                    Chess::k.setLocation(&tempK[1]);
                    
                    Chess::chessboard[1 - 1]['e' - 'a'].setOccupant(&Chess::K);
                    Chess::K.setLocation(&Chess::chessboard[1 - 1]['e' - 'a']);
                    Chess::chessboard[8 - 1]['e' - 'a'].setOccupant(&Chess::k);
                    Chess::k.setLocation(&Chess::chessboard[8 - 1]['e' - 'a']);
                #endif

                //White Pawns
                #ifdef WHITE_PAWN_H
                    Square tempWP[8];
                    for (int i = 0; i < 8; i++) {
                        Chess::P[i].setLocation(&tempWP[i]);
                    }
                    Chess::chessboard[2 - 1]['a' - 'a'].setOccupant(&Chess::P[0]);
                    Chess::P[0].setLocation(&Chess::chessboard[2 - 1]['a' - 'a']);
                    Chess::chessboard[2 - 1]['b' - 'a'].setOccupant(&Chess::P[1]);
                    Chess::P[1].setLocation(&Chess::chessboard[2 - 1]['b' - 'a']);
                    Chess::chessboard[2 - 1]['c' - 'a'].setOccupant(&Chess::P[2]);
                    Chess::P[2].setLocation(&Chess::chessboard[2 - 1]['c' - 'a']);
                    Chess::chessboard[2 - 1]['d' - 'a'].setOccupant(&Chess::P[3]);
                    Chess::P[3].setLocation(&Chess::chessboard[2 - 1]['d' - 'a']);
                    Chess::chessboard[2 - 1]['e' - 'a'].setOccupant(&Chess::P[4]);
                    Chess::P[4].setLocation(&Chess::chessboard[2 - 1]['e' - 'a']);
                    Chess::chessboard[2 - 1]['f' - 'a'].setOccupant(&Chess::P[5]);
                    Chess::P[5].setLocation(&Chess::chessboard[2 - 1]['f' - 'a']);
                    Chess::chessboard[2 - 1]['g' - 'a'].setOccupant(&Chess::P[6]);
                    Chess::P[6].setLocation(&Chess::chessboard[2 - 1]['g' - 'a']);
                    Chess::chessboard[2 - 1]['h' - 'a'].setOccupant(&Chess::P[7]);
                    Chess::P[7].setLocation(&Chess::chessboard[2 - 1]['h' - 'a']);
                #endif

                //Black Pawns
                #ifdef BLACK_PAWN_H
                    Square tempBP[8];
                    for (int i = 0; i < 8; i++) {
                        Chess::p[i].setLocation(&tempBP[i]);
                    }
                    Chess::chessboard[7 - 1]['a' - 'a'].setOccupant(&Chess::p[0]);
                    Chess::p[0].setLocation(&Chess::chessboard[7 - 1]['a' - 'a']);
                    Chess::chessboard[7 - 1]['b' - 'a'].setOccupant(&Chess::p[1]);
                    Chess::p[1].setLocation(&Chess::chessboard[7 - 1]['b' - 'a']);
                    Chess::chessboard[7 - 1]['c' - 'a'].setOccupant(&Chess::p[2]);
                    Chess::p[2].setLocation(&Chess::chessboard[7 - 1]['c' - 'a']);
                    Chess::chessboard[7 - 1]['d' - 'a'].setOccupant(&Chess::p[3]);
                    Chess::p[3].setLocation(&Chess::chessboard[7 - 1]['d' - 'a']);
                    Chess::chessboard[7 - 1]['e' - 'a'].setOccupant(&Chess::p[4]);
                    Chess::p[4].setLocation(&Chess::chessboard[7 - 1]['e' - 'a']);
                    Chess::chessboard[7 - 1]['f' - 'a'].setOccupant(&Chess::p[5]);
                    Chess::p[5].setLocation(&Chess::chessboard[7 - 1]['f' - 'a']);
                    Chess::chessboard[7 - 1]['g' - 'a'].setOccupant(&Chess::p[6]);
                    Chess::p[6].setLocation(&Chess::chessboard[7 - 1]['g' - 'a']);
                    Chess::chessboard[7 - 1]['h' - 'a'].setOccupant(&Chess::p[7]);
                    Chess::p[7].setLocation(&Chess::chessboard[7 - 1]['h' - 'a']);
                #endif

                //Empty Squares
                for (int rank = 3; rank <= 6; rank++) //rank
                {
                    for (char file = 'a'; file <= 'h'; file++) //file
                    {
                        Chess::chessboard[rank - 1][file - 'a'].setOccupant(nullptr);
                    }
                }
            }

            void clearCapturedPieces() {
                for (int i = 0; i < 15; i++) {
                    Chess::capturedBlackPieces[i].setOccupant(nullptr);
                    Chess::capturedWhitePieces[i].setOccupant(nullptr);
                }
                Chess::numCapturedBlackPieces = 0;
                Chess::numCapturedWhitePieces = 0;
            }
        #endif // End of conditional compilation for Lab 6 and later

    #pragma endregion

    #pragma region  TEST SQUARE CLASS 

        #ifndef SQUARE_H

            // Fail test and skip the test suite if SQUARE_H is not defined
            TEST_CASE("Class Square Defined") {
                CHECK_MESSAGE(false, "Square class is not defined or there is no header guard with the name SQUARE_H.");
            }

        #else

            // Test suite for testing Square class behavior
            TEST_SUITE("testSquare") {
                
                TEST_CASE("setRank") {
                    Square s1;
                    // Testing setRank for a range of ranks outside and inside the valid range (1-8)
                    s1.setRank(1);
                    for (int rank = -3; rank <= 12; rank++) {
                        s1.setRank(rank);
                        if (rank < 1 || rank > 8)
                            CHECK(s1.getRank() != rank); // Rank should not be set outside valid range
                        else
                            CHECK(s1.getRank() == rank); // Rank should be set within valid range
                    }
                }

                TEST_CASE("setFile") {
                    Square s1;
                    s1.setFile('a');
                    // Testing setFile for a range of files outside and inside the valid range ('a'-'h')
                    for (int file = 'a' - 4; file <= 'h' + 4; file++) {
                        s1.setFile(file);
                        if (file < 'a' || file > 'h')
                            CHECK(s1.getFile() != file); // File should not be set outside valid range
                        else
                            CHECK(s1.getFile() == file); // File should be set within valid range
                    }
                }

                #if LAB <= 4 // Occupant data type is char until Lab 5
                    TEST_CASE("isOccupiedByWhite") {
                        Square s1, s2;
                        s1.setOccupant('P'); // Assuming 'P' denotes a white piece
                        CHECK(s1.isOccupiedByWhite() == true); // Check if s1 is occupied by a white piece
                        
                        s2.setOccupant('p'); // Assuming 'p' denotes a black piece
                        CHECK(s2.isOccupiedByWhite() == false); // Check if s2 is not occupied by a white piece
                    }

                    TEST_CASE("isOccupiedByBlack") {
                        Square s1, s2;
                        s1.setOccupant('P'); // 'P' for white piece
                        CHECK(s1.isOccupiedByBlack() == false); // s1 should not be occupied by a black piece
                        
                        s2.setOccupant('p'); // 'p' for black piece
                        CHECK(s2.isOccupiedByBlack() == true); // s2 should be occupied by a black piece
                    }

                    TEST_CASE("isOccupied") {
                        Square s1;
                        s1.setOccupant('P'); // Occupied by a piece
                        CHECK(s1.isOccupied() == true); // s1 is occupied
                        
                        s1.setOccupant('p'); // Occupied by another piece
                        CHECK(s1.isOccupied() == true); // s1 is still occupied
                        
                        s1.setOccupant(' '); // Empty square
                        CHECK(s1.isOccupied() == false); // s1 is not occupied
                    }
                #endif
                #if LAB >= 5 // Occupant data type is pointer to ChessPiece class starting in  Lab 5
                    TEST_CASE("isOccupiedByWhite") {
                        Square s1, s2;
                        WhitePawn P('g', 3);
                        BlackPawn p('h', 3);
                        s1.setOccupant(&P);
                        CHECK(s1.isOccupiedByWhite());
                        s2.setOccupant(&p);
                        CHECK_FALSE(s2.isOccupiedByWhite());
                    }

                    TEST_CASE("isOccupiedByBlack") {
                        Square s1, s2;
                        WhitePawn P('g', 3);
                        BlackPawn p('h', 3);
                        s1.setOccupant(&P);
                        CHECK_FALSE(s1.isOccupiedByBlack());
                        s2.setOccupant(&p);
                        CHECK(s2.isOccupiedByBlack());
                    }

                    TEST_CASE("isOccupied") {
                        Square s1;
                        WhitePawn P('g', 3);
                        BlackPawn p('h', 3);
                        s1.setOccupant(&P);
                        CHECK(s1.isOccupied());
                        s1.setOccupant(&p);
                        CHECK(s1.isOccupied());
                        s1.setOccupant(nullptr);
                        CHECK_FALSE(s1.isOccupied());
                    }
                #endif

                #if LAB >= 7 // Operator overloading implemented in Lab 7
                    TEST_CASE(">>OperatorMovesPieces") {
                        Chess::initializeBoard();
                        resetBoard();
                        clearCapturedPieces();
                        FakePiece fp('d', 4);
                        Chess::printBoard();
                        Chess::chessboard[4 - 1]['d' - 'a']  >> Chess::chessboard[5 - 1]['d' - 'a'];
                        CHECK_EQ(Chess::chessboard[5 - 1]['d' - 'a'].getOccupant(), &fp);
                        Chess::printBoard();
                    }

                #endif

                #if LAB >= 8 // Stream insertion operator not overloaded until lab 8

                    TEST_CASE("<<OperatorPrintsSquares") {
                        resetBoard();
                        std::stringstream ss = {};
                        // "Printing" the square at e1 but sending the result to ss instead of cout
                        ss << Chess::chessboard[1 - 1]['e' - 'a']; 
                        // Check if the ss contains the "printed" char that correctly represents the occupant of the square
                        CHECK_EQ(ss.str()[0], checkForOccupant('e', 1)); 
                    }

                #endif
                
            } // End of test suite for the Square class
        #endif 

    #pragma endregion TEST SQUARE CLASS 

    #pragma region TEST CHESS CLASS

        #ifndef CHESS_H

            // Fail test and skip the test suite if SQUARE_H is not defined
            TEST_CASE("Class Chess Defined") {
                CHECK_MESSAGE(false, "Chess class is not defined or there is no header guard with the name CHESS_H.");
            }

        #else

            TEST_SUITE("testChess") {
                TEST_CASE("printBoard") {
                    // Initialize
                    Chess::initializeBoard();
                    #if LAB >= 6
                        resetBoard();
                    #endif
                    std::cout << "Testing print empty board:" << std::endl;
                    Chess::printBoard();
                    std::cout << "Check Printout Manually" << std::endl;
                    CHECK(true);
                }

                #if LAB >= 4 // Chess pieces not instantiated until Lab 4

                    TEST_CASE("ChessPiecesInstantiated") {
                        Chess::initializeBoard();
                        #if LAB >= 6
                            resetBoard();
                        #endif

                        #if LAB == 4

                            // Rooks
                            #ifdef ROOK_H
                                CHECK_EQ(Chess::chessboard[1 - 1]['a' - 'a'].getOccupant(), 'R');
                                CHECK_EQ(Chess::chessboard[1 - 1]['h' - 'a'].getOccupant(), 'R');
                                CHECK_EQ(Chess::chessboard[8 - 1]['a' - 'a'].getOccupant(), 'r');
                                CHECK_EQ(Chess::chessboard[8 - 1]['h' - 'a'].getOccupant(), 'r');
                            #endif

                            // Bishops
                            #ifdef BISHOP_H
                                CHECK_EQ(Chess::chessboard[1 - 1]['c' - 'a'].getOccupant(), 'B');
                                CHECK_EQ(Chess::chessboard[1 - 1]['f' - 'a'].getOccupant(), 'B');
                                CHECK_EQ(Chess::chessboard[8 - 1]['c' - 'a'].getOccupant(), 'b');
                                CHECK_EQ(Chess::chessboard[8 - 1]['f' - 'a'].getOccupant(), 'b');
                            #endif

                            // Kings
                            #ifdef KING_H
                                CHECK_EQ(Chess::chessboard[1 - 1]['e' - 'a'].getOccupant(), 'K');
                                CHECK_EQ(Chess::chessboard[8 - 1]['e' - 'a'].getOccupant(), 'k');
                            #endif

                            // WhitePawns
                            #ifdef WHITE_PAWN_H
                                CHECK_EQ(Chess::chessboard[2 - 1]['a' - 'a'].getOccupant(), 'P');
                                CHECK_EQ(Chess::chessboard[2 - 1]['b' - 'a'].getOccupant(), 'P');
                                CHECK_EQ(Chess::chessboard[2 - 1]['c' - 'a'].getOccupant(), 'P');
                                CHECK_EQ(Chess::chessboard[2 - 1]['d' - 'a'].getOccupant(), 'P');
                                CHECK_EQ(Chess::chessboard[2 - 1]['e' - 'a'].getOccupant(), 'P');
                                CHECK_EQ(Chess::chessboard[2 - 1]['f' - 'a'].getOccupant(), 'P');
                                CHECK_EQ(Chess::chessboard[2 - 1]['g' - 'a'].getOccupant(), 'P');
                                CHECK_EQ(Chess::chessboard[2 - 1]['h' - 'a'].getOccupant(), 'P');
                            #endif

                            // BlackPawns
                            #ifdef BLACK_PAWN_H
                                CHECK_EQ(Chess::chessboard[7 - 1]['a' - 'a'].getOccupant(), 'p');
                                CHECK_EQ(Chess::chessboard[7 - 1]['b' - 'a'].getOccupant(), 'p');
                                CHECK_EQ(Chess::chessboard[7 - 1]['c' - 'a'].getOccupant(), 'p');
                                CHECK_EQ(Chess::chessboard[7 - 1]['d' - 'a'].getOccupant(), 'p');
                                CHECK_EQ(Chess::chessboard[7 - 1]['e' - 'a'].getOccupant(), 'p');
                                CHECK_EQ(Chess::chessboard[7 - 1]['f' - 'a'].getOccupant(), 'p');
                                CHECK_EQ(Chess::chessboard[7 - 1]['g' - 'a'].getOccupant(), 'p');
                                CHECK_EQ(Chess::chessboard[7 - 1]['h' - 'a'].getOccupant(), 'p');
                            #endif

                        #endif // End of conditional compilation for Lab 4

                        #if LAB > 5 // Square occupant changes to pointer and Queens are added in Lab 5

                            // Rooks
                            #ifdef ROOK_H
                                CHECK_EQ(checkForOccupant('a', 1), 'R');
                                CHECK_EQ(checkForOccupant('h', 1), 'R');
                                CHECK_EQ(checkForOccupant('a', 8), 'r');
                                CHECK_EQ(checkForOccupant('h', 8), 'r');
                            #endif

                            // Bishops
                            #ifdef BISHOP_H
                                CHECK_EQ(checkForOccupant('c', 1), 'B');
                                CHECK_EQ(checkForOccupant('f', 1), 'B');
                                CHECK_EQ(checkForOccupant('c', 8), 'b');
                                CHECK_EQ(checkForOccupant('f', 8), 'b');
                            #endif

                            // Kings
                            #ifdef KING_H
                                CHECK_EQ(checkForOccupant('e', 1), 'K');
                                CHECK_EQ(checkForOccupant('e', 8), 'k');
                            #endif

                            // White Pawns
                            #ifdef WHITE_PAWN_H
                                CHECK_EQ(checkForOccupant('a', 2), 'P');
                                CHECK_EQ(checkForOccupant('b', 2), 'P');
                                CHECK_EQ(checkForOccupant('c', 2), 'P');
                                CHECK_EQ(checkForOccupant('d', 2), 'P');
                                CHECK_EQ(checkForOccupant('e', 2), 'P');
                                CHECK_EQ(checkForOccupant('f', 2), 'P');
                                CHECK_EQ(checkForOccupant('g', 2), 'P');
                                CHECK_EQ(checkForOccupant('h', 2), 'P');
                            #endif

                            // Black Pawns
                            #ifdef BLACK_PAWN_H
                                CHECK_EQ(checkForOccupant('a', 7), 'p');
                                CHECK_EQ(checkForOccupant('b', 7), 'p');
                                CHECK_EQ(checkForOccupant('c', 7), 'p');
                                CHECK_EQ(checkForOccupant('d', 7), 'p');
                                CHECK_EQ(checkForOccupant('e', 7), 'p');
                                CHECK_EQ(checkForOccupant('f', 7), 'p');
                                CHECK_EQ(checkForOccupant('g', 7), 'p');
                                CHECK_EQ(checkForOccupant('h', 7), 'p');
                            #endif

                            // Queens
                            #ifdef QUEEN_H
                                CHECK_EQ(checkForOccupant('d', 1), 'Q');
                                CHECK_EQ(checkForOccupant('d', 8), 'q');
                            #endif

                        #endif // End of conditional compilation for Lab 5 and later

                        #if LAB >= 6
                            // Knights
                            #ifdef KNIGHT_H
                                CHECK_EQ(checkForOccupant('b', 1), 'N');
                                CHECK_EQ(checkForOccupant('g', 1), 'N');
                                CHECK_EQ(checkForOccupant('b', 8), 'n');
                                CHECK_EQ(checkForOccupant('g', 8), 'n');
                            #endif // End of conditional compilation for Knight class
                        #endif  // End of conditional compilation for Lab 6 and later


                    } // End of test case for ChessPiecesInstantiated

                    // Test makeMove
                    TEST_CASE("ChessMakeMove") {
                        Chess::initializeBoard();
                        #if LAB >= 6
                            resetBoard();
                        #endif

                        #if LAB == 4
                        
                            // Move white pawns
                            std::cout << "Moving white pawns" << std::endl;
                            for (char col = 'a'; col <= 'h'; col++) {
                                simulateMakeMove(col, 2, col, 4);
                                CHECK_EQ(Chess::chessboard[4 - 1][col - 'a'].getOccupant(), 'P');
                                simulateMakeMove(col, 2, col, 4);
                                CHECK_FALSE(Chess::chessboard[2 - 1][col - 'a'].getOccupant() == 'P');
                            }

                            // Move black pawns
                            std::cout << "Moving black pawns" << std::endl;
                            for (char col = 'a'; col <= 'h'; col++) {
                                simulateMakeMove(col, 7, col, 5);
                                CHECK_EQ(Chess::chessboard[5 - 1][col - 'a'].getOccupant(), 'p');
                                CHECK_FALSE(Chess::chessboard[7 - 1][col - 'a'].getOccupant() == 'p');
                            }

                            // Move rooks
                            std::cout << "Moving white rooks" << std::endl;
                            simulateMakeMove('a', 1, 'a', 2);
                            CHECK_EQ(Chess::chessboard[2 - 1]['a' - 'a'].getOccupant(), 'R');
                            CHECK_FALSE(Chess::chessboard[1 - 1]['a' - 'a'].getOccupant() == 'R');
                            simulateMakeMove('h', 1, 'h', 2);
                            CHECK_EQ(Chess::chessboard[2 - 1]['h' - 'a'].getOccupant(), 'R');
                            CHECK_FALSE(Chess::chessboard[1 - 1]['h' - 'a'].getOccupant() == 'R');
                            
                            std::cout << "Moving black rooks" << std::endl;
                            simulateMakeMove('a', 8, 'a', 7);
                            CHECK_EQ(Chess::chessboard[7 - 1]['a' - 'a'].getOccupant(), 'r');
                            CHECK_FALSE(Chess::chessboard[8 - 1]['a' - 'a'].getOccupant() == 'r');
                            simulateMakeMove('h', 8, 'h', 7);
                            CHECK_EQ(Chess::chessboard[7 - 1]['h' - 'a'].getOccupant(), 'r');
                            CHECK_FALSE(Chess::chessboard[8 - 1]['h' - 'a'].getOccupant() == 'r');

                            // Move bishops
                            std::cout << "Moving white bishops" << std::endl;
                            simulateMakeMove('c', 1, 'b', 2);
                            CHECK_EQ(Chess::chessboard[2 - 1]['b' - 'a'].getOccupant(), 'B');
                            CHECK_FALSE(Chess::chessboard[1 - 1]['c' - 'a'].getOccupant() == 'B');
                            simulateMakeMove('f', 1, 'g', 2);
                            CHECK_EQ(Chess::chessboard[2 - 1]['g' - 'a'].getOccupant(), 'B');
                            CHECK_FALSE(Chess::chessboard[1 - 1]['f' - 'a'].getOccupant() == 'B');
                            
                            std::cout << "Moving black bishops" << std::endl;
                            simulateMakeMove('c', 8, 'b', 7);
                            CHECK_EQ(Chess::chessboard[7 - 1]['b' - 'a'].getOccupant(), 'b');
                            CHECK_FALSE(Chess::chessboard[8 - 1]['c' - 'a'].getOccupant() == 'b');
                            simulateMakeMove('f', 8, 'g', 7);
                            CHECK_EQ(Chess::chessboard[7 - 1]['g' - 'a'].getOccupant(), 'b');
                            CHECK_FALSE(Chess::chessboard[8 - 1]['f' - 'a'].getOccupant() == 'b');

                            // Move kings
                            std::cout << "Moving white king" << std::endl;
                            simulateMakeMove('e', 1, 'e', 2);
                            CHECK_EQ(Chess::chessboard[2 - 1]['e' - 'a'].getOccupant(), 'K');
                            CHECK_FALSE(Chess::chessboard[1 - 1]['e' - 'a'].getOccupant() == 'K');

                            std::cout << "Moving black king" << std::endl;
                            simulateMakeMove('e', 8, 'e', 7);
                            CHECK_EQ(Chess::chessboard[7 - 1]['e' - 'a'].getOccupant(), 'k');
                            CHECK_FALSE(Chess::chessboard[8 - 1]['e' - 'a'].getOccupant() == 'k');
                    
                        #endif // End of conditional compilation for Lab 4

                        #if LAB >= 5 // Square occupant changes to pointer and Queens are added in Lab 5

                            // Move white pawns
                            std::cout << "Moving white pawns" << std::endl;
                            for (char col = 'a'; col <= 'h'; col++) {
                                simulateMakeMove(col, 2, col, 4);
                                CHECK_EQ(checkForOccupant(col, 4), 'P');
                                CHECK(Chess::chessboard[2 - 1][col - 'a'].getOccupant() == nullptr);
                            }

                            // Move black pawns
                            std::cout << "Moving black pawns" << std::endl;
                            for (char col = 'a'; col <= 'h'; col++) {
                                simulateMakeMove(col, 7, col, 5);
                                CHECK_EQ(checkForOccupant(col, 5), 'p');
                                CHECK(Chess::chessboard[7 - 1][col - 'a'].getOccupant() == nullptr);
                            }

                            // Move rooks
                            std::cout << "Moving white rooks" << std::endl;
                            simulateMakeMove('a', 1, 'a', 2);
                            CHECK_EQ(checkForOccupant('a', 2), 'R');
                            CHECK(Chess::chessboard[1 - 1]['a' - 'a'].getOccupant() == nullptr);
                            simulateMakeMove('h', 1, 'h', 2);
                            CHECK_EQ(checkForOccupant('h', 2), 'R');
                            CHECK(Chess::chessboard[1 - 1]['h' - 'a'].getOccupant() == nullptr);

                            std::cout << "Moving black rooks" << std::endl;
                            simulateMakeMove('a', 8, 'a', 7);
                            CHECK_EQ(checkForOccupant('a', 7), 'r');
                            CHECK(Chess::chessboard[8 - 1]['a' - 'a'].getOccupant() == nullptr);
                            simulateMakeMove('h', 8, 'h', 7);
                            CHECK_EQ(checkForOccupant('h', 7), 'r');
                            CHECK(Chess::chessboard[8 - 1]['h' - 'a'].getOccupant() == nullptr);

                            //Move bishops
                            std::cout << "Moving white bishops" << std::endl;
                            simulateMakeMove('c', 1, 'b', 2);
                            CHECK_EQ(checkForOccupant('b', 2), 'B');
                            CHECK(Chess::chessboard[1 - 1]['c' - 'a'].getOccupant() == nullptr);
                            simulateMakeMove('f', 1, 'g', 2);
                            CHECK_EQ(checkForOccupant('g', 2), 'B');
                            CHECK(Chess::chessboard[1 - 1]['f' - 'a'].getOccupant() == nullptr);

                            std::cout << "Moving black bishops" << std::endl;
                            simulateMakeMove('c', 8, 'b', 7);
                            CHECK_EQ(checkForOccupant('b', 7), 'b');
                            CHECK(Chess::chessboard[8 - 1]['c' - 'a'].getOccupant() == nullptr);
                            simulateMakeMove('f', 8, 'g', 7);
                            CHECK_EQ(checkForOccupant('g', 7), 'b');
                            CHECK(Chess::chessboard[8 - 1]['f' - 'a'].getOccupant() == nullptr);

                            //Move kings
                            std::cout << "Moving white king" << std::endl;
                            simulateMakeMove('e', 1, 'e', 2);
                            CHECK_EQ(checkForOccupant('e', 2), 'K');
                            CHECK(Chess::chessboard[1 - 1]['e' - 'a'].getOccupant() == nullptr);

                            std::cout << "Moving black king" << std::endl;
                            simulateMakeMove('e', 8, 'e', 7);
                            CHECK_EQ(checkForOccupant('e', 7), 'k');
                            CHECK(Chess::chessboard[8 - 1]['e' - 'a'].getOccupant() == nullptr);
                            
                            // Move queens
                            #ifdef QUEEN_H
                                std::cout << "Moving white queen" << std::endl;
                                simulateMakeMove('d', 1, 'd', 2);
                                CHECK_EQ(checkForOccupant('d', 2), 'Q');
                                CHECK(Chess::chessboard[1 - 1]['d' - 'a'].getOccupant() == nullptr);
                                std::cout << "Moving black queen" << std::endl;
                                simulateMakeMove('d', 8, 'd', 7);
                                CHECK_EQ(checkForOccupant('d', 7), 'q');
                                CHECK(Chess::chessboard[8 - 1]['d' - 'a'].getOccupant() == nullptr);
                            #endif

                        #endif // End of conditional compilation for Lab 5 and later

                        #if LAB >= 6
                            // Move knights
                            #ifdef KNIGHT_H
                                std::cout << "Moving white knights" << std::endl;
                                simulateMakeMove('b', 1, 'c', 3);
                                CHECK_EQ(checkForOccupant('c', 3), 'N');
                                CHECK(Chess::chessboard[1 - 1]['b' - 'a'].getOccupant() == nullptr);
                                simulateMakeMove('g', 1, 'f', 3);
                                CHECK_EQ(checkForOccupant('f', 3), 'N');
                                CHECK(Chess::chessboard[1 - 1]['g' - 'a'].getOccupant() == nullptr);

                                
                                simulateMakeMove('b', 8, 'c', 6);
                                CHECK_EQ(checkForOccupant('c', 6), 'n');
                                CHECK(Chess::chessboard[8 - 1]['b' - 'a'].getOccupant() == nullptr);
                                simulateMakeMove('g', 8, 'f', 6);
                                CHECK_EQ(checkForOccupant('f', 6), 'n');
                                CHECK(Chess::chessboard[8 - 1]['g' - 'a'].getOccupant() == nullptr);
                            #endif // End of conditional compilation for Knight class
                        #endif // End of conditional compilation for Lab 6 and later


                    } // End of test case for makeMove
                
                #endif // End of conditional compilation for Lab 4 and later

                # if LAB >= 6

                    TEST_CASE("incrementAndDecrementNumCapturedPieces") {
                        Chess::initializeBoard();
                        resetBoard();
                        clearCapturedPieces();
                        // Both should be zero after clearing captured pieces
                        CHECK_EQ(Chess::numCapturedBlackPieces, 0);
                        CHECK_EQ(Chess::numCapturedWhitePieces, 0);
                        // Increment both by 1
                        Chess::incrementNumCapturedWhitePieces();
                        Chess::incrementNumCapturedBlackPieces();
                        // Verify increment happened
                        CHECK_EQ(Chess::numCapturedWhitePieces, 1);
                        CHECK_EQ(Chess::numCapturedBlackPieces, 1);
                        // Verify current number of captured pieces is returned
                        CHECK_EQ(Chess::incrementNumCapturedWhitePieces(), 2);
                        CHECK_EQ(Chess::incrementNumCapturedBlackPieces(), 2);
                        // Decrement both by 1
                        Chess::decrementNumCapturedWhitePieces();
                        Chess::decrementNumCapturedBlackPieces();
                        // Verify decrement happened
                        CHECK_EQ(Chess::numCapturedWhitePieces, 1);
                        CHECK_EQ(Chess::numCapturedBlackPieces, 1);
                        // Verify current number of captured pieces is returned
                        CHECK_EQ(Chess::decrementNumCapturedWhitePieces(), 0);
                        CHECK_EQ(Chess::decrementNumCapturedBlackPieces(), 0);
                    }

                    TEST_CASE("getNumCapturedPieces"){
                        Chess::initializeBoard();
                        resetBoard();
                        clearCapturedPieces();
                        // Both should be zero after clearing captured pieces
                        CHECK_EQ(Chess::getNumCapturedWhitePieces(), 0);
                        CHECK_EQ(Chess::getNumCapturedBlackPieces(), 0);
                        // Increment both by 1
                        Chess::incrementNumCapturedWhitePieces();
                        Chess::incrementNumCapturedBlackPieces();
                        // Verify increment happened
                        CHECK_EQ(Chess::getNumCapturedWhitePieces(), 1);
                        CHECK_EQ(Chess::getNumCapturedBlackPieces(), 1);
                    }

                #endif // End of conditional compilation for Lab 6 and later
                
                #if LAB >= 7 // Check detection implemented in Lab 7
                    TEST_CASE("checkVectorForCheck"){
                        Chess::initializeBoard();
                        resetBoard();
                        // Create vector of fake pieces
                        std::vector<FakePiece> fp = {FakePiece('p', 'd', 1), FakePiece('r', 'd', 2)};
                        // Check vector of black pieces for check agaist white king (FakePiece class can legally move to any square so this should return true no matter where on the board they are)
                        CHECK(Chess::checkVectorForCheck(fp, Chess::K) == true);
                        // Now check the white pieces against the black king
                        std::vector<FakePiece> FP = {FakePiece('P', 'e', 1), FakePiece('R', 'e', 2)};
                        CHECK(Chess::checkVectorForCheck(FP, Chess::k) == true);
                    }

                    TEST_CASE("checkWhiteCheckByQueen") {
                        Chess::initializeBoard();
                        resetBoard();
                        clearCapturedPieces();
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('e', 2, 'e', 4);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('e', 7, 'e', 5);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('f', 2, 'f', 4);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('d', 8, 'h', 4);
                        CHECK(Chess::checkWhiteCheck() == true);
                    }

                    TEST_CASE("checkBlackCheckByQueen") {
                        Chess::initializeBoard();
                        resetBoard();
                        clearCapturedPieces();
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('e', 7, 'e', 5);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('e', 2, 'e', 4);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('f', 7, 'f', 5);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('d', 1, 'h', 5);
                        CHECK(Chess::checkBlackCheck() == true);
                    }

                    TEST_CASE("checkWhiteCheckByRook") {
                        Chess::initializeBoard();
                        resetBoard();
                        clearCapturedPieces();
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('e', 2, 'e', 4);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('f', 7, 'f', 5);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('e', 4, 'f', 5);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('a', 7, 'a', 5);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('a', 2, 'a', 4);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('a', 8, 'a', 6);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('f', 2, 'f', 4);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('a', 6, 'e', 6);
                        CHECK(Chess::checkWhiteCheck() == true);
                    }

                    TEST_CASE("checkBlackCheckByRook") {
                        Chess::initializeBoard();
                        resetBoard();
                        clearCapturedPieces();
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('e', 7, 'e', 5);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('f', 2, 'f', 4);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('e', 5, 'f', 4);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('a', 2, 'a', 4);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('a', 7, 'a', 5);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('a', 1, 'a', 3);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('f', 7, 'f', 5);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('a', 3, 'e', 3);
                        CHECK(Chess::checkBlackCheck() == true);
                    }

                    TEST_CASE("checkWhiteCheckByPawn") {
                        Chess::initializeBoard();
                        resetBoard();
                        clearCapturedPieces();
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('f', 2, 'f', 4);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('g', 7, 'g', 5);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('f', 4, 'g', 5);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('f', 7, 'f', 5);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('a', 2, 'a', 4);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('f', 5, 'f', 4);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('a', 4, 'a', 5);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('f', 4, 'f', 3);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('a', 5, 'a', 6);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('f', 3, 'f', 2);
                        CHECK(Chess::checkWhiteCheck() == true);
                    }

                    TEST_CASE("checkBlackCheckByPawn") {
                        Chess::initializeBoard();
                        //clearBoard();
                        resetBoard();
                        resetBoard(); // For some unknown reason f2 occupant is not properly updated after a single reset but is after 2 resets????
                        std::cout << "The occupant of f2 after reset is " << checkForOccupant('f', 2) << std::endl;
                        clearCapturedPieces();
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('f', 7, 'f', 5);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('g', 2, 'g', 4);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('f', 5, 'g', 4); // capture white pawn
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('f', 2, 'f', 4);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('a', 7, 'a', 5);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('f', 4, 'f', 5);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('a', 5, 'a', 4);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('f', 5, 'f', 6);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('a', 4, 'a', 3);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('f', 6, 'f', 7);
                        CHECK(Chess::checkBlackCheck() == true);
                    }

                    TEST_CASE("checkWhiteCheckByKnight") {
                        Chess::initializeBoard();
                        resetBoard();
                        clearCapturedPieces();
                        simulateMakeMove('b', 8, 'c', 6);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('c', 6, 'd', 4);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('d', 4, 'f', 3);
                        CHECK(Chess::checkWhiteCheck() == true);
                    }

                    TEST_CASE("checkBlackCheckByKnight") {
                        Chess::initializeBoard();
                        resetBoard();
                        clearCapturedPieces();
                        simulateMakeMove('b', 1, 'c', 3);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('c', 3, 'd', 5);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('d', 5, 'f', 6);
                        CHECK(Chess::checkBlackCheck() == true);
                    }

                    TEST_CASE("checkWhiteCheckByBishop") {
                        Chess::initializeBoard();
                        resetBoard();
                        clearCapturedPieces();
                        simulateMakeMove('d', 2, 'd', 3);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('e', 7, 'e', 6);
                        CHECK(Chess::checkWhiteCheck() == false);
                        simulateMakeMove('f', 8, 'b', 4);
                        CHECK(Chess::checkWhiteCheck() == true);
                    }

                    TEST_CASE("checkBlackCheckByBishop") {
                        Chess::initializeBoard();
                        resetBoard();
                        clearCapturedPieces();
                        simulateMakeMove    ('d', 7, 'd', 6);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('e', 2, 'e', 3);
                        CHECK(Chess::checkBlackCheck() == false);
                        simulateMakeMove('f', 1, 'b', 5);
                        CHECK(Chess::checkBlackCheck() == true);
                    }

                #endif // End of conditional compilation for Lab 7

                #if LAB >=8 // Checkmate detection implemented in Lab 8

                    TEST_CASE("checkForCheckEscapeWhite") {
                        resetBoard();
                        CHECK_FALSE(Chess::checkWhiteCheckMate());
                        simulateMakeMove('f', 2, 'f', 4);
                        simulateMakeMove('e', 7, 'e', 6);
                        simulateMakeMove('g', 2, 'g', 4);
                        simulateMakeMove('a', 7, 'a', 6);
                        simulateMakeMove('e', 2, 'e', 3);
                        simulateMakeMove('d', 8, 'h', 4);
                        CHECK_FALSE(Chess::checkWhiteCheckMate());
                        CHECK(Chess::checkWhiteCheck());
                        CHECK_FALSE(Chess::checkVectorForCheckEscape(Chess::B));
                        CHECK_FALSE(Chess::checkVectorForCheckEscape(Chess::R));
                        CHECK_FALSE(Chess::checkVectorForCheckEscape(Chess::N));
                        CHECK_FALSE(Chess::checkVectorForCheckEscape(Chess::P));
                        CHECK_FALSE(Chess::checkPieceForCheckEscape(Chess::Q));
                        CHECK(Chess::checkPieceForCheckEscape(Chess::K));
                    }

                    TEST_CASE("checkForCheckEscapeBlack") {
                        resetBoard();
                        CHECK_FALSE(Chess::checkBlackCheckMate());
                        simulateMakeMove('f', 7, 'f', 5);
                        simulateMakeMove('e', 2, 'e', 3);
                        simulateMakeMove('g', 7, 'g', 5);
                        simulateMakeMove('a', 2, 'a', 3);
                        simulateMakeMove('e', 7, 'e', 6);
                        simulateMakeMove('d', 1, 'h', 5);
                        CHECK_FALSE(Chess::checkBlackCheckMate());
                        CHECK(Chess::checkBlackCheck());
                        CHECK_FALSE(Chess::checkVectorForCheckEscape(Chess::b));
                        CHECK_FALSE(Chess::checkVectorForCheckEscape(Chess::r));
                        CHECK_FALSE(Chess::checkVectorForCheckEscape(Chess::n));
                        CHECK_FALSE(Chess::checkVectorForCheckEscape(Chess::p));
                        CHECK_FALSE(Chess::checkPieceForCheckEscape(Chess::q));
                        CHECK(Chess::checkPieceForCheckEscape(Chess::k));
                    }

                    TEST_CASE("checkWhiteCheckMate") {
                        resetBoard();
                        CHECK_FALSE(Chess::checkWhiteCheckMate());
                        simulateMakeMove('f', 2, 'f', 3);
                        CHECK_FALSE(Chess::checkWhiteCheckMate());
                        simulateMakeMove('e', 7, 'e', 6);
                        CHECK_FALSE(Chess::checkWhiteCheckMate());
                        simulateMakeMove('g', 2, 'g', 4);
                        CHECK_FALSE(Chess::checkWhiteCheckMate());
                        simulateMakeMove('d', 8, 'h', 4);
                        CHECK(Chess::checkWhiteCheckMate());
                    }

                    TEST_CASE("checkBlackCheckMate") {
                        resetBoard();
                        CHECK_FALSE(Chess::checkBlackCheckMate());
                        simulateMakeMove('f', 7, 'f', 6);
                        CHECK_FALSE(Chess::checkBlackCheckMate());
                        simulateMakeMove('e', 2, 'e', 3);
                        CHECK_FALSE(Chess::checkBlackCheckMate());
                        simulateMakeMove('g', 7, 'g', 5);
                        CHECK_FALSE(Chess::checkBlackCheckMate());
                        simulateMakeMove('d', 1, 'h', 5);
                        CHECK(Chess::checkBlackCheckMate());
                    }

                #endif

            } // End of test suite for the Chess class
        #endif // End of conditional compilation for Chess class

    #pragma endregion TEST CHESS CLASS

    #pragma region  TEST BLACK_PAWN CLASS

        #ifndef BLACK_PAWN_H

            // Fail test and skip the test suite if class is not defined
            TEST_CASE("Class BlackPawn Defined") {
                CHECK_MESSAGE(false, "BlackPawn class is not defined or there is no header guard with the name BLACK_PAWN_H.");
            }

        #else

            TEST_SUITE("testBlackPawn") {
                
                #if LAB <= 4 // Occupant data type is char until Lab 5
                    TEST_CASE("BlackPawnsCreated") {
                        // Test creating pawns
                        Chess::initializeBoard();
                        clearBoard();
                        BlackPawn p1('a', 7);
                        BlackPawn p2('b', 7);
                        // Verify objects created wiht correct symbol
                        CHECK(p1.SYMBOL == 'p');
                        CHECK(p2.SYMBOL == 'p');
                        // Verify constructors inform square of the new occupant
                        CHECK(Chess::chessboard[7 - 1]['a' - 'a'].getOccupant() == 'p');
                        CHECK(Chess::chessboard[7 - 1]['b' - 'a'].getOccupant() == 'p');
                    }

                    TEST_CASE("moveUpTwoSpacesFirstMove") {
                        Chess::initializeBoard();
                        clearBoard();
                        BlackPawn p1('a', 7);
                        CHECK(p1.isMoveLegal('a', 5)); // Verify move is determined to be legal
                        p1.move('a', 5); // Move up two
                        CHECK(Chess::chessboard[4][0].getOccupant() == 'p'); // Verify destination square is occupied by pawn
                        CHECK_FALSE(Chess::chessboard[6][0].getOccupant() == 'p'); // Verify origin square is no longer occupied by pawn
                    }

                    TEST_CASE("moveUpOneSpaceAllowed") {
                        Chess::initializeBoard();
                        clearBoard();
                        BlackPawn p2('b', 7);
                        CHECK(p2.isMoveLegal('b', 6)); // Verify move is determined to be legal
                        p2.move('b', 6); // Move up one
                        CHECK(Chess::chessboard[5][1].getOccupant() == 'p'); // Verify destination square is occupied by pawn
                        CHECK_FALSE(Chess::chessboard[6][1].getOccupant() == 'p'); // Verify origin square is no longer occupied by pawn
                        p2.move('b', 5); // Move up one again
                        CHECK(Chess::chessboard[4][1].getOccupant() == 'p'); // Verify destination square is occupied by pawn
                        CHECK_FALSE(Chess::chessboard[5][1].getOccupant() == 'p'); // Verify origin square is no longer occupied by pawn
                    }

                    TEST_CASE("moveBackwardsOrDiagonalNotAllowed") {
                        Chess::initializeBoard();
                        clearBoard();
                        for (int rank = 1; rank <= 8; rank++) {
                            for (char file = 'a'; file <= 'h'; file++) {
                                BlackPawn pawn('d', 4);
                                bool isLegal = pawn.isMoveLegal(file, rank);
                                if ((rank == 3 && file == 'd') || (rank == 2 && file == 'd')) {
                                    CHECK(isLegal);
                                } else {
                                    CHECK_FALSE(isLegal);
                                }
                            }
                        }
                    }

                    TEST_CASE("moveOffBoardNotAllowed") {
                        Chess::initializeBoard();
                        clearBoard();
                        BlackPawn p2('b', 1);
                        CHECK_FALSE(p2.isMoveLegal('b', 0));
                    }

                    TEST_CASE("captureOpponentPiece") {
                        Chess::initializeBoard();
                        clearBoard();
                        BlackPawn p1('g', 3);
                        CHECK_FALSE(p1.isMoveLegal('f', 2));
                        WhitePawn P1('f', 2);
                        CHECK(p1.isMoveLegal('f', 2));
                        p1.move('f', 2);
                        CHECK(Chess::chessboard[1][5].getOccupant() == 'p');
                        CHECK_FALSE(p1.isMoveLegal('g', 1));
                        WhitePawn P2('g', 1);
                        CHECK(p1.isMoveLegal('g', 1));
                        p1.move('g', 1);
                        CHECK(Chess::chessboard[0][6].getOccupant() == 'p');
                    }

                    TEST_CASE("noCaptureSameColorPiece") {
                        Chess::initializeBoard();
                        clearBoard();
                        BlackPawn p1('d', 7);
                        BlackPawn('c', 6);
                        BlackPawn('e', 6);
                        CHECK_FALSE(p1.isMoveLegal('c', 6));
                        CHECK_FALSE(p1.isMoveLegal('e', 6));
                    }
                #endif 

                // Tests for Lab 3 and later labs only
                #if LAB >= 3

                    TEST_CASE("getLocationPointer"){
                        Chess::initializeBoard();
                        clearBoard();
                        BlackPawn p1('a', 1);
                        CHECK(p1.getLocation() == &Chess::chessboard[0][0]);
                    }

                #endif

                #if LAB >=5 // Occupant data type is pointer to ChessPiece class starting in  Lab 5
                    TEST_CASE("BlackPawnsCreated") {
                        // Test creating pawns
                        Chess::initializeBoard();
                        clearBoard();
                        BlackPawn p1('a', 7);
                        BlackPawn p2('b', 7);
                        // Verify objects created with correct symbol
                        CHECK(p1.getSymbol() == 'p');
                        CHECK(p2.getSymbol() == 'p');
                        // Verify constructors inform square of the new occupant
                        CHECK(checkForOccupant('a', 7) == 'p');
                        CHECK(checkForOccupant('b', 7) == 'p');
                    }

                    TEST_CASE("moveUpTwoSpacesFirstMove") {
                        Chess::initializeBoard();
                        clearBoard();
                        BlackPawn p1('a', 7);
                        CHECK(p1.isMoveLegal('a', 5)); // Verify move is determined to be legal
                        p1.move('a', 5); // Move up two
                        CHECK(checkForOccupant('a', 5) == 'p'); // Verify destination square is occupied by pawn
                        CHECK(Chess::chessboard[7 - 1]['a' - 'a'].getOccupant() == nullptr); // Verify origin square is no longer occupied by pawn
                    }

                    TEST_CASE("moveUpOneSpaceAllowed") {
                        Chess::initializeBoard();
                        clearBoard();
                        BlackPawn p2('b', 7);
                        CHECK(p2.isMoveLegal('b', 6)); // Verify move is determined to be legal
                        p2.move('b', 6); // Move up one
                        CHECK(checkForOccupant('b', 6) == 'p'); // Verify destination square is occupied by pawn
                        CHECK(Chess::chessboard[7 - 1]['b' - 'a'].getOccupant() == nullptr); // Verify origin square is no longer occupied by pawn
                        p2.move('b', 5); // Move up one again
                        CHECK(checkForOccupant('b', 5) == 'p'); // Verify destination square is occupied by pawn
                    }


                    TEST_CASE("tryAllSquares") {
                        Chess::initializeBoard();
                        clearBoard();
                        clearTracker();
                        for (int rank = 1; rank <= 8; rank++) {
                            for (int file = 'a'; file <= 'h'; file++) {
                                bool isLegal = BlackPawn('d', 4).isMoveLegal(file, rank);
                                if ((rank == 3) && (file == 'd')) {
                                    tracker[rank - 1][file - 'a'] = isLegal ? 'p' : 'x';
                                    CHECK(isLegal);
                                } else if ((rank == 4) && (file == 'd') || (rank == 2) && (file == 'd')) {
                                    if (rank == 4)
                                        tracker[rank - 1][file - 'a'] = 'P';
                                    continue; // Do not check no move or two move condition since only allowed first move
                                } else {
                                    tracker[rank - 1][file - 'a'] = isLegal ? '?' : ' ';
                                    CHECK_FALSE(isLegal);
                                }
                            }
                        }
                        printTracker("Tracker results for attempted moves to each square from d4\n"
                        "P: Starting square\n"
                        "p: Allowed Legal Move\n"
                        "x: Allowed Illegal Move\n"
                        "?: Disallowed Legal Move\n"
                        " : Disallowed Illegal Move\n");
                    }

                    TEST_CASE("moveOffBoardNotAllowed") {
                        Chess::initializeBoard();
                        clearBoard();
                        BlackPawn p2('b', 1);
                        CHECK_FALSE(p2.isMoveLegal('b', 0));
                    }

                    TEST_CASE("captureOpponentPiece") {
                        Chess::initializeBoard();
                        clearBoard();
                        BlackPawn p1('g', 3);
                        CHECK_FALSE(p1.isMoveLegal('f', 2));  // Check move legality before piece is placed
                        WhitePawn P1('f', 2);  // Place an opponent's piece
                        CHECK(p1.isMoveLegal('f', 2));  // Now move should be legal
                        p1.move('f', 2);  // Perform the capture
                        CHECK(checkForOccupant('f', 2) == 'p');  // Verify destination square is occupied by pawn
                        CHECK_FALSE(p1.isMoveLegal('g', 1));  // Check move legality before piece is placed

                        WhitePawn P2('g', 1);  // Place another opponent's piece
                        CHECK(p1.isMoveLegal('g', 1));  // Move should now be legal
                        p1.move('g', 1);  // Perform the capture
                        CHECK(checkForOccupant('g', 1) == 'p');  // Verify destination square is occupied by pawn
                    }


                    TEST_CASE("noCaptureSameColorPiece") {
                        Chess::initializeBoard();
                        clearBoard();
                        BlackPawn p1('d', 7);
                        BlackPawn('c', 6);
                        BlackPawn('e', 6);
                        CHECK_FALSE(p1.isMoveLegal('c', 6));
                        CHECK_FALSE(p1.isMoveLegal('e', 6));
                    }
                #endif
            } // End of test suite for the BlackPawn class
        #endif 
    #pragma endregion  TEST BLACK_PAWN CLASS

    #pragma region  TEST WHITE_PAWN CLASS

    #ifndef WHITE_PAWN_H

    // Fail test and skip the test suite if class is not defined
    TEST_CASE("Class WhitePawn Defined") {
        CHECK_MESSAGE(false, "WhitePawn class is not defined or there is no header guard with the name WHITE_PAWN_H.");
    }

    #else

    TEST_SUITE("testWhitePawn") {
        
        #if LAB <= 4 // Occupant data type is char until Lab 5
            TEST_CASE("pawnsCreated") {
                Chess::initializeBoard();
                clearBoard();
                // Test creating pawns
                WhitePawn P1('a', 2);
                WhitePawn P2('b', 2);
                // Verify objects created wiht correct symbol
                CHECK(P1.SYMBOL == 'P');
                CHECK(P2.SYMBOL == 'P');
                // Verify constructors inform square of the new occupant
                CHECK(Chess::chessboard[2 - 1]['a' - 'a'].getOccupant() == 'P');
                CHECK(Chess::chessboard[2 - 1]['b' - 'a'].getOccupant() == 'P');
            }

            TEST_CASE("moveUpTwoSpacesFirstMove") {
                Chess::initializeBoard();
                clearBoard();
                WhitePawn P1('a', 2);
                CHECK(P1.isMoveLegal('a', 4)); // Verify move is determined to be legal
                P1.move('a', 4); // Move up two
                CHECK(Chess::chessboard[3][0].getOccupant() == 'P'); // Verify destination square is occupied by pawn
                CHECK_FALSE(Chess::chessboard[1][0].getOccupant() == 'P'); // Verify origin square is no longer occupied by pawn
            }

            TEST_CASE("moveUpOneSpaceAllowed") {
                Chess::initializeBoard();
                clearBoard();
                WhitePawn P2('b', 2);
                CHECK(P2.isMoveLegal('b', 3)); // Verify move is determined to be legal
                P2.move('b', 3); // Move up one
                CHECK(Chess::chessboard[2][1].getOccupant() == 'P'); // Verify destination square is occupied by pawn
                CHECK_FALSE(Chess::chessboard[1][1].getOccupant() == 'P'); // Verify origin square is no longer occupied by pawn
                P2.move('b', 4); // Move up one again
                CHECK(Chess::chessboard[3][1].getOccupant() == 'P'); // Verify destination square is occupied by pawn
                CHECK_FALSE(Chess::chessboard[2][1].getOccupant() == 'P'); // Verify origin square is no longer occupied by pawn
            }

            TEST_CASE("moveBackwardsOrDiagonalNotAllowed") {
                Chess::initializeBoard();
                clearBoard();
                for (int rank = 1; rank <= 8; rank++) {
                    for (char file = 'a'; file <= 'h'; file++) {
                        WhitePawn P1('d', 4);
                        bool isLegal = P1.isMoveLegal(file, rank);
                        if ((rank == 5 && file == 'd') || (rank == 6 && file == 'd')) {
                            CHECK(isLegal);
                        } else {
                            CHECK_FALSE(isLegal);
                        }
                    }
                }
            }

            TEST_CASE("moveOffBoardNotAllowed") {
                Chess::initializeBoard();
                clearBoard();
                WhitePawn P2('b', 8);
                CHECK_FALSE(P2.isMoveLegal('b', 9));
            }

            TEST_CASE("captureOpponentPiece") {
                Chess::initializeBoard();
                clearBoard();
                WhitePawn P1('g', 3);
                CHECK_FALSE(P1.isMoveLegal('f', 4));
                BlackPawn p1('f', 4);
                CHECK(P1.isMoveLegal('f', 4));
                P1.move('f', 4);
                CHECK(Chess::chessboard[3][5].getOccupant() == 'P');
                CHECK_FALSE(P1.isMoveLegal('g', 5));
                BlackPawn p2('g', 5);
                CHECK(P1.isMoveLegal('g', 5));
                P1.move('g', 5);
                CHECK(Chess::chessboard[4][6].getOccupant() == 'P');
            }

            TEST_CASE("noCaptureSameColorPiece") {
                Chess::initializeBoard();
                clearBoard();
                WhitePawn P1('c', 2);
                WhitePawn('d', 3);
                WhitePawn('b', 3);
                CHECK_FALSE(P1.isMoveLegal('d', 3));
                CHECK_FALSE(P1.isMoveLegal('b', 3));
            }
        #endif

        // Tests for Lab 3 and later labs only
        #if LAB >= 3

                TEST_CASE("getLocationPointer"){
                    Chess::initializeBoard();
                    clearBoard();
                    WhitePawn P1('a', 1);
                    CHECK(P1.getLocation() == &Chess::chessboard[0][0]);
                }

        #endif

        #if LAB >=5 // Square occupant changes to pointer in Lab 5
            TEST_CASE("pawnsCreated") {
                WhitePawn P1('a', 2);
                WhitePawn P2('b', 2);
                WhitePawn P3('c', 2);
                WhitePawn P4('d', 2);
                WhitePawn P5('e', 2);
                WhitePawn P6('f', 2);
                WhitePawn P7('g', 2);
                WhitePawn P8('h', 2);
                CHECK(P1.getSymbol() == 'P');
                CHECK(P2.getSymbol() == 'P');
                CHECK(P3.getSymbol() == 'P');
                CHECK(P4.getSymbol() == 'P');
                CHECK(P5.getSymbol() == 'P');
                CHECK(P6.getSymbol() == 'P');
                CHECK(P7.getSymbol() == 'P');
                CHECK(P8.getSymbol() == 'P');
            }

            TEST_CASE("moveUpTwoSpacesFirstMove") {
                Chess::initializeBoard();
                clearBoard();
                WhitePawn P1('a', 2);
                CHECK(P1.isMoveLegal('a', 4));  // Check if the move is legal before performing it
                P1.move('a', 4);  // Perform the move
                CHECK(checkForOccupant('a', 4) == 'P');  // Verify destination square is occupied by the pawn
                CHECK(Chess::chessboard[2 - 1]['a' - 'a'].getOccupant() == nullptr);  // Verify origin square is no longer occupied
            }

            TEST_CASE("moveUpOneSpaceAllowed") {
                Chess::initializeBoard();
                clearBoard();
                WhitePawn P2('b', 2);
                CHECK(P2.isMoveLegal('b', 3));  // Check if the move is legal before performing it
                P2.move('b', 3);  // Perform the move
                CHECK(checkForOccupant('b', 3) == 'P');  // Verify destination square is occupied by the pawn
                P2.move('b', 4);  // Perform another move
                CHECK(checkForOccupant('b', 4) == 'P');  // Verify new destination square is occupied by the pawn
            }


            TEST_CASE("tryAllSquares") {
                Chess::initializeBoard();
                clearBoard();
                clearTracker();
                for (int rank = 1; rank <= 8; rank++) {
                    for (int file = 'a'; file <= 'h'; file++) {
                        bool isLegal = WhitePawn('d', 4).isMoveLegal(file, rank);
                        if ((rank == 5) && (file == 'd')) {
                            tracker[rank - 1][file - 'a'] = isLegal ? 'p' : 'x';
                            CHECK(isLegal);
                        } else if ((rank == 4) && (file == 'd') || (rank == 6) && (file == 'd')) {
                            if (rank == 4) // do not print d6
                                tracker[rank - 1][file - 'a'] = 'P';
                            continue; // Do not check no move condition or two move condition since only allowed first move
                        } else {
                            tracker[rank - 1][file - 'a'] = isLegal ? '?' : ' ';
                            CHECK_FALSE(isLegal);
                        }
                    }
                }
                printTracker("Tracker results for attempted moves to each square from d4\n"
                        "P: Starting square\n"
                        "p: Allowed Legal Move\n"
                        "x: Allowed Illegal Move\n"
                        "?: Disallowed Legal Move\n"
                        " : Disallowed Illegal Move\n");
            }

            TEST_CASE("moveOffBoardNotAllowed") {
                Chess::initializeBoard();
                clearBoard();
                WhitePawn P2('b', 8);
                CHECK_FALSE(P2.isMoveLegal('b', 9));
            }

            TEST_CASE("captureOpponentPiece") {
                Chess::initializeBoard();
                clearBoard();
                WhitePawn P1('g', 3);
                CHECK_FALSE(P1.isMoveLegal('f', 4));  // Check if the move is illegal before the opponent is placed
                BlackPawn p1('f', 4);  // Place an opponent's piece
                CHECK(P1.isMoveLegal('f', 4));  // Now move should be legal
                P1.move('f', 4);  // Perform the capture
                CHECK(checkForOccupant('f', 4) == 'P');  // Verify destination square is occupied by the pawn
                BlackPawn p2('g', 5);  // Place another opponent's piece
                CHECK(P1.isMoveLegal('g', 5));  // Move should now be legal
                P1.move('g', 5);  // Perform the capture
                CHECK(checkForOccupant('g', 5) == 'P');  // Verify destination square is occupied by the pawn
            }


            TEST_CASE("noCaptureSameColorPiece") {
                Chess::initializeBoard();
                clearBoard();
                WhitePawn P1('c', 2);
                WhitePawn('d', 3);
                WhitePawn('b', 3);
                CHECK_FALSE(P1.isMoveLegal('d', 3));
                CHECK_FALSE(P1.isMoveLegal('b', 3));
            }

        #endif
    }


    #endif // End of test suite for the WhitePawn class
    #pragma endregion  TEST WHITE_PAWN CLASS

#endif // End of conditional compilation for Lab 2 and later

// LAB 3 TESTS (King, Rook)
#if LAB >= 3 
    
    #include "King.h"
    #include "Rook.h"

    #pragma region  TEST KING CLASS

        #ifndef KING_H

            // Fail test and skip the test suite if class is not defined
            TEST_CASE("Class King Defined") {
                CHECK_MESSAGE(false, "King class is not defined or there is no header guard with the name KING_H.");
            }

        #else

            TEST_SUITE("testKing") {
                
                #if LAB <= 4 // Occupant data type is char until Lab 5
        
                    // Test creating kings
                    TEST_CASE("createKings") {
                        Chess::initializeBoard();
                        clearBoard();
                        King K1('K', 'e', 1);
                        King k1('k', 'e', 8);
                        CHECK_EQ(Chess::chessboard[1 - 1]['e' - 'a'].getOccupant(), 'K');
                        CHECK_EQ(Chess::chessboard[8 - 1]['e' - 'a'].getOccupant(), 'k');
                    }

                    // Test getLocation() function and verity that it is a pointer
                    TEST_CASE("getLocationPointer"){
                            Chess::initializeBoard();
                            clearBoard();
                            King k1('k','a', 1);
                            CHECK(k1.getLocation() == &Chess::chessboard[0][0]);
                        }

                    // Test unobstructed moves
                    TEST_CASE("KingMovesAllDirections") {
                        Chess::initializeBoard();
                        clearBoard();
                        King K1('K', 'e', 1);
                        K1.move('d', 1);
                        CHECK_FALSE(Chess::chessboard[1 - 1]['e' - 'a'].getOccupant() == 'K');
                        CHECK_EQ('K', Chess::chessboard[1 - 1]['d' - 'a'].getOccupant());
                        K1.move('d', 2); // move up
                        CHECK_FALSE(Chess::chessboard[1 - 1]['d' - 'a'].getOccupant() == 'K');
                        CHECK_EQ('K', Chess::chessboard[2 - 1]['d' - 'a'].getOccupant());
                        K1.move('e', 2); // move right
                        CHECK_FALSE(Chess::chessboard[2 - 1]['d' - 'a'].getOccupant() == 'K');
                        CHECK_EQ('K', Chess::chessboard[2 - 1]['e' - 'a'].getOccupant());
                        K1.move('f', 2); // move right
                        CHECK_FALSE(Chess::chessboard[2 - 1]['e' - 'a'].getOccupant() == 'K');
                        CHECK_EQ('K', Chess::chessboard[2 - 1]['f' - 'a'].getOccupant());
                        K1.move('f', 1); // move down
                        CHECK_FALSE(Chess::chessboard[2 - 1]['f' - 'a'].getOccupant() == 'K');
                        CHECK_EQ('K', Chess::chessboard[1 - 1]['f' - 'a'].getOccupant());
                        K1.move('e', 1); // move left
                        CHECK_FALSE(Chess::chessboard[1 - 1]['f' - 'a'].getOccupant() == 'K');
                        CHECK_EQ('K', Chess::chessboard[1 - 1]['e' - 'a'].getOccupant());
                    }

                    // Test capturing opposite color
                    TEST_CASE("KingCaptureOppositeColor") {
                        Chess::initializeBoard();
                        clearBoard();
                        King k1('k', 'd', 4);
                        King K1('K', 'd', 3);
                        CHECK_EQ('K', Chess::chessboard[3 - 1]['d' - 'a'].getOccupant());
                        k1.move('d', 3);
                        CHECK_FALSE(Chess::chessboard[4 - 1]['d' - 'a'].getOccupant() == 'k');
                        CHECK(Chess::chessboard[3 - 1]['d' - 'a'].getOccupant() == 'k');
                    }

                    // Test not capturing same color pieces
                    TEST_CASE("KingNoCaptureSameColor") {
                        Chess::initializeBoard();
                        clearBoard();
                        King k1('k', 'd', 4);
                        King k2('k', 'd', 3);
                        CHECK_EQ('k', Chess::chessboard[3 - 1]['d' - 'a'].getOccupant());
                        k1.move('d', 3);
                        CHECK(Chess::chessboard[4 - 1]['d' - 'a'].getOccupant() == 'k');
                    }

                    // Test isMoveLegal for all squares
                    TEST_CASE("moveOnlyToLegalSquares") {
                        Chess::initializeBoard();
                        clearBoard();
                        for (int rank = 1; rank <= 8; rank++) {
                            for (int file = 'a'; file <= 'h'; file++) {
                                bool isLegal = King('k', 'd', 4).isMoveLegal(file, rank);
                                // Do not check no move condition. Could be true or false
                                if ((rank == 4) && (file == 'd')) {
                                    // Do nothing
                                }
                                // If both file and rank are within 1 of the starting position d4, move should be legal
                                else if ((rank >= 3) && (rank <= 5) && (file >= 'c') && (file <= 'e')) {
                                    CHECK(isLegal);
                                }
                                // All other moves should not be letal
                                else {
                                    CHECK_FALSE(isLegal);
                                }
                            }
                        }
                    }
                #endif

                #if LAB >= 5

                    TEST_CASE("createKings") {
                        Chess::initializeBoard();
                        clearBoard();
                        King K1('K', 'e', 1);
                        King k1('k', 'e', 8);
                        CHECK(checkForOccupant('e', 1) == 'K');
                        CHECK(checkForOccupant('e', 8) == 'k');
                    }

                    TEST_CASE("KingMovesAllDirections") {
                        Chess::initializeBoard();
                        clearBoard();
                        King K1('K', 'e', 1);
                        K1.move('d', 1);
                        CHECK(checkForOccupant('d', 1) == 'K');
                        K1.move('d', 2); // move up
                        CHECK(checkForOccupant('d', 2) == 'K');
                        K1.move('e', 2); // move right
                        CHECK(checkForOccupant('e', 2) == 'K');
                        K1.move('f', 2); // move right
                        CHECK(checkForOccupant('f', 2) == 'K');
                        K1.move('f', 1); // move down
                        CHECK(checkForOccupant('f', 1) == 'K');
                        K1.move('e', 1); // move left
                        CHECK(checkForOccupant('e', 1) == 'K');
                    }

                    TEST_CASE("KingCaptureOppositeColor") {
                        
                        try {
                            Chess::initializeBoard();
                            clearBoard();
                            King k1('k', 'd', 4);
                            King K1('K', 'd', 3);
                            CHECK(checkForOccupant('d', 3) == 'K');
                            k1.move('d', 3);
                            CHECK(checkForOccupant('d', 3) == 'k');
                        } catch (const std::exception& e) {
                            std::cout << "Caught exception: " << e.what() << "\n";
                        }
                    }

                    TEST_CASE("KingNoCaptureSameColor") {
                        try{
                            Chess::initializeBoard();
                            clearBoard();
                            King k1('k', 'd', 4);
                            King k2('k', 'd', 3);
                            CHECK(checkForOccupant('d', 3) == 'k');
                            k1.move('d', 3);
                            CHECK(checkForOccupant('d', 4) == 'k');
                        } catch (const std::exception& e) {
                            std::cout << "Caught exception: " << e.what() << "\n";
                        }
                    }


                    TEST_CASE("tryAllSquares") {
                        Chess::initializeBoard();
                        clearBoard();
                        clearTracker();
                        for (int rank = 1; rank <= 8; rank++) {
                            for (int file = 'a'; file <= 'h'; file++) {
                                bool isLegal = King('k', 'd', 4).isMoveLegal(file, rank);
                                if ((rank == 4) && (file == 'd')) {
                                    tracker[rank - 1][file - 'a'] = 'K';
                                    continue; // Do not check no move condition. Could be true or false
                                } else if ((rank >= 3) && (rank <= 5) && (file >= 'c') && (file <= 'e')) {
                                    tracker[rank - 1][file - 'a'] = isLegal ? 'k' : 'x';
                                    CHECK(isLegal);
                                } else {
                                    tracker[rank - 1][file - 'a'] = isLegal ? '?' : ' ';
                                    CHECK_FALSE(isLegal);
                                }
                            }
                        }

                        printTracker("Tracker results for attempted moves to each square from d4\n"
                        "K: Starting square\n"
                        "k: Allowed Legal Move\n"
                        "x: Allowed Illegal Move\n"
                        "?: Disallowed Legal Move\n"
                        " : Disallowed Illegal Move\n");
                    }

                #endif

            } // End of test suite for King class
        #endif
    #pragma endregion

    #pragma region  TEST ROOK CLASS

        #ifndef ROOK_H

            // Fail test and skip the test suite if class is not defined
            TEST_CASE("Class Rook Defined") {
                CHECK_MESSAGE(false, "Rook class is not defined or there is no header guard with the name ROOK_H.");
            }

        #else

            TEST_SUITE("testRook") {
                
                #if LAB <= 4 // Occupant data type is char until Lab 5
                    // Test constructors
                    TEST_CASE("RooksCreated") {
                        Chess::initializeBoard();
                        clearBoard();
                        Rook R1('R', 'a', 1);
                        CHECK_EQ('R', Chess::chessboard[1 - 1]['a'-'a'].getOccupant());
                        Rook R2('R', 'h', 1);
                        CHECK_EQ('R', Chess::chessboard[1 - 1]['h' - 'a'].getOccupant());
                        Rook r1('r', 'a', 8);
                        CHECK_EQ('r', Chess::chessboard[8 - 1]['a' - 'a'].getOccupant());
                        Rook r2('r', 'h', 8);
                        CHECK_EQ('r', Chess::chessboard[8 - 1]['h' - 'a'].getOccupant());
                    }

                    // Test getLocation() function and verity that it is a pointer
                    TEST_CASE("getLocationPointer"){
                            Chess::initializeBoard();
                            clearBoard();
                            Rook r1('r','a', 1);
                            CHECK(r1.getLocation() == &Chess::chessboard[0][0]);
                        }
                    
                    // Test vertical movement without obstacles
                    TEST_CASE("RookVerticalMovementNoObstacles") {
                        Chess::initializeBoard();
                        clearBoard();
                        Rook r1('r','a', 1);
                        CHECK_FALSE(Chess::chessboard[5 - 1]['a' - 'a'].getOccupant() == 'r');
                        r1.move('a', 5); // move forward
                        CHECK_EQ('r', Chess::chessboard[5 - 1]['a' - 'a'].getOccupant());
                        CHECK_FALSE(Chess::chessboard[2 - 1]['a' - 'a'].getOccupant() == 'r');
                        r1.move('a', 2); // move backward
                        CHECK_EQ('r', Chess::chessboard[2 - 1]['a' - 'a'].getOccupant());
                    }

                    // Test horizontal movement without obstacles
                    TEST_CASE("RookHorizontalMovementNoObstacles") {
                        Chess::initializeBoard();
                        clearBoard();
                        Rook r1('r', 'a', 1);
                        CHECK_FALSE(Chess::chessboard[1 - 1]['e' - 'a'].getOccupant() == 'r');
                        r1.move('e', 1); // move right
                        CHECK_EQ('r', Chess::chessboard[1 - 1]['e' - 'a'].getOccupant());
                        CHECK_FALSE(Chess::chessboard[1 - 1]['b' - 'a'].getOccupant() == 'r');
                        r1.move('b', 1); // move left
                        CHECK_EQ('r', Chess::chessboard[1 - 1]['b' - 'a'].getOccupant());
                    }

                    // Test obstacle detection
                    TEST_CASE("RookObstacleDetection") {
                        Chess::initializeBoard();
                        clearBoard();
                        Rook r1('r', 'd', 4);
                        // Obstacles
                        Rook('R', 'b', 4);
                        Rook('R', 'f', 4);
                        Rook('R', 'd', 2);
                        Rook('R', 'd', 6);
                        r1.move('a', 4); // test left
                        CHECK_FALSE(Chess::chessboard[4 - 1]['a' - 'a'].getOccupant() == 'r');
                        CHECK_EQ('r', Chess::chessboard[4 - 1]['d' - 'a'].getOccupant());
                        r1.move('g', 4); // test right
                        CHECK_FALSE(Chess::chessboard[4 - 1]['g' - 'a'].getOccupant() == 'r');
                        CHECK_EQ('r', Chess::chessboard[4 - 1]['d' - 'a'].getOccupant());
                        r1.move('d', 1); // test down
                        CHECK_FALSE(Chess::chessboard[1 - 1]['d' - 'a'].getOccupant() == 'r');
                        CHECK_EQ('r', Chess::chessboard[4 - 1]['d' - 'a'].getOccupant());
                        r1.move('d', 7); // test up
                        CHECK_FALSE(Chess::chessboard[7 - 1]['d' - 'a'].getOccupant() == 'r');
                        CHECK_EQ('r', Chess::chessboard[4 - 1]['d' - 'a'].getOccupant());
                    }

                    // Test capturing opposite color pieces
                    TEST_CASE("RookCaptureOppositeColor") {
                        Chess::initializeBoard();
                        clearBoard();
                        Rook r1('r', 'd', 4);
                        Rook R1('R', 'd', 3);
                        CHECK_EQ('R', Chess::chessboard[3 - 1]['d' - 'a'].getOccupant());
                        r1.move('d', 3);
                        CHECK_FALSE(Chess::chessboard[4 - 1]['d' - 'a'].getOccupant() == 'r');
                        CHECK_EQ('r', Chess::chessboard[3 - 1]['d' - 'a'].getOccupant());
                    }

                    // Test not capturing same color pieces
                    TEST_CASE("RookNoCaptureSameColor") {
                        Chess::initializeBoard();
                        clearBoard();
                        Rook r1('r', 'd', 4);
                        Rook r2('r', 'd', 3);
                        CHECK_EQ('r', Chess::chessboard[3 - 1]['d' - 'a'].getOccupant());
                        r1.move('d', 3);
                        CHECK(Chess::chessboard[4 - 1]['d' - 'a'].getOccupant() == 'r');
                    }

                    // Test isMoveLegal for all squares
                    TEST_CASE("moveForwardAndBackwardOnly") {
                        Chess::initializeBoard();
                        clearBoard();
                        for (int rank = 1; rank <= 8; rank++) {
                            for (int file = 'a'; file <= 'h'; file++) {
                                bool isLegal = Rook('r', 'd', 4).isMoveLegal(file, rank);
                                if ((rank == 4) && (file == 'd')) {
                                    // Do not check no move condition. Could be true or false
                                }
                                else if ((rank == 4) || (file == 'd')) {
                                    CHECK(isLegal);
                                } 
                                else {
                                    CHECK_FALSE(isLegal);
                                }
                            }
                        }
                    }
                #endif

                #if LAB >= 5 // Square occupants are pointers starting in Lab 5

                    TEST_CASE("RooksCreated") {
                        Chess::initializeBoard();
                        clearBoard();
                        Rook R1('R', 'a', 1);
                        CHECK('R' == checkForOccupant('a', 1));
                        Rook R2('R', 'h', 1);
                        CHECK('R' == checkForOccupant('h', 1));
                        Rook r1('r', 'a', 8);
                        CHECK('r' == checkForOccupant('a', 8));
                        Rook r2('r', 'h', 8);
                        CHECK('r' == checkForOccupant('h', 8));
                    }

                    TEST_CASE("RookVerticalMovementNoObstacles") {
                        Chess::initializeBoard();
                        clearBoard();
                        Rook r1('r', 'a', 1);
                        r1.move('a', 5); // move forward
                        CHECK('r' == checkForOccupant('a', 5));
                        CHECK(Chess::chessboard[1 - 1]['a' - 'a'].getOccupant() == nullptr);
                        r1.move('a', 2); // move backward
                        CHECK('r' == checkForOccupant('a', 2));
                    }

                    TEST_CASE("RookHorizontalMovementNoObstacles") {
                        Chess::initializeBoard();
                        clearBoard();
                        Rook r1('r', 'a', 1);
                        r1.move('e', 1); // move right
                        CHECK('r' == checkForOccupant('e', 1));
                        CHECK(Chess::chessboard[1 - 1]['b' - 'a'].getOccupant() == nullptr);
                        r1.move('b', 1); // move left
                        CHECK('r' == checkForOccupant('b', 1));
                    }

                    TEST_CASE("RookObstacleDetection") {
                        try{
                            Chess::initializeBoard();
                            clearBoard();
                            Rook r1('r', 'd', 4);
                            // Obstacles
                            Rook('R', 'b', 4);
                            Rook('R', 'f', 4);
                            Rook('R', 'd', 2);
                            Rook('R', 'd', 6);
                            r1.move('a', 4); // test left
                            CHECK('r' == checkForOccupant('d', 4));  // Position remains unchanged due to obstacles
                            r1.move('g', 4); // test right
                            CHECK('r' == checkForOccupant('d', 4));  // Position remains unchanged due to obstacles
                            r1.move('d', 1); // test down
                            CHECK('r' == checkForOccupant('d', 4));  // Position remains unchanged due to obstacles
                            r1.move('d', 7); // test up
                            CHECK('r' == checkForOccupant('d', 4));  // Position remains unchanged due to obstacles
                        } catch (const std::exception& e) {
                            std::cout << "Caught exception: " << e.what() << "\n";
                        }
                    }

                    TEST_CASE("RookCaptureOppositeColor") {
                        try{
                            Chess::initializeBoard();
                            clearBoard();
                            // Black capture white
                            Rook r1('r', 'd', 4);
                            Rook R1('R', 'd', 3);
                            CHECK('R' == checkForOccupant('d', 3));
                            r1.move('d', 3);
                            CHECK('r' == checkForOccupant('d', 3));
                            
                            // White capture black
                            Rook r2('r', 'd', 3);
                            Rook R2('R', 'd', 1);
                            R2.move('d', 3);
                            CHECK('R' == checkForOccupant('d', 3));
                        } catch (const std::exception& e) {
                            std::cout << "Caught exception: " << e.what() << "\n";
                        }
                    }


                    TEST_CASE("RookNoCaptureSameColor") {
                        Chess::initializeBoard();
                        clearBoard();
                        // Black not capture black
                        Rook r1('r', 'd', 4);
                        Rook r2('r', 'd', 3);
                        CHECK_FALSE(r1.isMoveLegal('d', 3));

                        // White not capture white
                        Rook R1('R', 'd', 5);
                        Rook R2('R', 'd', 8);
                        CHECK_FALSE(R1.isMoveLegal('d', 8));
                    }

                    TEST_CASE("tryAllSquares") {
                        Chess::initializeBoard();
                        clearBoard();
                        clearTracker();
                        for (int rank = 1; rank <= 8; rank++) {
                            for (int file = 'a'; file <= 'h'; file++) {
                                bool isLegal = Rook('r', 'd', 4).isMoveLegal(file, rank);
                                
                                if ((rank == 4) && (file == 'd')) {
                                    tracker[rank - 1][file - 'a'] = 'R';
                                    continue; // Do not check no move condition. Could be true or false
                                } else if ((rank == 4) || (file == 'd')) {
                                    tracker[rank - 1][file - 'a'] = isLegal ? 'r' : 'x';
                                    CHECK(isLegal);
                                } else {
                                    tracker[rank - 1][file - 'a'] = isLegal ? '?' : ' ';
                                    CHECK_FALSE(isLegal);
                                }
                            }
                        }

                        printTracker("Tracker results for attempted moves to each square from d4\n"
                        "R: Starting square\n"
                        "r: Allowed Legal Move\n"
                        "x: Allowed Illegal Move\n"
                        "?: Disallowed Legal Move\n"
                        " : Disallowed Illegal Move\n");
                    }

                #endif
            }
        #endif
    #pragma endregion

#endif // End of conditional compilation for Lab 3 and later

// LAB 4 TESTS (Bishop)
#if LAB >= 4

    #include "Bishop.h"

    #pragma region TEST BISHOP CLASS

        #ifndef BISHOP_H

            // Fail test and skip the test suite if class is not defined
            TEST_CASE("Class Bishop Defined") {
                CHECK_MESSAGE(false, "Bishop class is not defined or there is no header guard with the name BISHOP_H.");
            }

        #else

            TEST_SUITE("testBishop") {
                
                #if LAB <= 4 // Occupant data type is char until Lab 5
                    // Test constructors
                    TEST_CASE("BishopsCreated") {
                        Chess::initializeBoard();
                        clearBoard();
                        Bishop B1('B', 'a', 1);
                        CHECK_EQ('B', Chess::chessboard[1 - 1]['a' - 'a'].getOccupant());
                        Bishop B2('B', 'h', 1);
                        CHECK_EQ('B', Chess::chessboard[1 - 1]['h' - 'a'].getOccupant());
                        Bishop b1('b', 'a', 8);
                        CHECK_EQ('b', Chess::chessboard[8 - 1]['a' - 'a'].getOccupant());
                        Bishop b2('b', 'h', 8);
                        CHECK_EQ('b', Chess::chessboard[8 - 1]['h' - 'a'].getOccupant());
                    }

                    // Test Northwest movement without obstacles
                    TEST_CASE("BishopNorthwestMovementNoObstacles") {
                        Chess::initializeBoard();
                        clearBoard();
                        Bishop b1('b', 'd', 4);
                        b1.move('b', 6); // move NW
                        CHECK(Chess::chessboard[6 - 1]['b' - 'a'].getOccupant() == 'b');
                        CHECK_FALSE(Chess::chessboard[4 - 1]['d' - 'a'].getOccupant() == 'b');
                        b1.move('a', 7); // move NW again
                        CHECK_FALSE(Chess::chessboard[6 - 1]['b' - 'a'].getOccupant() == 'b');
                        CHECK(Chess::chessboard[7 - 1]['a' - 'a'].getOccupant() == 'b');
                    }

                    // Test Northeast movement without obstacles
                    TEST_CASE("BishopNortheastMovementNoObstacles") {
                        Chess::initializeBoard();
                        clearBoard();
                        Bishop b1('b', 'd', 4);
                        b1.move('f', 6); // move NE
                        CHECK(Chess::chessboard[6 - 1]['f' - 'a'].getOccupant() == 'b');
                        CHECK_FALSE(Chess::chessboard[4 - 1]['d' - 'a'].getOccupant() == 'b');
                        b1.move('g', 7); // move NE again
                        CHECK_FALSE(Chess::chessboard[6 - 1]['f' - 'a'].getOccupant() == 'b');
                        CHECK(Chess::chessboard[7 - 1]['g' - 'a'].getOccupant() == 'b');
                    }

                    // Test Southeast movement without obstacles
                    TEST_CASE("BishopSoutheastMovementNoObstacles") {
                        Chess::initializeBoard();
                        clearBoard();
                        Bishop b1('b', 'd', 4);
                        b1.move('f', 2); // move SE
                        CHECK(Chess::chessboard[2 - 1]['f' - 'a'].getOccupant() == 'b');
                        CHECK_FALSE(Chess::chessboard[4 - 1]['d' - 'a'].getOccupant() == 'b');
                        b1.move('g', 1); // move SE again
                        CHECK_FALSE(Chess::chessboard[2 - 1]['f' - 'a'].getOccupant() == 'b');
                        CHECK(Chess::chessboard[1 - 1]['g' - 'a'].getOccupant() == 'b');
                    }

                    // Test Southwest movement without obstacles
                    TEST_CASE("BishopSouthwestMovementNoObstacles") {
                        Chess::initializeBoard();
                        clearBoard();
                        Bishop b1('b', 'd', 4);
                        b1.move('b', 2); // move SW
                        CHECK(Chess::chessboard[2 - 1]['b' - 'a'].getOccupant() == 'b');
                        CHECK_FALSE(Chess::chessboard[4 - 1]['d' - 'a'].getOccupant() == 'b');
                        b1.move('a', 1); // move SW again
                        CHECK_FALSE(Chess::chessboard[2 - 1]['b' - 'a'].getOccupant() == 'b');
                        CHECK(Chess::chessboard[1 - 1]['a' - 'a'].getOccupant() == 'b');
                    }

                    // Test obstacle detection
                    TEST_CASE("BishopObstacleDetection") {
                        Chess::initializeBoard();
                        clearBoard();
                        Bishop b1('b', 'd', 4); // Test Bishop
                        Bishop('B', 'b', 6); // NW obstacle
                        Bishop('B', 'f', 6); // NE obstacle
                        Bishop('B', 'f', 2); // SE obstacle
                        Bishop('B', 'b', 2); // SW obstacle
                        
                        b1.move('a', 7); // test NW
                        CHECK_FALSE(Chess::chessboard[7 - 1]['a' - 'a'].getOccupant() == 'b');
                        CHECK(Chess::chessboard[4 - 1]['d' - 'a'].getOccupant() == 'b');
                        b1.move('g', 7); // test NE
                        CHECK_FALSE(Chess::chessboard[7 - 1]['g' - 'a'].getOccupant() == 'b');
                        CHECK(Chess::chessboard[4 - 1]['d' - 'a'].getOccupant() == 'b');
                        b1.move('g', 1); // test SE
                        CHECK_FALSE(Chess::chessboard[1 - 1]['g' - 'a'].getOccupant() == 'b');
                        CHECK(Chess::chessboard[4 - 1]['d' - 'a'].getOccupant() == 'b');
                        b1.move('a', 1); // test SW
                        CHECK_FALSE(Chess::chessboard[1 - 1]['a' - 'a'].getOccupant() == 'b');
                        CHECK(Chess::chessboard[4 - 1]['d' - 'a'].getOccupant() == 'b');
                    }

                    // Test capturing opposite color pieces
                    TEST_CASE("BishopCaptureOppositeColor") {
                        Chess::initializeBoard();
                        clearBoard();
                        // Black capture white
                        Bishop b1('b', 'd', 4);
                        Bishop B1('B', 'f', 6);
                        b1.move('f', 6);
                        CHECK_FALSE(Chess::chessboard[4 - 1]['d' - 'a'].getOccupant() == 'b');
                        CHECK(Chess::chessboard[6 - 1]['f' - 'a'].getOccupant() == 'b');
                        // White capture black
                        Bishop B2('B', 'c', 3);
                        Bishop b2('b', 'a', 1);
                        B2.move('a', 1);
                        CHECK_FALSE(Chess::chessboard[3 - 1]['c' - 'a'].getOccupant() == 'B');
                        CHECK(Chess::chessboard[1 - 1]['a' - 'a'].getOccupant() == 'B');
                    }

                    // Test not capturing same color pieces
                    TEST_CASE("BishopNoCaptureSameColor") {
                        Chess::initializeBoard();
                        clearBoard();
                        // Black capture black
                        Bishop b1('b', 'd', 4);
                        Bishop b2('b', 'f', 6);
                        b1.move('f', 6);
                        CHECK_FALSE(b1.isMoveLegal('f',6));

                        // White capture white
                        Bishop B1('B', 'c', 3);
                        Bishop B2('B', 'a', 1);
                        B1.move('a', 1);
                        CHECK_FALSE(B1.isMoveLegal('a', 1));
                    }

                    // Test isMoveLegal for all squares
                    TEST_CASE("moveDiagonallyOnly") {
                        Chess::initializeBoard();
                        clearBoard();
                        for (int rank = 1; rank <= 8; rank++) {
                            for (int file = 'a'; file <= 'h'; file++) {
                                bool isLegal = Bishop('b', 'd', 4).isMoveLegal(file, rank);

                                if ((rank == 4) && (file == 'd')) {
                                    // Do not check no move condition. Could be true or false
                                }
                                else if (abs(rank - 4) == abs(file - 'd')) {
                                    CHECK(isLegal);
                                }
                                else {
                                    CHECK_FALSE(isLegal);
                                }
                            }
                        }
                    }
                #endif

                #if LAB >=5 
                    TEST_CASE("BishopsCreated") {
                        Chess::initializeBoard();
                        clearBoard();
                        Bishop B1('B', 'a', 1);
                        CHECK('B' == checkForOccupant('a', 1));
                        Bishop B2('B', 'h', 1);
                        CHECK('B' == checkForOccupant('h', 1));
                        Bishop b1('b', 'a', 8);
                        CHECK('b' == checkForOccupant('a', 8));
                        Bishop b2('b', 'h', 8);
                        CHECK('b' == checkForOccupant('h', 8));
                    }

                    TEST_CASE("BishopNorthwestMovementNoObstacles") {
                        Chess::initializeBoard();
                        clearBoard();
                        Bishop b1('b', 'd', 4);
                        b1.move('b', 6); // move NW
                        CHECK('b' == checkForOccupant('b', 6));
                        CHECK(Chess::chessboard[4 - 1]['d' - 'a'].getOccupant() == nullptr);
                        b1.move('a', 7); // move NW again
                        CHECK('b' == checkForOccupant('a', 7));
                    }

                    TEST_CASE("BishopNortheastMovementNoObstacles") {
                        Chess::initializeBoard();
                        clearBoard();
                        Bishop b1('b', 'd', 4);
                        b1.move('f', 6); // move NE
                        CHECK('b' == checkForOccupant('f', 6));
                        b1.move('g', 7); // move NE again
                        CHECK('b' == checkForOccupant('g', 7));
                    }

                    TEST_CASE("BishopSoutheastMovementNoObstacles") {
                        Chess::initializeBoard();
                        clearBoard();
                        Bishop b1('b', 'd', 4);
                        b1.move('f', 2); // move SE
                        CHECK('b' == checkForOccupant('f', 2));
                        b1.move('g', 1); // move SE again
                        CHECK('b' == checkForOccupant('g', 1));
                    }

                    TEST_CASE("BishopSouthwestMovementNoObstacles") {
                        try {
                            Chess::initializeBoard();
                            clearBoard();
                            Bishop b1('b', 'd', 4);
                            b1.move('b', 2); // move SW
                            CHECK('b' == checkForOccupant('b', 2));
                            b1.move('a', 1); // move SW again
                            CHECK('b' == checkForOccupant('a', 1));
                        } catch (const std::exception& e) {
                            std::cout << "Caught exception: " << e.what() << "\n";
                        }
                    }

                    TEST_CASE("BishopObstacleDetection") {
                        try{
                            Chess::initializeBoard();
                            clearBoard();
                            Bishop b1('b', 'd', 4); // Test Bishop
                            Bishop('B', 'b', 6); // NW obstacle
                            Bishop('B', 'f', 6); // NE obstacle
                            Bishop('B', 'f', 2); // SE obstacle
                            Bishop('B', 'b', 2); // SW obstacle
                            b1.move('a', 7); // test NW
                            CHECK('b' == checkForOccupant('d', 4));
                            b1.move('g', 7); // test NE
                            CHECK('b' == checkForOccupant('d', 4));
                            b1.move('g', 1); // test SE
                            CHECK('b' == checkForOccupant('d', 4));
                            b1.move('a', 1); // test SW
                            CHECK('b' == checkForOccupant('d', 4));
                        } catch (const std::exception& e) {
                            std::cout << "Caught exception: " << e.what() << "\n";
                        }
                    }

                    TEST_CASE("BishopCaptureOppositeColor") {
                        Chess::initializeBoard();
                        clearBoard();
                        Bishop b1('b', 'd', 4);
                        Bishop B1('B', 'f', 6);
                        b1.move('f', 6);
                        CHECK('b' == checkForOccupant('f', 6));
                        Bishop B2('B', 'c', 3);
                        Bishop b2('b', 'a', 1);
                        B2.move('a', 1);
                        CHECK('B' == checkForOccupant('a', 1));
                    }


                    TEST_CASE("BishopNoCaptureSameColor") {
                        try{
                            Chess::initializeBoard();
                            clearBoard();
                            Bishop b1('b', 'd', 4);
                            Bishop b2('b', 'f', 6);
                            b1.move('f', 6);
                            CHECK_FALSE(b1.isMoveLegal('f', 6));
                            Bishop B1('B', 'c', 3);
                            Bishop B2('B', 'a', 1);
                            B1.move('a', 1);
                            CHECK_FALSE(B1.isMoveLegal('a', 1));
                        } catch (const std::exception& e) {
                            std::cout << "Caught exception: " << e.what() << "\n";
                        }
                    }

                    TEST_CASE("tryAllSquares") {
                        Chess::initializeBoard();
                        clearBoard();
                        clearTracker();
                        for (int rank = 1; rank <= 8; rank++) {
                            for (int file = 'a'; file <= 'h'; file++) {
                                bool isLegal = Bishop('b', 'd', 4).isMoveLegal(file, rank);
                                if ((rank == 4) && (file == 'd')) {
                                    tracker[rank - 1][file - 'a'] = 'B';
                                    continue; // Do not check no move condition. Could be true or false
                                } else if (abs(rank - 4) == abs(file - 'd')) {
                                    tracker[rank - 1][file - 'a'] =  isLegal ? 'b' : 'x';
                                    CHECK(isLegal);
                                } else {
                                    tracker[rank - 1][file - 'a'] = isLegal ? '?' : ' ';
                                    CHECK_FALSE(isLegal);
                                }
                            }
                        }

                        printTracker("Tracker results for attempted moves to each square from d4\n"
                        "B: Starting square\n"
                        "b: Allowed Legal Move\n"
                        "x: Allowed Illegal Move\n"
                        "?: Disallowed Legal Move\n"
                        " : Disallowed Illegal Move\n");
                    }
                #endif
            } // End of test suite for the Bishop class
        #endif // End of test suite region for the Bishop class
    #pragma endregion

#endif // End of LAB 4 tests

// LAB 5 TESTS (Queen)
#if LAB >= 5

    #include "Queen.h"
    #include "ChessPiece.h"
    
    #pragma region TEST QUEEN CLASS
        #ifndef QUEEN_H

            // Fail test and skip the test suite if class is not defined
            TEST_CASE("Class Queen Defined") {
                CHECK_MESSAGE(false, "Queen class is not defined or there is no header guard with the name QUEEN_H.");
            }

        #else
        
            TEST_SUITE("testQueen") {

                TEST_CASE("QueensCreated") {
                    Chess::initializeBoard();
                    clearBoard();
                    Queen Q1('Q', 'a', 1);
                    CHECK('Q' == checkForOccupant('a', 1));
                    Queen Q2('Q', 'h', 1);
                    CHECK('Q' == checkForOccupant('h', 1));
                    Queen q1('q', 'a', 8);
                    CHECK('q' == checkForOccupant('a', 8));
                    Queen q2('q', 'h', 8);
                    CHECK('q' == checkForOccupant('h', 8));
                }

                TEST_CASE("QueenNorthwestMovementNoObstacles") {
                    Chess::initializeBoard();
                    clearBoard();
                    Queen q1('q', 'd', 4);
                    q1.move('b', 6); // move NW
                    CHECK('q' == checkForOccupant('b', 6));
                    CHECK(Chess::chessboard[3]['d' - 'a'].getOccupant() == nullptr);
                    q1.move('a', 7); // move NW again
                    CHECK(Chess::chessboard[5]['b' - 'a'].getOccupant() == nullptr);
                    CHECK('q' == checkForOccupant('a', 7));
                }

                TEST_CASE("QueenNortheastMovementNoObstacles") {
                    Chess::initializeBoard();
                    clearBoard();
                    Queen q1('q', 'd', 4);
                    q1.move('f', 6); // move NE
                    CHECK('q' == checkForOccupant('f', 6));
                    q1.move('g', 7); // move NE again
                    CHECK('q' == checkForOccupant('g', 7));
                }

                TEST_CASE("QueenSoutheastMovementNoObstacles") {
                    Chess::initializeBoard();
                    clearBoard();
                    Queen q1('q', 'd', 4);
                    q1.move('f', 2); // move SE
                    CHECK('q' == checkForOccupant('f', 2));
                    q1.move('g', 1); // move SE again
                    CHECK('q' == checkForOccupant('g', 1));
                }

                TEST_CASE("QueenSouthwestMovementNoObstacles") {
                    Chess::initializeBoard();
                    clearBoard();
                    Queen q1('q', 'd', 4);
                    q1.move('b', 2); // move SW
                    CHECK('q' == checkForOccupant('b', 2));
                    q1.move('a', 1); // move SW again
                    CHECK('q' == checkForOccupant('a', 1));
                }

                TEST_CASE("QueenVerticalMovementNoObstacles") {
                    Chess::initializeBoard();
                    clearBoard();
                    Queen q1('q', 'a', 1);
                    q1.move('a', 5); // move forward
                    CHECK('q' == checkForOccupant('a', 5));
                    CHECK(Chess::chessboard[0]['a' - 'a'].getOccupant() == nullptr);
                    q1.move('a', 2); // move backward
                    CHECK('q' == checkForOccupant('a', 2));
                }

                TEST_CASE("QueenHorizontalMovementNoObstacles") {
                    Chess::initializeBoard();
                    clearBoard();
                    Queen q1('q', 'a', 1);
                    q1.move('e', 1); // move right
                    CHECK('q' == checkForOccupant('e', 1));
                    CHECK(Chess::chessboard[0]['b' - 'a'].getOccupant() == nullptr);
                    q1.move('b', 1); // move left
                    CHECK('q' == checkForOccupant('b', 1));
                }

                TEST_CASE("QueenObstacleDetection") {
                    try{
                        Chess::initializeBoard();
                        clearBoard();
                        Queen q1('q', 'd', 4); // Test Queen
                        // Setting obstacles
                        Queen('Q', 'b', 6); // NW obstacle
                        Queen('Q', 'f', 6); // NE obstacle
                        Queen('Q', 'f', 2); // SE obstacle
                        Queen('Q', 'b', 2); // SW obstacle
                        Queen('Q', 'b', 4); // W obstacle
                        Queen('Q', 'f', 4); // E obstacle
                        Queen('Q', 'd', 2); // S obstacle
                        Queen('Q', 'd', 6); // N obstacle
                        
                        // Moving and checking that the queen hasn't moved due to obstacles
                        q1.move('a', 7); // test NW
                        CHECK('q' == checkForOccupant('d', 4));
                        q1.move('g', 7); // test NE
                        CHECK('q' == checkForOccupant('d', 4));
                        q1.move('g', 1); // test SE
                        CHECK('q' == checkForOccupant('d', 4));
                        q1.move('a', 1); // test SW
                        CHECK('q' == checkForOccupant('d', 4));
                        q1.move('a', 4); // test W
                        CHECK('q' == checkForOccupant('d', 4));
                        q1.move('g', 4); // test E
                        CHECK('q' == checkForOccupant('d', 4));
                        q1.move('d', 1); // test S
                        CHECK('q' == checkForOccupant('d', 4));
                        q1.move('d', 7); // test N
                        CHECK('q' == checkForOccupant('d', 4));
                    } catch (const std::exception& e) {
                        std::cout << "Caught exception: " << e.what() << "\n";
                    }
                }

                TEST_CASE("QueenCaptureOppositeColor") {
                    Chess::initializeBoard();
                    clearBoard();
                    // Black capture white
                    Queen q1('q', 'd', 4);
                    Queen Q1('Q', 'f', 6);
                    q1.move('f', 6);
                    CHECK('q' == checkForOccupant('f', 6));
                    // White capture black
                    Queen Q2('Q', 'c', 3);
                    Queen q2('q', 'a', 1);
                    Q2.move('a', 1);
                    CHECK('Q' == checkForOccupant('a', 1));
                }


                TEST_CASE("QueenNoCaptureSameColor") {
                    try{
                        Chess::initializeBoard();
                        clearBoard();
                        // Black capture black
                        Queen q1('q', 'd', 4);
                        Queen q2('q', 'f', 6);
                        q1.move('f', 6);
                        CHECK_FALSE(q1.isMoveLegal('f', 6));
                        // White capture white
                        Queen Q1('Q', 'c', 3);
                        Queen Q2('Q', 'a', 1);
                        Q1.move('a', 1);
                        CHECK_FALSE(Q1.isMoveLegal('a', 1));
                    } catch (const std::exception& e) {
                        std::cout << "Caught exception: " << e.what() << "\n";
                    }
                }

                TEST_CASE("tryAllSquares") {
                    Chess::initializeBoard();
                    clearBoard();
                    clearTracker();
        
                    for (int rank = 1; rank <= 8; rank++) {
                        for (int file = 'a'; file <= 'h'; file++) {
                            bool isLegal = Queen('q', 'd', 4).isMoveLegal(file, rank);

                            if ((rank == 4) && (file == 'd')) {
                                tracker[rank - 1][file - 'a'] = 'Q';
                                continue;  // Ignore the starting position
                            }
                            else if (abs(rank - 4) == abs(file - 'd')) {  // Diagonal move
                                CHECK(isLegal);
                                if (isLegal)
                                    tracker[rank - 1][file - 'a'] = 'q';  // Mark allowed legal diagonal move (correct)
                                else
                                    tracker[rank - 1][file - 'a'] = '?';  // Mark disallowed legal diagonal move (incorrect)
                            }
                            else if (rank == 4 || file == 'd') {  // Vertical or horizontal move
                                CHECK(isLegal);
                                if (isLegal)
                                    tracker[rank - 1][file - 'a'] = 'q';  // Mark allowed legal diagonal move (correct)
                                else
                                    tracker[rank - 1][file - 'a'] = '?';  // Mark disallowed legal diagonal move (incorrect)
                            }
                            else {
                                CHECK_FALSE(isLegal);
                                if (isLegal)
                                    tracker[rank - 1][file - 'a'] = 'x';  // Mark allowed illegal move (incorrect)
                                else
                                    tracker[rank - 1][file - 'a'] = ' ';  // Mark disallowed illegal move (correct)
                            }
                        }
                    }
                    printTracker("Tracker results for attempted moves to each square from d4\n"
                        "Q: Starting square\n"
                        "q: Allowed Legal Move\n"
                        "x: Allowed Illegal Move\n"
                        "?: Disallowed Legal Move\n"
                        " : Disallowed Illegal Move\n");
                
                }
            } // End of test suite for the Queen class
        #endif // End of test suite region for Queen class
    #pragma endregion

    #pragma region TEST CHESS_PIECE CLASS
        #ifndef CHESS_PIECE_H

            // Fail test and skip the test suite if class is not defined
            TEST_CASE("Class ChessPiece Defined") {
                CHECK_MESSAGE(false, "ChessPiece class is not defined or there is no header guard with the name CHESS_PIECE_H.");
            }

        #else

            TEST_SUITE("testChessPiece") {
                
                TEST_CASE("testConstructors") {
                    Chess::initializeBoard();
                    clearBoard();
                    FakePiece fake('b', 2);
                    CHECK(Chess::chessboard[2 - 1]['b' - 'a'].getOccupant() == &fake); // 3 arg constructor
                    FakePiece fake2 = fake;
                    CHECK_EQ(Chess::chessboard[2 - 1]['b' - 'a'].getOccupant(), &fake2); // copy constructor
                }

                TEST_CASE("moveUpdatesOriginAndDestinationOccupants") {
                    Chess::initializeBoard();
                    clearBoard();
                    FakePiece fake('b', 2);
                    fake.move('b', 3);
                    CHECK(Chess::chessboard[2 - 1]['b' - 'a'].getOccupant() == nullptr); // old square occupant is nullptr
                    CHECK(Chess::chessboard[3 - 1]['b' - 'a'].getOccupant() == &fake); // new square occupant is the "fake" object
                }   

                #if LAB >= 6
                    TEST_CASE("capturedPiecesMovedToCapturedArray") {
                        Chess::initializeBoard();
                        resetBoard();
                        clearCapturedPieces();
                        BlackPawn p1('g', 3);
                        WhitePawn P1('f', 2);
                        p1.move('f', 2);
                        CHECK_EQ(&p1, Chess::chessboard[2 - 1]['f' - 'a'].getOccupant());
                        CHECK_EQ(Chess::numCapturedWhitePieces, 1);
                        CHECK_EQ(Chess::capturedWhitePieces[0].getOccupant(), &P1);
                        WhitePawn P2('e', 1);
                        P2.move('f', 2);
                        CHECK_EQ(&P2, Chess::chessboard[2 - 1]['f' - 'a'].getOccupant());
                        CHECK_EQ(Chess::numCapturedBlackPieces, 1);
                        CHECK_EQ(Chess::capturedBlackPieces[0].getOccupant(), &p1);
                    }  

                    TEST_CASE("setLocation"){
                        Chess::initializeBoard();
                        resetBoard();
                        Chess::K.setLocation(&Chess::chessboard[4 - 1]['d' - 'a']);
                        CHECK_EQ(&Chess::K, Chess::chessboard[4 - 1]['d' - 'a'].getOccupant());
                    }

                    TEST_CASE("captureOpponent"){
                        resetBoard();
                        clearCapturedPieces();
                        Chess::Q.captureOpponent(&Chess::q);
                        CHECK_EQ(Chess::capturedBlackPieces[0].getOccupant(), &Chess::q);
                        Chess::k.captureOpponent(&Chess::K);
                        CHECK_EQ(Chess::capturedWhitePieces[0].getOccupant(), &Chess::K);
                    }
                #endif // End of conditional compilation for Lab 6

            } // End of test suite for the ChessPiece class
                
        #endif // End of test suite for ChessPiece class
    #pragma endregion

#endif // End of test suite for LAB 5

// LAB 6 TESTS (Knight)
#if LAB >= 6

    #include "Knight.h"
    
    #pragma region TEST KNIGHT CLASS
        #ifndef KNIGHT_H

            // Fail test and skip the test suite if class is not defined
            TEST_CASE("Class Knight Defined") {
                CHECK_MESSAGE(false, "Knight class is not defined or there is no header guard with the name KNIGHT_H.");
            }

        #else
        
            TEST_SUITE("testKnight") {

                TEST_CASE("KnightMovementNoObstacles"){
                    Chess::initializeBoard();
                    clearBoard();
                    Knight N1('N', 'd', 4);
                    N1.move('b', 3);
                    CHECK_EQ(&N1, Chess::chessboard[3 - 1]['b' - 'a'].getOccupant());
                    Knight N2('N', 'd', 4);
                    N2.move('c', 2);
                    CHECK_EQ(&N2, Chess::chessboard[2 - 1]['c' - 'a'].getOccupant());
                    Knight N3('N', 'd', 4);
                    N3.move('b', 5);
                    CHECK_EQ(&N3, Chess::chessboard[5 - 1]['b' - 'a'].getOccupant());
                    Knight N4('N', 'd', 4);
                    N4.move('c', 6);
                    CHECK_EQ(&N4, Chess::chessboard[6 - 1]['c' - 'a'].getOccupant());
                    Knight N5('N', 'd', 4);
                    N5.move('e', 6);
                    CHECK_EQ(&N5, Chess::chessboard[6 - 1]['e' - 'a'].getOccupant());
                    Knight N6('N', 'd', 4);
                    N6.move('f', 5);
                    CHECK_EQ(&N6, Chess::chessboard[5 - 1]['f' - 'a'].getOccupant());
                    Knight N7('N', 'd', 4);
                    N7.move('f', 3);
                    CHECK_EQ(&N7, Chess::chessboard[3 - 1]['f' - 'a'].getOccupant());
                    Knight N8('N', 'd', 4);
                    N8.move('e', 2);
                    CHECK_EQ(&N8, Chess::chessboard[2 - 1]['e' - 'a'].getOccupant());
                }

                TEST_CASE("KnightMovementWithObstacles"){
                    Chess::initializeBoard();
                    clearBoard();
                    BlackPawn('c', 3);
                    BlackPawn('c', 4);
                    BlackPawn('c', 5);
                    BlackPawn('d', 3);
                    BlackPawn('d', 5);
                    BlackPawn('e', 3);
                    BlackPawn('e', 4);
                    BlackPawn('e', 5);
                    Knight N1('N', 'd', 4);
                    N1.move('b', 3);
                    CHECK_EQ(&N1, Chess::chessboard[3 - 1]['b' - 'a'].getOccupant());
                    Knight N2('N', 'd', 4);
                    N2.move('c', 2);
                    CHECK_EQ(&N2, Chess::chessboard[2 - 1]['c' - 'a'].getOccupant());
                    Knight N3('N', 'd', 4);
                    N3.move('b', 5);
                    CHECK_EQ(&N3, Chess::chessboard[5 - 1]['b' - 'a'].getOccupant());
                    Knight N4('N', 'd', 4);
                    N4.move('c', 6);
                    CHECK_EQ(&N4, Chess::chessboard[6 - 1]['c' - 'a'].getOccupant());
                    Knight N5('N', 'd', 4);
                    N5.move('e', 6);
                    CHECK_EQ(&N5, Chess::chessboard[6 - 1]['e' - 'a'].getOccupant());
                    Knight N6('N', 'd', 4);
                    N6.move('f', 5);
                    CHECK_EQ(&N6, Chess::chessboard[5 - 1]['f' - 'a'].getOccupant());
                    Knight N7('N', 'd', 4);
                    N7.move('f', 3);
                    CHECK_EQ(&N7, Chess::chessboard[3 - 1]['f' - 'a'].getOccupant());
                    Knight N8('N', 'd', 4);
                    N8.move('e', 2);
                    CHECK_EQ(&N8, Chess::chessboard[2 - 1]['e' - 'a'].getOccupant());
                }

                TEST_CASE("KnightCaptureOppositeColor"){
                    Chess::initializeBoard();
                    clearBoard();

                    Knight N1('N', 'd', 4);
                    Knight n1('n', 'e', 6);
                    
                    N1.move('e', 6);
                    CHECK_EQ(Chess::chessboard[6 - 1]['e' - 'a'].getOccupant(), &N1);

                    Knight n2('n', 'd', 4);
                    n2.move('e', 6);
                    CHECK_EQ(Chess::chessboard[6 - 1]['e' - 'a'].getOccupant(), &n2);
                }

                TEST_CASE("KnightNoCaptureSameColor"){
                    try{
                        Chess::initializeBoard();
                        clearBoard();

                        Knight N1('N', 'd', 4);
                        Knight N2('N', 'e', 6);

                        N1.move('e', 6);
                        CHECK_EQ(Chess::chessboard[6 - 1]['e' - 'a'].getOccupant(), &N2);

                        N2.move('d', 4);
                        CHECK_EQ(Chess::chessboard[4 - 1]['d' - 'a'].getOccupant(), &N1);
                    }
                    catch (const std::exception& e) {
                        std::cout << "Caught exception: " << e.what() << "\n";
                    }
                }

                TEST_CASE("tryAllSquares"){
                    Chess::initializeBoard();
                    clearBoard();
                    clearTracker();
                    for (int rank = 1; rank <= 8; rank++) {
                        for (int file = 'a'; file <= 'h'; file++) {
                            bool isLegal = Knight('k', 'd', 4).isMoveLegal(file, rank);

                            if ((rank == 4) && (file == 'd')) {
                                tracker[rank - 1][file - 'a'] = 'N';
                                continue; // Do not check no move condition. Could be true or false
                            }
                            else if ((abs(file - 'd') < 1)
                                || (abs(rank - 4) < 1)
                                || (abs(file - 'd') > 2)
                                || (abs(rank - 4) > 2)
                                ) {
                                tracker[rank - 1][file - 'a'] = isLegal ? '?' : ' ';
                                CHECK_FALSE(isLegal);
                            }
                            else if (abs(file - 'd') + abs(rank - 4) != 3) {
                                tracker[rank - 1][file - 'a'] = isLegal ? '?' : ' ';
                                CHECK_FALSE(isLegal);
                            }
                            else {
                                tracker[rank - 1][file - 'a'] = isLegal ? 'n' : 'x';
                                CHECK(isLegal);
                            }
                        }
                    }

                    printTracker("Tracker results for attempted moves to each square from d4\n"
                        "N: Starting square\n"
                        "n: Allowed Legal Move\n"
                        "x: Allowed Illegal Move\n"
                        "?: Disallowed Legal Move\n"
                        " : Disallowed Illegal Move\n");
                }
            }
        #endif // End of test suite for Knight class
    #pragma endregion // End of test region for Knight class
#endif // End of test suite for LAB 6

// Lab 9 Tests (Invalid Move Exception)
#if LAB >= 9

 #include "invalid_move_ex.h"
    
    #pragma region TEST INVALID_MOVE_EX CLASS
        #ifndef INVALID_MOVE_EX_H

            // Fail test and skip the test suite if class is not defined
            TEST_CASE("Class Invalid Move Ex Defined") {
                CHECK_MESSAGE(false, "Invalid Move Ex class is not defined or there is no header guard with the name INVALID_MOVE_EX_H");
            }

        #else
        
            TEST_SUITE("invalidMoveException") {

                TEST_CASE("checkExceptionConstructors") {
                    CHECK_NOTHROW(invalid_move_ex e('a', 1));
                    CHECK_NOTHROW(invalid_move_ex e2('b', 2, "Big problem!"));
                    CHECK_THROWS_AS([](){ throw invalid_move_ex('b', 2, "Big problem!"); }(), std::runtime_error);
                }

                TEST_CASE("checkInvalidOriginFromInsertionOperator") {
                    resetBoard();
                    CHECK_THROWS_AS(Chess::chessboard[3 - 1]['c' - 'a'] >> Chess::chessboard[4 - 1]['c' - 'a'], invalid_move_ex);
                }

                TEST_CASE("checkInvalidOriginFromMakeMove") {
                    resetBoard();
                    CHECK_THROWS_AS(simulateMakeMove('c', 3, 'c', 4, false), invalid_move_ex);
                    CHECK_THROWS_AS(simulateMakeMove('z', 9, 'a', 4, false), invalid_move_ex);
                }

                TEST_CASE("checkInvalidDestination") {
                    resetBoard();
                    CHECK_THROWS_AS(simulateMakeMove('c', 2, 'c', 5, true), invalid_move_ex);
                    CHECK_THROWS_AS(simulateMakeMove('d', 2, 'z', 9, true), invalid_move_ex);
                }

                TEST_CASE("checkMoveWrongColorExceptionCreated") {
                    resetBoard();
                    CHECK_THROWS_AS(simulateMakeMove('a', 2, 'a', 4, false), invalid_move_ex);
                    CHECK_THROWS_AS(simulateMakeMove('a', 7, 'a', 5, true), invalid_move_ex);
                }
            }
        #endif // End of test suite (else branch)
    #pragma endregion // End of test region for Invalid Move Exception class
#endif // End of test suite for LAB 9

 
