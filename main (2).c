#include "project4.h"

int getNextNWSChar ()
{
    int ch;

    ch = getc(stdin);
    if (ch == EOF || ch == '\n')
        return ch;
    while (isspace (ch))
    {
        ch = getc(stdin);
        if (ch == EOF || ch == '\n')
            return ch;
    }
    return ch;
}

/* read in the next Positive Integer or error:    */
/*    we can count zero as a positive number */
int getPosInt ()
{
    int value = -1;

    /* clear white space characters */
    int ch;
    ch = getc(stdin);
    while (!isdigit(ch))
    {
        if ('\n' == ch)  /* error \n ==> no integer given */
            return -1;
        if (!isspace(ch)) /* error non white space ==> integer not given next */
        {
            clearToEoln();
            return -1;
        }
        ch = getc(stdin);
    }

    value = ch - '0';
    ch = getc(stdin);
    while (isdigit(ch))
    {
        value = value * 10 + ch - '0';
        ch = getc(stdin);
    }

    ungetc (ch, stdin);  /* put the last read character back in input stream */

    /* Integer value less than 0 is an error in this program */
    if (0 > value)
        clearToEoln();

    return value;
}

/* read in the name until the end of the input */
char *getName()
{
    /* skip over the white space characters */
    int ch;
    ch = getc(stdin);
    while (isspace(ch))
    {
        if ('\n' == ch)  /* error \n ==> no integer given */
            return NULL;
        ch = getc(stdin);
    }

    char *word;
    int size;
    size = 10;
    word = (char *) malloc (sizeof(char) * size);

    // read in character-by-character until the newline is encountered
    int count = 0;

    while (ch != '\n')
    {
        if (count+1 >= size)
        {
            // to grow an array to make it "dynamically sized" using malloc
            char* temp;
            int i;
            size = size * 2;
            temp = (char *) malloc (sizeof(char) * size);

            // copy the characters to the new array
            for (i = 0 ; i < count ; i++)
                temp[i] = word[i];

            free (word);
            word = temp;
        }

        word[count] = ch;
        count++;
        word[count] = '\0';

        // read next character
        ch = getc(stdin);
    }

    if (count > 30)
    {
        count = 30;
        word[count] = '\0';
    }

    /* clear ending white space characters */
    while (isspace (word[count-1]))
    {
        count--;
        word[count] = '\0';
    }

    return word;
}

/* Clear input until next End of Line Character - \n */
/* Read in until the first Non-White-Space character is Read */
/* The white space characters are:
 *      space, tab \t, newline \n, vertical tab \v,
 *      form feed \f, and carriage return \r
 */
void clearToEoln()
{
    int ch;

    do {
        ch = getc(stdin);
    }
    while ((ch != '\n') && (ch != EOF));
}

/* Print out a list of the commands for this program */
void printCommands()
{
    printf ("The commands for this program are:\n\n");
    printf ("q - to quit the program\n");
    printf ("? - to list the accepted commands\n");
    printf ("a <# burgers> <# salads> <name> - to add your order to the order list\n");
    printf ("c <# burgers> <# salads> <name> - to add a call-ahead order to the order list\n");
    printf ("w <name> - to specify a call-ahead group is now waiting in the restaurant\n");
    printf ("r <# burgers> <# salads> - to retrieve the first waiting group whose order matches the items on the counter\n");
    printf ("l <name> - list how many orders are ahead of the named order\n");
    printf ("d - display the order list information\n");
    printf ("t <name> - display an estimated wait time for the given order name\n");

    /* clear input to End of Line */
    clearToEoln();
}

int main (int argc, char **argv)
{
                                    // declare an instance of waitList to use as our head
    waitList *head = NULL;
    debug = false;                  // set debugMode to false

    int ch;

    for (int k =0; k < argc; k++)   // for loop used to read command line arguments
    {
        if (strcmp(argv[k], "-d") == 0) // checks each arguments for the "-d" flag
        {
            debug = true;   // if found set debugMode to TRUE
        }
    }

    printf ("Starting Fast Food Order Management Program\n\n");
    printf ("Enter command: ");

    while ((ch = getNextNWSChar ()) != EOF)
    {
        /* check for the various commands */
        if ('q' == ch)
        {
            waitList *temp;
            while(head != NULL)    // if user quits program, free remaining nodes in linked list
            {
                temp = head;
                head = head->next;
                free(temp->name);
                free(temp);

            }
            printf ("Quitting Program\n");
            return (0);
        }
        else if ('?' == ch)
        {
            printCommands();   // print command options
        }
        else if('a' == ch)
        {
            doAdd(&head);       // pass head to add an "in-restaurant" node to list
        }
        else if('c' == ch)
        {
            doCallAhead(&head);  // pass head to add a "call-in" node to list
        }
        else if('w' == ch)
        {
            doWaiting(&head);   // pass head to change customers status
        }
        else if('r' == ch)
        {
            doRetrieve(&head);  // pass head to remove a customer from linked list
        }
        else if('l' == ch)
        {
            doList(&head);  // pass head to list the customers in front said customer
        }
        else if('d' == ch)
        {
            doDisplay(&head); // pass head and display information about all orders
        }

        else if('t' == ch)
        {
            doEstimateTime(&head);  // pass head to calculate a customers waiting time
        }

        else if('\n' == ch)
        {
            /* nothing entered on input line     *
             * do nothing, but don't give error  */
        }
        else
        {
            // prompt for invalid input
            printf ("%c - in not a valid command\n", ch);
            printf ("For a list of valid commands, type ?\n");
            clearToEoln();
        }

        printf ("\nEnter command: ");
    }

    printf ("Quiting Program\n");
    return 1;
}
