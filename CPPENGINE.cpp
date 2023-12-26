#include <iostream>


#include "defs.h"

#include <string> 



int main(){

    AllInit();
    
    std::string FEN1_S = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    char* FEN1 = FEN1_S.data();
    printf("\n");
    S_BOARD board[1];
    S_MOVELIST list[1];
    ParseFen(FEN1, board);

    char inputmove[6];
    int Move = NOMOVE;
    int Pvnum = 0;
    int Max = 0;
    
    while(TRUE){
        PrintBoard(board);
        printf("\n\n\nEnter Move >");
        fgets(inputmove, 6, stdin);

        

        if(inputmove[0]=='q'){
            break;
        }else if(inputmove[0]=='t'){
            TakeMove(board);
        }else if(inputmove[0]=='g'){
            Max = GetPvLine(4, board);
            printf("Pv line of %d Moves: ", Max);
            for(Pvnum = 0; Pvnum < Max; ++ Pvnum){
                Move = board->PvArray[Pvnum];
                printf(" %s", PrMove(Move));
            }
            
            
           
        } else{
            Move = ParseMove(inputmove, board);
            if(Move !=NOMOVE){
                StorePvMove(board, Move);//theoretical
                MakeMove(board,Move);
            }else{
                printf("Move Not Parsed:%s\n",inputmove);
            }
            
        }
    }
    fflush(stdin);
}