#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

bool pal(int num) 
{
    char buffer[7];

    itoa(num, buffer, 10);

    size_t len = strlen(buffer);

    int i;
    for (i = 0; i < len/2; ++i) {
        if (buffer[i] != buffer[len - 1 - i])
            break;
    }

    return (i == len/2);
}


int main()
{
    // assume that i >= j
    int i, j, max;
    max = 0;
    for (i = 100; i <= 999; ++i)
        for(j = i; j <= 999; ++j) {
            if (pal(i*j)) {
                max = (max < i*j) ? i*j : max;
            }
        }

    printf("%d\n", max);

    return 0;
}
