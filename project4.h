#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#ifndef CS_211_PROJECT__4_V1_PROJECT4_H
#define CS_211_PROJECT__4_V1_PROJECT4_H

#define walkIn 0;
#define callIn 1;

bool debug;

typedef struct node{
    char *name;
    int status;
    int numBurgers;
    int numSalads;
    struct node *next;
} waitList;

// doFunctions //
void doAdd ();
void doCallAhead ();
void doWaiting ();
void doRetrieve ();
void doList ();
void doDisplay ();
void doEstimateTime();

// listFunctions //
void addToList(waitList** head, char *name, int numBurgers, int numSalads, int status);
void displayListInformation(waitList **head);
int displayWaitingTime(waitList** head, char *name);
bool doesNameExist (waitList** head, char *name);
bool updateStatus (waitList** head, char* name);
void retrieveAndRemove (waitList** head, int numBurgers, int numSalads );
int countOrdersAhead (waitList** head, const char* name);
void displayOrdersAhead (waitList** head, const char* name );

//userInterface
void clearToEoln();
int getNextNWSChar ();
int getPosInt ();
char *getName();
void printCommands();




#endif //

