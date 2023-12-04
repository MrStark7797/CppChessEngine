#include <iostream>
using namespace std;

#include "defs.h"

#include <string> 



int main(){

    AllInit();
    
    string FEN1_S = "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/7P/P1P1P3/RNBQKBNR w KQkq e6 0 1 ";
    char* FEN1 = FEN1_S.data();

 
    printf( "\n" );
    S_BOARD board[1];
    
    

    ParseFen(FEN1, board);
    PrintBoard(board);

    S_MOVELIST list[1];

    GenerateAllMoves(board, list);

    PrintMoveList(list);

}