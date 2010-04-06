#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// KISS Priciple

double area( double edges[3] )
{
  double s = ( edges[0] + edges[1] + edges[2] ) / 2;

  return sqrt( s*(s-edges[0])*(s-edges[1])*(s-edges[2]) );
}


int main( )
{
  int t;
  double edges[3];

  cin >> t;
  int i;
  cout << setprecision(3) << setiosflags(ios::fixed);
  while (t--) {
    i = 0;
    while ( i < 3 ) {
      cin >> edges[i];
      ++i;
    }
    cout << area(edges) << endl;
  }

  return 0;
}
