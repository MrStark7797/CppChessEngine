#ifndef DEFS_H

#define DEFS_H
#pragma once

#include <iostream>
#include <string>

//#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
}
#endif

//creates bitboard
typedef unsigned long long U64;

inline std::string NAME_S("Slice v1.0");
inline char* NAME = NAME_S.data();
enum{iWhite, iBlack, iPawn, iKnight, iBishop, iRook, iQueen, iKing, iOccupied, iEmpty};
enum{wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK, noneType};
const int MAX_GAMEMOVES = 2048;
const int MAX_POSITIONMOVES =256;
const int MAX_DEPTH = 64;
#define BOARD_SQ_NUM 120 //board will have 8x8 board where the game is played and 56 spare tiles to work as boarder squares

//rank and file defintions a-h and 1-8
// indexed from 0 to 7
enum { FILEA, FILEB, FILEC, FILED, FILEE, FILEF, FILEG, FILEH, FILENONE};
enum { RANK1, RANK2, RANK3, RANK4, RANK5, RANK6, RANK7, RANK8, RANKNONE};

inline std::string START_FEN_STRING = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
inline char* START_FEN = START_FEN_STRING.data(); 

//Number Corrolating to the colour of the peice, 0 is white, 1 is black and 2 is both
enum { WHITE, BLACK, BOTH};
enum { UCIMODE};

#undef TRUE
#undef FALSE

enum {FALSE, TRUE };

#define INFINITE 30000
#define ISMATE (INFINITE - MAX_DEPTH)


class BOARD{
    public:
        

        U64 pieceBB[10];
        int getPieceBB(int pieceType){
            
            if(pieceType < bP){
                return (pieceBB[pieceType2BB(pieceType)] & pieceBB[iWhite]);
            } else{
                return (pieceBB[pieceType2BB(pieceType)] & pieceBB[iBlack]);
            }
        };
        int getPieceFromSq(int sq){ 
            for(int pieceType = wP; pieceType <= bK; pieceType++){
                if(pieceType < bP){
                    if ((checkBit((pieceBB[pieceType2BB(pieceType)] & pieceBB[iWhite]), sq)) == 1)
                    {
                        return pieceType;
                    }
                    
                    
                } else{
                     if ((checkBit((pieceBB[pieceType2BB(pieceType)] & pieceBB[iBlack]), sq)) == 1)
                    {
                        return pieceType;
                    }
                }
            
            }
        };
        int side2move;
        int enPas;
        int fiftymove;
        int ply;
        int hisply;
    
        int castlePerm;
        //arrays used to store number of piece
        int pieceNum[13];
        //stores pieces by colour
        int bigPiece[3]; //anything not a pawn
        int majPiece[3]; //R &Q
        int minPiece[3]; //B&N
};
//GAME MOVE

#define FROMSQ(m) ((m) & 0x7F)
#define TOSQ(m) (((m)>>7) & 0x7F)
#define CAPTURED(m) (((m)>>14) & 0xF)
#define PROMOTED(m) (((m)>>20) & 0xF)

#define MFLAGEP 0x40000
#define MFLAGPS 0x80000
#define MFLAGCA 0x1000000

#define MFLAGCAP 0x7C000
#define MFLAGPROM 0xF00000

#define NOMOVE 0

//MACROS

#define SQ64(sq120) (Sq120ToSq64[(sq120)]) //macro to shorten what is typed.

#define FR2SQ(file, rank) (((file)) + ((rank)*8)) //marco which turns file and rank into the 64 bitboard square

#define CLEARBIT(bitboard,sq) ((bitboard) &= ClearMask[(sq)]) //takes bitboard and square and performs an and operation
#define SETBIT(bitboard,sq) ((bitboard) |= SetMask[(sq)]) //takes bitboard and square and performs an or operation

//GLOBALS
extern int Sq120ToSq64[BOARD_SQ_NUM];
extern int Sq64ToSq120[64];


//FUNCTIONS
//init.cpp
extern void AllInit();
//bitboard.cpp
extern void PrintBitBoard(U64 bb);
extern int CountBits(U64 b);
extern int checkBit(U64 bb, int n);
extern int pieceType2BB(int pieceType);
#endif 
// DEFS_H
