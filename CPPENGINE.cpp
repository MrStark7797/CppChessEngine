#include <iostream>


#include "defs.h"

#include <string> 



int main(){

    AllInit();
    
    std::string FEN1_S = "R7/6k1/4p3/R5pp/4P1P1/5n1K/1r6/8 b - - 0 37";
    char* FEN1 = FEN1_S.data();
    printf("\n");
    S_BOARD board[1]; 

    S_MOVELIST list[1];
    ParseFen(FEN1, board);

    S_SEARCHINFO info[1];
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
        }else if(inputmove[0]=='s'){
            int start = GetTimeMs();
            info->depth=4;
            printf("Max Depth Searched > %d\n", info->depth);
            SearchPosition(board, info);
            printf( "Solves In %d ms",(GetTimeMs() - start));
        }else if(inputmove[0]=='f'){
            
            std::string FENINPUT_S;
            printf("\n\n\nEnter FEN >");
            fgets(inputmove, 6, stdin);
            char* FENINPUT = FENINPUT_S.data();
            
           
            
           
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