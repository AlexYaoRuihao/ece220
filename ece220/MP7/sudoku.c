#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  for (int j=0; j<9; j++){  //loop whole row find if val already exist
    if (sudoku[i][j]==val){
      return 1;
    }
  }
  // BEG TODO
  
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for (int i=0; i<9; i++){ //loop whole col find if val already exist
    if (sudoku[i][j]==val){
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  int m = i % 3; // modulus row and col by 3 
  int n = j % 3;
  for (int ro=i-m; ro<i-m+3; ro++){ //get ro(1st row element in 3x3 square) and co(similar as ro) 
    for (int co=j-n; co<j-n+3; co++){ // check if val exist
      if (sudoku[ro][co]==val){
        return 1;
      }
    }
  }
  // BEG TODO
  
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  //assert(i>=0 && i<9 && j>=0 && j<9);
  if (is_val_in_row(val, i, sudoku)==0 && is_val_in_col(val, j, sudoku)==0 && is_val_in_3x3_zone(val, i, j, sudoku)==0){
    return 1; // call three funtion check, return 1 if val can be placed
  }
  // BEG TODO
  return 0;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i, j;
  int x, y; // get i and j value when loop break
  int full=1; // use as a flag, if not full, full=0
  for (i=0; i<9; i++){
    if (full==0){
      break;
    }
    else{
      for (j=0; j<9; j++){ // loop i,j find any 0 in array
        if (sudoku[i][j]==0){
          full=0; // not full
          x=i; //get i,j value
          y=j;
          break;
        }
      }
    }
  }  
  if (full!=0){
    return 1; // check if sudoku full
  }

    for (int num=1; num<=9; num++){
      if (is_val_valid(num,x,y,sudoku)==1){
        sudoku[x][y]=num;
        if (solve_sudoku(sudoku)==1){
          return 1;
        }
        sudoku[x][y]=0;
      }
    }
  

  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





