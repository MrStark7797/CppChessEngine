#include <iostream>
using namespace std;

#include "defs.h"

#include <string> 



int main(){

    AllInit();
    
    string FEN1_S = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    char* FEN1 = FEN1_S.data();
    printf("\n");
    S_BOARD board[1];
    S_MOVELIST list[1];
    ParseFen(FEN1, board);

    char inputmove[6];
    int Move = NOMOVE;
    while(TRUE){
        PrintBoard(board);
        printf("\n\n\nEnter Move >");
        fgets(inputmove, 6, stdin);

        fflush(stdin);

        if(inputmove[0]=='q'){
            break;
        }else if(inputmove[0]=='t'){
            TakeMove(board);
            
        } else{
            Move = ParseMove(inputmove, board);
            if(Move !=NOMOVE){
                MakeMove(board,Move);
            }
            
        }
    }
}