#include <stdio.h>
#include <string.h>

#define WLEN 75

unsigned short tags[WLEN];

void swap(char** a, char** b)
{
    char* tmp = *a;
    *a = *b;
    *b = tmp;
}

unsigned short diff(char* left, char* right)
{
    char* p = left;
    while (*p++ == *right++);

    return (unsigned short)((--p) - left);
}

unsigned short update(char** first, char** second)
{
    size_t len1 = strlen(*first);
    size_t len2 = strlen(*second);
    unsigned short tag = tags[len1-1] + 1;
    unsigned short pos = diff(*first, *second);
    
    if ( pos != len1 )
    {
        tag = tags[pos];
        while ( pos >= 0 && tags[pos] == tag )
        {
            tags[pos] = 0;
            --pos;
        }
        ++pos;
    }
    
    swap(first, second);
    while ( pos < len2 )
        tags[pos++] = tag;

    return tag;
}

int main()
{
    int i, t, n, len, maxLen;
    char first[WLEN + 1];
    char second[WLEN + 1];
    char *p1 = first;
    char *p2 = second;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        maxLen = 0;
        p1[0] = '\0';
        tags[0] = 0;

        for ( i = 0; i < n; ++i )
        {
            scanf("%s", p2);
            len = update(&p1, &p2);
            maxLen = (maxLen < len) ? len : maxLen;
        }
        printf("%d\n", maxLen);
    }

    return 0;
}