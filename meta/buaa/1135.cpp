#include <iostream>
using namespace std;

inline void mm( int data[5], int& min, int& max )
{
  min = max = data[0];

  int i = 1;
  while ( i < 5 ) {
    if( min > data[i] )
        min = data[i];
    if ( max < data[i] )
        max = data[i];
    ++i;
  }
    
}


int main()
{
  int t, data[5], j, min, max;
  cin >> t;
  while (t--) {
    j = 0;
    while ( j++ < 5 )
      cin >> data[j-1];
    mm( data, min, max );
    cout << max << " " << min << endl;
  }
  return 0;
}
