#include <iostream>
using namespace std;

#include "defs.h"
#include "init.cpp"
#include "bitboard.cpp"

int main() {
    AllInit();
    
    int index = 0;
    U64 playBitBoard = 0ULL;
    int input;
    cin >> input;
    while (-1 < input){
        SETBIT(playBitBoard, input);
        PrintBitBoard(playBitBoard);
        cin >> input;
    };
    cout << "clear";
    cin >> input;
    while (-1 < input){
        CLEARBIT(playBitBoard, input);
        PrintBitBoard(playBitBoard);
        cin >> input;
    };
    


    return 0;
}