#include "vector.h"
#include <stdlib.h>


vector_t * createVector(int initialSize)
{
  vector_t *ptr = (vector_t *)malloc(initialSize*sizeof(int));
  if(ptr == NULL)
  {
    printf("malloc fails!!!!!!");
    return 1;
  }
  return ptr;
}

void destroyVector(vector_t * vector)
{
  free(vector);
}

void resize(vector_t * vector)
{
  vector_t *ptr = (vector_t *)realloc(vector, 2*(vector->maxSize)*sizeof(int));
  vector -> maxSize = 2*(vector -> maxSize);
}

void push_back(vector_t * vector, int element)
{
  
}

int pop_back(vector_t * vector)
{
}

int access(vector_t * vector, int index)
{
}
