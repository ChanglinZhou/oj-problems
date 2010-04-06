#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef __int64 INT64;

const INT64 N = 1000000000000000000;


int subtract( vector<INT64>& x, const vector<INT64>& y )
{
    size_t lenX = x.size();
    size_t lenY = y.size();

    if ( lenX < lenY )
        return -1;

    for ( size_t i = 1; i <= lenX; ++i )
    {
        x[lenX -i] -= 
    }
}

vector<INT64> operator*( const vector<INT64>& x, const vector<INT64>& y )
{
    vector<INT64> z( x.size() + y.size(), 0 );

    size_t lenX = x.size();
    size_t lenY = y.size();
    size_t lenZ = z.size();

    for ( size_t i = 1; i <= lenY; ++i )
    {
        INT64 c = 0;
        for ( size_t j = 1; j <= lenX; ++j )
        {
            INT64 p = x[lenX - j] * y[lenY - i] + c;
            z[lenZ - i - j + 1] += p;
            c = z[lenZ - i - j + 1] / N;
            z[lenZ - i - j + 1] %= N;
        }

        z[lenZ - i - lenX] += c;
    }

    return z;
}


ostream& operator<<( ostream& os, const vector<INT64>& number )
{
    size_t len = number.size();
    size_t i = 0;
    while ( number[i] == 0 )
        ++i;

    if ( i < len )
        printf( "%d", number[i++] );

    while ( i < len )
        printf( "%.9d", number[i++] );

    printf("\n");

    return os;
}


vector<INT64> StringToInt( const string& line )
{

    size_t len = line.size();
    size_t head = len % 9;
    size_t total = len / 9 + static_cast<bool>(head > 0);
    vector<INT64> number(total, 0);

    size_t i, j;
    i = j = 0;
    while ( j < total )
    {

        size_t loop = 9;
        if ( j == 0 && head > 0 )
        {
            loop = head;
        }

        for ( size_t k = 0; k < loop; ++k, ++i )
        {        
            number[j] *= 10;
            number[j] += (line[i] - '0');
        }

        ++j;
    }

    return number;
}

int main()
{
    string line;

    cin >> line;
    vector<INT64> x = StringToInt( line );

    cin >> line;
    vector<INT64> y = StringToInt( line );

    vector<INT64> z = x * y;

    cout << z;

    return 0;
}

