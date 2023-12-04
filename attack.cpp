#include <iostream>
using namespace std;
#include "defs.h"

const int KnDir[8] = { -8, -19,	-21, -12, 8, 19, 21, 12 }; //2 rank away and 1 row or the otherway around
const int RkDir[4] = { -1, -10,	1, 10 }; //along same rank/file
const int BiDir[4] = { -9, -11, 11, 9 }; //diagonally allong
const int KiDir[8] = { -1, -10,	1, 10, -9, -11, 11, 9 }; //1 square away each side.


//Takes arguements of what is attacked the side attacking and the current position on the board
int SqAttacked(const int sq, const int side, const S_BOARD *pos) {

    int pce,index,t_sq,dir; //Defines the variables to hold a piece the indexing and temporary square
	
	ASSERT(SqOnBoard(sq));
	ASSERT(SideValid(side));
	ASSERT(CheckBoard(pos));
	
	// pawns
	if(side == WHITE) { //if attacking side is white
		if(pos->pieces[sq-11] == wP || pos->pieces[sq-9] == wP) { //the square north west and east diagonally
			return TRUE; //if so it is attacked
		}
	} else {
		if(pos->pieces[sq+11] == bP || pos->pieces[sq+9] == bP) { // if black and the square is south west/east
			return TRUE;
		}	
	}
	
	// knights
	for(index = 0; index < 8; ++index) {		 //loops through all 8 directions that a knight could attack from
		pce = pos->pieces[sq + KnDir[index]]; 

		if(pce != OFFBOARD && IsKn(pce) && PieceCol[pce]==side) {
			return TRUE;//Checks if on the square in one of the directions has a knight and if it does it returns true
		}
	}
	
	// rooks, queens
	for(index = 0; index < 4; ++index) {//checks all 4 directions
		dir = RkDir[index];
		t_sq = sq + dir;

		pce = pos->pieces[t_sq];

		while(pce != OFFBOARD) {  //since these peices are sliding pieces they can attack from a whole file/rank
			if(pce != EMPTY) { //checks squares along the path till it comes across a piece or an offboard square
				if(IsRQ(pce) && PieceCol[pce] == side) { //if the first piece along the file/rank is a rook or queen it attacks that square.
					return TRUE;
				}
				break;
			}
			t_sq += dir;

			pce = pos->pieces[t_sq];
		}
	}
	
	// bishops, queens
	for(index = 0; index < 4; ++index) {//checks all four diagonal
		dir = BiDir[index];
		t_sq = sq + dir;

		pce = pos->pieces[t_sq];

		while(pce != OFFBOARD) { //since these pieces are sliding pieces they can attack from a whole diagonal
			if(pce != EMPTY) {  //checks squares along the path till it comes across a piece or an offboard square
				if(IsBQ(pce) && PieceCol[pce] == side) {
					return TRUE;//if the first piece along the diagonal is a bishop or queen it attacks that square.
				}
				break;
			}
			t_sq += dir;

			pce = pos->pieces[t_sq];
		}
	}
	
	// kings
	for(index = 0; index < 8; ++index) {		//checks all 8 squares directly next to the square
		pce = pos->pieces[sq + KiDir[index]];

		if(pce != OFFBOARD && IsKi(pce) && PieceCol[pce]==side) {
			return TRUE;
		}
	}
	
	return FALSE;//if none are true no pieces are attacked

}