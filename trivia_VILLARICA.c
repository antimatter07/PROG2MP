/********************************************************************************************************* 
This is to certify that this project is my own work, based on my personal efforts in studying and applying
 the concepts learned. 
I have constructed the functions and their respective algorithms and corresponding code by myself. 
The program was run, tested, and debugged by my own efforts. 
I further certify that I have not copied in part or whole or otherwise plagiarized the work of other 
students and/or persons.
 Matthew James D. Villarica, DLSU ID 12049476 
*********************************************************************************************************/

/* Make sure that the main() is not in this file. */

#include "trivia.h"
#include<stdlib.h> //including this header file for rand() and srand()

/* You can add other data structures here.
   
   You are expected to implement other functions not listed
   in the trivia.h here. Do not forget to include internal 
   documentation. For functions with long (many lines) of code,
   make sure to also include inline comments to discuss your
   algorithm.
*/

/*
	Takes a string with a capacity of 21 and and gets user input
	(including spaces) until a newline is encountered (user presses enter). Used for getting
	input with a type strWord when spaces are possible.

	@param answer - the string (character array) where user input goes to

 */
void 
getPhraseWord(strWord answer) {
	
	int j;
	char ch;
	
	j = 0;
	
	do
	{
		scanf("%c", &ch);
		if(ch != '\n') {
			answer[j] = ch;
			j++;
		}
		else
			answer[j] = '\0';
		
	}while(ch != '\n');
}

/*
	When the user chooses to modify an entry during the maintenance phase, takes user input on what the user would
	want to do and executes those actions until user chooses to exit. Calls modifyEntry when user wants to modify
	the clues.

	@param oneEntry - a pointer that contains the address of a single trivia in the array aEntries, the entry
						the user ones to modify
	@param aEntries - the array of entries, called to check for duplicates in case the user wants to modify the word
	@param nElem - the amount of elements in aEntries.
*/
void 
modifyEntryChoice(struct triviaTag * oneEntry, wordList aEntries, int nElem) {
	
	int bInput = 1;
	int choice;
	
	char cDump;
	int res;
	strWord repWord;
	
	while(bInput == 1) {
		
		printf("\n[1]Modify Word\n[2]Modify Clue\n[3]Exit\n");
	
		
		do
		{
			printf("\nPlease enter the number of your next action: ");
			scanf("%d%c", &choice, &cDump);
			
		}while(!(choice >= 1 && choice <= 3));
		
		if(choice == 1) {
			printf("\nPlease enter the new word: "); 
			do
			{
				getPhraseWord(repWord);
				
				res = searchWord(repWord, aEntries, nElem);
				
				
				if(res != -1) 
					printf("\nThe word you entered already exists, please enter a new word.\n");
				
				
			}while(res != -1);
			
			
			
			strcpy(oneEntry->answer, repWord);
			printf("The word has been successfully replaced: %s", oneEntry->answer);
		} else if (choice == 2) {
			
			modifyEntry(oneEntry);
		} else if (choice == 3)
			bInput = 0;
	
	}
}
/*
	Counts the amount of instances of each letter as a starting letter of each word in
	the array of trivia. The count of apital letters are in index 0 - 25, while small letters are in 
	index 26 - 52. (i.e. if 6 words in aEntries start with 'A', then index 0 of FC[] contains 6);

	@param FC - 1D array of ints containing the count of each number.
	@param aEntries - the array of trivias, aEntries[x].word are the words being checked/counted
	@param n - the amount of elements there are in aEntries.

	

 */
void 
FrequencyCount(int FC[], wordList aEntries, int n)
{
	
	int j;
	int i;	
	int index;

	/*Initialize all to 0 */
	
	for(i = 0; i < 52; i++)
		FC[i] = 0;

	for(j = 0; j < n; j++) {
		
		/*Finds index if word starts with capital and small letter respectively */
		if(aEntries[j].answer[0] >= 'A' && aEntries[j].answer[0] <= 'Z')
			index = aEntries[j].answer[0] - 'A';
		else
			index = aEntries[j].answer[0] - 71;
		
		/*Capital letters are in index 0 - 25, while small letters are in index 26 - 51 */
		FC[index] = FC[index] + 1;
	}


}
/*
	Returns 1 if all elements are used, 0 otherwise.

	@param aEntries - array of trivia
	@param nElem - amount of elements in aEntries

 */
int 
isAllUsed(wordList aEntries, int nElem) {
	
	int count, i;
	
	count = 0;
	
	for(i = 0; i < nElem; i++) {
		if(aEntries[i].use == 1) 
			count++;
	}
	
	if(count == nElem)
		return 1;
	else return 0;
}


/*
 	Generates random number within a range inclusive of the upper and lower limits
 	this function also utilizes rand() which is getting reseeded.

 
 	@param nLower - the lower limit of the range of values
 	@param nUpper -	the upper limit of the range of values
 :
 Return value: int, the random number the function has generated within the range
*/
int getRandom(int nLower, int nUpper)
{
	int nRandom;
	int nIncUpper; //inclusive upper

	nIncUpper = nUpper + 1;
	nRandom = rand() % (nIncUpper - nLower);


	nRandom += nLower;


	return nRandom;
}
/*
		Finds the letter that should be prioritized in the initialization of the gameboar, the starting letter
		with the highest count. Returns the index of this letter. 

		@param A - array of counts of each starting letter found by FrequencyCount()
		@param n - amount of elements in A

  */
int findMax(int A[], int n)
{
	int j;
	int max = 0;
	
	for(j = 1; j < n; j++) {

		/*Finds max exclusive of 0  */
		if(A[j] > A[max] && A[j] != 0)
			max = j;
	}
	
	return max;
}
/* 
	Prints the matrix of characters that represents the gameboard.

	@param gameboard - 2D array of characters 
	@param nRows - the amount of rows in the gameboard
	@param nCols - the amount of columns in the gamebaord

*/

void printGB(arrMatrix gameboard, int nRows, int nCols)
{
	
	int j, i;
	printf("\n");
	
	for(j = 0; j < nRows; j++) {
		for(i = 0; i < nCols; i++) {
			
			printf("%c ", gameboard[j][i]);
			
			
		}
		printf("\n");
	}
	
	
}

/*
	Checks if a character is in the english alphabet. Returns 1 if it is and 0 if it does not.

	@param c - the char being checked
*/

int isLetter(char c)
{
	
	
	if(c >= 'a' && c <= 'z')
		return 1;
	else if(c >= 'A' && c <='Z')
		return 1;
	else return 0;
	

}



/*
	This function counts all the instances key is an element of the 1D array row[], 
	used to determine if a player loses once a row is filled with '-' and is called in
	IsOver()_.
	
	@param row - The row of the gameboard being checked.
	@param nCols - The amount of columns in the gameboard.
	@param key - The character that the function will keep count of.

*/
int countChar(char row[], int nCols, char key)
{
	int count = 0;
	int j;
	
	for(j = 0; j < nCols; j++) {
		if(row[j] == key)
			count++;
	}
	
	return count;
	
}

/*
	During the maintenance phase, when the user wishes to delete a clue from a word, this function prompts
	the user for a word whose clues they would like to delete and delete the specific clue after user input.

	@param aEntries - the array of trivia
	@param nElem - the amount of elements in aEntries

*/
void 
deleteClue(wordList aEntries, int nElem)
{
	int res = -1;
	int choice, j;
	strWord word;

	/*Prompt user for word until they enter a valid word */
	while(res == -1) {
		printf("\nPlease enter the word whose clue/s you would like to delete: ");
		getPhraseWord(word);

		res = searchWord(word, aEntries, nElem);

		if(res == -1)
		printf("\nThe word does not exist, please enter another word.\n");
	}

	printf("\n");

	if(aEntries[res].numClues > 1) {
		viewEntry(aEntries[res]);
		
		do
		{
			printf("\nPlease enter the number of the clue you would like to delete: ");
			scanf("%d", &choice);
		}while(!(choice >= 1 && choice <= aEntries[res].numClues));

		choice--;

		aEntries[res].numClues--;

		for(j = choice; j < aEntries[res].numClues; j++) {
			aEntries[res].clueList[j] = aEntries[res].clueList[j + 1];
		}
	} else {

		printf("\nUnable to delete any clues for this word since this word only has one clue.");
		printf("You may only modify or add clues to this word.\n");

	}

}
/*
	This function uses linear search to look for the key in a 1D array of integers and 
	returns the index once the key is found. If the key is not present in the array, the
	function returns -1;
	
	@param row - A row in the gameboard 
	@param nCols - The amount of columns each row has in the gameboard
	@param key - The character being searched for.

*/
int 
SearchInt(int row[], int nCols, int key)
{
	int j = 0;
	int bFound = 0;
	int index = -1;
	
	
	
	while(bFound == 0 && j < nCols) {
		
		if(row[j] == key) {
			
			bFound = 1;
			index = j;
			
		}
		else
			j++;
	}
	
	return index;
	
}
/*
	This function uses linear search to look for the key in a 1D array of characters and 
	returns the index once the key is found. If the key is not present in the array, the
	function returns -1;
	
	@param row - A row in the gameboard 
	@param nCols - The amount of columns each row has in the gameboard
	@param key - The character being searched for.

*/
int 
Search(char row[], int nCols, char key)
{
	int j = 0;
	int bFound = 0;
	int index = -1;
	
	while(bFound == 0 && j < nCols) {
		
		if(row[j] == key) {
			
			bFound = 1;
			index = j;
			
		}
		else
			j++;
	}
	
	return index;
	
}

/*
	This function determines if the game will keep going based on	
	the contents of the gameboard. If the game is over, it returns 1
	if the player wins (there is a star on every row of the gameboard) and -1 
	if the game is over because the player loses, and returns 0 if the game should 
	keep going.
	
	@param gameboard - The 2D array of characters that represents the gameboard
	@param nRows - the number of rows the gameboard
	@param nCols - the number of columns each row in the gameboard has
	
*/
int
IsOver(arrMatrix gameboard, int nRows, int nCols)
{
	int i;
	int starCount = 0;
	int bResult = 0;
	
	
	for(i = 0; i < nRows; i++) {
		
		if(Search(gameboard[i], nCols, '*') != -1)
			starCount++;
		if(countChar(gameboard[i], nCols, '-') == nCols)
			bResult = -1;
		
	}
	
	if(starCount == nRows)
		bResult = 1;
	
	return bResult;
	
}
/* 
	Checks if c is a smallercase or uppercase y or n.
	Returns 1 or 0 depending if input is valid or not.

	@param c - the char being checked
*/
int 
bIsYN(char c)
{
	if(c == 'Y' || c == 'N' || c == 'n' || c == 'y')
		return 1;
	else return 0;
}
/*
   Finds the index of the letter with the highest count (like findMax) with respect to the previous max since 
   the max can't repeat for each (each letter in a row has to be unique). 

   @param A - the array containing the counts of each letter. indeces 0-25 have the counts of letters A-Z while 26-51
			  contains the counts for letters a-z.
   @param prevMax - array of indeces that contain indeces that have already been used in that row, which are not valid maxes 
					anymore.
	@param n - the amount of elements in A
	@param nElemPrevMax - the amount of elmeents in prevMax

 */
int 
findMaxPrev(int A[], int prevMax[], int n, int nElemPrevMax)
{
	int j;
	int max = 0;
	
	
	
	for(j = 1; j < n; j++) {

		/*If A[j] contains a count that is higher than the current max and its a letter that is not used
		in the current row of the gameboard, then the current index should be the new max. */
		if(A[j] > A[max] && SearchInt(prevMax, nElemPrevMax, j) == -1 && A[j] > 0)
			max = j;
		
	}
	
	//When the code above stops working when all remaining letters have a count of 1, this is used
	if(A[max] == 0) {
		
		for(j = 1; j < n; j++) {
		
			if(A[j] == 1 && A[j] > 0)
				max = j;
		
		}
	}
	
	
	return max;
}

/* 
	The user is prompted to enter a word until the word is valid
	, and the clues of this word are displayed by the function.

	@param aEntries - the array of trivia
	@param nElem - the amount of elements in aEntries

*/
void 
viewClues(wordList aEntries, int nElem)
{
	
	strWord input;
	int res;
	
	printf("\nLIST OF WORDS: \n");
	listWords(aEntries, nElem);
	
	do
	{
		printf("\n\nPlease enter the word you would like to view the clues of: ");
		getPhraseWord(input);
		
		res = searchWord(input, aEntries, nElem);
		
	if(res == -1)
		printf("\nThe word you entered does not exist in the list, please enter a word that is in the list above.");
	}while(res == -1);
	
	fflush(stdin);
	
	viewEntry(aEntries[res]);
	
	
}
/*
	During play(), this function checks if the letter the user entered is in the row of the gameboard.
	Returns the index of the letter if it is found, returns -1 otherwise.

	@param ch - the input of the user in play(), letter being checked for validity
	@param gameRow - the current row of the gameboard
	@param nCols - the amount of columns each row in the gameboard has.

 */

int 
isValidLetter(char ch, char gameRow[], int nCols) 
{
	int j;
	int bFound = 0;
	
	int index;
	j = 0;

	while(bFound == 0 && j < nCols) {
		if(ch == gameRow[j]) {
			index = j;
			bFound = 1;
		}
		j++;
	}

	if(bFound == 0)
		return -1;
	else
		return index;



}

/* 
	During the maintenance when the user wants to modify a relation value of a certain word,
	this function replaces the current phrase relation value with user's input.

	@param oneEntry - pointer that contains the address of the entry that has the clue the
					  user wants to modify.
	
	@param clueChoice - the number of the clue the user choosed to modify.

*/

void 
getPhraseRelValue(struct triviaTag * oneEntry, int clueChoice)
{
	int j;
	char ch;

	do
	{
		j = 0;
		do
		{			
			scanf("%c", &ch);
					
			if(ch != '\n') {

				(*oneEntry).clueList[clueChoice - 1].relValue[j] = ch;
				j++;
			}		
			else
				(*oneEntry).clueList[clueChoice - 1].relValue[j] = '\0';
					
				
						
					
		}while(ch != '\n' || j == 0);
		//If the first char is not a letter, relation value entered is invalid
		if(!isLetter((*oneEntry).clueList[clueChoice - 1].relValue[0]))
				printf("\nInvalid input, first character must be in the alphabet, please enter again: ");
			
	}while(!isLetter((*oneEntry).clueList[clueChoice - 1].relValue[0]));
	
}

/*
	During the maintenance when the user wants to modify a relation of a certain word,
	this function replaces the current phrase relation with user's input.

	@param oneEntry - pointer that contains the address of the entry that has the clue the
					  user wants to modify.
	
	@param clueChoice - the number of the clue the user chose to modify.
	

*/
void 
getPhraseRelation(struct triviaTag * oneEntry, int clueChoice)
{
	
	int j;
	char ch;

	do
	{
		j = 0;
		do
		{			
			scanf("%c", &ch);
					
			if(ch != '\n') {

				(*oneEntry).clueList[clueChoice - 1].relation[j] = ch;
				j++;
			}		
			else
				(*oneEntry).clueList[clueChoice - 1].relation[j] = '\0';
					
				
						
					
		}while(ch != '\n' || j == 0);
		//If the first char is not a letter, relation entered is invalid
		if(!isLetter((*oneEntry).clueList[clueChoice - 1].relation[0]))
				printf("\nInvalid input, first character must be in the alphabet, please enter again: ");
			
	}while(!isLetter((*oneEntry).clueList[clueChoice - 1].relation[0]));
}

/*
	Returns 1 if ch is x, p or n in lowercase or uppercase. Returns 0 otherwise


	@param ch - the character (user input) being checked for validity.
 */
int 
isValidXPN(char ch)
{
	if(ch == 'P' || ch == 'X' || ch == 'N' || ch == 'p' || ch == 'x' || ch == 'n')
		return 1;
	else return 0;
}

/*
	Returns 1 if ch is x or p in lowercase or uppercase. Returns 0 otherwise


	@param ch - the character (user input) being checked for validity.
 */
int 
isValidXP(char ch)
{
	if(ch == 'P' || ch == 'X' || ch == 'p' || ch == 'x')
		return 1;
	else return 0;
}

/*
	Returns 1 if ch is x or n in lowercase or uppercase. Returns 0 otherwise


	@param ch - the character (user input) being checked for validity.
 */
int 
isValidXN(char ch)
{
	if(ch == 'X' || ch == 'N' || ch == 'x' || ch == 'n')
		return 1;
	else return 0;
}
/*
	This function takes input for the function viewWords(), checks for invalid input
	and returns the character the user inputs.


	@param i - the number that represents where the user is in the viewing of the array aEntries in viewWords().
	@param nElem - the amount of elements there are in aEntries, the array of trivia in the game.
 */
char 
inputViewWords(int i, int nElem)
{
	char ch, cDump;
	
	if (nElem == 1) {
		
		do
		{
			printf("\nThis is the only word in the game. Press [X] if you would like to exit: ");
			scanf("%c%c", &ch, &cDump);
			
		}while(!(ch == 'X' || ch == 'x'));
	
	} else if (i > 0 && i < nElem - 1) {
		
		do
		{
			printf("\nEnter [N] if you would like to view the next entry, and [P] to view the previous entry, and [X] to exit: ");
			scanf("%c%c", &ch, &cDump);
			
			
		}while(!isValidXPN(ch));
		
	} else if (i == 0) {
		
		do
		{		
			printf("\nEnter [N] if you would like to view the next entry, or [X] if you would like to exit: ");
			scanf("%c%c", &ch, &cDump);
			
		}while(!isValidXN(ch));	
	} else {
	
		
		do
		{		
			printf("\nThis is the last entry. Enter [P] if you would like to go to the previous entry, or [X] to exit: ");
			scanf("%c%c", &ch, &cDump);
			
		}while(!isValidXP(ch));	
	
	}
	
	return ch;
}



/* Implement the functions listed in trivia.h here. 
   Read through the comments to know what the function is
   supposed to accomplish.  Note that the function names
   may not exactly be performing the whole task indicated
   in the mp specs.  For example, some may not have the 
   getting of input be part of the function, instead it 
   could be somewhere else and was just passed to the 
   function as parameter.
   
   Provided below are examples of the comments before 
   each function.  
*/

/* Given the filename stored in fname, this function
   loads the entries of the text file and ADDS them to
   the array aEntries. The number of elements should be
   updated in pElem. For each trivia word in the file 
   that already exists in aEntries, the user is asked if 
   he wants to keep the one in the array or replace it 
   with the one from the text file.
 
   @param fname - the string filename, including the extension
   @param aEntries - the array of words with the corresponding clues
   @param pElem - the address where the number of elements are 
                  to be updated
*/
void
import(strWord fname, wordList aEntries, int * pElem)
{
	FILE *fp;
	int j;
	char ch;
	int index;
	int res = 1;
	char input;
	char cDump;
	int newlineCount;
	struct triviaTag tempTrivia;

	if((fp = fopen(fname, "rt")) == NULL) {
		fprintf(stderr, "ERROR: %s does not exist.\n", fname);
	}

	
	
	while(res != EOF && fp != NULL) {

		

		tempTrivia.numClues = 0;
		
		//skips the word before first colon, usually "Object:"
		do {

			fscanf(fp, "%c", &ch);

			

		}while(ch != ':');

		//After first colon, get phrase for answer
		j = 0;
		fscanf(fp, "%c", &ch); //catch the additional space after colon.

		do {
			fscanf(fp, "%c", &ch);

			if(ch != '\n') {
				tempTrivia.answer[j] = ch;
				j++;
			}
			else
				tempTrivia.answer[j] = '\0';
		}while(ch != '\n');

		//Checking of duplicates
		index = searchWord(tempTrivia.answer, aEntries, *pElem);
		if(index != -1) {

			fflush(stdin);

			do 
			{
				
				fprintf(stdout,"The word %s already exists in the entries. Would you like to replace the data for the word with the contents of the text file?\nEnter [Y] to overwrite the data and [N] to retain the data: ", tempTrivia.answer);
				fflush(stdin);
				fscanf(stdin, "%c%c", &input, &cDump);


			
			}while(!(input == 'Y' || input == 'y' || input == 'n' || input == 'N'));
		}

		/*GETTING OF CLUES*/

		//After newline, get phrase relation
		
		newlineCount = 0;

		do {
			if(newlineCount > 0)
				j = 1;
			else
				j = 0;

			newlineCount = 0;

			do {
				fscanf(fp, "%c", &ch);

				if(ch != ':') {
					tempTrivia.clueList[tempTrivia.numClues].relation[j] = ch;
					j++;
				}
				else
					tempTrivia.clueList[tempTrivia.numClues].relation[j] = '\0';
			}while(ch != ':');


			fscanf(fp, "%c", &ch); //catch additional space after colon

			//After colon and single space, get phrase relValue

			j = 0;
			do {
				fscanf(fp, "%c", &ch);

				if(ch != '\n') {
					tempTrivia.clueList[tempTrivia.numClues].relValue[j] = ch;
					j++;
				}
				else {
					tempTrivia.clueList[tempTrivia.numClues].relValue[j] = '\0';
					newlineCount++;
				}
			}while(ch != '\n');

			
			/*Counts amount of newlines. If its only 1, the next char is a phrase rel. 
			If it's two newlines, it can be the next word (word after next word, since "Object" should be skipped)
			 or EOF. 
			Assigns the first char of the next clue to proper string in list of clues. */

			do {

				res = fscanf(fp, "%c", &ch);
			
				if(ch == '\n')
					newlineCount++;
				else if(newlineCount == 1 && res != EOF)/*If it is not another newline, then ch contains the first letter of the next relation of the current word */
					tempTrivia.clueList[tempTrivia.numClues + 1].relation[0] = ch;
				
			}while(ch == '\n' && res != EOF);


			tempTrivia.numClues++;

		} while(newlineCount == 1);


		/*Overwrites entry if usere wishes to overwrite duplicate entry */
		if(index != -1) {

			if(input == 'Y' || input == 'y')
				aEntries[index] = tempTrivia;
			
		}
		else {
			
			aEntries[*pElem] = tempTrivia;
			++*pElem;
		}
		


		//To reuse temp, reinitialize all strings to null
		tempTrivia.answer[0] = '\0';

		for(j = 0; j < tempTrivia.numClues; j++) {
			tempTrivia.clueList[j].relation[0] = '\0';
			tempTrivia.clueList[j].relValue[0]= '\0';
		}

		

	
		
	
		//if((fscanf(fp, "%c", &ch)) == 0)
		//	bInput = 0;
		
		
		
	}

	fflush(stdin);

	fclose(fp);
	


	/*

	PSEUDO CODE
	1.) get the first word, which is the very first word after the first colon + space (skip "Object: "), 
	and  every after two newlines, the word after the first colon + space.

	2.) after every colon and 1 space (aside from the answer) is a relation value, after every single
		newline (only 1 newline) is a relation

	3.) do this until two newlines are encountered and a word is not present, in other words EOF
	*/

}

/* This function initializes the gameboard with nRows by
   nCols number of characters based on the contents of 
   aEntries.  The use member field is also updated to
   signify that this entry is already used in the board
   for the current game.  The function returns 1 if the
   board can be fully initialized with unique entries based
   on the needed dimension. Otherwise, the function returns 0.

   @param gameboard - 2D array of characters containing the
                      first letters of the answer
   @param nRows - the number rows to be initialized in gameboard
   @param nCols - the number columns to be initialized in gameboard
   @param aEntries - the array of words with the corresponding clues
   @param nElem - the number of elements in aEntries
   @return 1 if successful initialization of the gameboard, 0 otherwise
*/
int 
initBoard(arrMatrix gameboard, int nRows, int nCols,
              wordList aEntries, int nElem)
{
	int j;
	int i;
	int index;
	int aIndexUsed[CAP]; //array of used/already checked indices, used to check if a word has been checked already
	int nElemIU; //the amount of elements in aIndexUsed
	int FC[52]; 
	int bFound;
	int max;
	char prioCh;
	int prevMax[CAP];
	int nElemPrevMax = 0;
	int u = 0;
	
	
	int count, target_count;
	
	/*set seed of rand() to time so that its repeatedly getting reseeded, rand() used in getRandom() for
	random number generation within ranges*/
	srand(time(0));

	/*In case the gameboard was used before, cleans it of previous letters and symbols
	 so that it does not affect the new initialization */
	for(j = 0; j < nRows; j++) {
		for(i = 0; i < nCols; i++)
			gameboard[j][i] = '\0';
	}
	
	FrequencyCount(FC, aEntries, nElem);
	
	//for(j = 0; j < 52; j++)
	//	printf("Index %d: %d\n", j, FC[j]);
	
	count = 0;
	
	 
	
	target_count = nRows * nCols;
	
	/*Initializes the all entries as unused */
	for(j = 0; j < nElem; j++)
		aEntries[j].use = 0;
	
		nElemPrevMax = 0;
		
		u = 0;
		
		
	
		for(j = 0; j < nRows; j++) {
			
			max = findMax(FC, 52); //finds the character (starting letter of each word) that should be prioritized(has highest count)
			
			/*Converts index returned to max into a character */
			if(max >= 0 && max <= 25) {
					prioCh = max + 'A';
			}
			else
					prioCh = max + 71;
				
		
			
			for(i = 0; i < nCols; i++) {
				
				bFound = 0;
				nElemIU = 0;
			
				
				while(bFound == 0 && !isAllUsed(aEntries, nElem)) {
					
					//randomly generates a number within the range of aEntries that can possibly be the index of chosen word 
					//that will fill the spot
					index = getRandom(0, nElem - 1);
					
					if(aEntries[index].use == 0 && Search(gameboard[j], nCols, aEntries[index].answer[0]) == -1 && aEntries[index].answer[0] == prioCh) {
						
						gameboard[j][i] = aEntries[index].answer[0];
						aEntries[index].use = 1;
						count++;
						bFound = 1;
						FC[max] -= 1;
					}
					else if(SearchInt(aIndexUsed, nElemIU, index) == -1)           
					{
						/*Adds index to already checked indexes in aEntries if it is not already in the array */
						aIndexUsed[nElemIU] = index;
						nElemIU++;
					}
					
					
					/*If all possible unused entries have been checked and still can't find a word to fill the particular
					spot in the matrix, stop the loop and move on to next row or spot. Prevents infinite loop if
					game can not be initialized*/
					if(nElemIU == nElem)
							bFound = 1;
					
				}
				
				nElemPrevMax++;
				
				prevMax[u] = max;
				u++;
				max = findMaxPrev(FC, prevMax, 52, nElemPrevMax);
				
				//printf("max: (found with findMaxPrev) **%d**", max);
				
				if(max >= 0 && max <= 25) {
					prioCh = max + 'A';
				}
				else
					prioCh = max + 71;
				
				//printf("prio char: **%c**\n",prioCh );
				
			}
		}
	
	
	//PRINT CODE
	//printf("\n\nAFTER: \n");
	//for(j = 0; j < 52; j++)
	//	printf("Index %d: %d\n", j, FC[j]);
	
	
	if(count == target_count)
		return 1;
	else return 0;
	
	
}

/* This function facilitates the game play of the user,
   including determining when the game ends. 
   @param gameboard - the 2D array of characters
   @param nRows - the number of rows in gameboard
   @param nCols - the number of columns in gameboard
   @param aEntries - the array of words with the corresponding clues
   @param nElem - the number of elements in aEntries   
*/   
void 
play(arrMatrix gameboard, int nRows, int nCols,
          wordList aEntries, int nElem)
{
	int bOver = 0;
	char letterInput;
	char cDump;
	int currentrow = 0;
	int index;
	int bFound = 0;
	int clueIndex;
	int res;
	strWord playerAnswer;
	int bPlay = 1;
	char input;
	strWord fname;
	int test;
	
	do
	{
		while(bOver == 0 && letterInput != '0') {

			printf("\nYou may enter the number [0] if you wish to exit the game.\n");
			printGB(gameboard, nRows, nCols);

			fflush(stdin);

			/*Asks user to enter a letter until a valid letter is entered, a letter present in the row */
			do 
			{
				printf("\nPick a letter from row %d: \n", currentrow + 1);
				
				fscanf(stdin,"%c%c", &letterInput, &cDump);
			
				if(letterInput != '0')
					res = isValidLetter(letterInput, gameboard[currentrow], nCols);
				

				if(res == -1)
					printf("\nInvalid letter, please pick a letter from the specified row.\n");

				fflush(stdin);

			}while(res == -1 && letterInput != '0');


			/*Looks for a word that has the same starting letter as the chosen letter which is also in use for
			the current game */
			while(bFound == 0 && letterInput != '0') {
					
					index = getRandom(0, nElem - 1);
					if(aEntries[index].answer[0] == letterInput && aEntries[index].use == 1) {
						bFound = 1;
						aEntries[index].use = 0;


					}
			}

			if(letterInput != '0') {

				/*Randomly picks a clue within range of numCLues to display for the user */
				clueIndex = getRandom(0, aEntries[index].numClues - 1);

				printf("\nCLUE - %s: %s\n", aEntries[index].clueList[clueIndex].relation, aEntries[index].clueList[clueIndex].relValue);
				printf("What word do you think it is?\n");
				fflush(stdin);
				getPhraseWord(playerAnswer);

				if(strcmp(playerAnswer, aEntries[index].answer) == 0) {
					printf("\nCorrect!\n");
					
					gameboard[currentrow][res] = '*';

					currentrow++;

				} else {
					printf("\nWrong!\n");
					gameboard[currentrow][res] = '-';
				}
			}



			bFound = 0;
			
			bOver = IsOver(gameboard, nRows, nCols);

			
		}

		/*Reset amount of entries so that there won't be existing words when player decides to start
		a new game with a different text file and different set of words. */
		nElem = 0;
		
		if(bOver == 1) {
			printf("\nCongratulations, you won the game!\n");
			printGB(gameboard, nRows, nCols);
		} else if (bOver == -1) {
			printf("\nYou lost, better luck next time!\n");
			printGB(gameboard, nRows, nCols);
		}
		
		do
		{
			printf("\nWould you like to play again? [Y] or [N]:\n");
			scanf("%c%c", &input, &cDump);

		}while(!(input == 'y' || input == 'Y' || input == 'N' || input == 'n'));

		if(input == 'y' || input == 'Y') {

			bOver = 0;

			//So that the player can start another game after choosing to exit by pressing 0, letterInput takes 1 temporarily
			if(letterInput == '0')
				letterInput = '1';
			currentrow = 0;

			do
			{
				printf("How many rows for the board? ");
				scanf("%d", &nRows);
				printf("How many columns for the board? ");
				scanf("%d%c", &nCols, &cDump);
					
				printf("Enter filename for source of trivia: ");
				scanf("%s", fname);
				import(fname, aEntries, &nElem);
					
				test = initBoard(gameboard, nRows, nCols, aEntries, nElem);
				
				

			} while (test == 0 || !(nRows > 0 && nRows <= 10) ||
				         !(nCols > 0 && nCols <= 10));
			
			

		} else {
			bPlay = 0;

		}
	
	


	}while(bPlay == 1);

	fflush(stdin);
	
}

/* This function shows the menu options in the maintenance
   phase as well as call the functions (like listWords(), 
   addWord(), etc.) that are relevant to the chosen option.   
*/
void maintenance()
{
	wordList aEntries;
	strWord word;
	strWord filename; //CAN BE CHANGED, since strWord only has 21 chars

	int nElem = 0;
	int bRun = 1;
	int choice;
	char cDump;
	int res;
	
	while(bRun == 1) {
		
		printf("\n||Maintenance Phase||\n");
		printf("[0] Exit\n");
		printf("[1] Add Word \n");
		printf("[2] Add Trivia \n");
		printf("[3] Modify Entry \n");
		printf("[4] Delete Word\n");
		printf("[5] Delete Clue\n");
		printf("[6] View Words\n");
		printf("[7] View Clues\n");
		printf("[8] Export\n");
		printf("[9] Import\n");
		printf("\nPlease enter a number corresponding to the action you would like to do: ");
		scanf("%d%c", &choice, &cDump);
		
		switch(choice) {
			
			case 0:
			{
				bRun = 0;
				break;
			}
			case 1:
			{
				addWord(aEntries, &nElem);
				
				break;
				
			}
			case 2:
			{
				fprintf(stdout, "\nPlease enter the word you would like to add trivia to: ");
				getPhraseWord(word);

				res = searchWord(word, aEntries, nElem);

				if(res != -1) {
					addTrivia(&aEntries[res]);
				} else {
					fprintf(stdout,"\nUnable to add trivia since this word does not exist.\n");

				}

				
				break;
				
			}
			case 3:
			{
				printf("\nLIST OF ALL WORDS: \n");
				sortEntries(aEntries, nElem);
				listWords(aEntries, nElem);
				printf("\nPlease enter the word whose contents you would like to modify: ");
				getPhraseWord(word);

				res = searchWord(word, aEntries, nElem);
				if(res != -1) {
					modifyEntryChoice(&aEntries[res], aEntries, nElem);
				} else {
					printf("\nUnable to modify since the word does not exist.\n");
				}

				break;
			}
			case 4:
			{
				printf("\nLIST OF ALL WORDS: \n");
				sortEntries(aEntries, nElem);
				listWords(aEntries, nElem);

				deleteWord(aEntries, &nElem);


				break;
			}
			case 5:
			{
				printf("\nLIST OF ALL WORDS: \n");
				sortEntries(aEntries, nElem);
				listWords(aEntries, nElem);

				deleteClue(aEntries, nElem);
				break;

			}
			case 6:
			{
				sortEntries(aEntries, nElem);
				viewWords(aEntries, nElem);

				break;
			}
			case 7:
			{
				viewClues(aEntries, nElem);



				break;
			}
			case 8:
			{
				fprintf(stdout, "\nPlease enter the file name of the file you would like to export data to: ");
				fscanf(stdin, "%s", filename);
				export(filename, aEntries, nElem);

				break;
			}
			case 9:
			{
				fprintf(stdout, "\nPlease enter the file name of the file you would like to import data from: ");
				fscanf(stdin, "%s", filename);
				import(filename, aEntries, &nElem);

				break;

			}
			
			
			
			
			
			
			default: printf("Invalid number, please only pick numbers from 0 to 9.");
			
		}
		
	}
}

/* This function returns the index where the key was found
   in aEntries. If not found, the function returns -1.
   @param key - the word or phrase to look for
   @param aEntries - the array of words with the corresponding clues
   @param nElem - the number of elements in aEntries
   @return the index where key was found, -1 otherwise
*/
int 
searchWord(strWord key, wordList aEntries, int nElem)
{
	int j = 0;
	int index = -1;
	int bFound = 0;
	
	while(bFound == 0 && j < nElem) {
		if(strcmp(aEntries[j].answer, key) == 0) {
			bFound = 1;
			index = j;
			
		}
		j++;
	}
	
	return index;
}

/* This function displays the list of words (without the clues)
   in aEntries. 
   @param aEntries - the array of words with the corresponding clues
   @param nElem - the number of elements in aEntries
*/ 
void 
listWords(wordList aEntries, int nElem)
{
	
	
	int i;
	
	for(i = 0; i < nElem; i++)
		printf("%s\n", aEntries[i].answer);
}

/* This function will ask the user to input the word, calls
   searchWord() to check if the word is unique.  If unique, this
   word is added, the addTrivia() is called, and the
   number of elements is updated. Other error checking (as 
   indicated in the MP specs requirements) are also done.

   @param aEntries - the array of words with the corresponding clues
   @param pElem - the address where the number of elements are 
                  to be updated
*/
void 
addWord(wordList aEntries, int * pElem)
{
	strWord answer;
	int bValid;
	char ch, cDump;
	int bInput = 1;
	
	
	while(bInput == 1 && *pElem < CAP) {
		
		bValid = 1;
		printf("\nPlease enter the word you would like to add: ");
		getPhraseWord(answer);
		
		fflush(stdin);
		
		if(searchWord(answer, aEntries, *pElem) == -1) {
			strcpy(aEntries[*pElem].answer, answer);
			
			addTrivia(&aEntries[*pElem]);
			++*pElem;
		}
		else {
			printf("\nThe word already exists in the game, please enter another word. \n");
			bValid = 0;
		}
		
		if(bValid == 1 && *pElem < CAP) {
		
			do {
				printf("\nWould you like to enter another WORD? Please enter [Y] if yes and [N] if you would like to stop.\n");
				scanf("%c%c", &ch, &cDump);
				
				if(ch == 'n' || ch == 'N')
					bInput = 0;
				
			}while(!bIsYN(ch));
		}
		

		
		
	}
	
	if(*pElem == CAP)
			printf("\nYou have reached the max amount of words and can no longer add any more words.\n");
	
	
	
}



/* This function will ask the user for the relation and
   relation value as store it in the clueList member field
   in *oneEntry, as long as the array can still accommodate
   more data and as long as the user still wants to add
   more entries. If there are existing clues already, new
   entries are added (not overwritten). The member field
   numClues is also updated.

   @param oneEntry - address to the structure containing the
                     array of clues and the number of clues,
					 among other data
*/
void 
addTrivia(struct triviaTag * oneEntry)
{
	int j;
	int bInput = 1;
	char ch;
	char cDump; 

	
	while ((*oneEntry).numClues < MAX && bInput == 1) {
		
		printf("\nPlease enter the relation: ");
		
		do 
		{
			j = 0;
			
			do
			{
				scanf("%c", &ch);
				
				if(ch != '\n') {
					
					(*oneEntry).clueList[(*oneEntry).numClues].relation[j] = ch;
					j++;
				} 
				else
					(*oneEntry).clueList[(*oneEntry).numClues].relation[j] = '\0';
				
			
					
				
			}while(ch != '\n' || j == 0);

			/*If first char in string is not in the alphabet, string is invalid. */

			if(!isLetter((*oneEntry).clueList[(*oneEntry).numClues].relation[0]))
				printf("\nInvalid input, first character must be in the alphabet, please enter again: ");
			
			
		}while(!isLetter((*oneEntry).clueList[(*oneEntry).numClues].relation[0]));
		
		printf("\nPlease enter the relation value: ");
		
		do
		{
			j = 0;
			
			do
			{
				scanf("%c", &ch);
				
				if(ch != '\n') {
					(*oneEntry).clueList[(*oneEntry).numClues].relValue[j] = ch;
					j++;
				} 
				else
					(*oneEntry).clueList[(*oneEntry).numClues].relValue[j] = '\0';
				
					
				
			}while(ch != '\n' || j == 0);
			
			if(!isLetter((*oneEntry).clueList[(*oneEntry).numClues].relation[0]))
				printf("\nInvalid input, first character must be in the alphabet, please enter again: ");
			
		}while(!isLetter((*oneEntry).clueList[(*oneEntry).numClues].relation[0]));
		
		
		(*oneEntry).numClues++;
		
		
		if((*oneEntry).numClues < MAX) {
			
			do {
			printf("\nWould you like to enter another ENTRY for the word %s? Please enter [Y] if yes and [N] if you would like to stop.\n", (*oneEntry).answer);
			
			scanf("%c%c", &ch, &cDump);
			
			if(ch == 'n' || ch == 'N')
				bInput = 0;
			
			}while(!bIsYN(ch));
		}
		else {
			printf("\nYou have reached the max amount of clues.\n");
		}
	}
}

/* This function will ask the user for which part of the
   information in *oneEntry that will be modified (word or
   clue). The required input, including appropriate error
   checking as indicated in the specs, is done in this
   function.  The user is allowed to modify multiple parts
   of *oneEntry, until the user chooses to finish the 
   editing. For the clues, only modification can be done.
   That is, deletion or addition is not allowed here.

   @param oneEntry - address to the structure containing the
                     words, array of clues and the number of clues,
					 among other data
*/
void 
modifyEntry(struct triviaTag * oneEntry)
{
	int i, clueChoice;
	int choice;
	
	 
			
	printf("\nLIST OF CLUES: \n");
			
	for(i = 0; i < oneEntry->numClues; i++) {
				
		printf("[%d] %s: %s",i + 1,  oneEntry->clueList[i].relation,  oneEntry->clueList[i].relValue);
		printf("\n");
	}
			
	do
	{
		printf("\nPlease enter the number of the clue you would like to modify: ");
		scanf("%d", &choice);
	}while(!(choice >= 1 && choice <= oneEntry->numClues));
			
	clueChoice = choice;
				
	printf("\nWhich part of the clue would you like to modify?\n");
	printf("[1]Relation\n[2]Relation Value\n[3]Both Relation and Relation Value\n");
			
	printf("Please enter your choice: ");
			
	do
	{
		scanf("%d", &choice);
				
	}while(!(choice >= 1 && choice <= 3));
			
	switch(choice) {
		case 1:
		{
					
			printf("Please enter the new relation: ");
			getPhraseRelation(oneEntry, clueChoice);
			break;
					
		}
		case 2:
		{
			printf("Please enter the new relation value: ");
			getPhraseRelValue(oneEntry, clueChoice);
			break;
					
		}
				case 3:
		{
			printf("Please enter the new relation: ");
			getPhraseRelation(oneEntry, clueChoice);
					
			printf("Please enter the new relation value: ");
			getPhraseRelValue(oneEntry, clueChoice);
			break;
					
		}
	}
			
			
	
	
	
}



/* This function will ask the user to input the word (or phrase)
   that will be deleted.  Calls to other functions, like 
   searchWord(), as needed by the function, will be done.
   If deletion is successful (i.e., the word was found), the
   number of elements in pElem should also be updated.

   @param aEntries - the array of words with the corresponding clues
   @param pElem - the address where the number of elements are 
                  to be updated
*/
void 
deleteWord(wordList aEntries, int *pElem)
{
	int j;

	strWord rep;
	
	int res = -1;


	while(res == -1) {

		printf("Please enter the word that you wish to delete: ");

		getPhraseWord(rep);

		res = searchWord(rep, aEntries, *pElem);

		if(res == -1) {
			printf("\nThe word does not exist, please enter a word that is in the game.\n");

		}
	}

	--*pElem;

	for(j = res; j < *pElem ; j++) 
		aEntries[j] = aEntries[j + 1];
	
}




/* This function displays all information per element in aEntries.
   Part of the solution is to call the other function/s, like 
   viewEntry(), as needed by the function.
 
   @param aEntries - the array of words with the corresponding clues
   @param nElem - the number of elements in aEntries
*/
void 
viewWords(wordList aEntries, int nElem)
{
	int bView = 1;
	int i;
	char ch;
	
	
	i = 0;
	
	while(bView == 1 && nElem > 0) {
		
		printf("\nEntry #%d: ", i + 1);
		
		viewEntry(aEntries[i]);
		
		ch = inputViewWords(i, nElem);
		
		if(ch == 'X' || ch == 'x')
			bView = 0;
		else if (ch == 'N' || ch == 'n')
			i++;
		else 
			i--;
		
		
	}
	
	if(nElem == 0)
		printf("\nThere are no words to view, please import/enter some words to add to the game. \n");
}

/* This function displays all information in entry.
   Part of the solution is to call the other function/s, like 
   displayAllClues(), as needed by the function.
 
   @param entry - structure containing the word and the clues, 
                  among other data
*/
void
viewEntry(struct triviaTag entry)
{
	printf("WORD: %s\n", entry.answer);
	displayAllClues(entry.clueList, entry.numClues);
	
	
}

/* This function displays numClues number of elements from aList.

   @param aList - array of relation and relation values
   @param numClues - number of elements in aList
*/
void
displayAllClues(arrClues aList, int numClues)
{
	int i;
	
	printf("\nLIST OF CLUES: \n");
	for(i = 0; i < numClues; i++) {
		printf("[%d] %s: %s", i + 1, aList[i].relation, aList[i].relValue);
		printf("\n");
	}
}





/* Given the filename stored in fname, this function
   overwrites the contents of the text file with the contents 
   if the array aEntries. Contents of aEntries and nElem will 
   not change in this function.
 
   @param fname - the string filename, including the extension
   @param aEntries - the array of words with the corresponding clues
   @param nElem - the number of elements in aEntries
*/
void
export(strWord fname, wordList aEntries, int nElem)
{
	FILE* fp;
	int j;
	int i;

	fp = fopen(fname, "wt");

	for(j = 0; j < nElem; j++) {

		fprintf(fp, "Object: %s\n", aEntries[j].answer);

		for(i = 0; i < aEntries[j].numClues; i++) {
			fprintf(fp, "%s: %s\n", aEntries[j].clueList[i].relation, aEntries[j].clueList[i].relValue);
		}
		fprintf(fp, "\n");

	}

	fclose(fp);

	
}

/* This function sorts the contents of aEntries in increasing
   order (based on ASCII value). The solution to this function
   should be an IMPLEMENTATION of a sorting algorithm, NOT by
   calling a sort function from some C library.
   
   @param aEntries - the array of words with the corresponding clues
   @param nElem - the number of elements in aEntries
*/
void 
sortEntries(wordList aEntries, int nElem)
{
	int i;
	int j;
	int min;
	struct triviaTag tempTrivia;
	
	if(nElem > 0) {
		
		for(i = 0; i < nElem - 1; i++) {
			
			min = i;
			
			for(j = i + 1; j < nElem; j++) {
				
				
				
				if(strcmp(aEntries[min].answer, aEntries[j].answer) > 0) {
					
					min = j;
					
				}
				
			}
			
			tempTrivia = aEntries[i];
			aEntries[i] = aEntries[min];
			aEntries[min] = tempTrivia;
		}
	}
	
}
