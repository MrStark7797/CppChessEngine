#include <iostream>
using namespace std;
#include <stdlib.h> //for time
#include "defs.h"
#include "init.cpp"
#include "bitboard.cpp"
#include "board.cpp"
#include "data.cpp"
#include <string> 


int main() {
    AllInit();
    
    string FEN1_S = "8/8/2R2pk1/P5p1/8/5PK1/r4BP1/5b2 b - - 5 52;";
    
    S_BOARD board[1];
    char* FEN1 = FEN1_S.data();
    

    ParseFen(FEN1, board);
    PrintBoard(board);

    ASSERT(CheckBoard(board));

    printf("Forced\n");

    board->pieceNum[wP]--;
    ASSERT(CheckBoard(board));

}