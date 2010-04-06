#include <stdio.h>

int table[10];

int main()
{
    char c;

    while( scanf("%c", &c) != EOF )
    {
        if( c== '.')
            break;

        ++table[c-'0'];
    }

    int i;
    int count = 0;
    for( i = 0; i < 10; ++i )
    {
        if(table[i])
        {
            ++count;
            if( count > 1)
                printf(",");

            printf("%d:%d",i, table[i]); 
        }
    }

    return 0;
}