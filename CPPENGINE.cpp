#include <iostream>


#include "defs.h"

#include <string> 



int main(){

    AllInit();
    
    std::string FEN1_S = "r1b1k2r/ppppnppp/2n2q2/2b5/3NP3/2P1N3/PP3PPP/RN1QKB1R w KQkq - 0 1";
    char* FEN1 = FEN1_S.data();
    printf("\n");
    S_BOARD board[1]; 
    InitPvTable(board->PvTable);
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
        }else if(inputmove[0]=='p'){
            

            while(TRUE){
                std::string FEN2_S = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
                char* FEN2 = FEN2_S.data();
                int inputdepth;
                S_BOARD perftboard[1]; 
                S_MOVELIST perftlist[1];
                ParseFen(FEN2, perftboard);
                printf("\n\n\nEnter Depth >");
                std::cin >> inputdepth;
                if (inputdepth < 0)
                {
                    break;
                }else{
                    PerftTest(inputdepth, perftboard);
                }
                
            }
            
        }else if(inputmove[0]=='s'){
            int start = GetTimeMs();
            info->depth=9;
            printf("Max Depth Searched > %d\n", info->depth);
            SearchPosition(board, info);
            printf( "Solves In %d ms",(GetTimeMs() - start));
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