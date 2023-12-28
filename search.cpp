#include <iostream>
#include "defs.h"


static void CheckUp(){
    //Check if time up or interruot from GUI
}
int IsRepetition(const S_BOARD *pos){
    int index = 0;
    for(index = pos->hisPly - pos->fiftyMove; index < pos->hisPly-1; ++index){
        if(pos->posKey == pos->history[index].posKey){
            return TRUE;
        }
    }
    return FALSE;
}

static void ClearForSearch(S_BOARD *pos, S_SEARCHINFO *info){

}
static int Quiescence(int alpha, int beta, S_BOARD *pos, S_SEARCHINFO *info){
    return 0;
}
static int AlphaBeta(int alpha, int beta, int depth, S_BOARD *pos, S_SEARCHINFO *info, int DoNull){
    return 0;
}
void SearchPosition(S_BOARD *pos, S_SEARCHINFO *info){
    //iterative deepening
}