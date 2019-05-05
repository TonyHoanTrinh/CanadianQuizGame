/************************trinhQuocA2.c **************
 Student Name: Quoc (Tony) Trinh 			Email Id: trinhq@uoguelph.ca
 Date: November 8th, 2018					Course Name: CIS 1500
 I have exclusive control over this submission via my password.
 By including this statement in this header comment, I certify that:
 1) I have read and understood the University policy on academic integrity;
 2) I have completed the Computing with Integrity Tutorial on Moodle; and
 3) I have achieved at least 80% in the Computing with Integrity Self Test.
 I assert that this work is my own. I have appropriately acknowledged any and all material (data, images, ideas or words) that I have used,
 whether directly quoted or paraphrased.
 Furthermore, I certify that this assignment was prepared by me specifically for this course.
 ***********************************************************/


/**********************************************************
   Compiling the program
 *********************************************************
 The program should be compiled using the following flags:
 -std=c99
 -Wall
 compiling: gcc trinhQuocA2.c -std=c99 -Wall -o trinhQuocA2
 **********************************************************
 Running the Program
 **********************************************************
 running: ./trinhQuocA2
 The user is prompted for inputs of A,B,C and D for answering questions and Y,y,N and n for the lifeline options
 **********************************************************/

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_QUESTIONS 7

//function prototypes

void promptPlayerForName (char [50]);
void printWelcomeMessage (char  [50]);
int  calculateCurrentAward (int ,int);
void popUpCurrentQuestion4choices (int);
char askPlayerForLifeLine (void);
void popUpCurrentQuestion2choices (int);
char acceptPlayersFinalAnswer (void);
bool isCorrectFinalAnswer (char, int, char [MAX_QUESTIONS]);
void generateRandomGreeting (char [20]);
int calculateReducedAward (int, int);

int main(){

    char allCorrectAnswers [MAX_QUESTIONS + 1] = "CBCBACA";   // for my set of questions
    char greet [20];
    char nameForGame[50];
    int lifeLineUsed = 0; 
    int questionNumber = 1;
    char playersResponseLifeLine;
    char finalAnswer;
    int currentAwardAmount ;
    int reducedAmount;
    
    promptPlayerForName(nameForGame);
	
    printWelcomeMessage(nameForGame);
	
    while (questionNumber <= MAX_QUESTIONS)
    {
	
        currentAwardAmount = calculateCurrentAward(questionNumber, currentAwardAmount);
		
	popUpCurrentQuestion4choices(currentAwardAmount);
	
	if (lifeLineUsed == 0)
        {
	    playersResponseLifeLine = askPlayerForLifeLine();
		
	    if (playersResponseLifeLine == 'Y' || playersResponseLifeLine == 'y')
            {
		
	        popUpCurrentQuestion2choices(currentAwardAmount);
		lifeLineUsed ++; 
		printf("\nReminder - You get only 1 50-50 lifeline - and you are using it now \n\n");
	    }
	}
		
	finalAnswer = acceptPlayersFinalAnswer ();
		
	if (isCorrectFinalAnswer (finalAnswer, questionNumber, allCorrectAnswers) )
        {
		
	    generateRandomGreeting(greet);
	    printf("%s - You just won $ %d\n", greet, currentAwardAmount);
			
	    if (questionNumber < MAX_QUESTIONS)
            {
	        printf("Let us play the next question now\n\n"); 
	    }
	}
		
	else
	{
	    printf  ("Oops - that was incorrect.");
            
            reducedAmount = calculateReducedAward (questionNumber, currentAwardAmount);

	    printf("You still won $%d. Well done.\n\n", reducedAmount);
			
            questionNumber = MAX_QUESTIONS;
	}
    questionNumber ++;
    }
	
    printf("It was fun playing with you \n\n");
	
    return 0;

}	

/******
 promptPlayerForName: Asks user for their name and stores it in a string called fullName
 In: char fullName[50]
 Out: None
 Post: The fullName string is modified and used in the printWelcomeMessage function
*******/
void promptPlayerForName (char fullName[50])
{
    // Creates 2 string variables, 1 for the user's first name and 1 for the last name
    char firstName[20];
    char lastName[20];
    
    // Following statements asks and prompts user for their first and last name
    printf("Enter your first name: ");
    scanf("%s", firstName);
    printf("Enter your last name: ");
    scanf("%s", lastName);

    // Using strcat to add the firstName, a space and lastName into the fullName string variable
    strcat(fullName, firstName);
    strcat(fullName, " ");
    strcat(fullName, lastName);

    return;
}

/******
 printWelcomeMessage: Takes in the fullName string to display a welcome message to the game with asterisks as decorations
 In: char fullName[50]
 Out: None
 Post: Prints the welcome message with the user's full name with asterisks decoration
*******/
void printWelcomeMessage (char fullName[50])
{
    // Creates 2 counter variables called i and j to be used for looping
    int i;
    int j;

    // For loop to print the 1st 3 lines of the asterisks
    // i starts at 1 as the 1st line of asterisks has 1 asterisk, each iteration increases i by 1 and will print i number of asterisks
    for(i = 1; i < 4; i++)
    {
      // For loop which prints the asterisks themselves
      // Condition is based on the pattern of 1,2 and 3 asterisk for the respective rows
        for(j = i; j > 0; j--)
        {
	    // Prints the asterisks
            printf("*");
        }
	// Prints a newline for the next line of asterisks and iteration
        printf("\n");
    }

    // For loop to print asterisks equal to the length of the user's name + 8 for the line before welcoming
    for (i = 0; i < strlen(fullName) + 8; i++)
    {
        // Prints the asterisks
	printf("*");
    }
    
    printf("\n");
    // Following printfs, welcomes the user to the game and prints out their full name
    printf("Welcome %s\n", fullName);
    printf("Let us play WYDM!\n");

    // For loop to print asterisks equal to the length of the user's name + 8 for the line after welcoming
    for (i = 0; i < strlen(fullName) + 8; i++)
    {
        // Prints the asterisks
	printf("*");
    }
   
    printf("\n");
    // For loop to print the last 3 lines of asterisks
    // Loop starts at 3 as the 1st line will have 3 asterisks and i gets reduced by 1 for each iteration
    for (i = 3; i > 0; i--)
    {
        // For loop, startin at the current value of i to print the asterisks based on the current value of i
	for(j = i; j > 0; j--)
	{
	    // Prints the asterisks 
	    printf("*");
	}
	printf("\n");
    }

    return;
}

/******
 calculateCurrentAward: Calculates the current award amount for the current question the user is on
 In: int questionNumber, int awardPreviousQuestion
 Out: int 
 Post: Current award amount is calculated and returned back to main to be used in other functions
*******/
int  calculateCurrentAward (int questionNumber ,int awardPreviousQuestion)
{
    // Creates the currentAward variable to hold the amount that the current question awards
    int currentAward;

    // If the question number is 1
    if(questionNumber == 1)
    {
        // Sets the value of currentAward as 100 
        currentAward = 100;
    }
    // Checks if the question number is odd by using the modulus function and seeing if the remainder is not 0 or not
    // Using mod 2, if the answer is not equal to 0 then the question number is odd
    else if((questionNumber % 2) != 0)
    {
        // Sets the currentAward as equal to twice the award amount of the previous question
        currentAward = 2 * awardPreviousQuestion;
    }
    // Checks for the else statement
    // The only way situations that go into the else statement is when the question number is not 1 or odd
    // Therefore the even numbered questions go into this condition
    else
    {
        // Sets the currentAward as equal to 5 times the award amount of the previous question
        currentAward = 5 * awardPreviousQuestion;
    }

    // Returns the currentAward variable back to the main function to be used
    return currentAward;
}

/******
 popUpCurrentQuestion4choices: Pops up the 4 choices for the current question
 In: int currentAwardAmount
 Out: None
 Post: The 4 choices will be popped up for the current question for the user to decide on their answer
*******/
void popUpCurrentQuestion4choices (int currentAwardAmount)
{
    printf("\n");
    printf("Here is the $ %d question:", currentAwardAmount);
    printf("\n");
    // If the currentAwardAmount is equal to 100 which is the 1st Question it will go into this condition
    if (currentAwardAmount == 100)
    {
        printf("\n");
	printf("1. Which of the following programming language is taught in CIS1500 at the University of Guelph?\n");
        printf("A. Python \t \t B. Cobra \n");
	printf("C. C \t \t \t D. Java\n");
    }
    // If the currentAwardAmount is equal to 500 which is the 2nd question it will go into this condition
    else if (currentAwardAmount == 500)
    {
        printf("\n");
	printf("2. Which Canadian chain first opened in Hamilton in 1964?\n");
        printf("A. McDonalds \t \t \t B. Tim Hortons\n");
	printf("C. Wendys \t \t \t D. Mr. Sub\n");
    }
    // If the currentAwardAmount is equal to 1000 which is the 3rd question it will go into this condition
    else if (currentAwardAmount == 1000)
    {
        printf("\n");
	printf("3. What is Canada's national sport?\n");
        printf("A. Hockey \t \t \t \t B. Lacrosse\n");
	printf("C. Hockey and Lacrosse \t \t \t D. Baseball\n");
    }
    // If the currentAwardAmount is equal to 5000 which is the 4th question it will go into this condition
    else if (currentAwardAmount == 5000)
    {
        printf("\n");
	printf("4. Which Canadian city ranks as the most educated in the country?\n");
        printf("A. Montreal \t \t \t B. Ottawa\n");
	printf("C. Vancouver \t \t \t D. Toronto\n");
    }
    // If the currentAwardAmount is equal to 10000 which is the 5th question it will go into this condition 
    else if (currentAwardAmount == 10000)
    {
        printf("\n");
	printf("5. What is Canada's highest mountain?\n");
        printf("A. Mount Logan, Yukon  \t \t \t \t B. Whistler Mountain, BC\n");
	printf("C. Mont Tremblant, Quebec \t \t \t D. Tip Top Mountain, Ontario\n");
    }
    // If the currentAwardAmount is equal to 50000 which is the 6th question it will go into this condition
    else if (currentAwardAmount == 50000)
    {
        printf("\n");
	printf("6. What is the easternmost province of Canada?\n");
	printf("A. Ontario \t \t \t \t B. Prince Edward Island\n");
        printf("C. Newfoundland \t \t \t D. Nova Scotia\n");
    }
    // If the currentAwardAmount is equal to 100000 which is the 7th question it will go into this condition
    else if (currentAwardAmount == 100000)
    {
        printf("\n");
	printf("7. The southernmost point of mainland Canada is called Point Pelee. What province is it in?\n");
        printf("A. Ontario \t \t \t \t B. Quebec\n");
	printf("C. Newfoundland \t \t \t D. Nova Scotia\n");
    }

    printf("\n");

    return;
}

/******
 askPlayerForLifeLine: Asks the user if they want to use their lifeline option or not
 In: None
 Out: char
 Post: The user's will submit their answer to the lifeline option as yes or no which gets returned to main to be used
*******/
char askPlayerForLifeLine (void)
{
    // Creates the userAnswerForLine variable which will hold the user's answer if they want to use lifeline or not
    char userAnswerForLifeLine;

    // Creates a bool variable to check if the user choose yes or no to the lifeline option
    bool checksIfComplete;
    // Initially sets the checksIfComplete as false to be able to use it in the do-while loop
    checksIfComplete = false;

    // Asks user if they would like to use the lifeline or not
    printf("Would you like to use a lifeline (50-50)?\n");

    // Do-While loop which will run at least once to ensure to get the user's response to the lifeline question
    do
    {
        // Asks user if they want to use the lifeline or not and gets their response
        printf("Enter Y or y, N or n: ");
        scanf(" %c", &userAnswerForLifeLine);
	
	// 1st Condition which goes through if the user has entered in a valid answer of either 'Y' or 'y' for yes or 'N' or 'n' for no
        if (userAnswerForLifeLine == 'Y' || userAnswerForLifeLine == 'y' || userAnswerForLifeLine == 'N' || userAnswerForLifeLine == 'n')
        {
	    // Sets the bool checksIfComplete to true to get out of the Do-While Loop
	    printf("\n");
            checksIfComplete = true;
        }
	// 2nd Condition which goes through if the user has entered an invalid answer that is not 'Y', 'y', 'N' or 'n'
        else
        {
	    // Tells the user that they entered an invalid option
	    // The loop will continue until they enter in a valid response
            printf("Invalid option entered\n");
        }
    }
    while (checksIfComplete != true);
    // Condition for the Do-While which is while the checksIfComplete is not true

    // Returns the userAnswerForLifeLine back to the main
    return userAnswerForLifeLine;
}

/******
 popUpCurrentQuestion2choices: Pops up 2 choices for the user based on their current question. This function runs when they say yes to lifeline
 In: int currentAwardAmount
 Out: None
 Post: Pops up the 2 choices for user which they can see and decide on their response
*******/
void popUpCurrentQuestion2choices (int currentAwardAmount)
{
    printf("OK - here are your 2 choices after using the 50-50 lifeline\n");
  
    // If the currentAwardAmount is equal to 100 which is the 1st question it will go into this condition 
    if (currentAwardAmount == 100)
    {
        printf("\n");
        printf("A. Python \nC. C\n");
    }
    // If the currentAwardAmount is equal to 500 which is the 2nd question it will go into this condition
    else if (currentAwardAmount == 500)
    {
        printf("\n");
        printf("A. McDonalds \nB. Tim Hortons\n");
    }
    // If the currentAwardAmount is equal to 1000 which is the 3rd question it will go into this condition
    else if (currentAwardAmount == 1000)
    {
        printf("\n");
        printf("A. Hockey \nC. Hockey and Lacrosse\n");
    }
    // If the currentAwardAmount is equal to 5000 which is the 4th question it will go into this condition
    else if (currentAwardAmount == 5000)
    {
        printf("\n");
        printf("A. Montreal \nB. Ottawa\n");
    }
    // If the currentAwardAmount is equal is 10000 which is the 5th question it will go into this condition
    else if (currentAwardAmount == 10000)
    {
        printf("\n");
        printf("A. Mount Logan, Yukon  \nB. Whistler Mountain, BC\n");
    }
    // If the currentAwardAmount is equal to 50000 which is the 6th question it will go into this condition
    else if (currentAwardAmount == 50000)
    {
        printf("\n");
        printf("C. Newfoundland \nD. Nova Scotia\n");
    }
    // If the currentAwardAmount is equal to 100000 which is the the 7th question it will go into this condition
    else if (currentAwardAmount == 100000)
    {
        printf("\n");
        printf("A. Ontario \nB. Quebec\n");
    }

    printf("\n");

    return;
}

/******
 acceptPlayersFinalAnswer: Takes the user's answer to the current question 
 Int: None
 Out: char
 Post: The user's answer gets returned back to main and used in the isCorrectFinalAnswer to check if the answer is correct or not
*******/
char acceptPlayersFinalAnswer (void)
{
    // Creates a variable called userAnswer to hold the user's final answer
    char userAnswer;

    // Do-While loop that runs to get the user's answer to the question
    do
    {
        // Asks user for their final answer to the question as either "A", "B", "C" or "D"
        printf("Enter your FINAL ANSWER (‘A’, ‘B’, ‘C’ OR ‘D’) here:");
	// Gets the user's final answer 
        scanf(" %c", &userAnswer);
    }
    while (userAnswer != 'A' && userAnswer != 'B' && userAnswer != 'C' && userAnswer != 'D');
    // The Do-While Loop which runs while the userAnswer is not any of A,B,C or D

    printf("\n");
    // Returns the userAnswer back to main to be used in future evaluations such as the isCorrectFinalAnswer function
    return userAnswer;
}

/******
 isCorrectFinalAnswer: Checks the user's answer and the answerkey of the current question to see if they are correct or not
 In: char finalAnswer, int questionNumber, char allCorrectAnswers[MAX_QUESTIONS]
 Out: bool
 Post: The function returns the bool which tells if the answer was correct or not back to main to be used in future evaluations
*******/
bool isCorrectFinalAnswer (char finalAnswer, int questionNumber, char allCorrectAnswers[MAX_QUESTIONS])
{
    // Creates a variable called correctAnswer to hold the correct answer of the current question to be used in evaluations
    char correctAnswer;
    // Sets the correctAnswer to the index of the current question number of the allCorrectAnswers array
    // The -1 is needed as the array indexes start at 0 which makes the -1 neccessary to be at the correct index
    correctAnswer = allCorrectAnswers[questionNumber - 1];

    // 1st Condition which is when the user's final answer is the same as the correctAnswer
    if(finalAnswer == correctAnswer)
    {
        // Returns true back to main to say that the user's answer was correct for the question
        return true;
    }
    // 2nd Condition which is else when the user's answer is not correct which means the finalAnswer is not equal to the correctAnswer
    else
    {
        // Returns false back to main to say that the user's answer was incorrect for the question
        return false;
    }
}

/******
 generateRandomGreeting: Generates a number from 1 to 5 and creates a greeting message based on the random number
 In: char greet[20]
 Out: None
 Post: The greet string variable gets a greeting assigned to itself to be used in main 
*******/
void generateRandomGreeting (char greet[20])
{
    // Creates a variable called random to hold the randomly generated number
    int random;
    
    // Uses the rand() function with mod 5 to get a number between 0 to 4
    // The +1 causes the range to be pushed by 1 so the range now becomes 1 to 5 which is the desired range
    random = (rand() % 5) + 1;
    
    // Switch condition to evaluate the result of the randomly generated number
    // strcpy used to assign the greet string variable as 1 of the 5 random greetings
    switch (random)
    {
    case 1:
        strcpy(greet, "Bravo");
        break;
	    
    case 2:
        strcpy(greet, "Congrats");
        break;
	    
    case 3:
        strcpy(greet, "Well done");
        break;
	    
    case 4:
        strcpy(greet, "Very nice");
        break;
	    
    case 5:
        strcpy(greet, "Proud of you");
        break;
	    
    // Condition when the random number is not 1 to 5.
    // This condition can never ever be reached and is impossible however was written anyways as switch statements require a default always
    default:
        printf("This case will never be reached\n");
    }

    return;
}
/******
 calculateReducedAward: Calculates the reduced award amount when the user gets the answer wrong
 In: int questionNumber, int currentAwardAmount
 Out: int
 Post: The reduced award amount gets calculated and then returned back to main to be displayed as the game over message
*******/
int calculateReducedAward (int questionNumber, int currentAwardAmount)
{
    // Creates a variable called currentAward to hold the amount that the current award for the question is valued at
    int currentAward;

    // 1st condition checks if the question number is odd by checking that mod 2 gives a non zero answer
    if((questionNumber % 2) != 0)
    {
        // Sets the currentAward amount to be equal to half of the currentAwardAmount
        currentAward = 0.5 * currentAwardAmount;
	/*Note: If the user gets the 1st question wrong they will still get $50
	  Talking with Dr. Chaturvedi she said that it was fine for the user to get either $0 or $50 if they get the 1st question wrong
	  In this case for my program I made it so the user still got $50 when they get the 1st question wrong*/
    }
    // 2nd condition of else will only be met if the question number is even
    else
    {
      // Sets the currentAward amount to be equal to be reduced to 1/5 of the currentAwardAmount
      // Reduced to 1/5 is equivalent to multiplying the currentAwardAmount by 0.2 which is done here
      /*Note: Talking to Dr. Chaturvedi on the Assignment2.pdf it says "reduced by 1/5"
        But when asking her personally she said that she meant "reduced to 1/5" which is reflected here in the program
        She said to make a comment in the code to clarify when the TA is marking*/
        currentAward = 0.2 * currentAwardAmount;
    }

    // Returns the currentAward back to the main 
    return currentAward;
}

