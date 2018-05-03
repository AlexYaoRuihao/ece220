/*
Intro Paragraph: This MP is served to implement a C program that prints the semiprime numbers in a given range.
We implemented three functions inside this program. The first one is the int main() function. The second and third
one are served as subroutines in LC3 to execute tasks called in the main function. int main() functions asks the user to
type in two positive numbers and the first one must be strictly less than the second number. Otherwise, a message will appear
and the program halts. The second and third function will be introduced later in the program.
*/
#include <stdlib.h>
#include <stdio.h>

//Define function prototypes
int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);                            //Ask the user to type in two numbers a and b
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");  //The two inputs must be both positive
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");   //The first input must be strictly less than the second input
     return 1;
   }

   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
   print_semiprimes(a,b);//call the print_semiprimes() function.
}




/*
This is_prime(int number) function is served to detect if a given number is prime or not. This function's input is number.
The function's return value is 0 if the number is prime, else 1. What I implement is that I set up a special case when number
 is equal to 2 and it just returns 1 since 2 is a prime number. For the case when number is larger than 2, I set up a flag
in this function. Whenever the for loop detects that number can be divided by an integer, then it can't be a prime number.
Then, I change the flag's value and exit out the for loop.
*/
/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
  // Return 1 if n is a prime, and 0 if it is not
  if(number==2)
  {
    //printf("2 ");                 //Special case for 2 as a prime number
    return 1;
  }

  if(number>2)
  {
    int i;
    int flag = 1;                   //Set up the flag and define it to be 1
    for( i=2 ; i<=number-1 ; i++)
    {
      if(number%i==0)
      {
        flag = 0;                   //If I detect that the number is not prime, I change the flag's value and break out the loop.
        break;
      }
    }
       if(flag==0)
       {
         return 0;                  //If the flag's value is changed, then return 0
       }
       else
       {
         return 1;                  //If the flag's value is remained the same, then return 1
       }
  }
  return 0;
}


/*
This print_semiprimes(int a, int b) function is served to be called within the int main() function and
its purpose is to detect and print out the all of the semiprimes between int a and int b. Since the algorithm
is already given on the MP page, I don't need to specifically talk about it here.
 */

/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
  int i,j;
  int flag = 0;                              //Define another flag here

  for(i = a; i <= b; i++)
  {
    for(j = 2; j <= i-1; j++)
    {
      int j_is_prime, i_over_j_is_prime;
      j_is_prime = is_prime(j);
      i_over_j_is_prime = is_prime(i/j);
      if(i%j==0 && j_is_prime == 1 && i_over_j_is_prime == 1)   //implementation of "j is a prime factor of i and (i/j) is also a prime number"
      {
        printf("%d ", i);
        flag = 1;
        break;                                 //It's necessary that we break here because once we detect a number is semiprime, say 33, the program
      }                                        //will print out 33 twice because it's product of 3*11 and 11*3. So break here is necessary
    }
  }

  if(flag==1)
  {
    return 1;                                  //if there exists semiprimes, return 1
  }
  else{
    return 0;                                  //if there doesn't exist semiprimes, return 0
  }

}
