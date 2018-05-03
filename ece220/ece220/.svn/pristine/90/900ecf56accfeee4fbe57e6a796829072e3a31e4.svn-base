/*
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

 //Intro Paragraph!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 //For MP5, our goal is to implement three functions to realize the functions of the code breaker.
 //These functions form a hierarchy on top of each other. And they all play important roles during
 //the function call process occuring inside main.c .int set_seed (const char seed_str[]) is the first
 //function. As the name suggests, the user will set a seed values which determines the four solutions.
 //The second function is to create four solutions as specified by the set_seed function's seed value.
 //The third function is to check if user's values entered are valid or not. In addition, a standard format
 //of feedback will be given back to the user.



#include <stdio.h>
#include <stdlib.h>
#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;//Define five static variables here. Use static because we need to access
static int solution1;   //these variables inside the following functions. If we don't use static,
static int solution2;   //compilation errors will throw up because these variables won't be found
static int solution3;   //inside the following functions.
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[])
{

    int seed;//Set variables for storing seed value and post characters for sscanf
    char post[2];

    if (sscanf(seed_str, "%d%1s", &seed, post)==0)//Check if return value of sscanf is 0
    {
      //Wrong Case: The case when no items are read
      printf("set_seed: invalid seed\n");
      return 0;
    }

    else if(sscanf(seed_str, "%d%1s", &seed, post)==1)//Check is return value of sscanf is 1
    {
      //Correct case: When a single integer was read
      srand(seed);
      return 1;
    }

    else //check if return value of sscanf is 2
    {
      //Wrong Case: The case when no items are read
      printf("set_seed: invalid seed\n");
      return 0;
    }
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game (int* one, int* two, int* three, int* four)
{
    //your code here
    *one = rand() % 8 + 1;//Here, we generate the four solutions based on the seed values set by set_seed function.
    *two = rand() % 8 + 1;//We use the method of modulus 8 and plus 1 so that the range of the solution is 1 <= x <= 8
    *three = rand() % 8 + 1;
    *four = rand() % 8 + 1;

    guess_number = 1;//initialize the counter as guess_number as 1.
    solution1 = *one;//Store a copy of the four solutions because I am going to need them at the end.
    solution2 = *two;
    solution3 = *three;
    solution4 = *four;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str.
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{

    int x,y,z,w;//Set variables for storing seed value and post characters for sscanf
    char post[2];


    if(sscanf(guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post) == 0)//Check if sscanf return value is 0 which is invalid case
    {
      printf("make_guess: invalid guess\n");
      return 0;
    }
    else if(sscanf(guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post) == 4 && w>=1 && w<=8 && x>=1 && x<=8 && y>=1 && y<=8 && z>=1 && z<=8)
    {//Check if the return value is 4 and also w,x,y,z should be between 1 and 8 and if these two requirements are satisfied, it is valid
      *one = w;
      *two = x;
      *three = y;
      *four = z;
    }
    else//Other cases are marked as invalid
    {
      printf("make_guess: invalid guess\n");
      return 0;
    }

    //The below code is to print out the standard feedback message back to the user
    int guess_solution[4] = {*one, *two, *three, *four};//What I do is to concatenate solutions and guesses and flags corresponding to
    int true_solution[4] = {solution1, solution2, solution3, solution4};// an array like SystemVerilog.
    int flag_guess[4] = {0, 0, 0, 0};
    int flag_true[4] = {0, 0, 0, 0};

    int perfect_count = 0;//Set up and initialize counts for perfect_count and misplaced_count
    int misplaced_count = 0;


    //What I do here is to first count the perfect match case and mark them as flagged
    for(int i = 0; i < 4; i++)
    {
      if(guess_solution[i]==true_solution[i])
      {
        flag_guess[i] = 1;
        flag_true[i] = 1;
        perfect_count = perfect_count + 1;
      }
    }

    //Then I will check the rest cases to see if they are misplaced.
    for(int j = 0; j < 4; j++)
    {
        if(flag_guess[j] == 0)
        {
            for(int k = 0; k < 4; k++)
            {
                if(flag_true[k] == 0)
                {
                  if(guess_solution[j] == true_solution[k])
                  {
                    flag_guess[j] = 1;
                    flag_true[k] = 1;
                    misplaced_count = misplaced_count + 1;
                    break;
                  }
                }
            }
        }
    }

    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect_count, misplaced_count);
    guess_number = guess_number + 1;//increase the counter.
    return 1;
}
