// getPeaks.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "getPeaks" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/

DLList getPeaks(DLList L){

	DLList peaksL = newDLList();
	
    DLListNodeP tmp = L->first;
    
    while(tmp->next != NULL) {
        if(DLListLength(L) < 3) {
            break;
        }
        if(tmp->prev == NULL) {
            tmp = tmp->next;
        }
        if(tmp->value > tmp->prev->value && tmp->value > tmp->next->value) {
            DLListNodeP new = newDLListNode(tmp->value);
            //first time to insert node into peaksL
            if(DLListLength(peaksL) == 0) {
                peaksL->first = new;
                peaksL->curr = new;
                peaksL->last = new;
            } else {
                new->prev = peaksL->curr;
                peaksL->curr->next = new;
                peaksL->last = peaksL->curr;
                peaksL->curr = new;
                
            }
            peaksL->nitems++;
        }
        tmp = tmp->next;
    }

	return peaksL;

}



