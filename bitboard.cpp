#include <iostream>
#include "defs.h"

const int BitTable[64] = {
  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
  58, 20, 37, 17, 36, 8
};

int PopBit(U64 *bb) {
  U64 b = *bb ^ (*bb - 1);
  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
  *bb &= (*bb - 1);
  return BitTable[(fold * 0x783a9b23) >> 26];
} //takes the first bit starting at the least significant bit. setting it to zero.

int CountBits(U64 b) {
  int r;
  for(r = 0; b; r++, b &= b - 1);
  return r;
} //counts the total number iof bits

void PrintBitBoard(U64 bb) {
    //Used to print and visualise any bitboard on the screen
	U64 shiftMe = 1ULL;
	
	int rank = 0;
	int file = 0;
	int sq = 0;
	int sq64 = 0;

    //starts at 8th rank and file a moving down the table printing out the bitboard.
    printf("\n");
	for(rank = RANK_8; rank >= RANK_1; --rank) {
		for(file = FILE_A; file <= FILE_H; ++file) {
			sq = FR2SQ(file,rank);	// 120 based		
			sq64 = SQ64(sq); // 64 based

            //if a bit is stored as 1 on the bit board the output will be X
			if((shiftMe << sq64) & bb) 
				printf("X");
			else 
				printf("-");
		}
		printf("\n");
	}  
    printf("\n\n");
}
int checkBit(U64 bb, int n){
  int mask = 1 << n;
  int result = bb & mask;
  if(result != 0){
    return TRUE;
  }else{
    return FALSE;
  }
}
