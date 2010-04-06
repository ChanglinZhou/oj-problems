#include <iostream>
using namespace std;
typedef unsigned char uchar;
#define N 10000
int main()
{
   uchar a[N];
   long index = 0;
   for(long i=0; i<N; i++)
       a[i] = 0;
   for(long j=1; j<N; j++) {
        long k,r;
        k = r = j;
        while(k) {
            r +=k%10;
            k /= 10;
        }
        if(r <= N)
            a[r-1] = 1;
   }
   while(index < N) {
        if(!a[index])
            cout<<index+1<<endl;
        index ++;    
   }
   return 0;
}