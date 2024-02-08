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

void PrintBitBoard(U64 bb) {
    //Used to print and visualise any bitboard on the screen
	U64 shiftMe = 1ULL;
	
	int rank = 0;
	int file = 0;
	int sq = 0;


    //starts at 8th rank and file a moving down the table printing out the bitboard.
    printf("\n");
	for(rank = RANK8; rank >= RANK1; --rank) {
		for(file = FILEA; file <= FILEH; ++file) {
			sq = FR2SQ(file,rank);	// 120 based		
			

            //if a bit is stored as 1 on the bit board the output will be X
			if((shiftMe << sq) & bb) 
				printf("X");
			else 
				printf("-");
		}
		printf("\n");
	}  
    printf("\n\n");
}

int CountBits(U64 b) {
  int r;
  for(r = 0; b; r++, b &= b - 1);
  return r;
} //counts the total number iof bits
int checkBit(U64 bb, int n){
  int mask = 1 << n;
  int result = bb & mask;
  if(result != 0){
    return TRUE;
  }else{
    return FALSE;
  }
}
int pieceType2BB(int pieceType){
  switch (pieceType){
    case wP:
      return iPawn;
      break;
    case bP:
      return iPawn;
      break;
    case wN:
      return iKnight;
      break;
    case bN:
      return iKnight;
      break;
    case wB:
      return iBishop;
      break;
    case bB:
      return iBishop;
      break;
    case wR:
      return iRook;
      break;
    case bR:
      return iRook;
      break;
    case wQ:
      return iQueen;
      break;
    case bQ:
      return iQueen;
      break;
    case wK:
      return iKing;
      break;
    case bK:
      return iKing;
      break;
  }
}
/*
enum{iWhite, iBlack, iPawn, iKnight, iBishop, iRook, iQueen, iKing, iOccupied, iEmpty};
enum{wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK, noneType};
*/