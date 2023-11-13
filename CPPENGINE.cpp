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
    
    string FEN1_S = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";
    string FEN2_S = "rnbqkbnr/pp1ppppp/2p5/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq c6 0 2";
    string FEN3_S = "rnbqkbnr/pppppppp/2p5/8/4P3/5N2/PPPP1PPP/RNBQKBNR b KQkq - 1 2";


    S_BOARD board[1];
    char* FEN1 = FEN1_S.data();
    char* FEN2 = FEN2_S.data();
    char* FEN3 = FEN3_S.data();

    ParseFen(START_FEN, board);
    PrintBoard(board);

    ParseFen(FEN1, board);
    PrintBoard(board);

    ParseFen(FEN2, board);
    PrintBoard(board);

    ParseFen(FEN3, board);
    PrintBoard(board);

}