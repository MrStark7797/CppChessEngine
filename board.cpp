#include <iostream>
#include "defs.h"
#include <string> 
#include "hashkeys.cpp"
int CheckBoard(const S_BOARD *pos) {
	//function with asserts to trigger if there is a problem
	//sets up tempory to hold infomation passing through the board filling up the tempory values, checking at the end to see if they are the same as the values we have on the board
	int t_pceNum[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int t_bigPce[2] = { 0, 0};
	int t_majPce[2] = { 0, 0};
	int t_minPce[2] = { 0, 0};
	int t_material[2] = { 0, 0};

	int sq64,t_piece,t_pce_num,sq120,colour,pcount;

	U64 t_pawns[3] = {0ULL, 0ULL, 0ULL};

	t_pawns[WHITE] = pos->pawns[WHITE];
	t_pawns[BLACK] = pos->pawns[BLACK];
	t_pawns[BOTH] = pos->pawns[BOTH];

	// check piece lists
	//looping by piece type and then piece number
	for(t_piece = wP; t_piece <= bK; ++t_piece) {
		for(t_pce_num = 0; t_pce_num < pos->pieceNum[t_piece]; ++t_pce_num) {
			sq120 = pos->pList[t_piece][t_pce_num]; //Sets the value at t_peice and t_pce_num to the same as what SHOULD be in the piece list 
			ASSERT(pos->pieces[sq120]==t_piece); //checks if the tempory piece list is the same as what is currently stored on the board array.
		}
	}
	// check piece count and other counters
	for(sq64 = 0; sq64 < 64; ++sq64) {
		sq120 = SQ120(sq64);
		t_piece = pos->pieces[sq120];
		t_pceNum[t_piece]++;
		colour = PieceCol[t_piece];
		if( PieceBig[t_piece] == TRUE) t_bigPce[colour]++;
		if( PieceMin[t_piece] == TRUE) t_minPce[colour]++;
		if( PieceMaj[t_piece] == TRUE) t_majPce[colour]++;

		t_material[colour] += PieceVal[t_piece];
	} //increments through the square 64 then converts it to square 120
	//incrementsthrough all Big, Maj and Min peices to check if they are correct
	//used for when incrementing though the board when undoing moves
	for(t_piece = wP; t_piece <= bK; ++t_piece) {
		ASSERT(t_pceNum[t_piece]==pos->pieceNum[t_piece]);
	} //assert looping through to check if there are the same number of pieces in the temp pieceNum as there are in the actual pieceNum and if the peice types are the same

	// check bitboards count
	pcount = CountBits(t_pawns[WHITE]);
	ASSERT(pcount == pos->pieceNum[wP]);
	pcount = CountBits(t_pawns[BLACK]);
	ASSERT(pcount == pos->pieceNum[bP]);
	pcount = CountBits(t_pawns[BOTH]);
	ASSERT(pcount == (pos->pieceNum[bP] + pos->pieceNum[wP]));
	//checks that the pawn count is equal to the pawn count of the position

	// check bitboards squares
	while(t_pawns[WHITE]) {
		sq64 = POP(&t_pawns[WHITE]);
		ASSERT(pos->pieces[SQ120(sq64)] == wP);
	}
	//checks pawns in pieces that they must either be black or white pawn on the board untill all pieces are checked
	while(t_pawns[BLACK]) {
		sq64 = POP(&t_pawns[BLACK]);
		ASSERT(pos->pieces[SQ120(sq64)] == bP);
	}

	while(t_pawns[BOTH]) {
		sq64 = POP(&t_pawns[BOTH]);
		ASSERT( (pos->pieces[SQ120(sq64)] == bP) || (pos->pieces[SQ120(sq64)] == wP) );
	}
	ASSERT(t_material[WHITE]==pos->material[WHITE] && t_material[BLACK]==pos->material[BLACK]);
	ASSERT(t_minPce[WHITE]==pos->minPiece[WHITE] && t_minPce[BLACK]==pos->minPiece[BLACK]);
	ASSERT(t_majPce[WHITE]==pos->majPiece[WHITE] && t_majPce[BLACK]==pos->majPiece[BLACK]);
	ASSERT(t_bigPce[WHITE]==pos->bigPiece[WHITE] && t_bigPce[BLACK]==pos->bigPiece[BLACK]);
	
	ASSERT(pos->side2move==WHITE || pos->side2move==BLACK);//side must be white or black
	ASSERT(GeneratePosKey(pos)==pos->posKey); //when xoring the key we must check if the key is correct.

	ASSERT(pos->enPas==NO_SQ || ( RanksBrd[pos->enPas]==RANK_6 && pos->side2move == WHITE)
		 || ( RanksBrd[pos->enPas]==RANK_3 && pos->side2move == BLACK)); //Last move must have NO enpas square or must be rank 6 if its whites move or rank 3 if its blacks move

	ASSERT(pos->pieces[pos->KingSq[WHITE]] == wK);
	ASSERT(pos->pieces[pos->KingSq[BLACK]] == bK);




	return TRUE;




}

void UpdateListsMaterial(S_BOARD *pos) {

	int piece,sq,index,colour;

	for(index = 0; index < BRD_SQ_NUM; ++index) {
		sq = index;
		piece = pos->pieces[index];
		
		if(piece!=OFFBOARD && piece!= EMPTY) {
			colour = PieceCol[piece];
			

		    if( PieceBig[piece] == TRUE) pos->bigPiece[colour]++;
		    if( PieceMin[piece] == TRUE) pos->minPiece[colour]++;
		    if( PieceMaj[piece] == TRUE) pos->majPiece[colour]++;

			pos->material[colour] += PieceVal[piece];

			ASSERT(pos->pieceNum[piece] < 10 && pos->pieceNum[piece] >= 0);

			pos->pList[piece][pos->pieceNum[piece]] = sq;
			pos->pieceNum[piece]++;


			if(piece==wK) pos->KingSq[WHITE] = sq;
			if(piece==bK) pos->KingSq[BLACK] = sq;

			if(piece==wP) {
				SETBIT(pos->pawns[WHITE],SQ64(sq)); 
				SETBIT(pos->pawns[BOTH],SQ64(sq));
			} else if(piece==bP) {
				SETBIT(pos->pawns[BLACK],SQ64(sq));
				SETBIT(pos->pawns[BOTH],SQ64(sq));
			} //For both statements if the peice is a pawn the bitboard of pawns are set to a one, if the peice is white it is set on the bitboard of white pawns to one at the square on the 64 grid and vice versa.

		}
	}
}

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




	UpdateListsMaterial(pos);

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