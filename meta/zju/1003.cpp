#include <stdio.h>

int get_Winner(int s1, int s2)
{
    return s1;  
}

int main( )
{
    int s1, s2;

    while ( scanf("%d %d", &s1, &s2) != EOF ) 
    {
        printf( "%d\n", get_Winner(s1, s2) );
    }
    return 0;
}
