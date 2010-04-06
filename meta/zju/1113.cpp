#include <iostream>
using namespace std;

const int N = 10;

int f[N];

int fac()
{
    if(f == NULL) return -1;
    f[0] = 1;
    f[1] = 1;
    for (int i=2; i<N; i++) {
        f[i]=f[i-1]*i;
    }
    return 0;
}

double u_Cal_e(int i)
{
    double e = 0;
    while (i >= 0) {
        
        e += 1.0f/f[i];
        i --;
    }
    return e;
}
int main()
{
    int i=0;
    fac();
    cout<<"n e"<<endl;
    cout<<"- -----------"<<endl;
    for (i=0; i<N; i++) {
        cout<<i<<' ';
        if (i == 3) {
            cout.setf(ios::fixed);
            cout.precision(9);
        }
        cout<<u_Cal_e(i)<<endl;
    }
    return 0;
}