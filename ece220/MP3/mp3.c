/*this small function calculate the nth row in a pascal trangle. there are two parts in this program 
the first part is use factorial to call and caluculat the number of factorial. the second part is 
do the algerbra and print the value I use the double to do all calculation to prevent the overflow
and typecast it to uint_64 for printing!  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

double factorial(int n) //implement factorial funcion
{
    double result = 1;
    for (int i = 2; i <= n; i++)   
    {  
        result *= i;
    }
    return result;
}



int main()
{
  int row_index;            

  printf("Enter the row index : "); 
  scanf("%d",&row_index);

  // Your code starts from here
  for(int col_index = 0; col_index < row_index+1; col_index++)
  {
    double nminsk=row_index - col_index;
    double up = 1;
    double down = factorial(nminsk);
    for (int j = col_index+1; j < row_index+1; j++) //simplify binomial coefficient function by eliminating k! with n!
    {
      up *= j;
    }

    double num = up / down;         // will out of range if print num directly
    uint64_t pnum = (uint64_t) num;// transfer double num to num to be printed in uint_64 format
  
  	printf("%  " PRIu64 " ",pnum );  
  }



  return 0;
}
