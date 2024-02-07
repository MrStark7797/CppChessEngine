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
enum{iWhite, iBlack, iPawn, iKnight, iBishop, iRook, iQueen, iKing};
enum{wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, b, noneType};
const int MAX_GAMEMOVES = 2048;
const int MAX_POSITIONMOVES =256;
const int MAX_DEPTH = 64;
//rank and file defintions a-h and 1-8
// indexed from 0 to 7
enum { FILEA, FILEB, FILEC, FILED, FILEE, FILEF, FILEG, FILEH, FILENONE};
enum { RANK1, RANK2, RANK3, RANK4, RANK5, RANK6, RANK7, RANK8, RANKNONE};

inline std::string START_FEN_STRING = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
inline char* START_FEN = START_FEN_STRING.data(); 

enum { UCIMODE};

#undef TRUE
#undef FALSE

enum {FALSE, TRUE };

#define INFINITE 30000
#define ISMATE (INFINITE - MAX_DEPTH)

class BOARD{
    public:
        

        U64 pieceBB[8];
        int getPieceBB(int pieceType){
            
            if(pieceType < bP){
                return (pieceBB[pieceType] & pieceBB[iWhite]);
            } else{
                return (pieceBB[pieceType] & pieceBB[iBlack]);
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

//MACROS

#define FR2SQ(file, rank) (((file)) + ((rank)*8)) //marco which turns file and rank into the 64 bitboard square

//FUNCTIONS
extern void PrintBitBoard(U64 bb);
extern int CountBits(U64 b);
extern int checkBit(U64 bb, int n);
#endif 
// DEFS_H
