#include "project4.h"

void doAdd (waitList** head)
{
    /* get number of burgers ordered from input */
    int NumBurgers = getPosInt();
    if (NumBurgers < 0)
    {
        printf ("Error: Add command requires an integer value of at least 0\n");
        printf ("Add command format: a <# burgers> <# salads> <name>\n");
        return;
    }

    /* get number of salads ordered from input */
    int NumSalads = getPosInt();
    if (NumSalads < 0)
    {
        printf ("Error: Add command requires an integer value of at least 0\n");
        printf ("Add command format: a <# burgers> <# salads> <name>\n");
        return;
    }

    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Add command requires a name to be given\n");
        printf ("Add command format: a <# burgers> <# salads> <name>\n");
        return;
    }



    // add code to perform this operation here

    int status = walkIn;   // flag the customers status to walkIn

    if (doesNameExist (head, name)) // if the name already exists, prompt user and free the allocated memory for the name
    {
        printf("An order with the given name already exists. Try another name.\n");
        free(name);
    }
    else    // otherwise the name doesn't exist, and we can add it to our linked list
    {
        printf ("Adding In-restaurant order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);
        addToList(head, name, NumBurgers, NumSalads, status);
    }

}


void doCallAhead (waitList** head)
{
    /* get number of burgers ordered from input */
    int NumBurgers = getPosInt();
    if (NumBurgers < 0)
    {
        printf ("Error: Call-ahead command requires an integer value of at least 0\n");
        printf ("Call-ahead command format: c <# burgers> <# salads> <name>\n");
        return;
    }

    /* get number of salads ordered from input */
    int NumSalads = getPosInt();
    if (NumSalads < 0)
    {
        printf ("Error: Call-ahead command requires an integer value of at least 0\n");
        printf ("Call-ahead command format: c <# burgers> <# salads> <name>\n");
        return;
    }


    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Call-ahead command requires a name to be given\n");
        printf ("Call-ahead command format: c <# burgers> <# salads> <name>\n");
        return;
    }



    // add code to perform this operation here

    int status = callIn;    // flag customer as call-in status

    if (doesNameExist (head, name))  // if the name already exists, prompt user and free the allocated memory for the name
    {
        free(name);
        printf("An order with the given name already exists. Try another name.\n");
    }
    else            // otherwise the name doesn't exist, and we can add it to our linked list
    {
        printf ("Adding Call-ahead order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);
        addToList(head, name, NumBurgers, NumSalads, status);
    }
}

void doWaiting (waitList** head)
{
    /* get order name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Waiting command requires a name to be given\n");
        printf ("Wait command format: w <name>\n");
        return;
    }



    // add code to perform this operation here
    if (doesNameExist (head, name))     // check if the name exists
    {
        if (updateStatus (head, name))  // if it exists, change the status of said customer to walk-in
        {
            printf ("Call-ahead order \"%s\" is now waiting in the restaurant\n", name);
        }
        else    // if status is already marked as walk-in, prompt user
        {
            printf("Already marked as in store");
        }
    }
    else    // if a matching name was not found, prompt user and free the memory for name
    {
        printf("No match found for the given name. Try again!\n");
    }
    free(name);
}

void doRetrieve (waitList** head)
{
    /* get info of prepared food ready on the counter from input */
    int PreparedBurgers = getPosInt();
    if (PreparedBurgers < 0)
    {
        printf ("Error: Retrieve command requires an integer value of at least 0\n");
        printf ("Retrieve command format: r <# burgers> <# salads>\n");

        return;
    }

    int PreparedSalads = getPosInt();
    if (PreparedSalads < 0)
    {
        printf ("Error: Retrieve command requires an integer value of at least 0\n");
        printf ("Retrieve command format: r <# burgers> <# salads>\n");
        return;
    }

    clearToEoln();
    printf ("Retrieve and remove the first group that can pick up the order of %d burgers and %d salads\n", PreparedBurgers ,PreparedSalads);

    // add code to perform this operation here

    // call retrieve and remove to parse for the first matching order that can be fulfilled
    retrieveAndRemove (head, PreparedBurgers, PreparedSalads );

}

void doList (waitList** head)
{
    /* get order name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: List command requires a name to be given\n");
        printf ("List command format: l <name>\n");
        return;
    }
    // add code to perform this operation here

    if (doesNameExist(head,name))  // if the name exists, display the orders ahead of said customer
    {
        printf ("Order for \"%s\" is behind the following orders\n", name);
        countOrdersAhead(head, name);
        displayOrdersAhead(head, name);
    }
    else // else if name doesn't exist, prompt user and free memory of name
    {
        printf("No match found for the given name. Try again!\n");
    }
    free(name);
}

void doDisplay (waitList** head)
{
    clearToEoln();
    printf ("Display information about all orders\n");

    // add code to perform this operation here

    // call display info function and pass our linked list
    displayListInformation(head);
}


void doEstimateTime(waitList** head)
{
    /* get order name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Time command requires a name to be given\n");
        printf ("Time command format: t <name>\n");
        return;
    }
    // add code to perform this operation here
    int mins = 0; // integer variable that will store the return of the calculated wait time

    if (doesNameExist (head, name))   // if name exists, call function to calculate wait time and print it
    {
        mins = displayWaitingTime(head, name);
        printf("Estimated wait time for %s is %d minutes.\n", name , mins );
    }
    else // if no existing name found, free the name and prompt user
    {
        printf("No match found for the given name. Try again!\n");
    }

    free(name);

}
