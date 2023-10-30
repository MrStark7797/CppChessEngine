//init.cpp
#include "defs.h"

int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

#define RAND_64 	((U64)rand() | \
					(U64)rand() << 15 | \ 
					(U64)rand() << 30 | \ 
					(U64)rand() << 45 | \ 
					((U64)rand() & 0xf) << 60 )
//shifts 15 bits to left
//30 bits
//45 bits shifted
//0xf is 4 bits at the end and shifting by 60 gets a random number across the random 64 bit number.
U64 SetMask[64];
U64 ClearMask[64];

U64 PieceKeys[13][120];
U64 SideKey;
U64 CastleKeys[16]; // uses 4 bits 0 0 0 0 since bit is flipped to 1 for each posible castle ie blackkingside white queenside etc

void InitHashKeys() {

	int index = 0;
	int index2 = 0;
	for(index = 0; index < 13; ++index) {
		for(index2 = 0; index2 < 120; ++index2) {
			PieceKeys[index][index2] = RAND_64;
		}
	}
	SideKey = RAND_64;
	for(index = 0; index < 16; ++index) {
		CastleKeys[index] = RAND_64;
	}

} //two loops which fills up both castlekeys and piece keys with random numbers upon initialisation.

void InitBitMasks(){
    int index = 0;

    for(index = 0; index < 64; index++){
        SetMask[index] = 0ULL;
        ClearMask[index] = 0ULL;
    }
    for(index = 0; index < 64; index++){
        SetMask[index] |= (1ULL << index);
        ClearMask[index] = ~SetMask[index];
    }
}

void InitSq120To64(){
    //definitions of variables
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;
    //first thing is iterating through all of the squares in the array setting them to 65/120 as it is a value that should be imposible to be on the board (falsesafe)
    for(index = 0; index < BRD_SQ_NUM; ++index){
        Sq120ToSq64[index] = 65;
    };
    for(index = 0; index < 64; ++index){
        Sq64ToSq120[index] = 120;

    };
    //Starting at rank 1 and file 1 iterating through the file and the rank
    for(rank = RANK_1; rank <= RANK_8; ++rank){
        for(file = FILE_A; file <= FILE_H; ++file){
            //the square is collected through the macro
            sq = FR2SQ(file,rank);

            //gives value of sq from sq64 and vice versa.
            Sq64ToSq120[sq64] = sq;
            Sq120ToSq64[sq] = sq64;
            //incrementing the square 64 it increments through the board instead of calculating through the ranks and files

            sq64++;
        };
    };
}

void AllInit(){
    InitSq120To64();
    InitBitMasks();
    InitHashKeys();
}