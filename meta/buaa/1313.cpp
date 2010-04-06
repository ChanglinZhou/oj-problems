#include <stdio.h>

#define MAX 20

char str[MAX + 1];

int main()
{
    int t;
    size_t len;
    scanf("%d", &t);

    while( t-- )
    {
        len = 0;
        scanf("\n");
        while( scanf("%c", str+len) != EOF )
        {
            if( str[len] == '.' )
                break;

            ++len;
        }
        while( len-- ) {
            printf("%c", str[len]);
        }
        printf("\n");
    }

    return 0;
}