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