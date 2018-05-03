#include <stdio.h>
#include "prime.h"

int is_prime(int n); //Function Prototype

int main(){
  // Write the code to take a number n from user and print all the prime numbers between 1 and n
  int n;
//  int index;
//  int j;

  printf("Enter the value of n: ");
  scanf("%d",&n);
  printf("Printing the primes less than or equal to %d: ", n);
 // index = is_prime(n);

  if(n==2)
  {
    printf("2");
  }

  if(n>2)
  {
   // if(index==0)
   // {
      

    
    //printf("2 ");
    int index;
    int j;
    for( j=2 ; j<=n ; j++)
    { 
      index = is_prime(j);
      if(index==1)
      {
        printf("%d ", j);
      }
      //else
      //{
      //  return 0;
      //}
    }
  }
  return 0;
}
