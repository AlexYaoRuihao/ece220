#include "sudoku.h"
/*
  Intro Paragraph: Basically for this MP, we need to implement the sudoku game on a
  9*9 standard board using primarily recursive backtracking method. There are three
  restrictions on placing numbers 1-9. The first one is that a number cannot appear
  twice in a column. The second one is that a number cannot appear twice in a row. The
  third one is that a number cannot appear twice in the 3x3 matrix it belongs to. These
  are all helper functions. The recursion occurs in solve_sudoku() function, which will be
  discussed on the intro part of that function.
*/


//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int j;//declare the iteration variable
  for(j = 0; j < 9; j++)
  {
    if(sudoku[i][j] == val)//check the value on the same row, if found, then return 1
    {
      return 1;
    }
  }
  return 0;//if not, return 0
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int i;//declare the iteration variable
  for(i = 0; i < 9; i++)
  {
    if(sudoku[i][j] == val)
    {
      return 1;//check the value on the same col, if found, then return 1
    }
  }
  return 0;//if not, return 0
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)

//For this function, what I do is to divide the 9x9 matrix into nine 3x3 mareix.
//And first detect whether row belongs to 0-2, 3-5 or 6-8, and within each row range,
//I detect whether column belongs to 0-2, 3-5 or 6-8. So, wafter I iterate all 3x3 matrices
//task for this function is done.
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int a,b;//a and b are iteration variables
  if(i <= 2)
  {
    if(j <= 2)
    {
      for(a = 0; a <= 2; a++)
      {
        for(b = 0; b <= 2; b++)
        {
          if(sudoku[a][b] == val)
          {
            return 1;
          }
        }
      }
    }
    else if(j > 2 && j <= 5)
    {
      for(a = 0; a <= 2; a++)
      {
        for(b = 3; b <= 5; b++)
        {
          if(sudoku[a][b] == val)
          {
            return 1;
          }
        }
      }
    }
    else
    {
      for(a = 0; a <= 2; a++)
      {
        for(b = 6; b <= 8; b++)
        {
          if(sudoku[a][b] == val)
          {
            return 1;
          }
        }
      }
    }
  }

  else if(i > 2 && i <= 5)
  {
    if(j <= 2)
    {
      for(a = 3; a <= 5; a++)
      {
        for(b = 0; b <= 2; b++)
        {
          if(sudoku[a][b] == val)
          {
            return 1;
          }
        }
      }
    }
    else if(j > 2 && j <= 5)
    {
      for(a = 3; a <= 5; a++)
      {
        for(b = 3; b <= 5; b++)
        {
          if(sudoku[a][b] == val)
          {
            return 1;
          }
        }
      }
    }
    else
    {
      for(a = 3; a <= 5; a++)
      {
        for(b = 6; b <= 8; b++)
        {
          if(sudoku[a][b] == val)
          {
            return 1;
          }
        }
      }
    }
  }

  else
  {
    if(j <= 2)
    {
      for(a = 6; a <= 8; a++)
      {
        for(b = 0; b <= 2; b++)
        {
          if(sudoku[a][b] == val)
          {
            return 1;
          }
        }
      }
    }
    else if(j > 2 && j <= 5)
    {
      for(a = 6; a <= 8; a++)
      {
        for(b = 3; b <= 5; b++)
        {
          if(sudoku[a][b] == val)
          {
            return 1;
          }
        }
      }
    }
    else
    {
      for(a = 6; a <= 8; a++)
      {
        for(b = 6; b <= 8; b++)
        {
          if(sudoku[a][b] == val)
          {
            return 1;
          }
        }
      }
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.

//this is the helper function that we write. Basically, I first check is_val_in_row,
//then is_val_in_row, then is_val_in_3x3_zone, if all of them are not satisfied, return 1
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(is_val_in_row(val ,i , sudoku) == 1)
  {
    return 0;
  }
  else if(is_val_in_col(val, j, sudoku) == 1)
  {
    return 0;
  }
  else if(is_val_in_3x3_zone(val, i, j, sudoku) == 1)
  {
    return 0;
  }
  else{
    return 1;
  }
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.

//This is the recursion function using backtracking
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i,j,num;//define iteration variables and num
  for(i = 0; i < 9; i++)
  {
    for(j = 0; j < 9; j++)
    {
      if(sudoku[i][j] == 0)//find a non-filled cell
      {
        for(num = 1; num <= 9; num++)//iterate trhough and try filling the blank with 1-9
        {
          if(is_val_valid(num, i, j, sudoku) == 1)//if the num can be filled in this position
          {
            sudoku[i][j] = num;//fill the num
            if(solve_sudoku(sudoku) == 1)//recusively call the function to fill next position
            {
              return 1;
            }
            //else
            //{
              sudoku[i][j] = 0;//make the cell non-filled
            //}
          }
        }
        return 0;//return 0 here if no numbers can be filled in the given cell
      }
    }
}
  return 1;//at the end return 1
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
