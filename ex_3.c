#include <stdio.h>
#include <string.h>


/***************************
******** Menu Items ********
****************************/

#define REVERSE 1
#define PALINDROME 2
#define SENTENCES 3
#define ZIP 4
#define SUDOKU 5
#define EXIT 6


/***************************
*** DIMENSION PARAMETERS ***
****************************/

#define LONGEST_TERM 20
#define LONGEST_SENTENCE 62
#define MAX_NUMBER_OF_TERMS 10

#define ZIP_MAX_GRID_SIZE 20

#define SUDOKU_GRID_SIZE 9
#define SUDOKU_SUBGRID_SIZE 3


/***************************
* USER INTEFACE PROTOTYPES *
****************************/

void task1ReversePhrase();
void task2CheckPalindrome();
void task3GenerateSentences();
void task4SolveZipBoard();
void task5SolveSudoku();


/****************************
* IMPLEMENTATION PROTOTYPES *
*****************************/

void task1ReversePhraseImplementation();
int task2CheckPalindromeImplementation(int);
void task3GenerateSentencesImplementation(char[][LONGEST_TERM+1], int, char[][LONGEST_TERM+1], int,
                                            char[][LONGEST_TERM+1], int);
int task4SolveZipBoardImplementation(int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                        char[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], int, int, int, int);
int task5SolveSudokuImplementation(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);


/******************************
* HELPER FUNCTIONS PROTOTYPES *
*******************************/
int task2CheckPalindromeHelper(char phrase[], int, int);
void task3GenSenImpHelper(char[][LONGEST_TERM+1], int, char[][LONGEST_TERM+1], int, 
                          char[][LONGEST_TERM+1], int, int, int, int, int);
int solveZipRecursive(int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], 
                      char[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], 
                      int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE]'
                      int, int, int, int, int, int);
int readTerms(char[][LONGEST_TERM+1], int, char[]);
void printSudoku(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);



/******************************
********** MAIN MENU **********
*******************************/

int main()
{
    int task;
    do
    {
        printf("Please choose a task (1-5) or 6 to exit:\n");
        printf("%d. Reverse a phrase\n", REVERSE);
        printf("%d. Check Palindrome\n", PALINDROME);
        printf("%d. Generate sentences\n", SENTENCES);
        printf("%d. Solve Zip Board\n", ZIP);
        printf("%d. Solve Sudoku\n", SUDOKU);
        printf("%d. Exit\n", EXIT);

        scanf(" %d", &task);
        scanf("%*c");
        switch (task)
        {
        case REVERSE:
            task1ReversePhrase();
            break;
        case PALINDROME:
            task2CheckPalindrome();
            break;
        case SENTENCES:
            task3GenerateSentences();
            break;
        case ZIP:
            task4SolveZipBoard();
            break;
        case SUDOKU:
            task5SolveSudoku();
            break;
        case EXIT:
            printf("Goodbye!\n");
            break;
        default:
            printf("Please choose a task number from the list.\n");
            break;
        }
        printf("\n=============================\n\n");
    } while (task != EXIT);

    return 0;
}


/***************************
****** USER INTERFACE ******
****************************/


void task1ReversePhrase()
{
    printf("Please insert the phrase to reverse:\n");
    task1ReversePhraseImplementation();
    printf("\n");
}


void task2CheckPalindrome()
{
    printf("Please insert the phrase length:\n");
    int n;
    scanf("%d", &n);
    printf("Please insert the phrase to check:\n");
    scanf(" ");
    if (task2CheckPalindromeImplementation(n))
        printf("The phrase is a palindrome.\n");
    else
        printf("The phrase is not a palindrome.\n");
}


void task3GenerateSentences()
{
    char subjects[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    char verbs[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    char objects[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    int subjectsCount, verbsCount, objectsCount;

    subjectsCount=readTerms(subjects, MAX_NUMBER_OF_TERMS, "subjects");
    verbsCount=readTerms(verbs, MAX_NUMBER_OF_TERMS, "verbs");
    objectsCount=readTerms(objects, MAX_NUMBER_OF_TERMS, "objects");
    printf("List of Sentences:\n");
    task3GenerateSentencesImplementation(subjects, subjectsCount, verbs, verbsCount, objects, objectsCount);
}


void task4SolveZipBoard()
{
    int size;
    int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    int row, col;
    int highest=0;
    printf("Please enter the board size:\n");
    scanf("%d", &size);
    if (size < 1 || size > ZIP_MAX_GRID_SIZE)
    {
        printf("Invalid board size.\n");
        return;
    }

    printf("Please enter the grid:\n");
    for (int i = 0; i < size-1; i++)
    {
        for (int j = 0; j < size-1; j++)
        {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 1)
            {
                row = i;
                col = j;
            }
            if(board[i][j]>highest){
                highest=board[i][j];
            }
        }
    }
    if (task4SolveZipBoardImplementation(board, solution, size, row, col, highest))
    {
        printf("Solution:\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%c ", solution[i][j] ? solution[i][j] : 'X');
            }
            printf("\n");
        }
    }
    else
    {
        printf("No solution exists.\n");
    }
}


void task5SolveSudoku()
{
    printf("Please enter the sudoku board:\n");
    int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE] = {0};
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            scanf("%d", &board[i][j]);
        }
    }
    if (task5SolveSudokuImplementation(board))
    {
        printf("Solution found:\n");
        printSudoku(board);
    }
    else
    {
        printf("No solution exists.\n");
    }
}


/***************************
********* HELPERS **********
****************************/


int readTerms(char terms[][LONGEST_TERM+1], int maxNumOfTerms, char type[]){
    int termsCount;
    printf("Please insert number of %s:\n", type);
    scanf("%d", &termsCount);
    if(termsCount < 1 || termsCount > maxNumOfTerms){
        termsCount = maxNumOfTerms;
    }
    printf("Please insert the list of %s:\n", type);
    for(int i=0;i<termsCount;i++){
        printf("%d. ",i+1);
        scanf(" %[^\n]",terms[i]);
    }
    return termsCount;
}


void printSudoku(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE])
{
    printf("+-------+-------+-------+\n");
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        printf("| ");
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            if (board[i][j] == 0)
                printf(". ");
            printf("%d ", board[i][j]);

            if ((j + 1) % SUDOKU_SUBGRID_SIZE == 0)
                printf("| ");
        }
        printf("\n");
        if ((i + 1) % SUDOKU_SUBGRID_SIZE == 0)
            printf("+-------+-------+------ -+\n");
    }
}

/***************************
*********** TODO ***********
****************************/


void task1ReversePhraseImplementation(){
  char letter;
  scanf("%c", &letter);
  if (letter == '\n') {
    return;
  }
  task1ReversePhraseImplementation();
  printf("%c", letter);
}


int task2CheckPalindromeImplementation(int length){
  char phrase[LONGEST_SENTENCE + 1];
  scanf("%[^\n]", phrase);
  return task2CheckPalindromeHelper(phrase, 0, length-1);
}

int task2CheckPalindromeHelper(char phrase[], int leftSide, int rightSide) {
  if (leftSide >= rightSide) {
    return 1;
  }
  if (phrase[leftSide] != phrase[rightSide]) {
    return 0;
  }

  return task2CheckPalindromeHelper(phrase, leftSide+1, rightSide-1);
}


void task3GenerateSentencesImplementation(char subjects[][LONGEST_TERM+1], int subjectsCount,
                                            char verbs[][LONGEST_TERM+1], int verbsCount,
                                            char objects[][LONGEST_TERM+1], int objectsCount) {
  
  task3GenSenImpHelper(subjects, subjectsCount, verbs, verbsCount, objects, objectsCount, 0, 0, 0, 1);

}

void task3GenSenImpHelper(char subjects[][LONGEST_TERM+1], int subjectCount,
                          char verbs[][LONGEST_TERM+1], int verbCount,
                          char objects[][LONGEST_TERM+1], int objectCount,
                          int subject, int verb, int object, int index){
  if (subject == subjectCount) {
    return;
  }

  if (verb == verbCount) {
    task3GenSenImpHelper(subjects, subjectCount, verbs, verbCount, objects, 
                         objectCount, subject+1, 0, 0, index);

    return;
  }

  if (object == objectCount) {
    task3GenSenImpHelper(subjects, subjectCount, verbs, verbCount, objects,
                         objectCount, subject, verb+1, 0, index);

    return;
  }

  printf("%d. %s %s %s\n", index, subjects[subject], verbs[verb], objects[object]);

  task3GenSenImpHelper(subjects, subjectCount, verbs, verbCount, objects, 
                        objectCount, subject, verb, object+1, index+1);
}

  


int task4SolveZipBoardImplementation(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                    char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                    int size, int startR, int startC, int highest)
{
 int visited[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
 return solveZipRecursive(board, solution, visited, size, startR, startC, 2, highest, 1);
}

int solveZipRecursive(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], 
                      char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], 
                      int visited[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                      int size, int r, int c, int nextNumber, int highest, int visitedCount) {
    
  //  FIX: boundary check
    if (r < 0 || r >= size || c < 0 || c >= size)
        return 0;

    // 🔴 FIX: proper visited tracking (NOT solution[][])
    if (visited[r][c])
        return 0;

    // 🔴 FIX: enforce ascending numbered tiles rule
    if (board[r][c] != 0 && board[r][c] != nextNumber)
        return 0;

    // 🔴 FIX: mark visited
    visited[r][c] = 1;

    // 🔴 FIX: update next expected number
    if (board[r][c] == nextNumber)
        nextNumber++;

    // 🔴 FIX: base case (must cover ALL cells)
    if (visitedCount == size * size)
    {
        if (board[r][c] == highest)
        {
            solution[r][c] = 'X';
            return 1;
        }

        visited[r][c] = 0;
        return 0;
    }

    // 🔴 FIX: U → D → L → R recursion order (required by spec)

    // UP
    solution[r][c] = 'U';
    if (solveZipRecursive(board, solution, visited,
                 size, r - 1, c,
                 nextNumber, highest,
                 visitedCount + 1))
        return 1;

    // DOWN
    solution[r][c] = 'D';
    if (solveZipRecursive(board, solution, visited,
                 size, r + 1, c,
                 nextNumber, highest,
                 visitedCount + 1))
        return 1;

    // LEFT
    solution[r][c] = 'L';
    if (solveZipRecursive(board, solution, visited,
                 size, r, c - 1,
                 nextNumber, highest,
                 visitedCount + 1))
        return 1;

    // RIGHT
    solution[r][c] = 'R';
    if (solveZipRecursive(board, solution, visited,
                 size, r, c + 1,
                 nextNumber, highest,
                 visitedCount + 1))
        return 1;

    // 🔴 FIX: BACKTRACK (this is REQUIRED)
    visited[r][c] = 0;
    solution[r][c] = 0;

    return 0;
}


int task5SolveSudokuImplementation(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE])
{
    return 0;
}
