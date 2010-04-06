#include <stdio.h>
#include <string.h>

typedef unsigned char BOOL;
#define TRUE 1
#define FALSE 0

#define MAXSTRING 100
#define MAXCASE 100

char cases[MAXCASE][MAXSTRING+1];
char substr[MAXSTRING + 1];
char rsubstr[MAXSTRING + 1];

int n;

void getSubString( const char* str, int i, int j )
{
    int k;
    for( k = i; k <= j; ++k )
        substr[k-i] = str[k];
    substr[k-i] = '\0';
}

void getReverseSubString( const char* str, int i, int j )
{
    int k;
    for( k = j; k >= i; --k )
        rsubstr[j-k] = str[k];
    rsubstr[j-k] = '\0';
}

BOOL isSubString(const char* str1, const char* str2)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    int i, j;
    for( i = 0; i + len1 <= len2; ++i )
    {
        for( j = 0; j < len1; ++j )
            if( str1[j] != str2[i+j] )
                break;

        if( j == len1 )
            break;
    }

    return (i + len1 <= len2);
}

int longestSubString()
{
    size_t len;
    size_t minLen = MAXSTRING + 1;
    int i, j, k, longest, index;
    i = 0;
    while( i < n )
    {
        len = strlen(cases[i]);
        if( len < minLen )
        {
            minLen = len;
            index = i;
        }
        ++i;
    }

    longest = 0;

    for( i = 0; i < minLen; ++i )
    {
        for( j = i; j < minLen; ++j )
        {
            getSubString(cases[index], i, j);
            getReverseSubString(cases[index], i, j);
            for( k = 0; k < n; ++k )
            {
                if( k == index )
                    continue;
                if( !isSubString(substr, cases[k]) && !isSubString(rsubstr, cases[k]))
                    break;
            }
            if( k == n )
                longest = (longest < (j - i + 1)) ? (j- i + 1) : longest;
        }
    }

    return longest;
}

int main()
{
    int i, t, len, minLen, index;
    memset(cases, 0, sizeof(cases));

    scanf("%d", &t);
    while( scanf("%d", &n) != EOF )
    {
        i = 0;
        while(i < n) {
            scanf("%s", cases[i]);
            ++i;
        }
        printf("%d\n", longestSubString());
    }

    return 0;
}