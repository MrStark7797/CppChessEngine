#include <iostream>
using namespace std;

#include "defs.h"

#include <string> 



int main(){

    AllInit();
    
    string FEN1_S = "4k3/8/3p4/8/8/3N4/5K2/8 w - - 0 1";
    char* FEN1 = FEN1_S.data();

 
    printf( "\n" );
    S_BOARD board[1];
    
    

    ParseFen(FEN1, board);

    S_MOVELIST list[1];

    GenerateAllMoves(board, list);

    PrintMoveList(list);

}