#include <iostream>
using namespace std;
#include <stdlib.h> //for time
#include "defs.h"
#include "init.cpp"
#include "bitboard.cpp"


int main() {
    AllInit();
    
    int Piece1 = rand();
    int Piece2 = rand();
    int Piece3 = rand();
    int Piece4 = rand();

    printf("Piece1:%X\n",Piece1);
    printf("Piece1:%X\n",Piece2);
    printf("Piece1:%X\n",Piece3);
    printf("Piece1:%X\n",Piece4);

    int Key = Piece1 ^ Piece2 ^ Piece3 ^ Piece4;
    int TempKey = Piece1;
    TempKey ^= Piece2;
    TempKey ^= Piece3; 
    TempKey ^= Piece4; 

    printf("Key:%X\n", Key);
    printf("TempKey:%X\n", TempKey);
    return 0;
}