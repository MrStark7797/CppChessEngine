#include <iostream>


#include "defs.h"

#include <cstring> 



int main(){
	AllInit();
	BOARD myBoard;
	myBoard.pieceBB[0] = 0ULL;
	int sq = FR2SQ(FILEA, RANK5);
	myBoard.pieceBB[0] |= (1ULL << 4);
	myBoard.pieceBB[0] |= (1ULL << 1);
	myBoard.pieceBB[0] |= (1ULL << 7);
	PrintBitBoard(myBoard.pieceBB[0]);
	std::cout << CountBits(myBoard.pieceBB[0]) << std::endl;
	std::cout << checkBit(myBoard.pieceBB[0], 4) << std::endl;
	std::cout << checkBit(myBoard.pieceBB[0], 5) << std::endl;
	return 0;
    
}