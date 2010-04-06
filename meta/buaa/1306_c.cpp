#include <stdio.h>
#include <string.h>

#define WLEN 75
#define TLEN 2000

char words[TLEN][WLEN + 1];
unsigned short lens[TLEN];
unsigned short wordlist[TLEN];

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
    int i, t, n, top, maxLen;

    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n, words[0]);

        maxLen = 1;
        top = 1;
        wordlist[0] = 0;
        for ( i = 0; i < n; ++i )
        {
            scanf("%s", words[i]);
            lens[i] = 1;
        }

        for ( i = 1; i < n; ++i )
        {
            while ( top > 0 && !IsPrefix(words[wordlist[top-1]], words[i]) )
                --top;
            if ( top > 0 )
                lens[i] = lens[wordlist[top-1]] + 1;
            wordlist[top++] = i;
            if (maxLen < lens[i] )
                maxLen = lens[i];
        }
        printf("%d\n", maxLen);
    }

    return 0;
}