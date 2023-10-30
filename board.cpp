#include <iostream>
#include "defs.h"

void ResetBoard(S_BOARD *pos) {

	int index = 0;

    for(index = 0; index < BRD_SQ_NUM; ++index) {
		pos->pieces[index] = OFFBOARD;
	}
    //sets all tiles to offboard
	for(index = 0; index < 64; ++index) {
		pos->pieces[SQ120(index)] = EMPTY;
	}
    //Sets all peices on the board from offboard to empty so they are usable
    for(index = 0; index < 2; ++index) {
		pos->bigPiece[index] = 0;
		pos->majPiece[index] = 0;
		pos->minPiece[index] = 0;
		pos->material[index] = 0;
	} //Resets all peices and their arrays
    for(index = 0; index < 3; ++index) {
		pos->pawns[index] = 0ULL;
	}
    //sets all values in pawns to 0
	for(index = 0; index < 13; ++index) {
		pos->pieceNum[index] = 0;
	}
    //sets all values in peices to 0
	pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;

	pos->side2move = BOTH;
	pos->enPas = NO_SQ;
	pos->fiftyMove = 0;

	pos->ply = 0;
	pos->hisPly = 0;

	pos->castlePerm = 0;

	pos->posKey = 0ULL;
    //resets all colours to both colors and all other permisions and rules to 0. 
    //sets colours to both so we can assert if a peice is defined as both colours.
} 