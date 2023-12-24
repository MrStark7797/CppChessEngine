#include <iostream>
using namespace std;

#include "defs.h"

#include <string> 



int main(){

    AllInit();
    
    string FEN1_S = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    char* FEN1 = FEN1_S.data();
    printf("\n");
    S_BOARD board[1];
    S_MOVELIST list[1];
    ParseFen(FEN1, board);

    //Depth 1
    PerftTest(3, board);
    //Depth 2
    //PerftTest(2, board);
    //Depth 3
    //PerftTest(3, board);
}