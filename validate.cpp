#include <iostream>
#include "defs.h"


int SqOnBoard(const int sq){
    return FilesBrd[sq]==OFFBOARD ? 0 : 1; //expects the piece is either on or off the board
}
int SideValid(const  int side){
    return (side==WHITE || side== BLACK) ? 1:0; //checks if a piece is white or black
}
int FileRankValid(const int fr){
    return (fr >= 0 && fr <= 7) ? 1:0; //checks if a peice is on a valid rank
}
int PieceValidEmpty(const int pce){
    return (pce >= EMPTY && pce <= bK) ? 1:0;
}
int PieceVAlid(const int pce){
    return (pce >= wP && pce <= bR) ? 1:0;
}
//used in conjunction with assertys.