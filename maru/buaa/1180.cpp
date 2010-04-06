#include <iostream>
#include <iomanip>

using namespace std;

double mat[200*200];
double err[200*200];

double merror(int* v, int n, int s, int e)
{
    int d, i, t;

    if (err[s*n+e] == 0.0) {
        err[s*n+e] = 1.0, d = e - s;
        for (i = s+1; i < e; ++i) {
            t = (v[s] - v[i])*d + (v[e] - v[s])*(i-s);
            t = t > 0 ? t : -t;
            err[s*n+e] += t*1.0/d;
        }
    }

    return err[s*n+e] - 1.0;
}

double moogle(int* v, int n, int c)
{
    int b = sizeof(double)*n*n;
    memset(err, 0, b);
    c -= 2;
    if (!c)
        return merror(v, n, 0, n-1);

    memset(mat, 0, b);

    int i, j, k;
    for (i = n-2; i >= c; --i)
        mat[i] = merror(v, n, i, n-1);

    double t;
    for (i = 1; i < c; ++i) {
        for (j = c-i; j < n-i-1; ++j) {
            for (b = 1, k = j+1; k < n-i; ++k) {
                t = mat[(i-1)*n+k] + merror(v, n, j, k);
                if (b || t < mat[i*n+j])
                    mat[i*n+j] = t, b = 0;
            }
        }
    }

    for (b = 1, k = 1; k < n-c; ++k) {
        t = mat[(c-1)*n+k] + merror(v, n, 0, k);
        if (b || t < mat[c*n])
            mat[c*n] = t, b = 0;
    }

    return mat[c*n];
}

int main()
{
    int t, h, c, i;
    int v[200];
    cin>>t;
    cout<<fixed<<setprecision(4);
    while (t-- > 0) {
        cin>>h>>c;
        for (i = 0; i < h; ++i)
            cin>>v[i];
        cout<<moogle(v, h, c)/h<<endl;
    }
    return 0;
}