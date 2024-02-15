#include <iostream>

#include "defs.h"

const int KnDir[8] = { -6, -10,	-17, -15, 6, 10, 17, 15 }; //2 rank away and 1 row or the otherway around
const int RkDir[4] = { -1, -8,	1, 8 }; //along same rank/file
const int BiDir[4] = { -9, -7, 7, 9 }; //diagonally allong
const int KiDir[8] = { -1, -8,	1, 8, -7, -9, 9, 7 }; //1 square away each side.


//Takes arguements of what is attacked the side attacking and the current position on the board
int SqAttacked(const int sq, const int side, BOARD board) {

    int pce,index,t_sq,dir; //Defines the variables to hold a piece the indexing and temporary square
	
	ASSERT(SqOnBoard(sq));
	ASSERT(SideValid(side));
	ASSERT(CheckBoard(pos));
	
	// pawns
	if(side == WHITE) { //if attacking side is white
		if(board.getPieceFromSq(sq-9) == wP || board.getPieceFromSq(sq-7) == wP) { //the square north west and east diagonally
			return TRUE; //if so it is attacked
		}
	} else {
		if(board.getPieceFromSq(sq+9) == bP || board.getPieceFromSq(sq+7)== bP) { // if black and the square is south west/east
			return TRUE;
		}	
	}
	
	// knights
	for(index = 0; index < 8; ++index) {		 //loops through all 8 directions that a knight could attack from
		pce = board.getPieceFromSq(sq + KnDir[index]); 

		if(pce != OFFBOARD && IsKn(pce) && PieceCol[pce]==side) {
			return TRUE;//Checks if on the square in one of the directions has a knight and if it does it returns true
		}
	}
	
	// rooks, queens
	for(index = 0; index < 4; ++index) {//checks all 4 directions
		dir = RkDir[index];
		t_sq = sq + dir;

		pce = board.getPieceFromSq(t_sq);

		while(pce != OFFBOARD) {  //since these peices are sliding pieces they can attack from a whole file/rank
			if(pce != EMPTY) { //checks squares along the path till it comes across a piece or an offboard square
				if(IsRQ(pce) && PieceCol[pce] == side) { //if the first piece along the file/rank is a rook or queen it attacks that square.
					return TRUE;
				}
				break;
			}
			t_sq += dir;

			pce = board.getPieceFromSq(t_sq);
		}
	}
	
	// bishops, queens
	for(index = 0; index < 4; ++index) {//checks all four diagonal
		dir = BiDir[index];
		t_sq = sq + dir;

		pce = board.getPieceFromSq(t_sq);

		while(pce != OFFBOARD) { //since these pieces are sliding pieces they can attack from a whole diagonal
			if(pce != EMPTY) {  //checks squares along the path till it comes across a piece or an offboard square
				if(IsBQ(pce) && PieceCol[pce] == side) {
					return TRUE;//if the first piece along the diagonal is a bishop or queen it attacks that square.
				}
				break;
			}
			t_sq += dir;

			pce = board.getPieceFromSq(t_sq);
		}
	}
	
	// kings
	for(index = 0; index < 8; ++index) {		//checks all 8 squares directly next to the square
		pce = board.getPieceFromSq(sq + KiDir[index]);

		if(pce != OFFBOARD && IsKi(pce) && PieceCol[pce]==side) {
			return TRUE;
		}
	}
	
	return FALSE;//if none are true no pieces are attacked

}