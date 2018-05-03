#include "game.h"
/*
  Intro paragraph:
  This MP is an implementation of 2048 on a varied-sized board. The game logic is
  almost the same as the one we played. We need to successfully impolement the sliding
  function in all 4 directions and correctly merge same values and increase the scores
  accordingly. In addition to this, we also need to write several functions that return
  a pointer to the cell array to access the 1-D array conveniently and reset variables to
  its initial values.
*/



game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure)
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    //game game1;
    mygame->rows = rows;//since mygame here is a pointer type, if we need to
    mygame->cols = cols;//access members within the structs, we need to use ->.
    mygame->score = 0;//Here, we initialize the variables.

    int i,j;
    for(i = 0; i < mygame -> rows; i++)
    {
      for(j = 0; j < mygame -> cols; j++)
      {
        (mygame->cells[i*(mygame -> cols)+j]) = -1;//loop over to initialize every element in the cell array
      }
    }

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any
	memory previously allocated is not lost in this function.
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
   (*_cur_game_ptr)->rows = new_rows;//_cur_game_ptr is a double pointer. So we want to
   (*_cur_game_ptr)->cols = new_cols;//dereference it once to be a pointer to point to the
   (*_cur_game_ptr)->score = 0;//struct to access the members within.

   int i,j;
   for(i = 0; i < (*_cur_game_ptr)->rows; i++)
   {
     for(j = 0; j < (*_cur_game_ptr)->cols; j++)
     {
       (*_cur_game_ptr)->cells[i*((*_cur_game_ptr) -> cols)+j] = -1;//loop over to initialize every element in the cell array
     }
   }
	return;
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    if(row > cur_game->rows || col > cur_game->cols)//check if position is out of bounds
    {
      return NULL;
    }
    else{
      return &cur_game->cells[row*(cur_game->cols) + col];//return the pointer/address to the corresponding cell
    }
    //return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
{
    //YOUR CODE STARTS HERE
    int j,i,k;//define iteration variables
    int flag = 0;//set the flag to detect if there are any changes to the board
    for(j = 0; j < cur_game->cols; j++)
    {
        int last_combined_row = -1;//reset the last_combined_row
        for(i = 0; i < cur_game->rows; i++)
        {
          if(cur_game -> cells[i*(cur_game->cols)+j] != -1)//if the current row value is not empty
          {
            for(k = 0; k < i; k++)
            {
              if(cur_game -> cells[k*(cur_game->cols)+j] == -1)//find the first available target row
              {
                cur_game -> cells[k*(cur_game->cols)+j] = cur_game -> cells[i*(cur_game->cols)+j];//copy current row value into target row
                cur_game -> cells[i*(cur_game->cols)+j] = -1;//clear current row contents
                flag = 1;//mark the cell has been changed
                break;//break out of the for loop and use k later
              }
            }
            if((k - 1) != last_combined_row)//if the row above target row is not equal to last_combined_row
            {
              if(cur_game -> cells[(k - 1)*(cur_game -> cols)+j] == cur_game -> cells[k*(cur_game -> cols)+j])//if the value in the row above target row is equal to target row value
              {
                cur_game -> cells[(k - 1)*(cur_game -> cols)+j] = 2*(cur_game -> cells[(k - 1)*(cur_game -> cols)+j]);//row above target row is assigned the sum
                cur_game -> cells[k*(cur_game -> cols)+j] = -1;//target row value is assigned as empty
                cur_game -> score += cur_game -> cells[(k - 1)*(cur_game -> cols)+j];//update the score
                last_combined_row = k - 1;//last_combined_row is assigned as row above target row
                flag = 1;//mark the cell has been changed
              }
            }
          }
        }
    }

    return flag;
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int j,i,k;
    int flag = 0;
    for(j = 0; j < cur_game->cols; j++)
    //for(j = (cur_game->cols) - 1 ; j >= 0; j--)
    {
        int last_combined_row = cur_game -> rows;//reset last_combined_row
        //for(i = 0; i < cur_game->rows; i++)
        for(i = (cur_game->rows) - 1; i >= 0; i--)
        {
          if(cur_game -> cells[i*(cur_game->cols)+j] != -1)//if the current row value is not empty
          {
            //for(k = 0; k < i; k++)
            for(k = (cur_game -> rows)-1; k > i; k--)//find the first available target row
            {
              if(cur_game -> cells[k*(cur_game->cols)+j] == -1)
              {
                cur_game -> cells[k*(cur_game->cols)+j] = cur_game -> cells[i*(cur_game->cols)+j];//copy current row value into target row
                cur_game -> cells[i*(cur_game->cols)+j] = -1;//clear current row contents
                flag = 1;//mark the cell as changed
                break;//break out the for loop
              }
            }
            if((k + 1) != last_combined_row)//if row above target row is not equal to last_combined_row
            {
              if(cur_game -> cells[(k + 1)*(cur_game -> cols)+j] == cur_game -> cells[k*(cur_game -> cols)+j])//if value in row below target row is equal to target row value
              {
                cur_game -> cells[(k + 1)*(cur_game -> cols)+j] = 2*(cur_game -> cells[(k + 1)*(cur_game -> cols)+j]);//row below target row is assigned the sum
                cur_game -> cells[k*(cur_game -> cols)+j] = -1;//target row value is assigned as empty
                cur_game -> score += cur_game -> cells[(k + 1)*(cur_game -> cols)+j];//update the scores
                last_combined_row = k + 1;//last_combined_row is assigned as row below target row
                flag = 1;
              }
            }
          }
        }
    }

    return flag;

};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int j,i,k;
    int flag = 0;
    //for(j = 0; j < cur_game->cols; j++)
    for(i = 0; i < cur_game->rows; i++)
    {
        //int last_combined_row = -1;
        int last_combined_col = -1;//reset last_combined_col
        for(j = 0; j < cur_game->cols; j++)
        {
          if(cur_game -> cells[i*(cur_game->cols)+j] != -1)//if current col value is not empty
          {
            //for(k = 0; k < i; k++)
            for(k = 0; k < j; k++)//k now is the column index
            {
              if(cur_game -> cells[i*(cur_game->cols)+k] == -1)//find the first available target column
              {
                //cur_game -> cells[k*(cur_game->cols)+j] = cur_game -> cells[i*(cur_game->cols)+j];
                cur_game -> cells[i*(cur_game->cols)+k] = cur_game -> cells[i*(cur_game->cols)+j];//copy current col value into col number
                cur_game -> cells[i*(cur_game->cols)+j] = -1;//clear current col contents
                flag = 1;
                break;
              }
            }
            if((k - 1) != last_combined_col)//if col to the left of target col is not equal to last_combined_col
            {
              if(cur_game -> cells[i*(cur_game -> cols)+ (k - 1)] == cur_game -> cells[i*(cur_game -> cols)+k])//if the value in the col to the left of target col is not equal to target col value
              {
                cur_game -> cells[i*(cur_game -> cols)+ (k - 1)] = 2*(cur_game -> cells[i*(cur_game -> cols)+ k]);//col to the left target col is assigned the sum
                cur_game -> cells[i*(cur_game -> cols)+k] = -1;//target col is set as empty
                cur_game -> score += cur_game -> cells[i*(cur_game -> cols)+ (k - 1)];//update the score
                last_combined_col = k - 1;//last_combined_col is set as col left of target col
                flag = 1;//mark the cell has been changed
              }
            }
          }
        }
    }

    return flag;

};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int j,i,k;
    int flag = 0;
    //for(j = 0; j < cur_game->cols; j++)
    for(i = 0; i < cur_game->rows; i++)
    {
        //int last_combined_row = -1;
        int last_combined_col = cur_game -> cols;//reset last_combined_col
        //for(j = 0; j < cur_game->cols; j++)
        for(j = (cur_game->cols)-1; j >= 0; j--)
        {
          if(cur_game -> cells[i*(cur_game->cols)+j] != -1)
          {
            //for(k = 0; k < i; k++)
            //for(k = 0; k < j; k++)//k now is the column index
            for(k = ((cur_game -> cols)-1); k > j; k--)//find the first available target col
            {
              if(cur_game -> cells[i*(cur_game->cols)+k] == -1)//if current col value is not empty
              {
                //cur_game -> cells[k*(cur_game->cols)+j] = cur_game -> cells[i*(cur_game->cols)+j];
                cur_game -> cells[i*(cur_game->cols)+k] = cur_game -> cells[i*(cur_game->cols)+j];//copy current col value into target col value
                cur_game -> cells[i*(cur_game->cols)+j] = -1;//clear current col value
                flag = 1;
                break;
              }
            }
            if((k + 1) != last_combined_col)//if col right of the target col is not equal to last_combined_col
            {
              if(cur_game -> cells[i*(cur_game -> cols)+ (k + 1)] == cur_game -> cells[i*(cur_game -> cols)+k])//if the value is equal to target col value
              {
                cur_game -> cells[i*(cur_game -> cols)+ (k + 1)] = 2*(cur_game -> cells[i*(cur_game -> cols)+ (k + 1)]);//col right of target col is assigned the sum
                cur_game -> cells[i*(cur_game -> cols)+k] = -1;//target col is set as empty
                cur_game -> score += cur_game -> cells[i*(cur_game -> cols)+ (k + 1)];//update the scores
                last_combined_col = k + 1;//last_combined_col is assigned col right of target col
                flag = 1;
              }
            }
          }
        }
    }

    return flag;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    /*int i,j;
    for(i = 0; i < cur_game -> rows; i++)
    {
      for(j = 0; j < cur_game -> cols; j++)
      {
        if(cur_game -> cells[i*(cur_game -> cols) + j] == -1)
        {
          return 1;//iterate through every element in the cell array, if there is one element that is empty, return 1
        }
        //return 0;
      }
    }

    if(move_w(cur_game) == 0 && move_s(cur_game) == 0 && move_a(cur_game) == 0 && move_d(cur_game) == 0)
    {
      return 0;//if we can not move in all 4 directions anymore, return 0
    }
    else{
      return 1;//if any two adjacent tiles are the same, game is not over yet, return 1
    }*/
    int i,j;
    for(i = 0; i < cur_game -> rows; i++)
    {
      for(j = 0; j < cur_game -> cols; j++)
      {
        if(cur_game -> cells[i*(cur_game -> cols) + j] == -1)
        {
          return 1;//iterate through every element in the cell array, if there is one element that is empty, return 1
        }
      }
    }

    game *new_game = make_game(cur_game -> rows, cur_game -> cols);

    for(i = 0; i < cur_game -> rows; i++)
    {
      for(j = 0; j < cur_game -> cols; j++)
      {
          new_game -> cells[i*(new_game -> cols) + j] = cur_game -> cells[i*(cur_game -> cols) + j];
      }
    }

    if(move_w(new_game) == 0 && move_s(new_game) == 0 && move_a(new_game) == 0 && move_d(new_game) == 0)
    {
      return 0;//if we can not move in all 4 directions anymore, return 0
    }
    else{
      return 1;//if any two adjacent tiles are the same, game is not over yet, return 1
    }


}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{

	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    if (cell_ptr == NULL){
        printf("Bad Cell Pointer.\n");
        exit(0);
    }


	//check for an empty cell
	int emptycheck = 0;
	int i;

	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}

    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game)
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;

	printf("\n\n\nscore:%d\n",cur_game->score);


	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char


    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  ");
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }

	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char

    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;

    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}

		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		}

		remake_game(&cur_game,rows,cols);

		move_success = 1;

    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }




    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game);
		 print_game(cur_game);
    }

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
