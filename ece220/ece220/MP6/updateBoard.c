/*
Intro Paragraph:
For this MP, our goal is to implement Game of Life in C. Bascially, this MP involves stuff with pointers and arrays
and maybe 2-D arrays because we want a map for the cells. The gameboard has dimension of Width*Height and is represented
in binary. 0 means dead and 1 means alive. However, since we haven't got touch into malloc. So we will just represent the
2-D array into a row-majot order 1-D array. There are three functions to be implemented. countLiveNeighbor() is to count
the number of alive cells around a specific given location on the map. updateBoard() is to update each cell with either live or death
according to the rules specified by the live games. Finally, aliveStable() is to check if cells in next state is the same as the current state.
*/

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

//Description of countLiveNeighbor()
/*
	Basically, my algorithm is to first check the case of edge and corner cells since they either have 3 neighbor cells or have 5 neighbor cells.
	So, taking care of them separately is a good choice. Then, after checking those cells, I checks normal cells' neighbors, including top-left,
	top, top-right, left, right, bottom-left, bottom, bottom-right neighbors.
*/
int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
		if(row==0)//check if it is at the 1st row
		{
			if(col==0)//check if it is at the top-left corner
			{
				return board[1] + board[(row+1)*boardColSize] + board[(row+1)*boardColSize+1];
			}
			else if(col==boardColSize-1)//check if it is at the top-right corner
			{
				return board[col-1] + board[(row+1)*boardColSize+col-1] + board[(row+1)*boardColSize+col];
			}
			else//When it is at those top edge cells
			{
				return board[(row+1)*boardColSize+col-1] + board[(row+1)*boardColSize+col] + board[(row+1)*boardColSize+col+1] + board[row*boardColSize+col-1] + board[row*boardColSize+col+1];
			}
		}

		else if(row==boardRowSize-1)//check if it is at the bottom row
		{
			if(col==0)//check if it is at the bottom-left corner
			{
				return board[(row-1)*boardColSize] + board[(row-1)*boardColSize+1] + board[row*boardColSize+1];
			}
			else if(col==boardColSize-1)//check if it is at the bottom-right corner
			{
				return board[(row-1)*boardColSize+col-1] + board[(row-1)*boardColSize+col] + board[row*boardColSize+col-1];
			}
			else//When it is at those bottom edge cells
			{
				return board[(row-1)*boardColSize+col-1] + board[(row-1)*boardColSize+col] + board[(row-1)*boardColSize+col+1] + board[row*boardColSize+col-1] + board[row*boardColSize+col+1];
			}
		}

		else if(col == 0)
		{
			return board[(row-1)*boardColSize] + board[(row-1)*boardColSize+1] + board[row*boardColSize+1] + board[(row+1)*boardColSize] + board[(row+1)*boardColSize+1];
		}

		else if(col == boardColSize-1)
		{
			return board[(row-1)*boardColSize+col] + board[(row-1)*boardColSize+col-1] + board[row*boardColSize+col-1] + board[(row+1)*boardColSize+col-1] + board[(row+1)*boardColSize+col];
		}

		else//when it is at normal cells
		{
				return board[(row-1)*boardColSize+col-1] + board[(row-1)*boardColSize+col] + board[(row-1)*boardColSize+col+1] + board[row*boardColSize+col-1] + board[row*boardColSize+col+1] + board[(row+1)*boardColSize+col-1] + board[(row+1)*boardColSize+col] + board[(row+1)*boardColSize+col+1];
		}
}
/*
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */

 /*
	This function's essential is that I have to create a new 1-D array for updating the board
	because if we update cells on the current board we are mixing current generation's cells with
	next generation's cells and this causes data trash. So, copying the new 1-D array's cells into
	current generation's cells is pretty necessary
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
		int next_generation_board[boardRowSize*boardColSize];//create a new blank copy of gameboard
	  int i,j;//define iteration variables

//Here my algorithm checks first if countLiveNeighbor() returns 3, if this is the case, a cell is alive regardless
//of whether it is alive or dead previously. If countLiveNeighbor() returns less or equal to 1 or greater or equal
//to 4, a cell is guranteed to be dead. if countLiveNeighbor() returns 2 and the cell is previously alive, it is still alive.
//Otherwise, it is dead.
		for(i = 0; i<boardRowSize; i++)
		{
			for(j = 0; j<boardColSize; j++)
			{
				int count = countLiveNeighbor(board,boardRowSize,boardColSize,i,j);
				if(count == 3)
				{
					next_generation_board[i*boardColSize+j] = 1;
				}
				else if(count <=1 || count >= 4)
				{
					next_generation_board[i*boardColSize+j] = 0;
				}
				else if(board[i*boardColSize+j] == 1 && count == 2)
				{
					next_generation_board[i*boardColSize+j] = 1;
				}
				else{
					next_generation_board[i*boardColSize+j] = 0;
				}
		  }
    }
		//copying next_generation_board's elements 1 by 1 to our gameboard
		for(i = 0; i<boardRowSize; i++)
		{
			for(j = 0; j<boardColSize; j++)
			{
				board[i*boardColSize+j] = next_generation_board[i*boardColSize+j];
			}
		}
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */


 /*
		Here, this function is checking if out next generation's board is going to the same.
		We will also need to establish a new 1-D array for storing next generation's data.
		Then, we create 2 for loops to iterate through every element of the gameboard and board_next
		and compare them element by element. If we detect one element which is different, return 0.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize){

		int board_next[boardRowSize*boardColSize];//establish a new 1-D array
		int i,j;

		updateBoard(board_next,boardRowSize, boardColSize);//call updateBoard function to update new data onto the board_next

		for(i = 0; i<boardRowSize; i++)
		{
			for(j = 0; j<boardColSize; j++)
			{
					if(board_next[i*boardColSize+j] != board[i*boardColSize+j])//If we detect that 1 element is different, return 0
					{
						return 0;
					}
			}
		}
		return 1;//if every element is the same, return 1
}
