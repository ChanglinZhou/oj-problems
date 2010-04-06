#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// KISS Priciple

double average( int data[5] )
{
  double sum = 0.0;
  int i = 0;

  while ( i < 5 ) {
    sum += data[i];
    ++i;
  }

  return sum / 5;
}
 
double S( int data[5], double aver )
{
  double sum = 0.0;
  int i = 0;

  while ( i < 5 ) {
    sum += pow( (data[i] - aver), 2 );
    ++i;
  }

  return sqrt( sum / 5 );
}


int main( )
{
  int t;
  int data[5];

  cin >> t;
  int i;
  double aver;
  cout << setprecision(3) << setiosflags(ios::fixed);
  while ( t-- ) {
    i = 0;
    while ( i < 5 ) {
      cin >> data[i];
      ++i;
    }
    aver = average( data );
    cout << aver << " " << S( data, aver ) << endl;
  }

  return 0;
}
