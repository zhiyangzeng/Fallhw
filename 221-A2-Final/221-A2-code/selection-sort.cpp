//============================================================================
// Name        : selection-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of selection sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void
SelectionSort::sort(int A[], int size)        // main entry point
{
  /* Complete this function with the implementation of selection sort algorithm 
  Record number of comparisons in variable num_cmps of class Sort
  */
  
  num_cmps = 0;
  for (int k = 0; k < size-1; k++)
  {
    int index = k; 
    for (int i = k+1; i<size; i++){
      if((num_cmps++, A[i] < A[index])) index = i;
    }
    int temp = A[k];
    A[k] = A[index];
    A[index] = temp;
  }
}
