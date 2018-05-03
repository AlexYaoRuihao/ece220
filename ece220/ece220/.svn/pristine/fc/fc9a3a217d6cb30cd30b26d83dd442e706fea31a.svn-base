#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
/*
  Intro Paragraph: This MP is served to implement a maze-solver using recursion method called
  Depth-First Search. The general structure of this MP is that we first need to open the input
  file and read from it to write to the stream for further processing. Then, we need to dynamically
  allocate memory for the structure that self-defined in maze.h. In addition to allocate memory for
  that. We still need to allocate space for holding the whole maze. After that, we just apply DFS
  recursive search algorithm to solve the maze.
*/


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */

 /*
    This function is to help us create a maze from input file stream and we need to read information
    from the file and allocate specific size of memory according to the information given.
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    maze_t* structure_ptr = (maze_t*)malloc(sizeof(maze_t));//alloacate memory space for structure



    FILE *f = fopen(fileName, "r");
    if(f == NULL)//the case when it fails to open the file
    {
      printf("fail to open file!");
    }

    int row,col;
    fscanf(f, "%d%d", &col, &row);
    //maze_t* cells_ptr = (maze_t*)malloc(row*col*sizeof(char));

    structure_ptr->width = col;
    structure_ptr->height = row;

    structure_ptr->cells = (char**)malloc(row*sizeof(char*));//allocate memory space for double pointers
    int i,j;
    for(i = 0; i < row; i++)
    {
      structure_ptr->cells[i] = (char*)malloc(col*sizeof(char));//allocate memory space for single pointers

      //structure_ptr->cells[i] = fgetc(f);
      for(j = 0; j < col; j++)
      {
        //cells_ptr->cells[i][j] = fgetc(f);
        //structure_ptr->cells[i*col+j] = (char*)malloc(col*sizeof(char));
        //while(fgetc(f) == '\n')
        //{
          //;
        //}
        char c = fgetc(f);//read characters from the input file
        while(c == '\n')
        {
          c = fgetc(f);//if we read that the character is new-line, we skip it and read next one
        }
        structure_ptr->cells[i][j] = c;//assign the character we read into cells


        if(structure_ptr->cells[i][j] == 'S')//detect the starting point of the maze and assign startRow and startColumn
        {
          structure_ptr->startRow = i;
          structure_ptr->startColumn = j;
        }

        if(structure_ptr->cells[i][j] == 'E')//detect end point of the maze and assign endRow and endColumn
        {
          structure_ptr->endRow = i;
          structure_ptr->endColumn = j;
        }


      }
    }
    fclose(f);
    //printf("%d %d %d %d", structure_ptr->startRow, structure_ptr->startColumn, structure_ptr->endRow, structure_ptr->endColumn);
    return structure_ptr;
}





/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    //int i,j;
    int i;
    for(i = 0; i < maze->height; i++)
    {
      //for(j = 0; j < maze->width; j++)
      //{
        //free(maze->cells[i*(maze->width)+j]);
        free(maze->cells[i]);//free the array that stores cell rows
      //}
    }
    free(maze->cells);//free the double pointer
    free(maze);//free the structure declared
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    //printf(maze->width, " ", maze->height, "\n");
    //printf("%d %d\n", maze->width, maze->height);
    //int i,j;
    int i,j;
    for(i = 0; i < maze->height; i++)
    {
      for(j = 0;j < maze->width; j++)
      {
        //printf(maze->cells[i][j]);
        printf("%c", maze->cells[i][j]);//print the cells using 2-D array accessing method
      }
      printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    //return 0;
    if(row < 0 || (row >= maze->height) || col < 0 || (col >= maze->width))
    {
      return 0;//check if indexes are out of bound, if so, return 0
    }

    if(maze->cells[row][col] == 'E')
    {
      return 1;//check if it is end of maze, if so, return 1
    }

    if(maze->cells[row][col] != ' ' && maze->cells[row][col] != 'S')
    {
      return 0;//check if it's not empty and not starting point of maze, if so, return 0
    }

    if(maze->cells[row][col] != 'S')
    {
      maze->cells[row][col] = '*';//marj the solution
    }

    if(maze->cells[row][col-1] != 'S')
    {
    if(solveMazeManhattanDFS(maze, (col - 1), row) == 1)//if (solveMaze(left of (col, row) ) == true) return true
    {
      return 1;
    }
    }

    if(maze->cells[row][col+1] != 'S')
    {
    if(solveMazeManhattanDFS(maze, (col + 1), row) == 1)//if (solveMaze(right of (col, row) ) == true) return true
    {
      return 1;
    }
    }

    if(maze->cells[row-1][col] != 'S')
    {
    if(solveMazeManhattanDFS(maze, col, (row - 1)) == 1)//if (solveMaze(up of (col, row) ) == true) return true
    {
      return 1;
    }
    }

    if(maze->cells[row+1][col] != 'S')
    {
    if(solveMazeManhattanDFS(maze, col, (row + 1)) == 1)//if (solveMaze(down of (col, row) ) == true) return true
    {
      return 1;
    }
    }

    maze->cells[row][col] = '~';//unmark the solution and mark it as visited

    return 0;
}
