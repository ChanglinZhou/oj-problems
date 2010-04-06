#include <stdio.h>

int result[10][5] = { {1, 0} , { 1, 1 }, { 4, 2, 4, 8, 6 }, { 4, 3, 9, 7, 1 }, { 2, 4, 6 }, 
{ 1, 5 }, { 1, 6 }, { 4, 7, 9, 3, 1 }, { 4, 8, 4, 2, 6 }, { 2, 9, 1 } };

int last_digit( size_t n )
{
    int digit = n % 10;
    int cycle_length = result[digit][0];
    int index = n % cycle_length;
    index = (index == 0) ? cycle_length : index;
    return result[digit][index];
}
int main()
{
    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        printf("%d\n", last_digit(n));
    }
    return 0;
}