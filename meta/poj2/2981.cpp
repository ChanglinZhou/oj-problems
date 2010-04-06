#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef __int64 INT64;

const INT64 N = 1000000000000000000;

vector<INT64> operator+( const vector<INT64>& x, const vector<INT64>& y )
{
    size_t lenX = x.size();
    size_t lenY = y.size();
    size_t lenZ = (lenX >= lenY) ? (lenX + 1) : (lenY + 1);

    vector<INT64> z( lenZ, 0 );

    INT64 c = 0;
    size_t i = 1;
    while ( i <= lenX )
    {
        if ( i > lenY )
            break;

        z[lenZ - i] += (x[lenX - i] + y[lenY -i]);
        c = z[lenZ -i] / N;
        z[lenZ - i] %= N;
        z[lenZ - i - 1] += c;
        ++i;
    }

    if ( i <= lenX )
    {
        for ( size_t j = i; j <= lenX; ++j )
        {
            z[lenZ - j] += x[lenX - j];
            c = z[lenZ - j] / N;
            z[lenZ - j] %= N;
            z[lenZ - j - 1] += c;
        }
    }

    if ( i <= lenY )
    {
        for ( size_t j = i; j <= lenY; ++j )
        {
            z[lenZ - j] += y[lenX - j];
            c = z[lenZ - j] / N;
            z[lenZ - j] %= N;
            z[lenZ - j - 1] += c;
        }
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
    {
        printf( "%d", number[i++] );
            
        while ( i < len )
            printf( "%.18d", number[i++] );
    }
    else
        printf( "0" ); 

    printf("\n");

    return os;
}


vector<INT64> StringToInt( const string& line )
{

    size_t len = line.size();
    size_t head = len % 18;
    size_t total = len / 18 + static_cast<bool>(head > 0);
    vector<INT64> number(total, 0);

    size_t i, j;
    i = j = 0;
    while ( j < total )
    {

        size_t loop = 18;
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

    vector<INT64> z = x + y;

    cout << z;

    return 0;
}

