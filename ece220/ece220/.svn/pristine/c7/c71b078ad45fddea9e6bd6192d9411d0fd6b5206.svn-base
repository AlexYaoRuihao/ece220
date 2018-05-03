/* Code to simulate rolling three six-sided dice (D6)
 * User first types in seed value
 * Use seed value as argument to srand()
 * Call roll_three to generate three integers, 1-6
 * Print result "%d %d %d "
 * If triple, print "Triple!\n"
 * If it is not a triple but it is a dobule, print "Double!\n"
 * Otherwise print "\n"
 */
#include <stdio.h>
#include <stdlib.h>
#include "dice.h"
void roll_three(int* one, int* two, int* three);//Function prototype

int main(){
    int n;
    //int one,two,three;
    printf("Enter Seed: ");
    scanf("%d", &n);//Seed Value entered by the user
    srand(n);
    int one = rand();
    int two = rand();
    int three = rand();
    roll_three(&one, &two, &three);

}
