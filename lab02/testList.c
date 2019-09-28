// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DLList.h"

int main (void)
{
    DLList myList;
	myList = getDLList (stdin);
	putDLList (stdout, myList);
	assert (validDLList (myList));
    
    //test1 for DLListBefore
    //check the state
    printf("=======Start the Test1========\n");
    
    DLList List1 = myList;
    
	if(myList == NULL) {
	    assert(DLListCurrent (List1) == NULL);
	    assert(DLListLength (List1) == 0);
	} else {
	    assert(DLListLength (List1) >= 1);
	}
	printf("Print the current item: %s\n", DLListCurrent (List1));
    printf("Print the numbers of items in the list: %zu \n",DLListLength(List1));
    
    
    //put the new value before current node
    char *before = "abc";
    DLListBefore(List1, before);
    
    //checking the state after operation
    if(myList == NULL) {
	    assert(DLListCurrent(List1) == "abc");
	    assert(DLListLength(List1) == 1);
	} else if (DLListLength (myList) == 1) {
		assert(DLListCurrent(List1) == "abc");
	    assert(DLListLength(List1) == 2);
	} else {
	    printf("Print the current item: %s\n", DLListCurrent (List1));
	    assert(strcmp(DLListCurrent (List1),"abc") == 0);
	    printf("Print the numbers of items in the list: %zu\n",DLListLength(List1)); 
	    assert(DLListLength(List1) == 5);
	}
    
    printf("Print the new list:\n");
    putDLList (stdout, List1);
    assert(validDLList(List1));
    
    
    //test2 for DLListDelete
    //check the state 
    printf("\n======== Start test2 =======\n");
    
    DLList List2 = myList;
    
    if(myList == NULL) {
	    assert(DLListCurrent (List2) == NULL);
	    assert(DLListLength (List2) == 0);
	} else {
	    assert(DLListLength (List2) >= 1);
	}
	printf("\nPrint the current item: %s\n", DLListCurrent (List1));
	
	DLListDelete (List2);
    
     if (DLListLength (myList) == 1) {
		assert(DLListCurrent(List2) == NULL);
	    assert(DLListLength(List2) == 0);
	} else {
	    printf("Print the current item after deleting: %s\n", DLListCurrent (List2));
	    assert(strcmp(DLListCurrent (List2),"this is") == 0);
	    printf("Print the numbers of items in the list: %zu\n",DLListLength(List2)); 
	    assert(DLListLength(List2) == 4);
	}
    
    printf("Print the new list:\n");
    putDLList (stdout, List2);
    assert(validDLList(List2));
    
    //test3 for DLListAfter, adding new node to the end of the list
    //check the state
    printf("======== Start test3 =======\n");
    
    DLList List3 = myList;
    
    if(List3 == NULL) {
	    assert(DLListCurrent (List3) == NULL);
	    assert(DLListLength (List3) == 0);
	} else {
	    assert(DLListLength (List3) >= 1);
	}
	char *after = "def";
	
	DLListMoveTo (List3, 4);
	DLListAfter (List3, after);
    
     if(myList == NULL) {
	    assert(DLListCurrent(List3) == "def");
	    assert(DLListLength(List3) == 1);
	} else if (DLListLength (myList) == 1) {
		assert(DLListCurrent(List3) == "def");
	    assert(DLListLength(List3) == 2);
	} else {
	    printf("Print the current item after adding: %s\n", DLListCurrent (List3));
	    assert(strcmp(DLListCurrent (List3),"def") == 0);
	    printf("Print the numbers of items in the list: %zu\n",DLListLength(List3)); 
	    assert(DLListLength(List3) == 5);
	}
    
    printf("Print the new list:\n");
    putDLList (stdout, List3);
    assert(validDLList(List3));
    
    
    //short test
    //check the state
    printf("======== Start test4 =======\n");
    
    DLList List4 = myList;
    
    if(List4 == NULL) {
	    assert(DLListCurrent (List4) == NULL);
	    assert(DLListLength (List4) == 0);
	} else {
	    assert(DLListLength (List4) >= 1);
	}
	
	//delete the text until there has only one line of content
	while(DLListLength (List4) > 1) {
	    DLListDelete (List4);
	}
	
	//check the state after deleting
	assert(DLListLength (List4) == 1);
	putDLList (stdout, List4);
	
	//insert a new node before the curr
	char *new = "This is the new first line";
	DLListBefore (List4, new);
	
	
	assert(DLListLength (List4) == 2);
	putDLList (stdout, List4);
	
	printf("\nPrint the current item after adding: %s\n", DLListCurrent (List4));
	
	//delete the text until the list is empty
	while(DLListLength (List4) >= 1) {
	    DLListDelete (List4);
	}
	
	
	//now the list should be empty
	assert(DLListLength (List4) == 0);
	
	
	DLListAfter (List4, new);
	putDLList (stdout, List4);
	
	
	assert(validDLList(List4));
	
	freeDLList (myList);
	return EXIT_SUCCESS;
}


