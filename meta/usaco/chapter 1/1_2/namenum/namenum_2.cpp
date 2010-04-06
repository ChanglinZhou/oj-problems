/*
ID: amble_s1
LANG: C++
TASK: namenum
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5000
#define LEN 13

char number[LEN], solution[LEN];
char dict[MAX][LEN];
int nsolutions = 0;
int maxlen;
FILE *out;

void calc( int charloc, int low, int high ) 
{

    if ( charloc > 0 )
    {
        for ( int j = low; j < high; ++j ) 
        {
            if ( solution[charloc - 1] == dict[j][charloc - 1] ) 
            {
                low = j;
                for ( j = low + 1; j < high; ++j ) {
                    if ( solution[charloc - 1] != dict[j][charloc - 1] )
                        break;
                }
                high = j;
            }
        }
    }

    if ( low >= high )
        return;

    if ( charloc == maxlen )
    {
        solution[charloc] = '\0';
        for ( int x = low; x < high; ++x )
        {
            fprintf ( out, "%s\n", solution );
            ++nsolutions;
            break;
        }
        return;
    }


    switch( number[charloc] ) {

      case '2':
          solution[charloc] = 'A'; calc( charloc + 1, low, high );
          solution[charloc] = 'B'; calc( charloc + 1, low, high );
          solution[charloc] = 'C'; calc( charloc + 1, low, high );
          break; 

      case '3':
          solution[charloc] = 'D'; calc( charloc + 1, low, high );
          solution[charloc] = 'E'; calc( charloc + 1, low, high );
          solution[charloc] = 'F'; calc( charloc + 1, low, high );
          break; 

      case '4':
          solution[charloc] = 'G'; calc( charloc + 1, low, high );
          solution[charloc] = 'H'; calc( charloc + 1, low, high );
          solution[charloc] = 'I'; calc( charloc + 1, low, high );
          break; 

      case '5':
          solution[charloc] = 'J'; calc( charloc + 1, low, high );
          solution[charloc] = 'K'; calc( charloc + 1, low, high );
          solution[charloc] = 'L'; calc( charloc + 1, low, high );
          break; 

      case '6':
          solution[charloc] = 'M'; calc( charloc + 1, low, high );
          solution[charloc] = 'N'; calc( charloc + 1, low, high );
          solution[charloc] = 'O'; calc( charloc + 1, low, high );
          break; 

      case '7':
          solution[charloc] = 'P'; calc( charloc + 1, low, high );
          solution[charloc] = 'R'; calc( charloc + 1, low, high );
          solution[charloc] = 'S'; calc( charloc + 1, low, high );
          break; 

      case '8':
          solution[charloc] = 'T'; calc( charloc + 1, low, high );
          solution[charloc] = 'U'; calc( charloc + 1, low, high );
          solution[charloc] = 'V'; calc( charloc + 1, low, high );
          break; 

      case '9':
          solution[charloc] = 'W'; calc( charloc + 1, low, high );
          solution[charloc] = 'X'; calc( charloc + 1, low, high );
          solution[charloc] = 'Y'; calc( charloc + 1, low, high );
          break;

      default:
          break;
    }
}

int main()
{
    FILE *in = fopen( "namenum.in", "r" );
    FILE *in2 = fopen( "dict.txt", "r" );
    out = fopen( "namenum.out","w" );

    int nwords;
    for ( nwords = 0; fscanf( in2, "%s", dict[nwords++] ) != EOF; )
        ;

    fscanf( in, "%s", &number );
    maxlen = strlen(number);

    calc( 0, 0, nwords );

    if ( nsolutions == 0 ) 
        fprintf(out,"NONE\n");

    return 0;
}