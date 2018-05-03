//Function for generating three d6 rolls
#include <stdio.h>
#include <stdlib.h>
#include "dice.h"

void roll_three(int* one, int* two, int* three){
  //one = rand();
  int one1 = (*one % 6) + 1;

  //two = rand();
  int two1 = (*two % 6) + 1;

  //three = rand();
  int three1 = (*three % 6) + 1;

  printf("%d %d %d", one1, two1, three1);

  if(one1==two1 && one1==three1 && two1==three1)
  {
    printf(" Triple!\n");
  }
  else if(one1==two1 || one1==three1 || two1==three1)
  {
    printf(" Double!\n");
  }
  else{
    printf("\n");
  }

}
