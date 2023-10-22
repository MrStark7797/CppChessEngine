#include <iostream>
using namespace std;

#include "defs.h"
#include "init.cpp"
#include "bitboard.cpp"

int main() {
    AllInit();
    
    U64 playBitBoard = 0ULL;

    playBitBoard |= (1ULL << SQ64(D2));
    playBitBoard |= (1ULL << SQ64(D3));
    playBitBoard |= (1ULL << SQ64(D4));



}