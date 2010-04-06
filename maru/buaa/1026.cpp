#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

int  mat[10][10];
int  r, c, s, k;

unsigned char tab[50][10][10][4][20/8+1];
unsigned char mod[50];

inline bool gettab(int t, int i, int j, int d, int p)
{
    return ( tab[t][i][j][d][p/8] & (1<<(p%8)) ) != 0;
}

inline void settab(int t, int i, int j, int d, int p)
{
    tab[t][i][j][d][p/8] |= 1<<(p%8);
}

inline void resettab(int t, int i, int j, int d, int p)
{
    tab[t][i][j][d][p/8] &= ~(1<<(p%8));
}

// 0 - north, 1 - east, 2 - south, 3 - west
inline void next(int i, int j, int d, int& ni, int& nj)
{
    ni = i + (d-1)*(1-d%2);
    nj = j + (2-d)*(d%2);
}

inline bool valid(int i, int j)
{
    return i >= 0 && i < r && j >= 0 && j < c;
}

bool remain(int t, int i, int j, int p)
{
    for (int d = 0; d < 4; ++d) {
        if (gettab(t, i, j, d, p))
            return true;
    }
    return false;
}

void pathat(int t, int i, int j)
{
    if (t == 0) {
        settab(t, i, j, 0, mat[i][j]%k);
        return;
    }

    int ni, nj, p, q;
    q = mat[i][j]*mod[t];
    for (int d = 0; d < 4; ++d) {
        next(i, j, d, ni, nj);
        if (!valid(ni, nj))
            continue;
        for (p = 0; p < k; ++p) {
            if (remain(t-1, ni, nj, p))
                settab(t, i, j, d, (q+p)%k);
        }
    }
}

void findpath()
{
    // calc 10^(0~s-1) % k
    int t;
    mod[0] = 1;
    for (t = 1; t < s; ++t)
        mod[t] = (mod[t-1]*10) % k;

    memset(tab, 0, sizeof(tab));

    int i, j;
    for (t = 0; t < s; ++t) {
        for (i = 0; i < r; ++i) {
            for (j = 0; j < c; ++j)
                pathat(t, i, j);
        }
    }
}

long long getmin(char* sz)
{
    static long long num[2][10][10];

    // setup
    int i, j, p, q;
    for (i = 0; i < r; ++i) {
        for (j = 0; j < c; ++j)
            num[0][i][j] = 1;
    }
    p = 0, q = 1;

    // step
    int t, d, ni, nj, e, min;
    e = 0;
    for (t = s-1; t >= 0; --t) {
        // clear invalid and find minimal
        min = 10;
        for (i = 0; i < r; ++i) {
            for (j = 0; j < c; ++j) {
                if (!num[p][i][j])
                    continue;
                if (!remain(t, i, j, e)) {
                    num[p][i][j] = 0;
                    continue;
                }
                if (mat[i][j] < min)
                    min = mat[i][j];
            }
        }
        if (min == 10)      // no way
            return 0;
        *sz++ = min + '0';

        // clear valid but non-minimal
        for (i = 0; i < r; ++i) {
            for (j = 0; j < c; ++j) {
                if (mat[i][j] != min)
                    num[p][i][j] = 0;
            }
        }
        if (t == 0)         // to end
            break;

        // clear dest buffer
        memset(num[q], 0, sizeof(num[q]));

        // to next, remember the number of ways
        for (i = 0; i < r; ++i) {
            for (j = 0; j < c; ++j) {
                if (num[p][i][j]) {
                    for (d = 0; d < 4; ++d) {
                        next(i, j, d, ni, nj);
                        if (!valid(ni, nj))
                            continue;
                        num[q][ni][nj] += num[p][i][j];
                    }
                }
            }
        }

        // find next reminder and swap buffer
        e = (k - (min*mod[t])%k + e) % k;
        swap(p, q);
    }
    *sz = 0;

    // count
    long long ret = 0;
    for (i = 0; i < r; ++i) {
        for (j = 0; j < c; ++j)
            ret += num[p][i][j];
    }
    return ret;
}

int main()
{
    int t, i, j, p;
    char sz[51], *str;
    long long n;

    cin>>t;
    for (p = 1; p <= t; ++p) {
        cin>>r>>c>>s>>k;
        for (i = 0; i < r; ++i) {
            for (j = 0; j < c; ++j)
                cin>>mat[i][j];
        }
        findpath();
        n = getmin(sz);
        cout<<"Case "<<p<<": ";
        if (n) {
            str = sz;
            while (*str == '0')
                ++str;
            if (!*str)
                --str;
            cout<<str<<' '<<n;
        } else
            cout<<-1<<' '<<-1;
        cout<<endl;
    }
    return 0;
}