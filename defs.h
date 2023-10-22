#ifndef DEFS_H
#define DEFS_H 

#include "stdlib.h"

#define DEBUG

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
exit(1);}
#endif


//creates bitboard
typedef unsigned long long U64;

const string NAME = "Slice 1.0";

const int BRD_SQ_NUM = 120; //board will have 8x8 board where the game is played and 56 spare tiles to work as boarder squares

const int MAXGAMEMOVES = 2048;
/*defines peices stored first letter shows colour, second letter shows peice type
P = Pawn = 1
N = KNight = 2
B = Bishop = 3
R = rook = 4
Q = Queen = 5
K = King = 6
*/
enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK};

//rank and file defintions a-h and 1-8
// indexed from 0 to 7
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE};
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE};


//Number Corrolating to the colour of the peice, 0 is white, 1 is black and 2 is both
enum { WHITE, BLACK, BOTH};

//the squares of the board
//starts with A1 being on squarre 21 which starts the board while still having 56 boarder/spare squares
enum {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ
};

enum {FALSE, TRUE};

//Represented by 4 bits bit one tells us if white can castle kingside and so on
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8};

typedef struct{
    int move;
    int castlePerml;
    int enPas;
    int fiftyMove;
    U64 posKey;
} S_UNDO;

typedef struct {
    int pieces[BRD_SQ_NUM];
    U64 pawns[3]; 

    int KingSq[2];

    int side2move;
    int enPas;
    int fiftymove;

    int ply;
    int hisply;

    int castlePerm;

    U64 posKey;

    //arrays used to store number of piece
    int pieceNum[13];
    //stores pieces by colour
    int bigPiece[3]; //anything not a pawn
    int majPiece[3]; //R &Q
    int minPiece[3]; //B&N
    S_UNDO history[MAXGAMEMOVES];
    //peice list
    int pList[13][10];

} S_BOARD;

//MARCROS

#define FR2SQ(file, rank) ((21 +(file)) + ((rank)*10)) //marco which turns file and rank into the 120 bitboard square
#define SQ64(sq120) Sq120ToSq64[sq120] //macro to shorten what is typed.

//GLOBALS
extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];


//FUNCTIONS

extern void AllInit();

extern void PrintBitBoard(U64 bb);
extern int PopBit(U64 *bb);

#endif // DEFS_H