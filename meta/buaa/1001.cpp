#include<iostream>
using namespace std;

unsigned long long C( int m, int n )
{

  if( m <= 0 || n <= 0 || m < n )
    return 0;

  unsigned long long child, parent;

  n = (n > m / 2) ? ( m - n ) : n;
  child = 1;
  parent = 1;
  int i = n;
  while (i--) {
    child *= m - i;
    parent *= i + 1;
  }

  return child / parent;
}

int main()
{
  int t,n,m;
  cin >> t;
  
  while (t--) {
    cin >> n >> m;
    cout << C( m, n ) << endl;
  }

  return 0;
}
