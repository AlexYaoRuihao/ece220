#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>
/*
  Intro paragraph: this MP serves to implement the sparse matrix by the methods
  linked lists. We used linked lists here instead of arrays because sparse matrix
  consists mostly of zeroes. if we used arrays, we will involve a lot of memory accessses.
  And this is an pretty inefficient method because it will be extremely hard to get
  elements added or removed. However, for linked lists, adding an item or removing
  an item will be very ez but I have to traverse the linked lists every time I need to
  access members.
*/

void set_nz(sp_lils* list);

void create_nodes(sp_lils * mat_l, int row, int col, double value);

void delete_nodes(sp_lils * mat_l, int row, int col, double value);

int find(sp_lils* mat_l, int row, int col);

void replace_value(sp_lils *mat_l, int row, int col, double element);



sp_lils * load_lils(char* input_file)
{
    FILE *f = fopen(input_file, "r");
    if(f == NULL)//the case when it fails to open the file
    {
      printf("fail to open file!");
      return NULL;
    }

    sp_lils* mp10_list = (sp_lils*)malloc(sizeof(sp_lils));//allocate memory for struct

    mp10_list->row_list_head = NULL;
    //int row,col;
    fscanf(f, "%d %d\n", &(mp10_list->m), &(mp10_list->n));

    int row,col;
    double value;

    while(feof(f)==0)//check if it is at the end of file
    {
        fscanf(f, "%d %d %lf\n", &row, &col, &value);
        set_lils(mp10_list, row, col, value);
    }

    //set nonzero paramters
    set_nz(mp10_list);


    fclose(f);

    return mp10_list;
}


//helper function 1
void set_nz(sp_lils* list)
{
    list->nz = 0;//initialize nz in sp_lils struct
    sp_lils_row_node *current_row_node = list->row_list_head;

    sp_lils_col_node *current_col_node;

    while(current_row_node!=NULL)
    {
      current_col_node = current_row_node->col_list_head;
      while(current_col_node!=NULL)
      {
        (list->nz)++;
        current_col_node = current_col_node->next;
      }
      current_row_node = current_row_node->next;
    }
}


//return 0 if we don't find a match and return 1 if we find a match
int find(sp_lils* mat_l, int row, int col)
{
  sp_lils_row_node *current_row_node = mat_l->row_list_head;
  sp_lils_col_node *current_col_node;

  while(current_row_node != NULL)
  {
    if(current_row_node -> idx_r > row)
    {
      return 0;
    }
    if(current_row_node -> idx_r == row)
    {
      current_col_node = current_row_node -> col_list_head;
      while(current_col_node!=NULL)
      {
        if(current_col_node -> idx_c > col)
        {
          return 0;
        }
        if(current_col_node -> idx_c == col)
        {
          return 1;
        }
        current_col_node = current_col_node -> next;
      }
    }
    current_row_node = current_row_node -> next;
  }
  return 0;
}



double gv_lils(sp_lils * mat_l,int row,int col)
{
    sp_lils_row_node *current_row_node = mat_l->row_list_head;
    sp_lils_col_node *current_col_node;
    if(find(mat_l, row, col) == 1)
    {
    while(current_row_node!=NULL)
    {
      if(current_row_node -> idx_r == row)
      {
      current_col_node = current_row_node ->col_list_head;
      while(current_col_node!=NULL)
      {
        if(current_col_node -> idx_c == col){
          return current_col_node -> value;
        }
        current_col_node = current_col_node->next;
      }
    }
    current_row_node = current_row_node->next;
  }
}
return 0;
}



void set_lils(sp_lils * mat_l, int row, int col, double value)
{
  if(find(mat_l, row, col) == 1)
  {
    if(value != 0)
    {
      replace_value(mat_l, row, col, value);
    }
    else
    {
      delete_nodes(mat_l, row, col, value);
      mat_l -> nz -= 1;
    }
  }
  else{
    if(value==0)
    {
      return;
    }
    else
    {
      create_nodes(mat_l, row, col, value);
      mat_l -> nz += 1;
    }
  }
	return;
}

void replace_value(sp_lils *mat_l, int row, int col, double element)
{
    sp_lils_row_node *current_row_node = mat_l->row_list_head;
    sp_lils_col_node *current_col_node;

    while(current_row_node!=NULL)
    {
      if(current_row_node -> idx_r == row)
      {
      current_col_node = current_row_node ->col_list_head;
      while(current_col_node!=NULL)
      {
        if(current_col_node -> idx_c == col){
          current_col_node -> value = element;
          return;
        }
        current_col_node = current_col_node->next;
      }
    }
    current_row_node = current_row_node->next;
  }
}

//helper function 2
void create_nodes(sp_lils * mat_l, int row, int col, double value)
{
    sp_lils_row_node* node_row = mat_l->row_list_head;

    sp_lils_col_node* node_col;
    sp_lils_col_node *current_column, *previous_column;


    if(node_row==NULL)
    {
      node_row = (sp_lils_row_node*)malloc(sizeof(sp_lils_row_node));
      node_row->idx_r = row;
      node_row->col_list_head = NULL;
      node_row->next = NULL;

      mat_l->row_list_head = node_row;

      node_col = (sp_lils_col_node*)malloc(sizeof(sp_lils_col_node));
      node_col->idx_c = col;
      node_col->value = value;
      node_col->next = NULL;

      node_row->col_list_head = node_col;


      return;
    }
    else
    {
        while(node_row!=NULL)
        {
          if(row==node_row->idx_r)//replace the already-existing node
          {
              if(node_row->col_list_head == NULL)
              {
                sp_lils_col_node* col_node = (sp_lils_col_node*)malloc(sizeof(sp_lils_col_node));
                col_node->idx_c = col;
                col_node->value = value;
                col_node->next = NULL;
                node_row->col_list_head = col_node;
                return;
              }
              //set up the case when there are not only one cols
              previous_column = node_row->col_list_head;
              current_column = previous_column->next;

              while(previous_column!=NULL)
              {
                if(col<previous_column->idx_c)
                {
                  //the case between the head and 1st node
                  sp_lils_col_node* col_node = (sp_lils_col_node*)malloc(sizeof(sp_lils_col_node));
                  col_node->idx_c = col;
                  col_node->value = value;
                  col_node->next = previous_column;
                  node_row->col_list_head = col_node;
                  return;
                }
                //the case when it is the end of linked lists
                if(col>previous_column->idx_c && current_column == NULL)
                {
                  sp_lils_col_node* col_node = (sp_lils_col_node*)malloc(sizeof(sp_lils_col_node));
                  col_node->idx_c = col;
                  col_node->value = value;
                  col_node->next = NULL;
                  previous_column->next = col_node;
                  return;
                }
                //at the middle of linked lists
                if(col>previous_column->idx_c && col<current_column->idx_c)
                {
                  sp_lils_col_node* col_node = (sp_lils_col_node*)malloc(sizeof(sp_lils_col_node));
                  col_node->idx_c = col;
                  col_node->value = value;
                  col_node->next = current_column;
                  previous_column->next = col_node;
                  return;
                }
                previous_column = current_column;
                current_column = current_column->next;
              }
          }
          node_row = node_row->next;
        }

        //arrange the nodes for row
        sp_lils_row_node *current_row, *next_row;
        current_row = mat_l->row_list_head;
        next_row = current_row->next;

        while(current_row != NULL)
        {
          //the case between head and 1st row node
          if(row < current_row->idx_r)
          {
            sp_lils_row_node* row_node = (sp_lils_row_node*)malloc(sizeof(sp_lils_row_node));
            row_node->idx_r = row;
            row_node->col_list_head = NULL;
            row_node->next = current_row;
            mat_l->row_list_head = row_node;
            break;
          }

          //the case when at the end of lined lists
          if(row > current_row->idx_r && next_row == NULL)
          {
            sp_lils_row_node* row_node = (sp_lils_row_node*)malloc(sizeof(sp_lils_row_node));
            row_node->idx_r = row;
            row_node->col_list_head = NULL;
            row_node->next = NULL;
            current_row->next = row_node;
            break;
          }

          //the case when at the middle of lined lists
          if(row > current_row->idx_r && row < next_row->idx_r)
          {
            sp_lils_row_node* row_node = (sp_lils_row_node*)malloc(sizeof(sp_lils_row_node));
            row_node->idx_r = row;
            row_node->col_list_head = NULL;
            row_node->next = next_row;
            current_row->next = row_node;
            break;
          }
          current_row = next_row;
          next_row = next_row->next;
        }


    }
    //create columns nodes
    create_nodes(mat_l, row, col, value);
    return;
}

//helperfunction 3
void delete_nodes(sp_lils * mat_l, int row, int col, double value)
{
    sp_lils_row_node *previous_row_node;
    sp_lils_row_node *current_row_node = mat_l->row_list_head;

    sp_lils_col_node *previous_col_node;
    sp_lils_col_node *current_col_node;

    while(current_row_node != NULL)
    {
      if(current_row_node->idx_r == row)
      {
        current_col_node = current_row_node -> col_list_head;
        if(current_col_node == NULL)
        {
          break;
        }
        while(current_col_node != NULL)
        {
          if(current_col_node -> idx_c == col)
          {
            if(current_col_node == current_row_node -> col_list_head)
            {
              current_row_node->col_list_head = current_col_node -> next;
              free(current_col_node);
              break;
            }
            else
            {
              previous_col_node -> next = current_col_node -> next;
              free(current_col_node);
              break;
            }
          }
          previous_col_node = current_col_node;
          current_col_node = current_col_node -> next;
        }
        break;
      }
      previous_row_node = current_row_node;
      current_row_node = current_row_node -> next;
    }
    //check if we need to delete row entries when there are no row nodes any more
    if(current_row_node -> col_list_head == NULL)
    {
      if(current_row_node == mat_l -> row_list_head)
      {
        mat_l -> row_list_head = current_row_node -> next;
        free(current_row_node);
        return;
      }
      previous_row_node->next = current_row_node -> next;
      free(current_row_node);
    }
    return;
  }




void save_lils(char * file_name,sp_lils * mat_l)
{
  FILE *f = fopen(file_name, "w");
  if(f == NULL)
  {
    printf("open file failed");
    return;
  }

  fprintf(f, "%d %d\n", mat_l->m, mat_l->n);

  //sp_lils_row_node *previous_row_node;
  sp_lils_row_node *current_row_node = mat_l->row_list_head;

  //sp_lils_col_node *previous_col_node;
  sp_lils_col_node *current_col_node;

  while(current_row_node != NULL)
  {
      current_col_node = current_row_node -> col_list_head;
      while(current_col_node != NULL)
      {
        fprintf(f, "%d %d %lf\n", current_row_node->idx_r, current_col_node->idx_c, current_col_node->value);
        //previous_col_node = current_col_node;
        current_col_node = current_col_node -> next;
      }
      //previous_row_node = current_row_node;
      current_row_node = current_row_node -> next;
  }
    fclose(f);
	   return;
}


sp_lils * add_lils(sp_lils * matA, sp_lils * matB){
  if((matA->m != matB->m) || (matA->n != matB->n))//check if matrix A&B are addable
  {
    return NULL;
  }

  sp_lils* matC = (sp_lils*)malloc(sizeof(sp_lils));
  matC -> m = matA -> m;
  matC -> n = matA -> n;
  matC -> row_list_head = NULL;

  sp_lils_row_node *A_current_row_node = matA->row_list_head;
  sp_lils_col_node *A_current_col_node;

  sp_lils_row_node *B_current_row_node = matB->row_list_head;
  sp_lils_col_node *B_current_col_node;

  int a,b;
  double sumAC, sumBC;

  while(A_current_row_node!=NULL)
  {
    A_current_col_node = A_current_row_node -> col_list_head;
    while(A_current_col_node!=NULL && A_current_col_node->value!=0)
    {
        a = A_current_row_node->idx_r;
        b = A_current_col_node->idx_c;
        sumAC = gv_lils(matC, a, b) + A_current_col_node->value;
        set_lils(matC, a, b, sumAC);

        A_current_col_node = A_current_col_node -> next;
    }
    A_current_row_node = A_current_row_node -> next;
  }

  while(B_current_row_node!=NULL)
  {
    B_current_col_node = B_current_row_node -> col_list_head;
    while(B_current_col_node!=NULL && B_current_col_node->value!=0)
    {
        a = B_current_row_node->idx_r;
        b = B_current_col_node->idx_c;
        sumBC = gv_lils(matC, a, b) + B_current_col_node->value;
        set_lils(matC, a, b, sumBC);

        B_current_col_node = B_current_col_node -> next;
    }
    B_current_row_node = B_current_row_node -> next;
  }

  set_nz(matC);
  return matC;
}


void destroy_lils(sp_lils * mat_l){
    sp_lils_row_node *temp_row_node;
    sp_lils_row_node *current_row_node = mat_l->row_list_head;

    sp_lils_col_node *temp_col_node;
    sp_lils_col_node *current_col_node;

    while(current_row_node!=NULL)
    {
      current_col_node = current_row_node->col_list_head;
      while(current_col_node!=NULL)
      {
        temp_col_node = current_col_node;
        current_col_node = current_col_node -> next;
        free(temp_col_node);
      }
      temp_row_node = current_row_node;
      current_row_node = current_row_node -> next;
      free(temp_row_node);
    }
    free(mat_l);
    return;
}
