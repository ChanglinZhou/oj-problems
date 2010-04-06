#include <stdio.h>

typedef unsigned char BOOL;
#define TRUE 1
#define FALSE 0

#define MAX 50

char word[5] = "ICPC"; 
char data[MAX + 1];

BOOL HiddenICPC(const char* str)
{
    int i = 0;
    const char* p = str;

    while(*p)
    {
        if( *p == word[i] && i < 4 )
            ++i;
        ++p;
    }

    return ( i == 4 && (p - str) > 4 );
}

int main()
{
    int i, t;
    scanf("%d", &t);
    for( i = 1; i <= t; ++i )
    {
        scanf("%s", data);
        printf("Case %d: ", i);
        if( HiddenICPC(data) )
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
