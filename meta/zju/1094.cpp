#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 26
struct matrix
{
    char name;
    int row;
    int col;
}m[N];

struc matrix Evaluate(char exp[], int pos)
{
    if (exp[pos] == '(')
        Evaluate(exp, pos + 1);
    else if (
}
int main()
{
    int n;
    memset(exp, '\0', sizeof(char) * M);
    memset(m, 0, sizeof(matrix) * N);

    scanf("%d", &n);
    
    int i = 0;
    while (i++ < n)
    {
    	scanf("%c %d %d", m + i, m + i + 4, m + i + 8);
    }
    
    char ch;
    int count;
    while (scanf("%c", ch) != EOF)
    { 
    	
    }
    return 0;
}