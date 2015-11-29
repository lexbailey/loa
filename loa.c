#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){
	return a>b?a:b;
}

int min(int a, int b){
	return a<b?a:b;
}

#define BOARD_WIDTH (4)
#define BOARD_HEIGHT (4)

#define INDEX_OF(x,y) ((y*BOARD_WIDTH)+x)

#define MAX_PAWN_EACH (4)

#define EMPTY_SQUARE (0)
#define BLACK_PAWN   (1)
#define WHITE_PAWN   (2)

#define LINE_DIR_UP_DOWN           (1)
#define LINE_DIR_LEFT_RIGHT        (2)
#define LINE_DIR_UPLEFT_DOWNRIGHT  (3)
#define LINE_DIR_UPRIGHT_DOWNLEFT  (4)

#define MOVE_DIR_UP         (1)
#define MOVE_DIR_DOWN       (2)
#define MOVE_DIR_LEFT       (3)
#define MOVE_DIR_RIGHT      (4)
#define MOVE_DIR_UPLEFT     (5)
#define MOVE_DIR_DOWNRIGHT  (6)
#define MOVE_DIR_UPRIGHT    (7)
#define MOVE_DIR_DOWNLEFT   (8)

int totalInLine(int board[], int x, int y, int line_dir){
	int index;
	int total = 0;
	int mx, my;
	switch (line_dir){
		case LINE_DIR_UP_DOWN:
			for (my=0; my<=BOARD_HEIGHT-1; my++){index = INDEX_OF(x,my); total += board[index]!=EMPTY_SQUARE?1:0;}
			break;
		case LINE_DIR_LEFT_RIGHT:
			for (mx=0; mx<=BOARD_WIDTH-1; mx++){index = INDEX_OF(mx,y); total += board[index]!=EMPTY_SQUARE?1:0;}
			break;
		case LINE_DIR_UPLEFT_DOWNRIGHT:
			for (mx=x, my=y; mx>=0&&my<=BOARD_HEIGHT-1; mx--,my++){index = INDEX_OF(mx,my); total += board[index]!=EMPTY_SQUARE?1:0;}
			for (mx=x+1, my=y-1; mx<=BOARD_WIDTH-1&&my>=0; mx++,my--){index = INDEX_OF(mx,my); total += board[index]!=EMPTY_SQUARE?1:0;}
			break;
		case LINE_DIR_UPRIGHT_DOWNLEFT:
			for (mx=x, my=y; mx<=BOARD_WIDTH-1&&my<=BOARD_HEIGHT-1; mx++,my++){index = INDEX_OF(mx,my); total += board[index]!=EMPTY_SQUARE?1:0;}
			for (mx=x-1, my=y-1; mx>=0&&my>=0; mx--,my--){index = INDEX_OF(mx,my); total += board[index]!=EMPTY_SQUARE?1:0;}
			break;
	}
	printf("from position %d, %d, line dir %d has a total of %d pieces.\n", x,y,line_dir, total);
	return total;
}

void getDest(int x, int y, int amount, int move_dir, int *resX, int *resY){
	switch (move_dir){
		case MOVE_DIR_UP:
			*resX = x;
			*resY = y+amount;
			break;
		case MOVE_DIR_DOWN:
			*resX = x;
			*resY = y-amount;
			break;
		case MOVE_DIR_LEFT:
			*resX = x-amount;
			*resY = y;
			break;
		case MOVE_DIR_RIGHT:
			*resX = x+amount;
			*resY = y;
			break;
		case MOVE_DIR_UPLEFT:
			*resX = x-amount;
			*resY = y+amount;
			break;
		case MOVE_DIR_DOWNRIGHT:
			*resX = x+amount;
			*resY = y-amount;
			break;
		case MOVE_DIR_UPRIGHT:
			*resX = x+amount;
			*resY = y+amount;
			break;
		case MOVE_DIR_DOWNLEFT:
			*resX = x-amount;
			*resY = y-amount;
			break;
	}
}

int isValidSquare(int x, int y){
	return ((x>=0)&&(x<=BOARD_WIDTH-1)) && ((y>=0)&&(y<=BOARD_HEIGHT-1));
}

int canMoveBy(int amount, int board[], int x, int y, int line_dir){
	int index;
	int mx, my;
	int canMove = 0;
	int player = board[INDEX_OF(x,y)];
	int otherPlayer = player == BLACK_PAWN?WHITE_PAWN:BLACK_PAWN;
	int destValid = 0;
	int dx, dy;
	switch (line_dir){
		case LINE_DIR_UP_DOWN:
			//Up
			getDest(x,y,amount, MOVE_DIR_UP, &dx, &dy);
			if (isValidSquare(dx,dy) && board[INDEX_OF(dx,dy)] != player){
				canMove = 1;
				for (my=y+1; my<=y+amount-1; my++){
					index = INDEX_OF(x,my);
					if (board[index] == otherPlayer){canMove = 0; break;}
				}
				if (canMove){printf("Up\n");return 1;}
			}
			//Down
			getDest(x,y,amount, MOVE_DIR_DOWN, &dx, &dy);
			if (isValidSquare(dx,dy) && board[INDEX_OF(dx,dy)] != player){
				canMove = 1;
				for (my=y-1; my>=y-amount+1; my--){
					index = INDEX_OF(x,my);
					if (board[index] == otherPlayer){canMove = 0; break;}
				}
				if (canMove){printf("Down\n");return 1;}
			}
			break;
		case LINE_DIR_LEFT_RIGHT:
			//Left
			getDest(x,y,amount, MOVE_DIR_LEFT, &dx, &dy);
			if (isValidSquare(dx,dy) && board[INDEX_OF(dx,dy)] != player){
				canMove = 1;
				for (mx=x+1; mx<=x+amount-1; mx++){
					index = INDEX_OF(mx,y);
					if (board[index] == otherPlayer){canMove = 0; break;}
				}
				if (canMove){printf("Left\n");return 1;}
			}
			//Right
			getDest(x,y,amount, MOVE_DIR_RIGHT, &dx, &dy);
			if (isValidSquare(dx,dy) && board[INDEX_OF(dx,dy)] != player){
				canMove = 1;
				for (mx=x-1; mx>=x-amount+1; mx--){
					index = INDEX_OF(mx,y);
					if (board[index] == otherPlayer){canMove = 0; break;}
				}
				if (canMove){printf("Right\n");return 1;}
			}
			break;
		case LINE_DIR_UPLEFT_DOWNRIGHT:
			//Up-Left
			getDest(x,y,amount, MOVE_DIR_UPLEFT, &dx, &dy);
			if (isValidSquare(dx,dy) && board[INDEX_OF(dx,dy)] != player){
				canMove = 1;
				for (mx=x-1,my=y+1; mx>=x-amount+1,my<=y+amount-1; my++,mx--){
					index = INDEX_OF(mx,my);
					if (board[index] == otherPlayer){canMove = 0; break;}
				}
				if (canMove){printf("Up-Left\n");return 1;}
			}
			//Down-Right
			getDest(x,y,amount, MOVE_DIR_DOWNRIGHT, &dx, &dy);
			if (isValidSquare(dx,dy) && board[INDEX_OF(dx,dy)] != player){
				canMove = 1;
				for (mx=x+1,my=y-1; mx<=x+amount-1,my>=y-amount+1; my--,mx++){
					index = INDEX_OF(mx,my);
					if (board[index] == otherPlayer){canMove = 0; break;}
				}
				if (canMove){printf("Down-Right\n");return 1;}
			}
			break;
		case LINE_DIR_UPRIGHT_DOWNLEFT:
			//Up-Right
			getDest(x,y,amount, MOVE_DIR_UPRIGHT, &dx, &dy);
			if (isValidSquare(dx,dy) && board[INDEX_OF(dx,dy)] != player){
				canMove = 1;
				for (mx=x+1,my=y+1; mx<=x+amount-1,my<=y+amount-1; my++,mx++){
					index = INDEX_OF(mx,my);
					if (board[index] == otherPlayer){printf("\t\tcan't\n");canMove = 0; break;}
				}
				if (canMove){printf("Up-Right\n");return 1;}
			}
			else{
				printf("\tDest is invalid\n");
			}
			//Down-Left
			getDest(x,y,amount, MOVE_DIR_DOWNLEFT, &dx, &dy);
			if (isValidSquare(dx,dy) && board[INDEX_OF(dx,dy)] != player){
				canMove = 1;
				for (mx=x-1,my=y-1; mx>=x-amount+1,my>=y-amount+1; my--,mx--){
					index = INDEX_OF(mx,my);
					if (board[index] == otherPlayer){canMove = 0; break;}
				}
				if (canMove){printf("Down-Left\n");return 1;}
			}
			break;
	}
	return 0;
}

int playerCanMove(int board[], int x, int y, int player){
	for (int line_dir = 1; line_dir <=4; line_dir++){
		int tot = totalInLine(board, x, y, line_dir);
		if (canMoveBy(tot, board, x, y, line_dir)){
			printf("The %s player can move by %d spaces from %d, %d.\n", player==BLACK_PAWN?"black":"white", tot, x, y);
			return 1;
		}
	}
	return 0;
}

int isValidBoard(int board[]){
	int black = 0;
	int white = 0;

	for (int x = 0; x<= BOARD_WIDTH-1; x++){
		for (int y = 0; y<= BOARD_HEIGHT-1; y++){
			int i = INDEX_OF(x,y);
			int thisSquare = board[i];
			if (thisSquare == EMPTY_SQUARE){
				continue;
			}
			if (thisSquare == BLACK_PAWN){
				black++;
			}
			else if (thisSquare == WHITE_PAWN){
				white++;
			}
			else {
				return 0;
			}
			if (white>MAX_PAWN_EACH || black>MAX_PAWN_EACH){
				return 0;
			}
		}
	}
	if (white<2 || black<2){
		return 0;
	}
	return 1;
}

int bothCanMove(int board[]){
	int blackHasMove = 0;
	int whiteHasMove = 0;

	for (int x = 0; x<= BOARD_WIDTH-1; x++){
		for (int y = 0; y<= BOARD_HEIGHT-1; y++){
			int i = INDEX_OF(x,y);
			int thisSquare = board[i];
			if (thisSquare == EMPTY_SQUARE){
				continue;
			}
			if (thisSquare == BLACK_PAWN && !blackHasMove){
				blackHasMove = playerCanMove(board, x, y, BLACK_PAWN);
			}
			if (thisSquare == WHITE_PAWN && !whiteHasMove){
				whiteHasMove = playerCanMove(board, x, y, WHITE_PAWN);
			}
			if (whiteHasMove && blackHasMove){
				printf("White and black can both move.\n");
				return 1;
			}
		}
	}

	return 0;
}

int neitherCanMove(int board[]){
	for (int x = 0; x<= BOARD_WIDTH-1; x++){
		for (int y = 0; y<= BOARD_HEIGHT-1; y++){
			int i = INDEX_OF(x,y);
			int thisSquare = board[i];
			if (thisSquare == EMPTY_SQUARE){
				continue;
			}
			if (playerCanMove(board, x, y, thisSquare)){
				return 0;
			}
		}
	}

	return 1;
}

void testArbitraryBoard(int board[BOARD_HEIGHT*BOARD_WIDTH]){
	#ifdef ASSERT_CBMC
	//assert(!isValidBoard(board)||bothCanMove(board));
	assert(!isValidBoard(board)||!neitherCanMove(board));
	#endif
}

int nondet_int();

void testRandomBoard(){
	#ifdef ASSERT_CBMC
	int board[BOARD_HEIGHT*BOARD_WIDTH];
	int i;
	for (int x = 0; x<= BOARD_WIDTH-1; x++){
		for (int y = 0; y<= BOARD_HEIGHT-1; y++){
			i = INDEX_OF(x,y);
			board[i] =  nondet_int();
		}
	}
	testArbitraryBoard(board);
	#endif
}

int main(){

	int board[] = {
			 1,0,1,0,0,0,0,0,
			 0,0,0,0,0,0,0,0,
			 1,0,2,2,0,0,0,0,
			 0,0,0,0,0,0,0,0,
			 0,0,0,0,0,0,0,0,
			 0,0,0,0,0,0,0,0,
			 0,0,0,0,0,0,0,0,
			 0,0,0,0,0,0,0,0
			};
/*
	int board[] = {
			 0,0,2,2,
			 0,1,0,2,
			 1,1,0,0,
			 0,0,0,0
			};
*/
	printf("bothCanMove() = %d, isValidBoard() = %d\n", bothCanMove(board), isValidBoard(board));
}
