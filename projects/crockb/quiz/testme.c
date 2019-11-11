/* testme.c - Random Testing Quiz
  Author/Date:  Bryant Crock  11/10/19
  Description:  Achieve 85% branch coverage for testme() function in < 5 minutes
*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


char inputChar()
{
    int n;
    char set[9] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']' };

    n = rand() % 9;

    return set[n];
}


char *inputString()
{

    int n, i;
    char myString[] = "reset";
    char temp;
    char *returnString;

    for (i = 0; i < 5; i++)
    {
        n = rand() % 5;

        // shuffle the characters
        temp = myString[n];
        myString[n] = myString[i];
        myString[i] = temp;
    }

    returnString = malloc(10 * sizeof(char));
    memset(returnString, '\0', 10 * sizeof(char));
    sprintf(returnString, myString);

    return returnString;
}


void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
