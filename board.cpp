#include <iostream>
#include "defs.h"
#include <string> 
#include "hashkeys.cpp"

int ParseFen(char *fen, S_BOARD *pos) {

	ASSERT(fen!=NULL);
	ASSERT(pos!=NULL);

	int  rank = RANK_8;
    int  file = FILE_A;
    int  piece = 0;
    int  count = 0;
    int  i = 0;
	int  sq64 = 0;
	int  sq120 = 0;

	ResetBoard(pos);
	//switch to current counter, while loop iterates through all squares in fine turning the peice at that position to its equivelent in our enum of peices and colors 
	while ((rank >= RANK_1) && *fen) {
	    count = 1;
		switch (*fen) {
            case 'p': piece = bP; break;
            case 'r': piece = bR; break;
            case 'n': piece = bN; break;
            case 'b': piece = bB; break;
            case 'k': piece = bK; break;
            case 'q': piece = bQ; break;
            case 'P': piece = wP; break;
            case 'R': piece = wR; break;
            case 'N': piece = wN; break;
            case 'B': piece = wB; break;
            case 'K': piece = wK; break;
            case 'Q': piece = wQ; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                piece = EMPTY;
                count = *fen - '0'; //subtracts ascii values from each number.
                break;

            case '/':
            case ' ':
                rank--;
                file = FILE_A;
                fen++;
                continue;
			//if / or space there is a break or at the end therefore we iterate onto approprite square
            default: //just incase of error
                printf("FEN error \n");
                return -1;

        }	
		//starting at zero and looping through, empty spaces
		//however When the postition isn't empty, we add the correct piece notation in "pieces"
		for (i = 0; i < count; i++) {
            sq64 = rank * 8 + file;
			sq120 = SQ120(sq64);
            if (piece != EMPTY) {
                pos->pieces[sq120] = piece;
            }
			file++;
        }
		fen++;
	}
	ASSERT(*fen == 'w' || *fen == 'b'); //FEN must either point to a w or a b otherwise the piece is an incorrect colour
	
	pos->side2move = (*fen == 'w') ? WHITE : BLACK; // an if statement where if the fen points to a white peice its white if not is black,
	fen += 2;

	for (i = 0; i < 4; i++) {
        if (*fen == ' ') {
            break;
        }
		switch(*fen) {
			case 'K': pos->castlePerm |= WKCA; break;
			case 'Q': pos->castlePerm |= WQCA; break;
			case 'k': pos->castlePerm |= BKCA; break;
			case 'q': pos->castlePerm |= BQCA; break;
			default:	     break;
        }
		fen++; //checks all values in the Castling Rules to see which sides can castle and once iterating through it will break.
	}
	fen++;
	ASSERT(pos->castlePerm>=0 && pos->castlePerm <= 15); 
	//If En Pessaunt isnt pointing towards a dash there is a square. Therefore the next two char are a letter and a number
	if (*fen != '-') {
		file = fen[0] - 'a';
		rank = fen[1] - '1';

		ASSERT(file>=FILE_A && file <= FILE_H);
		ASSERT(rank>=RANK_1 && rank <= RANK_8);

		pos->enPas = FR2SQ(file,rank);
    }

	pos->posKey = GeneratePosKey(pos); //generates hashkey

	//UpdateListsMaterial(pos);

	return 0;
	
}
void ResetBoard(S_BOARD *pos) {

	int index = 0;

    for(index = 0; index < BRD_SQ_NUM; ++index) {
		pos->pieces[index] = OFFBOARD;
	}
    //sets all tiles to offboard
	for(index = 0; index < 64; ++index) {
		pos->pieces[SQ120(index)] = EMPTY;
	}
    //Sets all peices on the board from offboard to empty so they are usable
    for(index = 0; index < 2; ++index) {
		pos->bigPiece[index] = 0;
		pos->majPiece[index] = 0;
		pos->minPiece[index] = 0;
		pos->material[index] = 0;
	} //Resets all peices and their arrays
    for(index = 0; index < 3; ++index) {
		pos->pawns[index] = 0ULL;
	}
    //sets all values in pawns to 0
	for(index = 0; index < 13; ++index) {
		pos->pieceNum[index] = 0;
	}
    //sets all values in peices to 0
	pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;

	pos->side2move = BOTH;
	pos->enPas = NO_SQ;
	pos->fiftyMove = 0;

	pos->ply = 0;
	pos->hisPly = 0;

	pos->castlePerm = 0;

	pos->posKey = 0ULL;
    //resets all colours to both colors and all other permisions and rules to 0. 
    //sets colours to both so we can assert if a peice is defined as both colours.
} 

void PrintBoard(const S_BOARD *pos){
	int sq,file,rank,piece;

	printf("\nGame Board:\n\n");
	//starting at the 8th rank decending a rank at a time printing rank number 
	for(rank = RANK_8; rank >= RANK_1; rank--) {
		printf("%d  ",rank+1);
		for(file = FILE_A; file <= FILE_H; file++) {
			sq = FR2SQ(file,rank);
			piece = pos->pieces[sq];
			printf("%3c",PceChar[piece]);
		}
		printf("\n");
	}
	//
	printf("\n   ");
	for(file = FILE_A; file <= FILE_H; file++) {
		printf("%3c",'a'+file);
	}
	printf("\n");
	printf("side:%c\n",SideChar[pos->side2move]);
	printf("enPas:%d\n",pos->enPas);
	printf("castle:%c%c%c%c\n",
			pos->castlePerm & WKCA ? 'K' : '-',
			pos->castlePerm & WQCA ? 'Q' : '-',
			pos->castlePerm & BKCA ? 'k' : '-',
			pos->castlePerm & BQCA ? 'q' : '-'
			); //conditional stating that if castle permition and the castling 4 bit number are the same print the corrosponding letter else print a -
	printf("PosKey:%llX\n",pos->posKey);
}