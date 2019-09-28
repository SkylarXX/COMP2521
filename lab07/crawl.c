// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders
// <vince@kyllikki.org>

#include <ctype.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include "graph.h"
#include "html.h"
#include "set.h"
#include "stack.h"
#include "url_file.h"
#include "queue.h"

#define BUFSIZE 1024

static void setFirstURL (char *, char *);

int main (int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	char next[BUFSIZE];
	int maxURLs;

	if (argc > 2) {
		strcpy (baseURL, argv[1]);
		setFirstURL (baseURL, firstURL);
		maxURLs = atoi (argv[2]);
		if (maxURLs < 40)
			maxURLs = 40;
	} else {
		fprintf (stderr, "Usage: %s BaseURL MaxURLs\n", argv[0]);
		exit (1);
	}
	
	
	Queue ToDoList = newQueue();
	//create new graph and new set
	Graph g = newGraph(maxURLs);
    //the URL that has been seen will be put into s
	Set seen = newSet();
	
	//put firstURL into list	
	enterQueue(ToDoList, firstURL);
	insertInto(seen,firstURL);

    while(!emptyQueue(ToDoList) && (int)nVertices(g) < maxURLs) {
        char *temp = leaveQueue(ToDoList);
        
        strcpy(next,temp);
        //insertInto(seen,next);
        
        handle = url_fopen (next, "r");
        if (!handle) {

            fprintf (stderr, "Couldn't open %s\n", next);
            exit (1);
        }
        
        //for each line in the opened URL
        while (!url_feof (handle)) {

            url_fgets (buffer, sizeof(buffer), handle);
            // fputs(buffer,stdout);
            int pos = 0;
            char result[BUFSIZE];
            memset (result, 0, BUFSIZE);
            //printf("%s\n",buffer);
            while ((pos = GetNextURL (buffer, next, result, pos)) > 0) {

                showQueue (ToDoList);
                //showSet(seen);
                //insertInto(s,result);
                
                if((int)nVertices(g) <= maxURLs || !isConnected(g,next,result)) {
                
                    printf("next page: \n %s \n",next);
                    printf("result found:\n\n%s\n\n",result);
                    //printf("\n addEdge \n");
                    addEdge (g,next,result);
                    printf("after add : %d",(int)nVertices(g));
                }
                if(isElem (seen, result) == 0) {
                    //printf("\n none seen \n");
                    insertInto(seen,result);
                    enterQueue(ToDoList,result);
                      
                }
                printf ("Found: '%s'\n", result);
                memset (result, 0, BUFSIZE);
            }
            //printf("POS: %d\n",pos);
        }
        
        free(temp);
        url_fclose (handle);
        sleep (1);      
    }
    showGraph(g,0);
    showGraph (g, 1);
    dropQueue(ToDoList);
    dropGraph (g);
    dropSet(seen);

	
    
    return 0;   
}

// setFirstURL(Base,First)
// - sets a "normalised" version of Base as First
// - modifies Base to a "normalised" version of itself
static void setFirstURL (char *base, char *first)
{
	char *c;
	if ((c = strstr (base, "/index.html")) != NULL) {
		strcpy (first, base);
		*c = '\0';
	} else if (base[strlen (base) - 1] == '/') {
		strcpy (first, base);
		strcat (first, "index.html");
		base[strlen (base) - 1] = '\0';
	} else {
		strcpy (first, base);
		strcat (first, "/index.html");
	}
}
