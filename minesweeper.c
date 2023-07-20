//Josh Matni
//Project: Minesweeper!

#include <stdio.h>

#define FIELD_FILE  "field.txt"
#define NAMEANDSCORES "winners.txt"
#define ROWS 8
#define COLS 8
#define STR_LEN 50
#define MAX 100

char getOption(void);
void readFileContents(FILE *, int [][COLS], char [][COLS]);
int displayBoard(char [][COLS]);
void clearBoard(int, int, char [][COLS]);
void updateMoves(int, int, char [][COLS], int [][COLS], char);
void markCell(int, int, char [][COLS]);
_Bool checkBomb(int, int, char [][COLS], int [][COLS]);
void uncoverCells(int original[][COLS], char modified[][COLS], int row, int col,int key);
void getPlayerMove(int *, int *);
_Bool uncoverBomb(int, int, char [][COLS]);
void youLost(char []);
void getName(char [STR_LEN + 1]);
void displayNames(FILE *, char [][STR_LEN + 1]);
void win();

int main()
{
    int userRow, userCol, original[ROWS][COLS], board;
    char userChoice, modified[ROWS][COLS], userName[MAX][STR_LEN + 1], name[STR_LEN + 1];
    FILE *fp1, *fp2;
    
    fp1 = fopen(FIELD_FILE, "r");
    if(fp1 == NULL)
    {
   		printf("Sorry, couldn't open file");
    }
    else
    {
	   	readFileContents(fp1, original, modified);
	   	fclose(fp1);
    }
    
    fp2 = fopen(NAMEANDSCORES, "r");
    if(fp2 == NULL)
    {
   		printf("Sorry, couldn't open file");
    }
    else
    {
   		printf("\n\nBEAT THE HIGH SCORES!\n\n\n");
   		displayNames(fp2, userName);
   		printf("\n\n");
   		fclose(fp2);
    }
    
    clearBoard(userRow, userCol, modified);
    board = displayBoard(modified);
    
    do
    {
    
		getPlayerMove(&userRow, &userCol);
		userChoice = getOption();
		updateMoves(userRow, userCol, modified, original, userChoice);
		board=displayBoard(modified);
		
    }while((uncoverBomb(userRow, userCol, modified) != 1) || (board == 1));

    youLost(name);
    
    return 0;
}

void readFileContents(FILE *fp, int original[][COLS], char modified[][COLS])
{
    int value;
    
    for (int row = 0, col  = 0; (row < ROWS); row++)
    {
	   	 for(int col = 0; col < COLS && fscanf(fp, "%d", &value) == 1; col++)
	   	 {
	   		 original[row][col] = value;
	   	 }
    }
}

char getOption(void)
{
    char userChoice;
    
    printf("(M)ark this cell with a bomb flag\n");
    printf("(U)ncover to reveal what's in this cell\n");
    printf("(C)heck the surrounding cells\n");
    printf("Which move? ");
    
    scanf(" %c", &userChoice);
    
    return userChoice;
}

void getPlayerMove(int *row, int *col)
{
    printf("Which cell? ");
    scanf("%d %d", row, col);
}

int displayBoard(char modified[][COLS])
{
    printf("    1   2   3   4   5   6   7   8  \n");
    printf("  ---------------------------------");
	
	int count = 0;
    for(int row = 0; row < ROWS; row++)
    {
	   	 printf("\n %d", (row + 1));
	   	 
	   	 for(int col = 0; col < COLS; col++)
	   	 {
	   		printf("| %c ", modified[row][col]);
	   		
			if(modified[row][col]== ' ')
			{
				count++;
			}
   	 }
   	 printf("|");
   	 printf("\n  ---------------------------------");
    }
    printf("\n");
	if(count == 0)
	{
		win();
		return 1;
	}
	return 0;
}

void clearBoard(int row, int col, char modified[][COLS])
{
    for(row = 0; row < ROWS; row++)
    {
	   	 for(col = 0; col < COLS; col++)
	   	 {
	   		 modified[row][col] = ' ';
	   	 }
    }                                                                                      	 
}

void updateMoves(int row, int col, char modified[][COLS], int original[][COLS], char userChoice)
{
    int key = 0; //Key keeps the marked chells in check
    switch(userChoice)
    {
	   	 case 'M':
	   	 case 'm':
	   		 markCell(row, col, modified);
	   		 break;
	   	 case 'U':
	   	 case 'u':
			 key=1;
	   		 uncoverCells(original, modified, row, col,key);
	   		 //displayBoard(modified);
	   		 break;
	   	 case 'C':
	   	 case 'c':
	   		 checkBomb(row, col, modified, original);
	   		 //displayBoard(modified);
	   	 default:
	   	 printf("Please Enter a valid character\n");
	   	 break;
    }
}

void markCell(int row, int col, char modified[][COLS])
{
    modified[row - 1][col - 1] = 'F';
    //displayBoard(modified);
}

void uncoverCells(int original[][COLS], char modified[][COLS], int row, int col,int key)
{
    
    switch(original[row - 1][col - 1])
    {
   	 case 0:
   		 if((key!=1)&&modified[row - 1][col - 1] == 'F')
   		 {
   			 modified[row - 1][col - 1] == 'F';
   		 }
   		 else
   		 {
   			 modified[row - 1][col - 1] = '_';
   		 }
   		 break;
   	 case 1:
   		 if((key!=1)&&modified[row - 1][col - 1] == 'F')
   		 {
   			 modified[row - 1][col - 1] == 'F';
   		 }
   		 else
   		 {
   			 modified[row - 1][col - 1] = 49;
   		 }
   		 break;
   	 case 2:
   		 if((key!=1)&&modified[row - 1][col - 1] == 'F')
   		 {
   			 modified[row - 1][col - 1] == 'F';
   		 }
   		 else
   		 {
   			 modified[row - 1][col - 1] = 50;
   		 }
   		 break;
   	 case 3:
   		 if((key!=1)&&modified[row - 1][col - 1] == 'F')
   		 {
   			 modified[row - 1][col - 1] == 'F';
   		 }
   		 else
   		 {
   			 modified[row - 1][col - 1] = 51;
   		 }
   		 break;
   	 case 99:    
   		 if((key!=1)&&modified[row - 1][col - 1] == 'F')
   		 {
   			 modified[row - 1][col - 1] == 'F';
   		 }
   		 else
   		 {
   			 modified[row - 1][col - 1] = 'X';
   		 }
   		 break;
    }
}

_Bool checkBomb(int row, int col, char modified[][COLS], int original[][COLS])
{
    int key = 0;
    if(row == 1 && col == 1) // for top left corner
    {
   	 //modified[row][col] = original[row][col];
   	 uncoverCells(original, modified, row, col,key);
   	 //modified[row + 1][col - 0] = original[row + 1][col - 0];
   	 uncoverCells(original, modified, row+1, col,key);
   	 //modified[row - 0][col + 1] = original[row - 0][col + 1];
   	 uncoverCells(original, modified, row, col+1,key);
   	 //modified[row + 1][col + 1] = original[row + 1 ][col + 1];
   	 uncoverCells(original, modified, row+1, col+1,key);
    }
    else if(row == 8 && col == 8) //for bottom right corner
    {
   	 //modified[row][col] = original[row][col];
   	 uncoverCells(original, modified, row, col,key);
   	 //modified[row - 1][col - 0] = original[row - 1][col - 0];
   	 uncoverCells(original, modified, row - 1, col,key);
   	 //modified[row - 0][col - 1] = original[row - 0][col - 1];
   	 uncoverCells(original, modified, row, col-1,key);
   	 //modified[row - 1][col - 1] = original[row - 1][col - 1];
   	 uncoverCells(original, modified, row-1, col-1,key);
    }
    else if(row == 1 && col == 8) //for top right corner
    {
   	 //modified[row][col] = original[row][col];
   	 uncoverCells(original, modified, row, col,key);
   	 //modified[row - 0][col - 1] = original[row - 0][col - 1];
   	 uncoverCells(original, modified, row, col-1,key);
   	 //modified[row + 1][col - 1] = original[row + 1][col - 1];
   	 uncoverCells(original, modified, row+1, col-1,key);
   	 //modified[row + 1][col - 0] = original[row + 1][col - 0];
   	 uncoverCells(original, modified, row+1, col,key);
    }
    else if(row == 8 && col == 1) //for bottom left corner
    {
   	 //modified[row][col] = original[row][col];
   	 uncoverCells(original, modified, row, col,key);
   	 //modified[row - 1][col - 0] = original[row - 1][col - 0];
   	 uncoverCells(original, modified, row-1, col,key);
   	 //modified[row - 1][col + 1] = original[row - 1][col + 1];
   	 uncoverCells(original, modified, row-1, col+1,key);
   	 //modified[row - 0][col + 1] = original[row - 0][col + 1];
   	 uncoverCells(original, modified, row, col+1,key);
    }
    else if(row == 8) // for bottom row
    {
   	 //modified[row][col] = original[row][col];
   	 uncoverCells(original, modified, row, col,key);
   	 //modified[row - 1][col - 1] = original[row - 1][col - 1];
   	 uncoverCells(original, modified, row-1, col-1,key);
   	 //modified[row - 1][col - 0] = original[row - 1][col - 0];
   	 uncoverCells(original, modified, row-1, col,key);
   	 //modified[row - 1][col + 1] = original[row - 1][col + 1];
   	 uncoverCells(original, modified, row-1, col+1,key);
   	 //modified[row - 0][col - 1] = original[row - 0][col - 1];
   	 uncoverCells(original, modified, row, col-1,key);
   	 //modified[row - 0][col + 1] = original[row - 0][col + 1];
   	 uncoverCells(original, modified, row, col+1,key);
    }
    else if(row == 0) // for top row
    {
   	 //modified[row][col] = original[row][col];
   	 uncoverCells(original, modified, row, col,key);
   	 //modified[row - 0][col - 1] = original[row - 0][col - 1];
   	 uncoverCells(original, modified, row, col-1,key);
   	 //modified[row + 1][col - 1] = original[row + 1][col - 1];
   	 uncoverCells(original, modified, row+1, col-1,key);
   	 //modified[row + 1][col - 0] = original[row + 1][col - 0];
   	 uncoverCells(original, modified, row+1, col,key);
   	 //modified[row + 1][col + 1] = original[row + 1][col + 1];
   	 uncoverCells(original, modified, row+1, col+1,key);
   	 //modified[row - 0][col + 1] = original[row - 0][col + 1];
   	 uncoverCells(original, modified, row, col+1,key);
   	 
    }
    else if(col == 8) // for right colum
    {
   	 //modified[row][col] = original[row][col];
   	 uncoverCells(original, modified, row, col,key);
   	 //modified[row - 0][col - 1] = original[row - 0][col - 1];
   	 uncoverCells(original, modified, row, col-1,key);
   	 //modified[row - 1][col - 1] = original[row - 1][col - 1];
   	 uncoverCells(original, modified, row-1, col-1,key);
   	 //modified[row - 0][col - 1] = original[row - 0][col - 1];
   	 uncoverCells(original, modified, row, col-1,key);
   	 //modified[row + 1][col - 1] = original[row + 1][col - 1];
   	 uncoverCells(original, modified, row+1, col-1,key);
   	 //modified[row + 1][col - 0] = original[row + 1][col - 0];
   	 uncoverCells(original, modified, row+1, col,key);
    }
    else if(col == 1) // for left colum
    {
   	 //modified[row][col] = original[row][col];
   	 uncoverCells(original, modified, row, col,key);
   	 //modified[row - 1][col - 0] = original[row - 1][col - 0];
   	 uncoverCells(original, modified, row-1, col,key);
   	 //modified[row - 1][col + 1] = original[row - 1][col + 1];
   	 uncoverCells(original, modified, row-1, col+1,key);
   	 //modified[row - 0][col + 1] = original[row - 0][col + 1];
   	 uncoverCells(original, modified, row, col+1,key);
   	 //modified[row + 1][col + 1] = original[row + 1][col + 1];
   	 uncoverCells(original, modified, row+1, col+1,key);
   	 //modified[row + 1][col - 0] = original[row + 1][col - 0];
   	 uncoverCells(original, modified, row+1, col,key);
    }
    else // for the center cells
    {
   	 //modified[row][col] = original[row][col];
   	 uncoverCells(original, modified, row, col,key);
   	 //modified[row - 1][col - 1] = original[row - 1][col - 1];
   	 uncoverCells(original, modified, row-1, col-1,key);
   	 //modified[row - 1][col - 0] = original[row - 1][col - 0];
   	 uncoverCells(original, modified, row-1, col,key);
   	 //modified[row - 1][col + 1] = original[row - 1][col + 1];
   	 uncoverCells(original, modified, row-1, col+1,key);
   	 //modified[row - 0][col - 1] = original[row - 0][col - 1];
   	 uncoverCells(original, modified, row, col-1,key);
   	 //modified[row - 0][col + 1] = original[row - 0][col + 1];
   	 uncoverCells(original, modified, row, col+1,key);
   	 //modified[row + 1][col + 1] = original[row + 1][col + 1];
   	 uncoverCells(original, modified, row+1, col+1,key);
   	 //modified[row + 1][col - 1] = original[row + 1][col - 1];
   	 uncoverCells(original, modified, row+1, col-1,key);
   	 //modified[row + 1][col - 0] = original[row + 1][col - 0];
   	 uncoverCells(original, modified, row+1, col,key);
    }

}

_Bool uncoverBomb(int row, int col, char modified[][COLS])
{
    
    for(int rowIndex = 0; rowIndex < COLS; rowIndex++)
    {
	   	 for(int colIndex = 0; colIndex < COLS; colIndex++)
	   	 {
	   		 
	   		 if(modified[rowIndex][colIndex] == 'X')
	   		 {
	   			 return 1;    
	   		 }
	   	 }
    }
    return 0;
}

void youLost(char userName[])
{
    char userInput;
    FILE *fp = fopen(NAMEANDSCORES, "a");
    printf("You lose :(\n");
    printf("Play again (Y/N) ");
    scanf(" %c", &userInput);
    
    if(fp != NULL)
    {
   		switch(userInput)
   	 	{
   			case 'Y':
   			case 'y':
   			 	main();
   			 	break;
   		 	case 'N':
   		 	case 'n':
   			 	printf("What is your name? ");+
   			 	scanf("%s", userName);
   			 	fprintf(fp, "%s", userName);
   			 	break;
   		 	default:
   			 	printf("Enter a valid option!\n");
   			 	break;
   	 	}
    }
    else
    {
   	 	printf("File not found");
    }
}

void displayNames(FILE *fp, char userName[][STR_LEN+1])
{
    for(int rowIndex = 0; (rowIndex < ROWS) && fscanf(fp, "%s", &userName[rowIndex]) == 1; rowIndex++)
    {
   		printf("%s: 1\n", userName[rowIndex]);
	} 
}

void win()
{
	char userInput;
	
	printf("\n\nyou win\n\n");
	printf("Play again (Y/N) ");
	scanf(" %c", &userInput);
	
	if(userInput == 'Y' || 'y')
	{
		main();
	}
}



   		 
   	 	




