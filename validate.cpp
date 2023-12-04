#include <iostream>
#include "defs.h"



int SqOnBoard(const int sq) {//expects the piece is either on or off the board
	return FilesBrd[sq]==OFFBOARD ? 0 : 1;
}

int SideValid(const int side) { //checks if a piece is white or black
	return (side==WHITE || side == BLACK) ? 1 : 0;
}

int FileRankValid(const int fr) {//checks if a peice is on a valid rank
	return (fr >= 0 && fr <= 7) ? 1 : 0;
}

int PieceValidEmpty(const int pce) {
	return (pce >= EMPTY && pce <= bK) ? 1 : 0;
}

int PieceValid(const int pce) {
	return (pce >= wP && pce <= bK) ? 1 : 0;
}
//used in conjunction with assertys.