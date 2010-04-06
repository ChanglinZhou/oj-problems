#include <iostream>
using namespace std;


inline int min( int a, int b, int c )
{
  int min = a;

  if ( min > b )
    min = b;

  if ( min > c )
    min = c;

  return min;
}

inline int max( int a, int b, int c )
{
  int max = a;

  if ( max < b )
    max = b;

  if ( max < c )
    max = c;

  return max;
}

int main()
{
    int t, a, b, c;
    cin >> t;
    while (t--) {
      cin >> a >> b >> c;
        cout << (a + b + c) << " "
             << (a + b + c) / 3 << " "
             << (a * b * c) << " "
             << min( a, b, c) << " "
             << max( a, b, c) << endl;
    }

    return 0;
}
