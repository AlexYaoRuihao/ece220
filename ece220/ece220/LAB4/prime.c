#include "prime.h"

int is_prime(int n){
  // Return 1 if n is a prime, and 0 if it is not
  if(n==2)
  {
    //printf("2 ");                 //Special case for 2 as a prime number
    return 1;
  }

  if(n>2)
  {
    int i;
    int flag = 1;
    for( i=2 ; i<=n-1 ; i++)
    {
      if(n%i==0)
      {
        flag = 0;
        break;
      }
    }
       if(flag==0)
       {
         return 0;
       }
       else
       {
         return 1;
       }
  }

}
