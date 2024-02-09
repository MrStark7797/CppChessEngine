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
enum{EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK, noneType};
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

//the squares of the board
//starts with A1 being on squarre 0 which starts the board
enum {
    A1 = 0, B1, C1, D1, E1, F1, G1, H1,
    A2 = 8, B2, C2, D2, E2, F2, G2, H2,
    A3 = 16, B3, C3, D3, E3, F3, G3, H3,
    A4 = 24, B4, C4, D4, E4, F4, G4, H4,
    A5 = 32, B5, C5, D5, E5, F5, G5, H5,
    A6 = 40, B6, C6, D6, E6, F6, G6, H6,
    A7 = 48, B7, C7, D7, E7, F7, G7, H7,
    A8 = 56, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD,
};

#undef TRUE
#undef FALSE

enum {FALSE, TRUE };

#define INFINITE 30000
#define ISMATE (INFINITE - MAX_DEPTH)

//Represented by 4 bits bit one tells us if white can castle kingside and so on
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8};

class MOVE{
    public:
    int move;
    int score;
};
class MOVELIST{
    public:
    MOVE moves[MAX_POSITIONMOVES];
    int count;
};
class PVENTRY{
    public:
    U64 posKey;
	int move;
	int score;
	int depth;
};
class PVTABLE{
    public:
    PVENTRY *pTable;
	int numEntries;
};
enum {  HFNONE, HFALPHA, HFBETA, HFEXACT};

class UNDO{
    public:
    int move;
    int castlePerm;
    int enPas;
    int fiftyMove;
    U64 posKey;    
};
class BOARD{
    public:
        

        U64 pieceBB[8];
        U64 occupiedBB;
        U64 emptyBB;
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
        int KingSq[2];
        
        int side2move;
        int enPas;
        int fiftymove;
        
        int ply; //half moves in current search
        int hisPly; // half moves in history of the game

        U64 posKey; //unique number representing position on the board links with history to determine if their are repititions
        int castlePerm;
        //arrays used to store number of piece
        int pieceNum[13];
        //stores pieces by colour
        int bigPiece[3]; //anything not a pawn
        int majPiece[3]; //R &Q
        int minPiece[3]; //B&N
        UNDO history[MAX_GAMEMOVES];
        PVTABLE PvTable[1];
        int PvArray[MAX_DEPTH];
        int searchHistory[13][BOARD_SQ_NUM];
	    int searchKillers[2][MAX_DEPTH];//2 moves that cause a non capture which beat beta.



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

extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16];


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
