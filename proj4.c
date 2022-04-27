
// Samuel Bankole

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;
int debugMode = FALSE;


/* forward definition of functions */
void clearToEoln(); 

/* Read in until the first Non-White-Space character is Read */
/* The white space characters are:
 *      space, tab \t, newline \n, vertical tab \v, 
 *      form feed \f, and carriage return \r
 */ 
 
 typedef struct restaurant
{
	char* name;
	int size;
	int status;
	struct restaurant* next;
	struct restaurant* prev;
} bar;

void addToList(bar **head, bar **tail, int theSize, char* names, int status){
	bar* ptr = (bar*) malloc(sizeof(bar));
	ptr->name = names;
	ptr->size = theSize;
	ptr->status = status;
	ptr->next = NULL;
	if (*head == NULL){
		*head = ptr;
		*tail = ptr;
	}
	else{
	    (*tail)->next = ptr;
	    ptr->prev = *tail;
	    *tail = ptr;
	}
}

int doesNameExist(bar* pointer, char* name){
	if (pointer == NULL){
		return FALSE;
	}
	else{
		bar* temp = pointer;
		while (temp != NULL){
			if (debugMode == TRUE){
  			printf("\n");
            printf("traversing...");
  			printf("name: %s \n", temp->name);
	    	printf("size: %d \n", temp->size);
	    	if (temp->status == TRUE){
	    	 printf("status: In restaurant \n");
			}
			else {
		     printf("status: Not in restaurant \n");	
	    	}
       	 }	
			if (strcmp(temp->name, name) == 0){
				return TRUE;
			}
		temp = temp->next;	
		}
		return FALSE;
	}
}

char* retrieveAndRemove(bar** point, bar** tailP, int tsize){
	char* nameV;
	if (*point == NULL){
		return;
	}
	else if ((*point)->size <= tsize && (*point)->next == NULL){
		   nameV = (*point)->name;
		   bar* temp = *point;
		   free(temp);
		   *point = NULL;
		   return nameV;
		}
	else{
		if ((*point)->size <= tsize){
		   bar* temp;	
		   temp = *point;
		   *point = (*point)->next;
		   nameV = temp->name;	
		   free(temp);
		   return nameV;
		}
		if ((*tailP)->size <= tsize){
	   	 bar* temp;
		 temp = *tailP;
	   	 *tailP = (*tailP)->prev;
	   	 (*tailP)->next = NULL;
	   	 nameV = temp->name;
	   	 free(temp);
	   	 return nameV;
	   }
	   bar* temp = *point;
		while(temp->next != NULL){
			if (temp->size <= tsize){	
			  nameV = temp->name;
		      temp->prev->next = temp->next;
		      temp->next->prev = temp->prev;
		      free(temp);
		      return nameV;
		    }
		temp = temp->next;
	   }
    }
}

int countGroupsAhead(bar* head, char* name){
  if (head == NULL){
  	return 0;
  }
  
  int num = 0;
  bar* temp =head;
  while(strcmp(temp->name,name) != 0){
  	if (debugMode == TRUE){
  		printf("\n");
  		printf("name: %s \n", temp->name);
	    printf("size: %d \n", temp->size);
	    if (temp->status == TRUE){
	    	printf("status: In restaurant \n");
		}
		else {
		   printf("status: Not in restaurant \n");	
		}
	}
   	num++;
   	temp = temp->next;
   }
   return num;
}

void displayGroupSizeAhead(bar* head, char* name){
	if (head == NULL){
		return;
	}
	int i = 0;
	bar* temp = head;
	while (temp!= NULL){
	  if (debugMode == TRUE){
  		printf("\n");
  		printf("name: %s \n", temp->name);
	    printf("size: %d \n", temp->size);
	    if (temp->status == TRUE){
	    	printf("status: In restaurant \n");
		}
		else {
		   printf("status: Not in restaurant \n");	
	    }
       }
	  if (strcmp(temp->name, name) == 0){
		break;
	  } 
	printf("group %d, %s with %d people \n", i+1 , temp->name, temp->size);
	i++;
	temp = temp->next;
	}
}

void displayListInformation(bar* head){
	if (head == NULL){
		return;
	}
	bar* temp = head;
	while (temp != NULL){
		printf("\n");
		printf("name: %s \n", temp->name);
	    printf("size: %d \n", temp->size);
	    if (temp->status == TRUE){
	    	printf("status: In restaurant \n");
		}
		else {
		   printf("status: Not in restaurant \n");	
		}
	printf ("\n");
	temp = temp->next;
	}	
}

int getNextNWSChar ()
{
 int ch;

 ch = getc(stdin);
 if (ch == EOF || ch == '\n')
   return ch;
 while (isspace (ch))    ch = getc(stdin);

   {
    if (ch == EOF || ch == '\n')
      return ch;
   }
 return ch;
}

void statusChange(bar* head, char* name){
	bar* temp = head;
	while(temp!= NULL){
	  if (debugMode == TRUE){
  			printf("\n");
            printf("traversing...\n");
  			printf("name: %s \n", temp->name);
	    	printf("size: %d \n", temp->size);
	    	if (temp->status == TRUE){
	    	 printf("status: In restaurant \n");
			}
			else {
		     printf("status: Not in restaurant \n");	
	    	}
       	}	
		if (strcmp(temp->name, name) == 0){
			temp->status = TRUE;
		return;
		}
	temp = temp->next;
	}
}

/* read in the next Positive Integer or error:    */
/* This is based on the Mathematical definition of a Postive Integer */
/*    zero is not counted as a positive number */ 
int getPosInt ()
{
 int value = 0;

 /* clear white space characters */
 int ch;
 ch = getc(stdin);
 while (!isdigit(ch))
   {
    if ('\n' == ch)  /* error \n ==> no integer given */
       return 0;
    if (!isspace(ch)) /* error non white space ==> integer not given next */
      {
       clearToEoln();
       return 0;
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

 /* Integer value of 0 is an error in this program */
 if (0 == value)
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
       
       // printf ("Growing array from size %d to size %d\n", count, size);
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
 printf ("a <size> <name> - to add a group to the wait list\n");
 printf ("c <size> <name> - to add a call-ahead group to the wait list\n");
 printf ("w <name> - to specify a call-ahead group is now waiting in the restaurant\n");
 printf ("r <table-size> - to retrieve the first waiting group that can fit at the available table size\n");
 printf ("l <name> - list how many groups are ahead of the named group\n");
 printf ("d - display the wait list information\n");
       
 /* clear input to End of Line */
 clearToEoln();
}

void doAdd (bar* *head, bar* *tail)
{
 /* get group size from input */
 int size = getPosInt();
 if (size < 1)
   {
    printf ("Error: Add command requires an integer value of at least 1\n");
    printf ("Add command is of form: a <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
   }

 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Add command requires a name to be given\n");
    printf ("Add command is of form: a <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
   }

 printf ("Adding In-restaurant group \"%s\" of size %d\n", name, size);
 int status = TRUE;
 // add code to perform this operation here
 addToList(head, tail, size, name, status);
}


void doCallAhead (bar* *heade, bar* *taile)
{
 /* get group size from input */
 int size = getPosInt();
 if (size < 1)
   {
    printf ("Error: Call-ahead command requires an integer value of at least 1\n");
    printf ("Call-ahead command is of form: c <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
   }

 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Call-ahead command requires a name to be given\n");
    printf ("Call-ahead command is of form: c <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
   }

 printf ("Adding Call-ahead group \"%s\" of size %d\n", name, size);
 int status = FALSE;
 // add code to perform this operation here
 addToList(heade, taile, size, name, status);
}

void doWaiting (bar* head)
{
 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Waiting command requires a name to be given\n");
    printf ("Waiting command is of form: w <name>\n");
    printf ("  where: <name> is the name of the group that is now waiting\n");
    return;
   }

 // add code to perform this operation here
 int check;
 check = doesNameExist(head, name);
 if (check == TRUE){
 	statusChange(head, name);
 	printf ("Call-ahead group \"%s\" is now waiting in the restaurant\n", name);
 }
 else if (check == FALSE){
 	printf("This group is not on the list \n");
 }

}

void doRetrieve (bar** head, bar** tail)
{
 /* get table size from input */
 int size = getPosInt();
 if (size < 1)
   {
    printf ("Error: Retrieve command requires an integer value of at least 1\n");
    printf ("Retrieve command is of form: r <size>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    return;
   }
 clearToEoln();
 printf ("Retrieve (and remove) the first group that can fit at a tabel of size %d\n", size);

 // add code to perform this operation here
 char* Gname = retrieveAndRemove(head, tail, size);
 printf("%s \n", Gname);
}

void doList (bar* head)
{
 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: l <name>\n");
    printf ("  where: <name> is the name of the group to inquire about\n");
    return;
   }

 printf ("Group \"%s\" is behind the following groups\n", name);
int num = 0;
num = countGroupsAhead(head, name);
 // add code to perform this operation here
 printf("\n");
 printf("There are %d groups ahead of %s.\n", num, name);
 displayGroupSizeAhead(head, name);
}
 
void doDisplay (bar* head)
{
 clearToEoln();
 printf ("Display information about all groups\n");

 // add code to perform this operation here
 displayListInformation(head);
}


int main (int argc, char **argv)
{

 char *input;
 int ch;
 bar* head;
 bar* tail;

 printf ("Starting Restaurant Wait List Program\n\n");
 printf ("Enter command: ");

 while ((ch = getNextNWSChar ()) != EOF)
   {
   	
    /* check for the various commands */
    if ('q' == ch)
      {
       printf ("Quitting Program\n");
       return (0);
      }
    else if ('?' == ch)
      {
       printCommands();
      }
    else if('a' == ch)
      {
       doAdd(&head, &tail);
      } 
    else if('c' == ch)
      {
       doCallAhead(&head, &tail);
      } 
    else if('w' == ch)
      {
       doWaiting(head);
      } 
    else if('r' == ch)
      {
       doRetrieve(&head,&tail);
      } 
    else if('l' == ch)
      {
       doList(head);
      } 
    else if('d' == ch)
      {
       doDisplay(head);
      } 
    else if('\n' == ch)
      {
       /* nothing entered on input line     *
        * do nothing, but don't give error  */
      } 
    else if ('-' == ch)
   	 {
   	    debugMode = TRUE;
   	    printf("Debugging information(s)...\n");
	 }
    else
      {
       printf ("%c - is not a valid command\n", ch);
       printf ("For a list of valid commands, type ?\n");
       clearToEoln();
      }

    printf ("\nEnter command: ");
   }

 printf ("Quiting Program - EOF reached\n");
 return 1;
}
