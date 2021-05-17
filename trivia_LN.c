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

//MAKE FUNC SPECS FOR THIS
void getPhraseWord(strWord answer) {
	
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
void 
FrequencyCount(int FC[], wordList aEntries, int n)
{
	/* Declare your own local variables.  Implement the body of this function. */
	int j;
	int i;	
	int index;
	
	for(i = 0; i < 52; i++)
		FC[i] = 0;

	for(j = 0; j < n; j++) {
		
		if(aEntries[j].answer[0] >= 'A' && aEntries[j].answer[0] <= 'Z')
			index = aEntries[j].answer[0] - 'A';
		else
			index = aEntries[j].answer[0] - 71;
		
		FC[index] = FC[index] + 1;
	}
	


		

			//index = List[j][i] - 'A';
			//FC[index] = FC[index] + 1;


}
//MAKE FUNCTION SPECS FOR THIS
int isAllUsed(wordList aEntries, int nElem) {
	
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
 Description: generates random number within a range inclusive of the upper and lower limits
 			  this function also utilizes rand() which is constantly getting reseeded to time
 			  in main() which makes the number generated by rand() more random

 Parameters:
 	int nLower	the lower limit of the range of values
 	int nUpper	the upper limit of the range of values
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
//MAKE FUNC SPECS FOR THIS!
int findMax(int A[], int n)
{
	int j;
	int max = 0;
	
	for(j = 1; j < n; j++) {
		
		if(A[j] > A[max] && A[j] != 0)
			max = j;
	}
	
	return max;
}

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
//MAKE FUNC SPECS
int bIsYN(char c)
{
	if(c == 'Y' || c == 'N' || c == 'n' || c == 'y')
		return 1;
	else return 0;
}
//FUNC SPECS
int findMaxPrev(int A[], int prevMax[], int n, int nElemPrevMax)
{
	int j;
	int max = 0;
	
	
	
	for(j = 1; j < n; j++) {
		
		if(A[j] > A[max] && SearchInt(prevMax, nElemPrevMax, j) == -1 && A[j] > 0)
			max = j;
		
	}
	
	//If the code above stops working since all remaining letters have a count of 1, this is used
	if(A[max] == 0) {
		
		for(j = 1; j < n; j++) {
		
			if(A[j] == 1 && A[j] > 0)
				max = j;
		
		}
	}
	
	
	return max;
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

	
	
	while(res != EOF) {

		

		tempTrivia.numClues = 0;
		
		//SKIP THE WORD BEFORE FIRST COLON
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

			do 
			{
				fprintf(stdout,"The word %s already exists in the entries. Would you like to replace the data for the word with the contents of the text file?\nEnter [Y] to overwrite the data and [N] to retain the data: ", tempTrivia.answer);

				fscanf(stdin, "%c%c", &input, &cDump);


			
			}while(!(input == 'Y' || input == 'y' || input == 'n' || input == 'N'));
		}
		//GETTING OF CLUES 
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
			If it's two newlines, it can be the next word or EOF. Assigns the first char
			of the next clue to proper string in list. */
			do {

				res = fscanf(fp, "%c", &ch);
			
				if(ch == '\n')
					newlineCount++;
				else if(newlineCount == 1 && res != EOF)/*If it is not another newline, then ch contains the first letter of the next relation of the current word */
					tempTrivia.clueList[tempTrivia.numClues + 1].relation[0] = ch;
				
			}while(ch == '\n' && res != EOF);

			//printf("\n%d %s: %s\n",tempTrivia.numClues, tempTrivia.clueList[tempTrivia.numClues].relation,tempTrivia.clueList[tempTrivia.numClues].relValue);
			
			//printf("newline count: %d\n", newlineCount);

			//fprintf(stdout, "res: %d\n", res);
			
			
			//printf("\n%c", tempTrivia.clueList[tempTrivia.numClues + 1].relation[0]);

			tempTrivia.numClues++;

		} while(newlineCount == 1);

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

	fclose(fp);


	/*

	PSEUDO CODE
	1.) get the first word, which is the very first word after the first colon + space, and  every
	after two newlines, the word after the first colon + space.

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
			
			max = findMax(FC, 52); //finds the character(starting letter of each word) that should be prioritized(has highest count)
			
			/*Converts index returned to max into a character */
			if(max >= 0 && max <= 25) {
					prioCh = max + 'A';
			}
			else
					prioCh = max + 71;
				
			//printf("prio char: **%c**\n",prioCh );
			
			for(i = 0; i < nCols; i++) {
				
				bFound = 0;
				nElemIU = 0;
			//printf("\n*****%c**\n", prioCh);
				
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
					
					
					/*If all possible unused entries have been checked and still can't find a wordto fill the particular
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
	
	while(bOver == 0) {
		
		
		
		bOver = IsOver(gameboard, nRows, nCols);
	}
	
}

/* This function shows the menu options in the maintenance
   phase as well as call the functions (like listWords(), 
   addWord(), etc.) that are relevant to the chosen option.   
*/
void maintenance()
{
	int bRun = 1;
	int choice;
	
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
		scanf("%d", &choice);
		
		switch(choice) {
			
			case 0:
			{
				bRun = 0;
				break;
			}
			case 1:
			{
				
				break;
				
			}
			case 2:
			{
				
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
	
	//THIS MAYBE NEEDS TO BE ALPHABETIZED, maybe make a separate function fior that
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
void getPhraseRelValue(struct triviaTag * oneEntry, int clueChoice)
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
		
		if(!isLetter((*oneEntry).clueList[clueChoice - 1].relValue[0]))
				printf("\nInvalid input, first character must be in the alphabet, please enter again: ");
			
	}while(!isLetter((*oneEntry).clueList[clueChoice - 1].relValue[0]));
	
}
/*
	MAKE FUNC SPECS

*/
void getPhraseRelation(struct triviaTag * oneEntry, int clueChoice)
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
		
		if(!isLetter((*oneEntry).clueList[clueChoice - 1].relation[0]))
				printf("\nInvalid input, first character must be in the alphabet, please enter again: ");
			
	}while(!isLetter((*oneEntry).clueList[clueChoice - 1].relation[0]));
}
//MY OWN FUNCS, put it up there maybe after


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

//MAKE FUNC SPECS
void modifyEntryChoice(struct triviaTag * oneEntry, wordList aEntries, int nElem) {
	
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



int isValidXPN(char ch)
{
	if(ch == 'P' || ch == 'X' || ch == 'N')
		return 1;
	else return 0;
}
int isValidXP(char ch)
{
	if(ch == 'P' || ch == 'X')
		return 1;
	else return 0;
}
int isValidXN(char ch)
{
	if(ch == 'X' || ch == 'N')
		return 1;
	else return 0;
}
char inputViewWords(int i, int nElem)
{
	char ch, cDump;
	
	if (nElem == 1) {
		
		do
		{
			printf("\nThis is the only word in the game. Press [X] if you would like to exit: ");
			scanf("%c%c", &ch, &cDump);
			
		}while(ch != 'X');
	
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
		
		if(ch == 'X')
			bView = 0;
		else if (ch == 'N')
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

/* 
		MAKE FUNC SPECS FOR THIS
		

*/
void viewClues(wordList aEntries, int nElem)
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

/*Make func specs */
void 
deleteClue(wordList aEntries, int nElem)
{
	int res = -1;
	int choice, j;
	strWord word;

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
	strWord temp;
	
	if(nElem > 0) {
		
		for(i = 0; i < nElem - 1; i++) {
			
			min = i;
			
			for(j = i + 1; j < nElem; j++) {
				
				
				
				if(strcmp(aEntries[min].answer, aEntries[j].answer) > 0) {
					
					min = j;
					
				}
				
			}
			
			strcpy(temp, aEntries[i].answer);
			strcpy(aEntries[i].answer, aEntries[min].answer);
			strcpy(aEntries[min].answer, temp);
		}
	}
	
}
