#include "project4.h"

void addToList(waitList** head, char *name, int numBurgers, int numSalads, int status)
{
    waitList *new = (waitList*) malloc (sizeof(waitList));     //allocate memory for the new node
    new->name = name;                 // set the corresponding data items
    new->numBurgers = numBurgers;
    new-> numSalads = numSalads;

    if (status == 1)            /* if we have flagged the customer as callIn
                                 from previous function, set the data member to call-in */ //shark
    {
        new->status = callIn;
    }
    else if (status == 0) // if we have flagged the customer as walkIn from previous function, set the data member to walk-in
    {
        new->status = walkIn;
    }

    new-> next = NULL;  // initialize the next node to NULL

    if(*head == NULL)   // initialize the head of our linked list
    {
        *head = new;
    }
    else    // if we already have a head
    {
        waitList *temp = *head;     // use temp variable to parse the list
        while(temp)
        {
            if(debug == true)       // if debug mode is on, display the nodes we traverse through
            {
                printf("Visiting node %s with values %d and %d\n", temp->name, temp->numBurgers, temp->numSalads);
            }
            if (temp->next== NULL)      // if we've reached the end, break out of our loop
            {
                break;
            }
            temp = temp-> next;      // otherwise keep traversing list
        }

        temp->next = new;  // add the new node to the end of the list
    }
}
void displayListInformation(waitList **head)
{
    waitList *temp = *head;     // temp variable for traversing list

    if (temp == NULL)   // if the head is NULL the list is empty
    {
        printf("List is empty.");
    }

    while (temp != NULL)    // otherwise traverse list
    {
        if(temp->status == 0)  // print information for all in-store customers
        {
            printf("%s: %d burgers and %d salads, currently in the restaurant.\n", temp->name, temp->numBurgers,
                   temp->numSalads);
        }
        else   //print information for all out-of-store customers
        {
            printf("%s: %d burgers and %d salads, currently not in the restaurant.\n", temp->name, temp->numBurgers,
                   temp->numSalads);
        }
        temp = temp-> next;  // go to next node
    }
}
int displayWaitingTime(waitList** head, char *name)
{
    waitList *temp = *head;     //temp variable for traversing list
    int waitTime = 0;       // integer variable to store the calculated wait time for customer

    while (strcmp(temp->name, name) != 0)   // traverse list while a valid name is not found
    {
        if(debug == true)   // if debug mod is on, print the nodes we traverse
        {
            printf("Visiting node %s with values %d and %d\n", temp->name, temp->numBurgers, temp->numSalads);
        }
        // update and store the wait time for each customer in from of the target customer
        waitTime = waitTime + (temp->numBurgers * 5) + (temp->numSalads * 2);

        temp = temp->next; //  go to next node
    }

    // return our calculated wait time
    return waitTime;
}

bool doesNameExist (waitList** head, char *name)
{
    waitList *temp = *head;  // temp variable for traversing list

    if (temp == NULL)   // if the list is empty, name not found
    {
        return false;
    }

    while (temp != NULL)    // otherwise traverse the list
    {
        if(strcmp(temp->name, name) == 0)   // if a valid name is found, return true
        {
            return true;
        }
        temp = temp->next;  // go to next node
    }
}
bool updateStatus (waitList** head, char* name)
{
    waitList *temp = *head; // temp variable for traversing list

    while (temp != NULL)    // traverse list until null node is reached
    {
        if(strcmp(temp->name, name) == 0)   // if a valid name is found
        {
            if (temp->status == 1)  // and if the customers status is a call-in
            {
                temp->status = walkIn;  // change their status to walk-in, and return true
                return true;
            }
            else    // otherwise the name wasn't found
            {
                return false;
            }
        }
        temp = temp->next; // go to next node
    }
}
void retrieveAndRemove (waitList** head, int numBurgers, int numSalads )
{
    waitList *temp = *head;     // 2 pointers to keep track of the current and previous nodes of our list
    waitList *prev = *head;

    // if the head of list is matching order...
    if (temp != NULL && temp->numBurgers <= numBurgers && temp->numSalads <= numSalads && temp->status == 0 )
    {
        *head = temp->next; // move the head

        free(temp->name);   // free the old head
        free(temp);
        return;
    }
    // otherwise traverse the list until a matching order is found
    while (temp != NULL && ((temp->numBurgers > numBurgers || temp->numSalads > numSalads) || temp->status != 0))
    {
        if(debug == true)  // if debug mode is on, print the nodes we traverse
        {
            printf("Visiting node %s with values %d and %d\n", temp->name, temp->numBurgers, temp->numSalads);
        }
        prev = temp;    // update our previous node
        temp = temp->next;  // go to next node
    }
    if (temp == NULL)   // if we reached the end, no matching order was found
    {
        printf("No matching orders found.");
        return;
    }
    if(debug == true)
    {
        printf("Visiting node %s with values %d and %d\n", temp->name, temp->numBurgers, temp->numSalads);
    }
    prev->next = temp->next;    // when matching order is found, remove the node and patch the list back together
    free(temp->name);
    free(temp);
}
int countOrdersAhead (waitList** head, const char* name )
{
    int orderCount = 0;   // integer variable to store the number of orders ahead of a customer
    waitList *temp = *head; // temp pointer for traversing list

    while (temp != NULL && strcmp(temp->name, name) != 0 )   // traverse the list until a matching name is found
    {
        orderCount = orderCount + 1;    // increment oder count for each node
        temp = temp->next;  // go to next node
    }
    return orderCount;
}

void displayOrdersAhead (waitList** head, const char* name )
{
    waitList *temp = *head;     // temp pointer for traversing list

    while (temp != NULL && strcmp(temp->name, name) != 0 )  // traverse list until valid name is found
    {
        // print order info for each node
        printf("%s: %d burgers and %d salads\n", temp->name, temp->numBurgers, temp->numSalads);

        temp = temp->next;// go to next node
    }
}
