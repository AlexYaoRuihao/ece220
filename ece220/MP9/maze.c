#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
//this program is a maze sovler which takes a maze.txt file as input.
//it allocates dynamic memory for maze through function createMaze and then solve it through function i wrote bellow
/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    FILE *f;
    maze_t *maze;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int w, h;

    f=fopen(fileName,"r");
    if (f== NULL){
    	printf("%s open failed\n", fileName );
    	return NULL;
    }

    fscanf(f, "%d %d\n", &w, &h);

    maze = (maze_t *)malloc(sizeof(maze_t)); // allocate memory for maze 

    if (maze != NULL){
    	maze->width = w; //set up maze size
    	maze->height= h;

    	maze->cells = (char **)malloc(h*sizeof(char *));// allocate memory for row cell

    	int i = 0;
    	while ((read = getline(&line, &len, f)) != -1){

    		maze->cells[i] = (char*) malloc(maze->width*sizeof(char)); // allocate memory for cell cols 

    		strcpy(maze->cells[i], (char*) line); // copy string to maze->cells[row]

    		for(int j=0; j<w; j++){
    			if(maze->cells[i][j]=='S'){ //search for 'S'
    				maze->startColumn=j;
    				maze->startRow=i;
    			}
    			if (maze->cells[i][j]=='E'){ //search for 'E'
    				maze->endColumn=j;
    				maze->endRow=i;
    			}
    		}
    		i++;
            printf("%d",i);

    	}


    }

    free(line);
    return maze;
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
    for (int i=0; i<maze->height; i++){    //free spaces i used above
    	free(maze->cells[i]);
    }
    free(maze->cells);
    free(maze);
    return;
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
    printf("%d %d \n", maze->width, maze->height); 
    for(int i=0; i<maze->height; i++){    //print array
    	for(int j=0; j<maze->width; j++){
    		printf("%c", maze->cells[i][j]);
    	}
    	printf("\n");
    }
    return;
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
    
    if(row<0 || col<0 || col>=maze->width || row>=maze->height){
    	return 0;
    }
    if(maze->cells[row][col]=='%' || maze->cells[row][col]=='.' || maze->cells[row][col]=='.'){
    	return 0;
    }
    if(maze->cells[row][col] == 'E'){
    	return 1;
    }

    maze->cells[row][col]='.';

    if( solveMazeManhattanDFS(maze,col-1,row)==1){
        maze->cells[maze->startRow][maze->startColumn]='S';  // avoiding eliminate 'S'
    	return 1;
    }
    if( solveMazeManhattanDFS(maze,col+1,row)==1){
        maze->cells[maze->startRow][maze->startColumn]='S';
    	return 1;
    }
    if( solveMazeManhattanDFS(maze,col,row-1)==1){
        maze->cells[maze->startRow][maze->startColumn]='S';
    	return 1;
    }
    if( solveMazeManhattanDFS(maze,col,row+1)==1){
        maze->cells[maze->startRow][maze->startColumn]='S';
    	return 1;
    }

    maze->cells[row][col]='~';

    return 0;
}
