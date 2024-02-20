#include <iostream>
#include "defs.h"

#define HASH_PCE(pce,sq) (board.posKey ^= (PieceKeys[(pce)][(sq)]))
#define HASH_CA (board.posKey ^= (CastleKeys[(board.castlePerm)]))
#define HASH_SIDE (board.posKey ^= (SideKey))
#define HASH_EP (board.posKey ^= (PieceKeys[EMPTY][(board.enPas)]))

const int CastlePerm[120] = {
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 13, 15, 15, 15, 12, 15, 15, 14, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15,  7, 15, 15, 15,  3, 15, 15, 11, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};
void ClearPiece(U64 toBB, BOARD board, int sq){
    int pieceType = pieceType2BB(board.getPieceFromSq(sq));
    int side = board.side2move;
    if (side == WHITE){
        board.pieceBB[pieceType] ^=  toBB;       // reset the captured piece
        board.pieceBB[iBlack] ^=  toBB;
    }

}
void MovePiece(const int from, const int to, BOARD board, U64 toBB, U64 fromBB){
    U64 fromToBB = fromBB ^ toBB; // |+
    board.pieceBB[pieceType2BB(board.getPieceFromSq(from))]  ^=  fromToBB;   // update piece bitboard
    board.pieceBB[board.side2move]  ^=  fromToBB;   // update white or black color bitboard
    board.occupiedBB            ^=  fromToBB;   // update occupied ...
    board.emptyBB               ^=  fromToBB;
}
void AddPiece(const int to, BOARD board, U64 toBB, int prPiece){
    board.pieceBB[pieceType2BB(prPiece)]  ^=  toBB;   // update piece bitboard
    board.pieceBB[board.side2move]  ^=  toBB;   // update white or black color bitboard
    board.occupiedBB            ^=  toBB;
};
int MakeMove(BOARD board, int move){
    int from = SQ64(FROMSQ(move));
    int to = SQ64(TOSQ(move));
    int side = board.side2move;
    U64 fromBB = 1ULL << from;
    U64 toBB = 1ULL << to;
    U64 fromToBB = fromBB ^ toBB; // |+
    int pieceType = board.getPieceFromSq(from);
    if(move & MFLAGEP) {
        if(side == WHITE) {
            ClearPiece(toBB, board, to-8);
        } else {
            ClearPiece(toBB, board, to+8);
        }
    } else if (move & MFLAGCA) {
        switch(to) {
            case C1:
                U64 castleFBB = 1ULL << A1;
                U64 castleTBB = 1ULL << D1;
                MovePiece(A1, D1, board, toBB, fromBB);
			break;
            case C8:
                U64 castleFBB = 1ULL << A8;
                U64 castleTBB = 1ULL << D8;
                MovePiece(A8, D8, board, toBB, fromBB);
			break;
            case G1:
                U64 castleFBB = 1ULL << H1;
                U64 castleTBB = 1ULL << F1;
                MovePiece(H1, F1, board, toBB, fromBB);
			break;
            case G8:
                U64 castleFBB = 1ULL << H8;
                U64 castleTBB = 1ULL << F8;
                MovePiece(H8, F8, board, toBB, fromBB);
			break;
            default: ASSERT(FALSE); break;
        }
    }
    if(board.enPas != NO_SQ) HASH_EP;
    HASH_CA;
    board.history[board.hisPly].move = move;
    board.history[board.hisPly].fiftyMove = board.fiftymove;
    board.history[board.hisPly].enPas = board.enPas;
    board.history[board.hisPly].castlePerm = board.castlePerm;

    board.castlePerm &= CastlePerm[from];
    board.castlePerm &= CastlePerm[to];
    board.enPas = NO_SQ;

	HASH_CA;
	
	int captured = CAPTURED(move);
    board.fiftymove++;
	
	if(captured != EMPTY) {
        ASSERT(PieceValid(captured));
        ClearPiece(toBB, board, to);
        board.fiftymove = 0;
    }
	
	board.hisPly++;
	board.ply++;
	
	ASSERT(board.hisPly >= 0 && board.hisPly < MAX_GAMEMOVES);
	ASSERT(board.ply >= 0 && board.ply < MAX_DEPTH);
	
	if(board.getPieceFromSq(from) == wP || bP) {
        board.fiftymove = 0;
        if(move & MFLAGPS) {
            if(side==WHITE) {
                board.enPas=from+10;
                ASSERT(RanksBrd[board.enPas]==RANK3);
            } else {
                board.enPas=from-10;
                ASSERT(RanksBrd[board.enPas]==RANK6);
            }
            HASH_EP;
        }
    }
	
	MovePiece(from, to, board, toBB, fromBB);
	
	int prPce = PROMOTED(move);
    if(prPce != EMPTY)   {
        ASSERT(PieceValid(prPce) && !PiecePawn[prPce]);
        ClearPiece(toBB, board, to);
        AddPiece(to, board, toBB, prPce);
    }
	
	if(board.getPieceFromSq(to) == wK || bK) {
        board.KingSq[board.side2move] = to;
    }
	
	board.side2move ^= 1;
    HASH_SIDE;

    ASSERT(CheckBoard(board));
    	
	if(SqAttacked(board.KingSq[side],board.side2move, board))  {
        TakeMove(board);
        return FALSE;
    }

	return TRUE;
	
}
void TakeMove(BOARD board) {
	
	ASSERT(CheckBoard(board));
	
	board.hisPly--;
    board.ply--;
    
	
	ASSERT(board.hisPly >= 0 && board.hisPly < MAX_GAMEMOVES);
	ASSERT(board.ply >= 0 && board.ply < MAX_DEPTH);
	
    int move = board.history[board.hisPly].move;
    int from = SQ64(FROMSQ(move));
    int to = SQ64(TOSQ(move));
    int side = board.side2move;
    U64 fromBB = 1ULL << from;
    U64 toBB = 1ULL << to;
    U64 fromToBB = fromBB ^ toBB; // |+
    int pieceType = board.getPieceFromSq(from);
	
	ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));
	
	if(board.enPas != NO_SQ) HASH_EP;
    HASH_CA;

    board.castlePerm = board.history[board.hisPly].castlePerm;
    board.fiftymove = board.history[board.hisPly].fiftyMove;
    board.enPas = board.history[board.hisPly].enPas;

    if(board.enPas != NO_SQ) HASH_EP;
    HASH_CA;

    board.side2move ^= 1;
    HASH_SIDE;
	
	if(MFLAGEP & move) {
        if(board.side2move == WHITE) {
            AddPiece(to-10, board, toBB, bP);
        } else {
            AddPiece(to+10, board, toBB, wP);
        }
    } else if(MFLAGCA & move) {
        switch(to) {
            case C1: MovePiece(D1, A1, board, toBB, fromBB); break;
            case C8: MovePiece(D8, A8, board, toBB, fromBB); break;
            case G1: MovePiece(F1, H1, board, toBB, fromBB); break;
            case G8: MovePiece(F8, H8, board, toBB, fromBB); break;
            default: ASSERT(FALSE); break;
        }
    }
	
	MovePiece(to, from, board, toBB, fromBB);
	
	if(PieceKing[board.pieces[from]]) {
        board.KingSq[board.side2move] = from;
    }
	
	int captured = CAPTURED(move);
    if(captured != EMPTY) {
        ASSERT(PieceValid(captured));
        AddPiece(to, board, captured);
    }
	
	if(PROMOTED(move) != EMPTY)   {
        ASSERT(PieceValid(PROMOTED(move)) && !PiecePawn[PROMOTED(move)]);
        ClearPiece(from, board);
        AddPiece(from, board, (PieceCol[PROMOTED(move)] == WHITE ? wP : bP));
    }
	
    ASSERT(CheckBoard(board));

}

    
