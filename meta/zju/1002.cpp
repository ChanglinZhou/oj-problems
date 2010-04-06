#include <stdio.h>

const int MAX_N = 4;
char map[MAX_N][MAX_N + 1];

int n, maxCount;

bool CanPut(int row, int col)
{
    if ( map[row][col] != '.' )
        return false;

    int i;
    for(i = row-1; i>=0; i--) {
        if (map[i][col] == 'O') return false;
        if (map[i][col] == 'X') break;
    }
    
    for(i = col-1; i>=0; i--) {
        if (map[row][i] == 'O') return false;
        if (map[row][i] == 'X') break;
    }
    return true;
}

void PutBlockHouse(int pos, int count)
{
    if (pos == (n * n)) {
        maxCount = (count > maxCount) ? count : maxCount;
    }
    else {
        int row = pos / n;
        int col = pos % n;
        if (CanPut(row, col)) {
            map[row][col] = 'O';
            PutBlockHouse(pos + 1, count + 1);
            map[row][col] = '.';
        }
        PutBlockHouse(pos + 1,count);
    }
}

int main( )
{
    scanf("%d", &n);
    while (n > 0) 
    {
        for (int i = 0; i < n; i++) 
            scanf("%s\n", &map[i]);

        maxCount = 0;
        PutBlockHouse(0, 0);
        printf("%d\n", maxCount);
        scanf("%d", &n);
    }
    return 0;
}
