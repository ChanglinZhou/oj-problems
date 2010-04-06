#include <iostream>
using namespace std;

int const IMAX=0x7fffffff;

inline int rdist(int r, int g, int b)
{
    return 255-r+g+b;
}
inline int gdist(int r, int g, int b)
{
    return 255-g+r+b;
}

inline int bdist(int r, int g, int b)
{
    return 255-b+r+g;
}

int const num = 400;
int mat[num/3+1][num/3+1];

void addp(int r, int g, int b, int n, int m)
{
    if (n == 1) {
        mat[0][0] = bdist(r, g, b);
        mat[0][1] = gdist(r, g, b);
        mat[1][0] = rdist(r, g, b);
        return;
    }

    static int line[num/3+1];

    int t, i, j, p, q;
    p = min(n, m/3+1);
    for (i = 0; i <= p; ++i) {
        q = min(n-i, m/3+1);
        for (j = 0; j <= q; ++j) {
            t = IMAX;
            if (i > 0) {
                t = min(mat[i-1][j]+rdist(r, g, b), t);
                mat[i-1][j] = line[j];
            }
            if (j > 0)
                t = min(mat[i][j-1]+gdist(r, g, b), t);
            if (i+j < n) {
                t = min(mat[i][j]+bdist(r, g, b), t);
                line[j] = t;
            } else
                mat[i][j] = t;
        }
    }
    i = m/3+1;
    q = min(n-i-1, m/3+1);
    for (j = 0; j <= q; ++j)
        mat[i][j] = line[j];
}

int dist(int n)
{
    int t, p = n/3;

    t = mat[p][p];
    if (n%3 == 2)
        t = mat[p+1][p+1];
    if (n%3 != 0) {
        t = min(mat[p][p+1], t);
        t = min(mat[p+1][p], t);
    }

    return t;
}

int main()
{
    int t, n, m, i, j, r, g, b;
    char c;
    cin>>t;
    for (i = 1; i <= t; ++i) {
        cin>>n>>m;
        n *= m;
        for (j = 1; j <= n; ++j) {
            cin>>c>>r>>c>>g>>c>>b>>c;
            addp(r, g, b, j, n);
        }
        cout<<"Case "<<i<<": "<<dist(n)<<endl;
    }
    return 0;
}