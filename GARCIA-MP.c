/******************************************************************
This is to certify that this project is my own work, based on my
personal efforts in studying and applying the concepts learned. I
have constructed the functions and their respective algorithms
and corresponding code by myself. The program was run, tested, and
debugged by my own efforts. I further certify that I have not
copied in part or whole or otherwise plagiarized the work of other
students and/or persons.

Reina Althea C. Garcia, DLSU ID# 12276502
******************************************************************/

/*
Description: This program lets two players play a game called checkers.
Programmed by: Reina Althea C. Garcia Block 10B
Last modified: 04/12/2022
Version: version 2
[Acknowledgements: <list of sites or borrowedlibraries and sources>]
*/

#include <stdio.h>
#include <stdlib.h> // for rand()
#include <time.h> // seed for generating random number

// function prototype //
void getBlackPieces();
void displayBoard();
void assignPieces ();
void displayErrorMessage();
void eatPieceX();
void eatPieceO();
void displayWinnerA();
void displayWinnerB();
int checkSurrender(char); 
void displayTurn ();
void displayPiecesCount();
void updateSetPiecesOne ();

// main function //
int main ()
{
	//variable declaration //
	char board[8][8] = {0}; // for the board
	int nChoice; //menu
	int nWins = 0; // checking of winner
	int nQuit = 0; // quit
	int nScoreA = 0; // score count for player A
	int nScoreB = 0; // score count for player B
	
	//start of the program//
	printf("\n        WELCOME TO CHECKERS!");
	printf("\n\n [1]PLAY   [2]VIEW SCORES   [3]Quit\n");

	// first do-while loop is for looping the whole game
	do 
	{
		// second do-while loop is for asking the user/s again for input in case their first input is wrong.
		do 
		{
			printf("\n Enter selection: ");
			scanf("%d", &nChoice); 
			getchar();
			
			switch (nChoice)
			{
				//play//
				case 1 : 
				{
					system("cls");
					assignPieces(board);
						
					// third do-while (to loop the prompts of user)
					do
					{
						updateSetPiecesOne(board, &nWins, &nScoreA, &nScoreB);
							
					} while  (nWins == 0); //loops until there's a winner
					
					//going back to the main menu
					system("pause");
					system("cls");
					printf("\n        WELCOME TO CHECKERS!");
					printf("\n\n [1]PLAY   [2]VIEW SCORES   [3]Quit\n");
					break;
				}
					
				//view scores//
				case 2 : 
				{
					system("cls");
					printf("\n VIEW SCORES\n");
					
					// printing of score counts for each player
					printf("\n PLAYER A SCORES: %d", nScoreA);
					printf("\n PLAYER B SCORES: %d", nScoreB);
					
					// going back to the main menu
					printf("\n\n");
					system("pause");
					system("cls");
					printf("\n        WELCOME TO CHECKERS!");
					printf("\n\n [1]PLAY   [2]VIEW SCORES   [3]Quit\n");
					
					break;
				}
				
				//Quit//
				case 3 : 
				{		
					system("cls");
					printf("\n          Quit\n");
					printf("\n Thank you for playing!");
					printf("\nTry it out again soon! <3");
					printf("\n   Have a nice day!\n\n");		
					system("pause");
					
					//to stop the loop (terminate the program)
					nQuit = 1;
					break;
				}
		
				//Invalid input from the user
				default : 
				{
					printf("\nINVALID!\n");
					printf("Please enter again.\n");
				}
			}
	
		} while (nChoice >= 4 || nChoice <= 0); // ask the user again for inputs
		
	} while (nQuit == 0); // loops the menu until no one's quitting
	
	return 0;
}

//function description//

/* 
This function randomly assigns black (X) and white (O) pieces to the players (using rand() function)
@param *cPlayerA - where the piece of Player A will be stored
@param *cPlayerB - where the piece of Player B will be stored
@return does not return anything
*/
void getBlackPieces (char* cPlayerA, char* cPlayerB)
{
	int nNum; //where the random number will be stored
	
	//generate random number from 0-9
	srand(time(NULL));
	nNum = rand() % 10;
	
	system("cls");
	printf("\a"); // to have a sound effect
	
	if (nNum >= 0 && nNum <= 4) 
	{
		//printing of who gets the pieces
		printf("------------------------------------");
		printf("\n PLAYER A gets the BLACK (X) pieces");
		printf("\n PLAYER B gets the WHITE (O) pieces");
		printf("\n------------------------------------\n");
		
		// assigning the pieces X and O to each respective player
		*cPlayerA = 'X';
		*cPlayerB = 'O';
	}
	else if (nNum > 4 && nNum <= 9) 
	{
		//printing of who gets the pieces
		printf("------------------------------------");
		printf("\n PLAYER B gets the BLACK (X) pieces");
		printf("\n PLAYER A gets the WHITE (O) pieces");
		printf("\n------------------------------------\n");
		
		// assigning the pieces X and O to each respective player
		*cPlayerB = 'X';
		*cPlayerA = 'O';
	}
	system("pause");
	system("cls");
}

/* 
This function prints/displays the board
@param board[8][8] the board of the game
@return does not return anything
*/
void displayBoard(char board[8][8])
{
	int i; // y-coordinate
	int j; // x-coordinate

	//printing of board //
	printf("\n     1   2   3   4   5   6   7   8   X");
	for (i = 0; i < 8; i++) // y coordinate
	{
		printf("\n   +---+---+---+---+---+---+---+---+\n"); //printing of separators
 		printf(" %d |", i+1); //printing of the numbers on the left side of the table
		for (j = 0; j < 8; j++) // x coordinate
		{
			printf(" %c |", board[j][i]); //printing of each box on the board
		}
	}
	printf("\n   +---+---+---+---+---+---+---+---+\n");
	printf(" Y");
}

/* 
This function is use to assign pieces (X, O, and #) to every space on the board, respectively.
@param board[8][8] - board of the game
@return does not return anything
*/
void assignPieces (char board[8][8])
{
	// X means black pieces (assigning X)
	board[1][0] = 'X'; board[3][0] = 'X'; board[5][0] = 'X'; board[7][0] = 'X';
	board[0][1] = 'X'; board[2][1] = 'X'; board[4][1] = 'X'; board[6][1] = 'X';
	board[1][2] = 'X'; board[3][2] = 'X'; board[5][2] = 'X'; board[7][2] = 'X';
	
	// O means white pieces (assigning O)
	board[0][5] = 'O'; board[2][5] = 'O'; board[4][5] = 'O'; board[6][5] = 'O';
	board[1][6] = 'O'; board[3][6] = 'O'; board[5][6] = 'O'; board[7][6] = 'O';
	board[0][7] = 'O'; board[2][7] = 'O'; board[4][7] = 'O'; board[6][7] = 'O';
	
	//blank black spaces (assigning #)
	board[0][3] = '#'; board[4][3] = '#'; board[1][4] = '#'; board[5][4] = '#';
	board[2][3] = '#'; board[6][3] = '#'; board[3][4] = '#'; board[7][4] = '#';
	
	//blank white spaces (assigning space)
	board[0][0] = ' '; board[2][0] = ' '; board[4][0] = ' '; board[6][0] = ' ';
	board[1][1] = ' '; board[3][1] = ' '; board[5][1] = ' '; board[7][1] = ' ';
	board[0][2] = ' '; board[2][2] = ' '; board[4][2] = ' '; board[6][2] = ' ';
	board[1][3] = ' '; board[3][3] = ' '; board[5][3] = ' '; board[7][3] = ' ';
	board[0][4] = ' '; board[2][4] = ' '; board[4][4] = ' '; board[6][4] = ' ';
	board[1][5] = ' '; board[3][5] = ' '; board[5][5] = ' '; board[7][5] = ' ';
	board[0][6] = ' '; board[2][6] = ' '; board[4][6] = ' '; board[6][6] = ' ';
	board[1][7] = ' '; board[3][7] = ' '; board[5][7] = ' '; board[7][7] = ' ';
}

/* 
This function prints error messages
@param no parameter needed.
@return does not return anything.
*/
void displayErrorMessage()
{
	//for printing of error messages
	printf("\n------------------------------------");
	printf("\n INVALID COORDINATE!\n");
	printf(" Please enter again.\n");
	printf("------------------------------------");
}

/* 
This function is for the moving and eating of X Pieces (BLACK)
precondition: x[4] is a positive integer
@param - x[4] is an array where the coordinates of the pieces to be moved, and the new position are stored.
@param - board[8][8] is the board
@param - *nTurn determines which turn it is to move (1 for X; 0 for O)
@param - *nPieceCountO count pieces of O, which updates every eat of X
@return does not return anything
*/
void eatPieceX(int x[4], char board[8][8], int* nTurn, int* nPieceCountO)
{
	char posA = board[x[0]][x[1]]; //position A is current coordinate to be moved
	char posB = board[x[2]][x[3]]; //position B is the new coordinate/ the landing position
	
	//---------- eat Piece for 'X' only (diagonal right) --------------//
	
	/* Checking if the current position (posA) and the landing position (posB) 
		are acceptable. Accessing the address for an easy checking */
	if (posA == 'X' && (&board[x[2]][x[3]] == &board[x[0]+2][x[1]+2]) && 
		posB == '#' && board[x[0]+1][x[1]+1] == 'O') 
	{
		/* changing the piece in between the posA and posB */
		board[x[0]+1][x[1]+1] = '#';
		
		/* swapping the value of posA and posB */
		board[x[0]][x[1]] = '#';
		board[x[2]][x[3]] = 'X';
		
		printf("\nWhite (O) piece captured!\n");
		system("pause");
		system("cls");
		*nTurn = 0;
		*nPieceCountO -= 1;
	}
	
	//----------- eat Piece for 'X' only (diagonal left) ---------------//
	
	/* Checking if the current position (posA) and the landing position (posB) 
		are acceptable. Accessing the address for an easy checking */
	else if (posA == 'X' && (&board[x[2]][x[3]] == &board[x[0]-2][x[1]+2]) && 
			 posB == '#' && board[x[0]-1][x[1]+1] == 'O') 
	{
		/* changing the piece in between posA and posB 
		to make it appear like it has been eaten*/
		board[x[0]-1][x[1]+1] = '#';
		
		/* swapping the pieces to make it seem like it moved */
		board[x[0]][x[1]] = '#';
		board[x[2]][x[3]] = 'X';
		
		printf("\nWhite (O) piece captured!\n");
		system("pause");
		system("cls");
		*nTurn = 0;
		*nPieceCountO -= 1;	
	}
	
	//----------------------- moves for 'X" only -----------------------//
	
	else if (posA == 'X' && posB == '#') 
	{
			
		/* The address of the new position must be equal to the address of the blocks diagonal adjacent to the current 
			position so that the user's movement will be limited to forward moves and diagonally adjacent to it only  */
		if ((&board[x[2]][x[3]] == &board[x[0]+1][x[1]+1]) || (&board[x[2]][x[3]] == &board[x[0]-1][x[1]+1])) 
		{
			/* swapping the pieces to make it seem like it moved */ 
			board[x[0]][x[1]] = '#';
			board[x[2]][x[3]] = 'X';
			
			system("cls");
			*nTurn = 0;			
		}
		else 
		{
			system("cls");
			displayErrorMessage();
			*nTurn = 1;
		}
	}
	else 
	{
		system("cls");
		displayErrorMessage();
		*nTurn = 1;
	}
}

/* 
This function is for the moving and eating of O (WHITE)
precondition: x[4] is a positive integer
@param - x[4] is an array where the coordinates of the pieces to be moved, and the new position.
@param - board[8][8] is the board
@param - *turn determins which turn it is to move (1 for X; 0 for O)
@param - *nPieceCountX count pieces of O, which updates every eat of X
@return does not return anything
*/
void eatPieceO(int x[4], char board[8][8], int* nTurn, int* nPieceCountX)
{
	char posA = board[x[0]][x[1]]; //position A is the coordinate of the piece to be moved.
	char posB = board[x[2]][x[3]]; //position B is the new coordinate 
	
	//------------- eat Piece for 'O' only (diagonal right) -----------------//
	
	/* Checking if the current position (posA) and the landing position (posB) 
		are acceptable. Accessing the address for an easy checking */
	if (posA == 'O' && (&board[x[2]][x[3]] == &board[x[0]+2][x[1]-2]) && 
		posB == '#' && board[x[0]+1][x[1]-1] == 'X') 
	{ 
		/* changing the piece in between the posA and posB */
		board[x[0]+1][x[1]-1] = '#';
		
		/* swapping the pieces to make it seem like it moved */
		board[x[0]][x[1]] = '#';
		board[x[2]][x[3]] = 'O';
		
		printf("\nBlack (X) piece captured!\n");
		system("pause");	
		system("cls");
		*nTurn = 1;
		*nPieceCountX -= 1;
	}
	
	//-------------- eat Piece for 'O' only (diagonal left) ------------------//
	 
	 /* Checking if the current position (posA) and the landing position (posB) 
		are acceptable. Accessing the address for an easy checking */
	else if (posA == 'O' && (&board[x[2]][x[3]] == &board[x[0]-2][x[1]-2]) && 
			 posB == '#' && board[x[0]-1][x[1]-1] == 'X') 
	{
		/* changing the piece in between the posA and posB */
		board[x[0]-1][x[1]-1] = '#';
		
		/* swapping the pieces to make it seem like it moved */
		board[x[0]][x[1]] = '#';
		board[x[2]][x[3]] = 'O';
		
		printf("\nBlack (X) piece captured!\n");
		system("pause");
		system("cls");
		*nTurn = 1;
		*nPieceCountX -= 1;	
	}
	
	//-------------------------- moves for 'O" only --------------------------//
	
	else if (posA == 'O' && posB == '#') 
	{
		/* the address of the new position must be equal to the address of the blocks diagonal adjacent to the current 
			position so that the user's move will be limited to forward moves and diagaonally adjacent to it only */
		if ((&board[x[2]][x[3]] == &board[x[0]+1][x[1]-1]) || (&board[x[2]][x[3]] == &board[x[0]-1][x[1]-1]))
		{
			/* swapping the pieces to make it seem like it moved */ 
			board[x[0]][x[1]] = '#';
			board[x[2]][x[3]] = 'O';
			
			system("cls");
			*nTurn = 1;
		} 
		else 
		{
			system("cls");
			displayErrorMessage();
			*nTurn = 0;
		}	
	}
	else 
	{
		system("cls");
		displayErrorMessage();
		*nTurn = 0;
	}
}

/* 
This function prints a huge letter A, declaring it as the winner of the game
@param no parameter needed.
@return does not return anything.
*/
void displayWinnerA ()
{
	//printing a huge A to display it as a Winner
	system("cls");
	printf("\n");
	printf("             ####		    \n");
	printf("            ######	 	    \n");
	printf("           ########         \n");
	printf("          ###    ###        \n");
	printf("         ###      ###       \n");
	printf("        ##############      \n");
	printf("       ###          ###     \n");
	printf("      ###            ###    \n");
	printf("     ###              ###   \n");
	printf("    ###                ###  \n");
	printf("\n");
	printf("   PLAYER A WINS THE GAME!\n\n   ");
}

/* 
This function prints a huge letter B, declaring it as the winner of the game
@param no parameter needed.
@return does not return anything.
*/
void displayWinnerB ()
{
	//printing a huge B to display it as a Winner
	system("cls");
	printf("\n");
	printf("     #############         \n");
	printf("     ###         ###       \n");
	printf("     ###          ###      \n");
	printf("     ###          ####     \n");
	printf("     ###          ###      \n");
	printf("     ###         ####      \n");
	printf("     ##############        \n");
	printf("     ###        ###        \n"); 
	printf("     ###          ###      \n");
	printf("     ###          ####     \n");
	printf("     ###          ###      \n");
	printf("     ###        ####       \n");
	printf("     #############         \n");
	printf("\n");
	printf("  PLAYER B WINS THE GAME!\n   ");
}

/* 
This function checks if the in-turn Player is surrendering
Precondition: cSurrender is a letter.
@param - cSurrender is where the choice (Y or N) of the in-inturn player is stored.
@return - 1 if the player surrenders
@return - 0 if the player surrenders.
*/
int checkSurrender (char cSurrender)
{
	//loop the prompts every time the user input is wrong
	do
	{
		printf("\n\n Do you like to Surrender (y/n)? ");
		scanf(" %c", &cSurrender);
		
		// if it's equal to Y or y, it means the user surrenderes; hence, return 1 and stop the round.
		if (cSurrender == 'y' || cSurrender == 'Y') 
			return 1;
			
		// if it's equal to N or n, it means the user did not surrender; hence, return 0 and continue the game.
		else if (cSurrender == 'n' || cSurrender == 'N')
			return 0;
			
		// if the input is wrong, it will diplay error messagges
		else if (cSurrender != 'y' || cSurrender != 'n' || cSurrender != 'Y' || cSurrender != 'N')
			displayErrorMessage();
		
	} while (cSurrender != 'y' || cSurrender != 'n' || cSurrender != 'Y' || cSurrender != 'N');
	
	return 0;
}

/* 
This function prints whose turn it is to move the pieces.
@param cFirstA - piece assigned to player A
@param cSecondB - piece assigned to player B
@param nTurn - 1 for Black's turn; 0 for White's turn
@return does not return anything
*/
void displayTurn (char* cFirstA, char* cSecondB, int* nTurn)
{
	if (*nTurn == 1)
	{
		if (*cFirstA == 'X')
		{
			printf("\n -----------------------------------");
			printf("\n      PLAYER A (BLACK-X) turn.");
			printf("\n -----------------------------------");
		}
		else if (*cSecondB == 'X')
		{
			printf("\n -----------------------------------");
			printf("\n      PLAYER B (BLACK-X) turn.");
			printf("\n -----------------------------------");
		}
	}
	else if (*nTurn == 0)
	{
		if (*cFirstA == 'O')
		{
			printf("\n -----------------------------------");
			printf("\n      PLAYER A (WHITE-O) turn.");
			printf("\n -----------------------------------");
		}
		else if (*cSecondB == 'O')
		{
			printf("\n -----------------------------------");
			printf("\n      PLAYER B (WHITE-O) turn.");
			printf("\n -----------------------------------");
		}
	}
}

/*
This function prints the pieces count of each piece
@param *nCountX - pieces count for X (black) pieces
@param *nCountO - pieces count for O (white) pieces
@return does not return anything.
*/
void displayPiecesCount(int* nCountX, int* nCountO)
{
	printf("\n\n BLACK (X) piece count: %d", *nCountX);
	printf("\n WHITE (O) piece count: %d", *nCountO);
}

/* 
This function is where the in-turn player is asked to enter coordinates where the piece will be moved.
It is also checked here if there's a winner already or not.
@param - board[8][8] is the board
@param - *nWinner is used to check if there's a winner already (1 if yes; 0 if none)
@param - *nScoreA is the count for the scores of player A
@param - *nScoreB is the count for the scores of player B
@return does not return anything
*/

//game proper//
void updateSetPiecesOne (char board[8][8], int* nWinner, int* nScoreA, int* nScoreB)
{
	//variable declaration//
	
	int x[4]; //four coordinates; should be positive integers
	int nPieceX = 12; //piece count X
	int nPieceO = 12; //piece count O
	int battleInProgress = 1;
	int nTurn = 1; 
	int nAns; // choice of the user (surrender or not)
	
	int i; // y-coordinate
	int j; // x-coordinate
	int piecesOnBoardX = 0; // pieces left on the board
	int piecesOnBoardO = 0;
	int blockedPiecesX = 0; // pieces that are blocked
	int blockedPiecesO = 0;
	
	char cSurrender = '\0'; //surrender count
	char cPlayerA; //assigned piece to player A
	char cPlayerB; //assigned piece to player B
	
	//calls the function to see who gets the pieces//
	getBlackPieces(&cPlayerA, &cPlayerB);
	
	do 
	{
		// printing
		displayBoard(board);
		displayTurn(&cPlayerA, &cPlayerB, &nTurn);
		displayPiecesCount(&nPieceX, &nPieceO);
		
		//check if the player surrenders
		nAns = checkSurrender(cSurrender);
		
		// black (X) move
		if (nTurn == 1) 
		{
			//in turn player did not surrender
			if(nAns == 0) 
			{
				// prompts the user to input coordinates
				do 
				{
					printf("\n------------------------------------");
					printf("\n            (X-Y-X-Y) (1-8)");
					printf("\n Initial (X-Y) to landing position (X-Y).");
					printf("\n    Press ENTER every input of number.\n");
					printf("\n Enter position:\n");
					scanf("%d %d %d %d", &x[0], &x[1], &x[2], &x[3]);
					getchar();
					
					/* if the user input is wrong, it will display error 
						messages and ask the user for input again */
					if (x[0] >= 9 || x[1] >= 9 || x[2] >= 9 || x[3] >= 9 ||
						x[0] <= 0 || x[1] <= 0 || x[2] <= 0 || x[3] <= 0) 
					{
						system("cls");
						
						//printing
						displayErrorMessage();
						displayBoard(board);
						displayTurn(&cPlayerA, &cPlayerB, &nTurn);
						displayPiecesCount(&nPieceX, &nPieceO);

						printf("\n");
					}	
						
				} while (x[0] >= 9 || x[1] >= 9 || x[2] >= 9 || x[3] >= 9 ||
						 x[0] <= 0 || x[1] <= 0 || x[2] <= 0 || x[3] <= 0);
		
				/* decrementing to access the correct vaue of a
					a specific box on the baord, since array starts at zero*/
				x[0] -= 1;
				x[1] -= 1;
				x[2] -= 1;
				x[3] -= 1;
				
				//call the function eatPieceX to implement the moving/eating of X piece
				eatPieceX(x, board, &nTurn, &nPieceO);
			}
			
			//player black (X) surrenders
			else if (nAns == 1) 
			{ 
				//stop the game
				battleInProgress = 0;
				*nWinner = 1;
				
				/* increment the score count of the 
					player who has WHITE (O) piece */
				if (cPlayerB == 'O') 
				{
					*nScoreB += 1;
					displayWinnerB();
				}
				else if (cPlayerA == 'O')
				{
					*nScoreA += 1;
					displayWinnerA();
				}
			}
		}	
		
		// WHITE (O) move
		else if (nTurn == 0) 
		{	
			//in-turn player did not surrender
			if(nAns == 0) 
			{
				//prompts the user to input coordinates
				do 
				{
					printf("\n------------------------------------");
					printf("\n            (X-Y-X-Y) (1-8)");
					printf("\n Initial (X-Y) to landing position (X-Y).");
					printf("\n    Press ENTER every input of number.\n");
					printf("\n Enter position:\n");
					scanf("%d %d %d %d", &x[0], &x[1], &x[2], &x[3]);
					getchar();
					
					/* if the user input is wrong, it will display error 
						messages and ask the user for input again */
					if (x[0] >= 9 || x[1] >= 9 || x[2] >= 9 || x[3] >= 9 ||
						x[0] <= 0 || x[1] <= 0 || x[2] <= 0 || x[3] <= 0) 
					{
						system("cls");
						
						//printing
						displayErrorMessage();
						displayBoard(board);
						displayTurn(&cPlayerA, &cPlayerB, &nTurn);
						displayPiecesCount(&nPieceX, &nPieceO);
						
						printf("\n");
					} 
				
				} while (x[0] >= 9 || x[1] >= 9 || x[2] >= 9 || x[3] >= 9 ||
						 x[0] <= 0 || x[1] <= 0 || x[2] <= 0 || x[3] <= 0);
		
				/* decrementing to access the correct corresponding 
					array piece, since array starts at zero*/
				x[0] -= 1;
				x[1] -= 1;
				x[2] -= 1;
				x[3] -= 1;
				
				//calls the function to execute the move/eating of WHITE (O) piece
				eatPieceO(x, board, &nTurn, &nPieceX);
			}
			
			// WHITE (O) piece surrenders
			else if (nAns == 1) 
			{
				//stop the game
				battleInProgress = 0;
				*nWinner = 1;
				
				/* increment the score count of the 
					player who has BLACK (X) piece */
				if (cPlayerB == 'X') 
				{
					*nScoreB += 1;
					displayWinnerB();
				}
				
				else if (cPlayerA == 'X')
				{
					*nScoreA += 1;
					displayWinnerA();
				}
			}
		}	
		
		//--------------------checking of winner-------------------- //
		
		/*--------checking the winner based on the pieces count. 
			the first piece count to get to zero, loses the game-------*/
			
		// for X
		if (nPieceX == 0) 
		{
			//stop the game
			battleInProgress = 0;
			*nWinner = 1;
			
			/* increment the score count of the 
					player who has WHITE (O) piece */
			if (cPlayerB == 'O') 
			{
				*nScoreB += 1;
				
				//printing
				displayBoard(board);
				displayPiecesCount(&nPieceX, &nPieceO);
				printf("\n\n PLAYER B has captured all the pieces!\n");
				system("pause");
				displayWinnerB();
			}
			
			else if (cPlayerA == 'O') 
			{
				*nScoreA += 1;
				
				//printing
				displayBoard(board);
				displayPiecesCount(&nPieceX, &nPieceO);
				printf("\n\n PLAYER A has captured all the pieces!\n");
				system("pause");
				displayWinnerA();
			}
		}
		//for O
		else if (nPieceO == 0) 
		{
			//stop the game
			battleInProgress = 0;
			*nWinner = 1;
			
			/* increment the score count of the 
				player who has BLACK (X) piece */
			if (cPlayerB == 'X')
			{
				*nScoreB += 1;
				
				//printing
				displayBoard(board);
				displayPiecesCount(&nPieceX, &nPieceO);
				printf("\n\n PLAYER B has captured all the pieces!\n");
				system("pause");
				displayWinnerB();
			}
			else if (cPlayerA == 'X')
			{
				*nScoreA += 1;
				
				//printing
				displayBoard(board);
				displayPiecesCount(&nPieceX, &nPieceO);
				printf("\n\n PLAYER A has captured all the pieces!\n");
				system("pause");
				displayWinnerA();
			}
		}
		
		/*----------checking winner based on the first 
			piece to reach the end row--------------*/
			
		// for O (WHITE)
		if (board[1][0] == 'O' || board[3][0] == 'O' || board[5][0] == 'O' || board[7][0] == 'O') 
		{
			//stop the game
			battleInProgress = 0;
			*nWinner = 1;
			
			/* increment the score count of the player who has 
				WHITE (O) piece and also display the winner! */
			if (cPlayerB == 'O') 
			{
				*nScoreB += 1;
				
				//printing
				displayBoard(board);
				printf("\n\n PLAYER B has reached the opponent's side!\n\n");
				system("pause");
				displayWinnerB();
			}
			else if (cPlayerA == 'O')
			{
				*nScoreA += 1;
				
				//printing
				displayBoard(board);
				printf("\n\n PLAYER A has reached the opponent's side!\n\n");
				system("pause");
				displayWinnerA();
			}
		}
		
		// for X (BLACK) 
		else if (board[0][7] == 'X' || board[2][7] == 'X' || board[4][7] == 'X' || board[6][7] == 'X') 
		{
			//stop the game
			battleInProgress = 0;
			*nWinner = 1;
			
			/* increment the score count of the player who has 
				BLACK (X) piece and also display the winner! */
			if (cPlayerB == 'X') 
			{
				*nScoreB += 1;
				displayBoard(board);
				printf("\n\n PLAYER B has reached the opponent's side!\n\n");
				system("pause");
				displayWinnerB();
			}
			else if (cPlayerA == 'X')
			{
				*nScoreA += 1;
				displayBoard(board);
				printf("\n\n PLAYER A has reached the opponent's side!\n\n");
				system("pause");
				displayWinnerA();
			}
		}
		
		/*-----------checking winner based on blocked pieces-------------*/
		
		for (i = 0; i < 8; i++) // y coordinate
		{
			for (j = 0; j < 8; j++) // x coordinate
			{
				if (nTurn == 1)
				{
					/*to see how many X (black) piece are there on the board */
					if (board[j][i] == 'X') 
					{
						piecesOnBoardX += 1;
						
						/*to see check if the pieces left on the board are blocked or not */
						if (board[j][i] == 'X' && board[j + 1][i + 1] == 'O' && board[j + 2][i + 2] == 'O' &&
							board[j-1][i+1] == 'O' && board[j-2][i+2] == 'O')
							blockedPiecesX += 1;
						
						//half blocked
						else if (board[j][i] == 'X' && board[6][i + 1] == 'O' && board [5][i + 2] == 'O')
							blockedPiecesX += 1;
								
						else if (board[j][i] == 'X' && board[1][i + 1] == 'O' && board [2][i + 2] == 'O')
							blockedPiecesX += 1;
							
						else if (board[j][i] == 'X' && board[j + 1][7] == 'O' && board[j - 1][7] == 'O')
							blockedPiecesX += 1;
					}
				}
				else if (nTurn == 0)
				{
					/*to see how many O (white) piece are there on the board */
					if (board[j][i] == 'O') 
					{
						piecesOnBoardO += 1;
						
						/*to see check if the pieces left on the board are blocked or not */
						if (board[j][i] == 'O' && board[j-1][i-1] == 'X' && board[j-2][i-2] == 'X' &&
							board[j+1][i-1] == 'X' && board[j+2][i-2] == 'X')
							blockedPiecesO += 1;
							
						//half blocked
						else if (board[j][i] == 'O' && board[6][i + 1] == 'X' && board [5][i + 2] == 'X')
							blockedPiecesO += 1;
								
						else if (board[j][i] == 'O' && board[1][i + 1] == 'X' && board [2][i + 2] == 'X')
							blockedPiecesO += 1;
							
						else if (board[j][i] == 'O' && board[j - 1][0] == 'X' && board[j + 1][0] == 'X')
							blockedPiecesO += 1;
					}
				}
			}
		}	
		/* all the pieces on the board must be blocked in order for a winner to happen */
		if (nTurn == 1)
		{
			if (piecesOnBoardX == blockedPiecesX)
			{
				battleInProgress = 0;
				*nWinner = 1;
				
				if (cPlayerB == 'O') 
				{
					*nScoreB += 1;
					displayBoard(board);
					printf("\n\n PLAYER A cannot make a move anymore!\n\n");
					system("pause");
					displayWinnerB();
				}
				else if (cPlayerA == 'O')
				{
					*nScoreA += 1;
					displayBoard(board);
					printf("\n\n PLAYER B cannot make a move anymore!\n\n");
					system("pause");
					displayWinnerA();
				}
			}
		}
		else if (nTurn == 0)
		{
			if (piecesOnBoardO == blockedPiecesO)
			{
				battleInProgress = 0;
				*nWinner = 1;
				
				if (cPlayerB == 'X') 
				{
					*nScoreB += 1;
					displayBoard(board);
					printf("\n\n PLAYER A cannot make a move anymore!\n\n");
					system("pause");
					displayWinnerB();
				}
				else if (cPlayerA == 'X')
				{
					*nScoreA += 1;
					
					displayBoard(board);
					printf("\n\n PLAYER B cannot make a move anymore!\n\n");
					system("pause");
					displayWinnerA();
				}
			}
		}
		
	} while (battleInProgress == 1); //continue looping until there's a winner
}