#include <iostream>
#include "defs.h"

static void AddQuietMove( const S_BOARD *pos, int move, S_MOVELIST *list ) {


	list->moves[list->count].move = move;
    list->moves[list->count].score = move;
    list->count++;
}
static void AddCaptureMove( const S_BOARD *pos, int move, S_MOVELIST *list ) {


	list->moves[list->count].move = move;
    list->moves[list->count].score = move;
    list->count++;
}
static void AddEnPassantMove( const S_BOARD *pos, int move, S_MOVELIST *list ) {


	list->moves[list->count].move = move;
    list->moves[list->count].score = move;
    list->count++;
}

void GenerateAllMoves(const S_BOARD *pos, S_MOVELIST *list){
    list->count = 0;
}