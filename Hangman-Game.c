#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
	
	printf("\e[1mHangman Game\e[0m\n");
	
	// To have random numbers based on time
	srand(time(NULL));
	
	char guessWords[][16] = {
		"green",
		"yellow",
		"purple",
		"windows",
		"linux",
		"apple"
	};
	
	// index for random word
	int randomIndex = rand() % 6; // divides random num by 6 and the remainder is 0
	// Random number picker logic
//	int fullrand = 0;
//	for(int i = 0; i < 10; i++){
//		fullrand= rand();
//		randomIndex = fullrand % 6;
//		printf("%d -> %d\n", fullrand, randomIndex);
//	}

	int numLives = 6;
	int numCorrect = 0;
	int oldCorrect = 0; 
	
	int lengthWord = strlen(guessWords[randomIndex]);
	
	// How this works: if purple (it will loop to search then make 1
	//                       0 1 2 3 4 5
	//                       p u r p l e
	//	letterGuessed[10] = {1,0,1,0,0,0,0,0,0,0};
	int letterGuessed[10] = {0,0,0,0,0,0,0,0,0,0};
	
	int quit = 0;
	
	char guess[16];
	char letterEntered;
	
	printf("Guess Words: %s, Random Index: %d, Length of Word: %d\n", guessWords[randomIndex], randomIndex, lengthWord);
	
	// Game will keep running while number of letters guessed correctly is less than the length of the word
	while(numCorrect < lengthWord){
	
		printf("\nNew Turn...\nHangman Word:");
		for(int i = 0; i < lengthWord; i++){
			if(letterGuessed[i] == 1){
				printf("\e[1m%c\e[0m", guessWords[randomIndex][i]);
			} else {
				printf("-");
			}
		}
		
		printf("\n");
		
		printf("Number correct so far: %d\n", numCorrect);
		printf("\nEnter a guess letter (Will take the first letter of input): ");
		fgets(guess, 16, stdin);
		
		for(int i = 0; i < 16; i++){
			guess[i] = tolower(guess[i]);
		}

		if(strncmp(guess, "quit", 4) == 0){
			quit = 1;
			break; 
		}
		
		letterEntered = guess[0];
		printf("Letter Guessed: %c\n", letterEntered);
		
		oldCorrect = numCorrect;
		
		for(int i = 0; i < lengthWord; i++){
			//To prevent the program from ending after reaching lengthWord and haven't guessed correctly yet
			if(letterGuessed[i] == 1){
				continue; // To go around the next index
			}
			
			if(letterEntered == guessWords[randomIndex][i]){
				letterGuessed[i] =  1;
				numCorrect++;
			}
		}
		
		// Lose a life
		if(oldCorrect == numCorrect){ // We didn't get any letters
			numLives--;
			printf("Sorry wrong guess. Lives: %d\n", numLives);
			if(numLives== 0){
				break;
			}
		} else {
			printf("Correct Guess!\n");	
		}	
	} // while loop
	
	if(quit == 1){
		printf("The user has quit early\n");
	} else if (numLives == 0){
		printf("You're dead! The word was <%s>\n", guessWords[randomIndex]);
	} else {
		printf("\nYOU WIN!\n");
	}
		
	return 0;
}
