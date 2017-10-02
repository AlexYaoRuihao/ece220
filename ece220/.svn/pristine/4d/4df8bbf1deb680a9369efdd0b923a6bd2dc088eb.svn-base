#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>





sp_tuples * load_tuples(char* input_file)
{
	f=fopen(input_file,"r");
    if (f== NULL){
    	printf("%s open failed\n", input_file );
    	return NULL;
    }
    sp_tuples* sp_tuples = (sp_tuples*)malloc(sizeof(sp_tuples));

    int row, col;
    double value;

    char line[256]; 
    
    FILE *f = fopen(input_file, "r");

    sp_tuples * myTuples = (sp_tuples*)malloc(sizeof(sp_tuples)); 

    myTuples->tuples_head = NULL; 

    fscanf(f, "%d %d\n", &(myTuples->m), &(myTuples->n)); 
    while(fgets(line, sizeof(line), f))
    {
        sscanf(line, "%d %d %lf\n", &row, &col, &value); 
        set_tuples(myTuples, row, col, value);                 
    }

    helper(myTuples); 

    fclose(f);

    return myTuples;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
      sp_tuples_node * cur = mat_t->tuples_head;
    
      while(cur != NULL)
    {
        if(cur->row == row && cur->col == col)
        {
            return cur->value;
        }
        else
        {
            cur = cur->next;
        }
    }
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{     
   /* sp_tuples_node* pre =NULL;
    sp_tuples_node* current =(*mat_t).tuples_head;
    sp_tuples_node* temp =NULL;
    int i, j;

    while(current!=NULL){
    	i=current->row;
    	j=current->col;
    	if(i==row && j==col){
    		if(value==0){
    			if(pre==NULL){
    				temp = current->next;
    				free(current);
    				mat_t->tuples_head=temp;
    				mat_t->nz--;
    				return;
    			}
    			temp=current->next;
    			free(current);
    			pre->next=temp;
    			mat_t->nz--;
    			return;
    		}
    		current->value = value;
    		return;
    	}
    	current=current->next;
    }
    sp_tuples_node* new_node=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    new_node->value=value;
    new_node->row=row;
    new_node->col=col;
    new_node->next=mat_t->tuples_head;
    mat_t->tuples_head=new_node;
    return;*/
    sp_tuples_node *tmp;
    sp_tuples_node *pre;

        if(mat_t->tuples_head == NULL && value != 0){// empty list, add the head (not zero)
                mat_t->tuples_head = malloc(sizeof(sp_tuples_node));
                mat_t->tuples_head->row = row;
                mat_t->tuples_head->col = col;
                mat_t->tuples_head->value = value;
                mat_t->tuples_head->next = NULL;
                mat_t->nz++;
                return;
        }

        tmp = mat_t->tuples_head;
        pre = NULL;
        while(tmp != NULL && row > tmp->row){
                pre = tmp;
                tmp = tmp->next;
        }

        while(tmp != NULL && row >= tmp->row && col > tmp->col){
                pre = tmp;
                tmp = tmp->next;
        }

        if(tmp != NULL && row == tmp->row && col == tmp->col){// coordinate repeat
                if(value != 0)// coordinate repeat, value is not 0, change the value
                        tmp->value = value;
                else{// coordinate repeat, value is 0, delete
                        if(pre != NULL){ // the delete node is not at the head
                                pre->next = tmp->next;
                        }else{ // the delete node is at the head
                                mat_t->tuples_head = mat_t->tuples_head->next;
                        }
                        free(tmp);
                        mat_t->nz--;
                }

        }else if(value != 0){// no coordinates repeat && not 0
                if(pre != NULL){// add node not at the head
                        pre->next = malloc(sizeof(sp_tuples_node));
                        pre->next->row = row;
                        pre->next->col = col;
                        pre->next->value = value;
                        pre->next->next = tmp;
                        mat_t->nz++;
                }else{// add node at the head
                        mat_t->tuples_head = malloc(sizeof(sp_tuples_node));
                        mat_t->tuples_head->row = row;
                        mat_t->tuples_head->col = col;
                        mat_t->tuples_head->value = value;
                        mat_t->tuples_head->next = tmp;
                        mat_t->nz++;
                }
        }

}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
	f=fopen(input_file,"r");
    if (f== NULL){
    	printf("%s open failed\n", input_file );
    	return NULL;
    }

	FILE *f = fopen(file_name, "w");
    
    fwrite(mat_t, sizeof(sp_tuples), sizeof(mat_t), f);

    fclose(f);
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
	sp_tuples * matTemp = (sp_tuples*)malloc(sizeof(sp_tuples)); 
	matTemp->m = matA->m;
	matTemp->n = matA->n;
	matTemp->tuples_head = NULL;
	int x, y;
	if(matA->m == matB->m && matA->n == matB->n) 
	{
		sp_tuples_node * curA = matA->tuples_head;
		sp_tuples_node * curB = matB->tuples_head;
		double sum1 = 0; 
		double sum2 = 0;		
	while(curA != NULL) 
	{
			x = curA->row;
			y = curA->col;

			sum1 = gv_tuples(matTemp, x, y) + curA->value;

			set_tuples(matTemp, x, y, sum1); 
			
			curA = curA->next;
	}

	while(curB != NULL)
	{
			x = curB->row;
			y = curB->col;
			sum2 = gv_tuples(matTemp, x, y) + curB->value;
			set_tuples(matTemp, x, y, sum2); 
			curB = curB->next;
	}

	helper(matTemp);
	return matTemp;	
	}
	else
	{
		return NULL; 
	}	
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB)
{ 
   if(matA->n == matB->m)
{
	sp_tuples * matTemp = (sp_tuples*)malloc(sizeof(sp_tuples)); 
	matTemp->m = matA->m;
	matTemp->n = matA->n;
	matTemp->nz = 0;
	matTemp->tuples_head = NULL;
	sp_tuples_node * curA = matA->tuples_head;
	int Ax, Ay, Bx, By;
	double sum = 0;

	while(curA != NULL)
	{
	Ax = curA->row;
	Ay = curA->col;
	sp_tuples_node * curB = matB->tuples_head;
	while(curB != NULL)
{
	Bx = curB->row;
	By = curB->col;
	if(Bx == Ay)
	{
	sum = gv_tuples(matTemp, Ax, By) + curA->value*curB->value;
	set_tuples(matTemp, Ax, By, sum);
	}

	curB = curB->next;
}

	curA = curA->next;
	}

	helper(matTemp);

	return matTemp;				
	}
else
{
	return NULL; 
}

}


	
void destroy_tuples(sp_tuples * mat_t){
	
    sp_tuples_node * move = mat_t->tuples_head;
    sp_tuples_node * temp;

    while(move != NULL)
    {
        temp = move;
        move = move->next;
        free(temp);
    }
    mat_t->tuples_head = NULL;
    free(mat_t);    
}  


void helper(sp_tuples * mat_temp)
{
	sp_tuples_node * cur = mat_temp->tuples_head;
	mat_temp->nz = 0;
	
	while(cur != NULL) //count non-zero elements
	{
		mat_temp->nz++;
		cur = cur->next;
	}
}



