#ifndef DEFS_H

#define DEFS_H


#include <iostream>
using namespace std;

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
}
#endif


//creates bitboard
typedef unsigned long long U64;

const std::string NAME = "Slice 1.0";

const int BRD_SQ_NUM = 120; //board will have 8x8 board where the game is played and 56 spare tiles to work as boarder squares

const int MAXGAMEMOVES = 2048;
const int MAXPOSITIONMOVES =256;

inline string START_FEN_STRING = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
inline const char* START_FEN = START_FEN_STRING.data(); 

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
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
};

enum {FALSE, TRUE};

//Represented by 4 bits bit one tells us if white can castle kingside and so on
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8};

typedef struct{
    int move;
    int score;
} S_MOVE;
typedef struct{
    S_MOVE moves[MAXPOSITIONMOVES]; //contains array of S_MOVE structures upt to 256 moves
    int count;
} S_MOVELIST;
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
    int fiftyMove;

    int ply;
    int hisPly;

    int castlePerm;

    U64 posKey; //unique number representing position on the board links with history to determine if their are repititions

    //arrays used to store number of piece
    int pieceNum[13];
    //stores pieces by colour
    int bigPiece[2]; //anything not a pawn
    int majPiece[2]; //R &Q
    int minPiece[2]; //B&N
    int material[2]; 
    S_UNDO history[MAXGAMEMOVES];
    //peice list
    int pList[13][10];

} S_BOARD;

// GAME MOVE

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


//MARCROS

#define FR2SQ(file, rank) ((21 +(file)) + ((rank)*10)) //marco which turns file and rank into the 120 bitboard square

#define SQ64(sq120) (Sq120ToSq64[(sq120)]) //macro to shorten what is typed.
#define SQ120(sq64) (Sq64ToSq120[(sq64)]) //Turns square in U64 to square into U120 for resetting board
#define POP(bit) PopBit(bit)
#define COUNT(bit) CountBits(bit)
#define CLEARBIT(bitboard,sq) ((bitboard) &= ClearMask[(sq)]) //takes bitboard and square and performs an and operation
#define SETBIT(bitboard,sq) ((bitboard) |= SetMask[(sq)]) //takes bitboard and square and performs an or operation


//macros to check if a peice is bishop/queen rook/queen or Knight or king
#define IsBQ(p) (PieceBishopQueen[(p)])
#define IsRQ(p) (PieceRookQueen[(p)])
#define IsKn(p) (PieceKnight[(p)])
#define IsKi(p) (PieceKing[(p)])



//GLOBALS
extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];
extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16];
extern char PceChar[]; //four arrays which are indexed in order to print peice side rank and file
extern char SideChar[];
extern char RankChar[];
extern char FileChar[];

extern int PieceBig[13];
extern int PieceMaj[13];
extern int PieceMin[13];
extern int PieceVal[13];
extern int PieceCol[13];
extern int PiecePawn[13];

extern int FilesBrd[BRD_SQ_NUM];
extern int RanksBrd[BRD_SQ_NUM];

extern int PieceKnight[13];
extern int PieceKing[13];
extern int PieceRookQueen[13];
extern int PieceBishopQueen[13];
extern int PieceSlides[13];
//FUNCTIONS
//init.cpp
extern void AllInit();

//bitboard.cpp
extern void PrintBitBoard(U64 bb);
extern int PopBit(U64 *bb);
extern int CountBits(U64 b);

// hashkeys.cpp
extern U64 GenPosKey(const S_BOARD *pos);

// board.cpp
extern void ResetBoard(S_BOARD *pos);
extern void PrintBoard(const S_BOARD *pos);
extern int ParseFen(char *fen, S_BOARD *pos);
extern void UpdateListsMaterial(S_BOARD *pos);
extern int CheckBoard(const S_BOARD *pos);

//attack.cpp

extern int SqAttacked(const int sq, const int side, const S_BOARD *pos);

//io.cpp

extern char *PrMove(const int move);
extern char *PrSq(const int sq);
extern void PrintMoveList(const S_MOVELIST *list);
//validate.cpp

extern int SqOnBoard(const int sq);
extern int SideValid(const  int side);
extern int FileRankValid(const int fr);
extern int PieceValidEmpty(const int pce);
extern int PieceVAlid(const int pce);


//movegen.cpp

extern void GenerateAllMoves(const S_BOARD *pos, S_MOVELIST *list);


#endif 
// DEFS_H
