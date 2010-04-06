#include <iostream>
#include <cstdlib>
using namespace std;

#define N 5001
#define MAX(a, b) ((a > b) ? a : b)
char* table[N] = {NULL};

void printFibonacci(char* p)
{
    if (p == NULL)
        return;

    if (*p != '0' || strlen(p) == 1)
        cout<<*p;

    while (*(++p))
    {
        cout<<*p;
    }
}


char* BigNumber_Add(char* p1, char* p2)
{
    if (p1 == NULL || p2 == NULL)
        return NULL;

    int L1 = strlen(p1);
    int L2 = strlen(p2);
    int i = L1 - 1;
    int j = L2 - 1;

    if (*p1 == '0' && L1 > 1)
        L1--;
    if (*p2 == '0' && L2 > 1)
        L2--;
    int L = MAX(L1, L2) + 2;
    char *p = NULL;
    p = new char[L];
    if (p == NULL)
        exit(1);
    int k = L - 2;
    p[L - 1] = '\0';
    unsigned char carry = 0;
    unsigned char sum;

    while (i >= 0 || j >= 0)
    {
        sum = 0;
        if (i >= 0) {
            sum += (p1[i] - '0');
            i--;
        }
        if (j >= 0) {
            sum += (p2[j] - '0');
            j--;
        }

        sum += carry;
        p[k] = sum % 10 + '0';
        carry = sum / 10;
        k--;
    }

    if (k == 0)
        p[k] = carry + '0';

    return p;
}

void freeAll()
{
    for (int i = 2; i <= N; i++)
    {
        if (table[i] != NULL)
            delete [](table[i]);
        table[i] = NULL;
    }
}

char* DP_Fibonacci(int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (table[i] == NULL)
            table[i] = BigNumber_Add(table[i - 1], table[i - 2]);
    }
    return table[n];
}

int main()
{
    int n;
    table[0] = "0";
    table[1] = "1";

    while (cin>>n) {
        cout<<"The Fibonacci number for "<<
            n<<" is ";
        printFibonacci(DP_Fibonacci(n));
        cout<<endl;
    }
    freeAll();
    return 0;
}



