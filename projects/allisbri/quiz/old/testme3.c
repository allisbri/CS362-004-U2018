#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
	char cs[10];
	memset(cs, 10, '\0');
	strcpy(cs, '[({ ax})]');
	int randNum = rand()%9; //0-8
    return cs[randNum];
}

char *inputString()
{
    // TODO: rewrite this function
	string[6];
	stringOut[6];
	memset(string, '\0', 6);
	memset(stringOut, '\0', 6);
	strcpy(string, "reset");
	int first, second, third, fourth, fifth = -1;	
	randNum = -2;
	first = rand()%5;
	do {
		second = rand()%5;
	} while (first == second);
	do {
		third = rand()%5;
	} while (third == second || third == first);
	do {
		fourth = rand()%5;
	} while (fourth == first || fourth == second || fourth == third);
	do {
		fifth = rand()%5;
	} while (fifth == first || fifth == fourth || fifth == third || fifth == second || fifth == first);
	
	stringOut[0] = string[first];
	stringOut[1] = string[second];
	stringOut[2] = string[third];
	stringOut[3] = string[fourth];
	stringOut[4] = string[fifth];
    return stringOut;
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
