#include <stdio.h>
#include <string.h>

#define WLEN 75
#define TLEN 2000

char words[TLEN][WLEN + 1];
unsigned short lens[TLEN];

typedef unsigned char BOOL;
#define TRUE 1
#define FALSE 0

BOOL IsPrefix( char* left, char* right )
{
    while (*left++ == *right++);

    return (*--left == '\0');
}

int main()
{
    int i, j, t, n, maxLen;

    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n, words[0]);

        maxLen = 1;
        for ( i = 0; i < n; ++i )
        {
            scanf("%s", words[i]);
            lens[i] = 1;
        }

        for ( i = 1; i < n; ++i )
        {
            for ( j = 0; j < i; ++j )
            {
                if ( IsPrefix(words[j], words[i]) )
                {
                    if ( lens[j] + 1 > lens[i] )
                        lens[i] = lens[j] + 1;
                }
            }
            if (maxLen < lens[i] )
                maxLen = lens[i];
        }
        printf("%d\n", maxLen);
    }

    return 0;
}