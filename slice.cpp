#include <iostream>


#include "defs.h"

#include <cstring> 



int main(){


    AllInit();
    
    S_BOARD pos[1];
    S_SEARCHINFO info[1];
    info->quit = FALSE;
	pos->PvTable->pTable = NULL;
    InitPvTable(pos->PvTable);
	setbuf(stdin, NULL);
    setbuf(stdout, NULL);
	/* std::string FEN1_S = "r1b1k2r/ppppnppp/2n2q2/2b5/3NP3/2P1N3/PP3PPP/RN1QKB1R b KQkq - 0 1";
    char* FEN1 = FEN1_S.data();
    printf("\n");
    S_MOVELIST list[1];
    ParseFen(FEN1, pos); */
	
	
    int ArgNum = 0;

    
    char line[256];
	while (TRUE) {
		memset(&line[0], 0, sizeof(line));

		fflush(stdout);
		if (!fgets(line, 256, stdin))
			continue;
		if (line[0] == '\n')
			continue;
		if (!strncmp(line, "uci",3)) {
			Uci_Loop(pos, info);
			if(info->quit == TRUE) break;
			continue;
		
		} else if(!strncmp(line, "quit",4))	{
			break;
		}
    free(pos->PvTable->pTable);
    fflush(stdin);
    return 0; 
    }
}