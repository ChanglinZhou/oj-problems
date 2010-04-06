#include <iostream>
#include <cstdlib>
using namespace std;

#define N 112
#define UNIT 1000000000 // 10-bits dec number 
typedef unsigned int uint32;
uint32 a[N];
uint32 b[N];
uint32 c[N];

bool IsDividedBy3(uint32* p)
{
    uint32 sum = 0;
    uint32 u;
    int i = 0;
    
    while (i < N && p[i])
        ++i;
    
    while (i < N)
    {
    	u = p[i];
    	while (u) {
    	    sum += u % 10;
    	    u /= 10;
    	}
    	++i; 
    }
    if (sum % 3 == 0)
        return true;
    return false;
}

void zeroFill(uint32* p)
{
    int i = 0;
    while (i < N)
    {
    	p[i++] = 0;
    }
}

// p1 = p2
void Array_Assignment(uint32*p1, uint32* p2)
{
    if (p1== NULL || p2 == NULL)
        return;
    
    int i = 0;
    
    while (i < N)
    {
    	p1[i] = p2[i];
    	++i;
    }
}

void printNonFirst(uint32 u)
{
    char printInfo[9];
    memset(printInfo, '0', 9);
    
    int i = 8;
    while (u)
    {
    	printInfo[i--] += u % 10;
    	u /= 10;
    }
    
    i = 0;
    while (i < 9)
        cout<<printInfo[i++];
    
}
void printFibonacci(uint32* p)
{
    if (p == NULL)
        return;
    
    int i = 0;
    while (p[i] == 0 && i < N)
    	++i;
    if (i == N)
    	cout<<0;
    
    int j = i;
    while (j < N)
    {
    	if (j == i)
            cout<<p[j];
        else
            printNonFirst(p[j]);
        ++j;
    }
}

void BigNumber_Add(uint32* p1, uint32* p2, uint32* p)
{
    if (p1 == NULL || p2 == NULL || p == NULL)
        return;

    int i = N - 1;
    unsigned char carry = 0;
    uint32 sum;

    while (i >=0 && (p1[i] || p2[i]))
    {
    	sum = p1[i] + p2[i] + carry;
    	carry = sum / UNIT;
        p[i] = sum % UNIT;
        i--;
    }
    if (i >= 0)
    	p[i] = carry;
}

uint32* DP_Fibonacci(int n)
{
    zeroFill(a);
    zeroFill(b);
    zeroFill(c);
    
    b[N - 1] = 7;
    c[N - 1] = 11;
    
    if (n == 0)
        return b;
        
    for (int i = 2; i <= n; i++)
    {
    	Array_Assignment(a, b);
    	Array_Assignment(b, c);
    	BigNumber_Add(a, b, c);
    }
    return c;
}

int main()
{
    int n;
    while (cin>>n) {
    	if (IsDividedBy3(DP_Fibonacci(n)))
    	    cout<<"yes"<<endl;
    	else
    	    cout<<"no"<<endl;
    }
    
    return 0;
}
