#include <iostream>
using namespace std;

#include "defs.h"
#include "init.cpp"
#include "bitboard.cpp"

int main() {
    AllInit();
    
    int index = 0;
    U64 playBitBoard = 0ULL;

    SETBIT(playBitBoard, 61);
    PrintBitBoard(playBitBoard);

    
    return 0;
}