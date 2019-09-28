// MMList.c ... implementation of List-of-Mail-Messages ADT
// Written by John Shepherd, Feb 2019

//Assignment 1 - Email Threads
//XIAO xiaoshan (z5191546)

#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "MMList.h"
#include "MailMessage.h"

// data structures representing MMList

typedef struct MMListNode *Link;

typedef struct MMListNode {
	MailMessage data; // message associated with this list item
	Link next;		  // pointer to node containing next element
} MMListNode;

typedef struct MMListRep {
	Link first; // node containing first value
	Link last;  // node containing last value
	Link curr;  // current node (for iteration)
} MMListRep;

static Link newMMListNode (MailMessage mesg);

// create a new empty MMList
MMList newMMList (void)
{
	MMListRep *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate MMList");
	*new = (MMListRep) { };
	return new;
}

// free up memory associated with list
// note: does not remove Mail Messages
void dropMMList (MMList L)
{
	assert (L != NULL);
	Link curr = L->first;
	while (curr != NULL) {
		Link next = curr->next;
		free (curr);
		curr = next;
	}
	free (L);
}

// display list as one integer per line on stdout
void showMMList (MMList L)
{
	assert (L != NULL);
	for (Link curr = L->first; curr != NULL; curr = curr->next)
		showMailMessage (curr->data, 0);
}

// insert mail message in order
// ordering based on MailMessageDateTime
void MMListInsert (MMList L, MailMessage mesg)
{
	assert (L != NULL);
	assert (MMListIsOrdered (L));

	assert (mesg != NULL);

    
    Link p = L->first;
    Link pre = p;
    
    DateTime m = MailMessageDateTime (mesg);
    Link new = newMMListNode(mesg);
    
    //if the list is empty
    if(p == NULL) {
        L->first = new;
        L->last = new;
        return;
    }
    //if the list is not empty, we can get the DateTime of first node
    DateTime list = MailMessageDateTime (p->data);
    
    while(p->next != NULL && DateTimeAfter(m,list)) {
        pre = p;
        p = p->next;
        //update the DateTime when we move to the next node
        list = MailMessageDateTime (p->data);
    }
    
    if(DateTimeBefore(m,list)) {
        //if the node will be inserted before the first one
        if(p == L->first) {
            new->next = p;
            L->first = new;
        } else {
            new->next = p;
            pre->next = new;
        }
        
        //finding the node that is equal to the new node
    } else if(m == list) {
        new->next = p;
        pre->next = new;
        //the time of given message is after the last node in the list,
        //it becomes the new last
    } else {
        p->next = new;
        new->next = NULL;
        L->last = new;
    }
    
}

// create a new MMListNode for mail message
// (this function is used only within the ADT)
static Link newMMListNode (MailMessage mesg)
{
	Link new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate MMList node");
	*new = (MMListNode) { .data = mesg };
	return new;
}

// check whether a list is ordered (by MailMessageDate)
bool MMListIsOrdered (MMList L)
{
	DateTime prevDate = NULL;
	for (Link n = L->first; n != NULL; n = n->next) {
		DateTime currDate = MailMessageDateTime (n->data);
		if (prevDate != NULL && DateTimeAfter (prevDate, currDate))
			return false;
		prevDate = currDate;
	}
	return true;
}

// start scan of an MMList
void MMListStart (MMList L)
{
	assert (L != NULL);
	L->curr = L->first;
}

// get next item during scan of an MMList
MailMessage MMListNext (MMList L)
{
	assert (L != NULL);
	if (L->curr == NULL)
		// this is probably an error
		return NULL;

	MailMessage mesg = L->curr->data;
	L->curr = L->curr->next;
	return mesg;
}

// check whether MMList scan is complete
bool MMListEnd (MMList L)
{
	assert (L != NULL);
	return (L->curr == NULL);
}
