#include <iostream>
#include "defs.h"

U64 GenPosKey(const S_BOARD *pos) {

	int sq = 0;
	U64 finalKey = 0;
	int piece = EMPTY;
	
	// pieces
	for(sq = 0; sq < BRD_SQ_NUM; ++sq) {
		piece = pos->pieces[sq];
		if(piece!=NO_SQ && piece!=EMPTY && piece != OFFBOARD) {
			ASSERT(piece>=wP && piece<=bK);
			finalKey ^= PieceKeys[piece][sq];
		}		
	} //Looped through all squares setting piece equal to value in the array at that square
    //at a boarder square the square is skipped, as well as if the piece is a real piece where it is within the enum of piece they are valid and can be used for arrays.
	
	if(pos->side2move == WHITE) {
		finalKey ^= SideKey;
	} //if white move hash in sidekey
		
	if(pos->enPas != NO_SQ) {
		ASSERT(pos->enPas>=0 && pos->enPas<BRD_SQ_NUM);
		
		finalKey ^= PieceKeys[EMPTY][pos->enPas];
	} //If a pawn is moved forward 2 squares the enPasaunt square is set generates a square for the square and indexes it by empty or 0, if this is the case we hash it in
	
	ASSERT(pos->castlePerm>=0 && pos->castlePerm<=15); //chechs if castle permision is within
	
	finalKey ^= CastleKeys[pos->castlePerm]; //is hashed in as we use 4 bits 
	
	return finalKey;
}

