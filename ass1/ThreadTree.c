// ThreadTree.c ... implementation of Tree-of-Mail-Threads ADT
// Written by John Shepherd, Feb 2019

//Assignment 1 - Email Threads
//XIAO xiaoshan (z5191546)

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "MMList.h"
#include "MMTree.h"
#include "MailMessage.h"
#include "ThreadTree.h"

// Representation of ThreadTree's

typedef struct ThreadTreeNode *Link;

typedef struct ThreadTreeNode {
	MailMessage mesg;
	Link next, replies;
	char *ID;
} ThreadTreeNode;

typedef struct ThreadTreeRep {
	Link messages;
} ThreadTreeRep;

// Auxiliary data structures and functions

// Add any new data structures and functions here ...

//my own functions
static Link newTTreeNode(MailMessage m);
static Link treeTraversal(Link root, char *id);
static ThreadTree ThreadTreeInsert(ThreadTree t, MailMessage m);

static void doDropThreadTree (Link t);
static void doShowThreadTree (Link t, int level);

// END auxiliary data structures and functions

// create a new empty ThreadTree
ThreadTree newThreadTree (void)
{
	ThreadTreeRep *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate ThreadTree");
	*new = (ThreadTreeRep) { };
	return new;
}

void dropThreadTree (ThreadTree tt)
{
	assert (tt != NULL);
	doDropThreadTree (tt->messages);
}

// free up memory associated with list
static void doDropThreadTree (Link t)
{
	if (t == NULL)
		return;

	for (Link curr = t, next; curr != NULL; curr = next) {
		next = curr->next;
		doDropThreadTree (curr->replies);
		// don't drop curr->mesg, in case referenced elsehwere
		free (curr);
	}
}

void showThreadTree (ThreadTree tt)
{
	assert (tt != NULL);
	doShowThreadTree (tt->messages, 0);
}

// display thread tree as hiearchical list
static void doShowThreadTree (Link t, int level)
{
	if (t == NULL)
		return;
	for (Link curr = t; curr != NULL; curr = curr->next) {
		showMailMessage (curr->mesg, level);
		doShowThreadTree (curr->replies, level + 1);
	}
}

// insert mail message into ThreadTree
// if a reply, insert in appropriate replies list
// whichever list inserted, must be in timestamp-order
ThreadTree ThreadTreeBuild (MMList mesgs, MMTree msgids)
{
    ThreadTree t = newThreadTree();
    
    MMList node = mesgs;
    MMListStart(node);
    MailMessage m;
    
    while(!MMListEnd(node)) {
        m = MMListNext(node);
        if(t->messages == NULL) {
            t->messages = newTTreeNode(m);
        }else {
            ThreadTreeInsert(t,m);
        }
        
    }
    return t;
}

//create a ThreadTree node
static Link newTTreeNode(MailMessage m) {
    struct ThreadTreeNode *new = malloc(sizeof(ThreadTreeNode));
    if (new == NULL) err (EX_OSERR, "couldn't allocate newTTreeNode");
    new->mesg = m;
    new->next = NULL;
    new->replies = NULL;
    new->ID = MailMessageID(m);
    return new;
    
}

//travel the ThreadTree to find a certain message dependens on the ID
static Link treeTraversal(Link root, char *id) {
    if(root == NULL) {
        return NULL;
    }
    if(strcmp(root->ID,id) == 0) {
        return root;
    }
    Link find = treeTraversal(root->next, id);
    if(find)
        return find;
    return treeTraversal(root->replies, id);
   
}

//insert the message into threadtree for a suitable place
static ThreadTree ThreadTreeInsert(ThreadTree t, MailMessage m) {
    
    Link root = t->messages;
    //the Message m should replies to any other MailMessage
    if(MailMessageRepliesTo(m) != NULL) {
        //finding which mail did Message m replies to
        Link tmp = treeTraversal(root, MailMessageRepliesTo(m));
        //if the reply list of that mail is empty,insert m directly
        if(tmp->replies == NULL) {
            tmp->replies = newTTreeNode(m);
        //tmp->replies != NULL
        }else {
            Link curr = tmp->replies;            
            while(curr->next != NULL) {
                curr = curr->next;
            }
            //insert Message m after the last node in the reply list
            curr->next = newTTreeNode(m);
        }
    //the reply-to field is NULL
    } else {
        if(root->next == NULL) {
            root->next = newTTreeNode(m);
        }else {
            Link curr = root;
            while(curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = newTTreeNode(m);
        }
    }
    
    return t;
}
