//Intro Paragraph:
/*This MP serves to print the Pascal's Triangle. This Pascal's Triangle follows some rules on
its coefficients. There are two integers that specify a position's coefficient, n and k.
n is the row number and k is the binomial coefficient. Like Row 3's 2nd number is just 3Choose1
since all of them start from 0. "Choose" can be implemented by timing (n+1-i)/i. This is bassically
my algorithm. */



#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row;                                                                               //define integer row

  printf("Enter a row index: ");
  scanf("%d",&row);                                                                      //ask the user to type in the row index

  // Write your code here
  unsigned long int coefficient_triangle = 1;                                            //define unsigned long int tyoe of coefficient_triangle
  if(row == 0)                                                                           //define a special case that when row is 0, we want our output to be 1
  {
    printf("1\n");
  }

  if(row >= 1)                                                                           //define the general case that when row is greater or equal to 1
  {
    printf("1 ");                                                                        //Regardless of row number, the first number coefficient is always 1

    int binomial_coefficient;
    int i;                                                                               //define binomial_coefficient and i to be iteration variable
    for(binomial_coefficient = 1; binomial_coefficient <= row; binomial_coefficient++)   //First iterate binomial_coefficient
    {
      for(i = 1; i<=binomial_coefficient; i++)                                           //The iterate i
      {
        coefficient_triangle = coefficient_triangle*( row + 1 - i )/(i);                 //inplement n choose k
      }
      printf("%lu ", coefficient_triangle);
      coefficient_triangle = 1;                                                          //Reset coefficient_triangle to 1 for next iteration
    }
    printf("\n");
  }

  return 0;
}
