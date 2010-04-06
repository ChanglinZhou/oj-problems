#include <iostream>
using namespace std;

struct buint {
    int d[101];
    int n;

    buint() { clear(); }
    buint(char* s);

    buint & operator *= (buint const & r);
    buint & operator += (buint const & r);
    void operator = (int r) { clear(); d[0] = r, n = 1; }
    void clear() { memset(d, 0, sizeof(d)), n = 1; }
    bool zero() { return n == 1 && d[0] == 0; }
};

ostream& operator << (ostream& os, buint const & r)
{
    int m = r.n;
    while (m--)
        os<<r.d[m];
    return os;
}

buint::buint(char* s)
{
    clear();

    n = (int)strlen(s);
    for (int i = 0; i < n; ++i)
        d[i] = s[n-i-1] - '0';
}

buint& buint::operator *= (const buint &r)
{
    static int t[101];
    memcpy(t, d, sizeof(d));
    memset(d, 0, sizeof(d));

    int i, j, m = min(n + r.n, 101);
    for (i = 0; i < n; ++i) {
        for (j = 0; j < r.n; ++j) {
            if (i + j >= m)
                break;
            d[i+j] += t[i]*r.d[j];
        }
    }

    int c = 0;
    for (i = 0; i < m; ++i) {
        d[i] += c;
        c = d[i]/10;
        d[i] %= 10;
    }

    while (m > 0 && !d[m-1])
        --m;
    n = m;

    return *this;
}

buint& buint::operator += (buint const & r)
{
    int i;
    for (i = 0; i < r.n; ++i) {
        d[i] += r.d[i];
    }

    int c;
    n = max(n, r.n);
    c = 0;
    for (i = 0; i < n; ++i) {
        d[i] += c;
        c = d[i]/10;
        d[i] %= 10;
    }
    if (c)
        d[n++] = c;

    return *this;
}

buint circle(char* s, int k)
{
    static bool mark[10];

    int c, i;
    buint n, p, a, b, t, r(s);

    b = r, p = 1;
    for (i = 0; i < k; ++i) {
        memset(mark, 0, sizeof(mark));

        t = 1, n = 0;
        while (1) {
            t *= b;
            a = r;
            a *= t, n += p;

            c = a.d[i];
            if (c == r.d[i])
                break;
            if (mark[c])
                return buint();
            mark[c] = true;
        }
        p = n, b = t;
    }

    return n;
}

int main()
{
    char str[100], *s;
    int k;
    buint r;
    cin>>str>>k;
    while (k) {
        s = str + max( (int)strlen(str) - k, 0 );
        r = circle(s, k);
        if (r.zero())
            cout<<-1;
        else
            cout<<r;
        cout<<endl;
        cin>>str>>k;
    }
}