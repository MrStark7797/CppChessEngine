#include <iostream>
#include "defs.h"

U64 SetMask[64];
U64 ClearMask[64];
int Sq120ToSq64[BOARD_SQ_NUM];
int Sq64ToSq120[64];
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
    int file = FILEA;
    int rank = RANK1;
    int sq64 = 0;
    int sq = 0;
    //first thing is iterating through all of the squares in the array setting them to 65/120 as it is a value that should be imposible to be on the board (falsesafe)
    for(index = 0; index < BOARD_SQ_NUM; ++index){
        Sq120ToSq64[index] = 65;
    };
    for(index = 0; index < 64; ++index){
        Sq64ToSq120[index] = 120;

    };
    //Starting at rank 1 and file 1 iterating through the file and the rank
    for(rank = RANK1; rank <= RANK8; ++rank){
        for(file = FILEA; file <= FILEH; ++file){
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

}