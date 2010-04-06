#include <iostream>
using namespace std;

int const nmax = 20;

int combination(int m, int n)
{
    static int c[nmax+1][nmax+1];

    if (!c[m][n]) {
        if (!m || m == n)
            c[m][n] = 1;
        else
            c[m][n] = combination(m, n-1) + combination(m-1, n-1);
    }
    return c[m][n];
}

int main()
{
    int t, m, n;
    cin>>t;
    while (t-- > 0) {
        cin>>m>>n;
        cout<<combination(m, n)<<endl;
    }
    return 0;
}