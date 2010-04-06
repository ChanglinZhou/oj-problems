#include <iostream>
using namespace std;

const int LENGTH = sizeof(int) * 8;


void print_binary( unsigned int n )
{
    for ( int i = 0; i < LENGTH; ++i )
    {
        if ( n & 0x80000000 )
            cout << '1';
        else
            cout << '0';

        n <<= 1;
    }

    cout << endl;
}




unsigned int flip1( unsigned int n, unsigned int high, unsigned int low )
{
    if ( high == 0 || high > LENGTH || low == 0 || low > LENGTH || high < low )
        return n;

    unsigned int n1, n2, n3;

    // x1x2...A...xn
    n1 = n;
    // 00...x1x2...A
    n1 >>= (low - 1);
    // A...00...00
    n1 <<= ( (low - 1) + (LENGTH - high) );
    // 00...A...00
    n1 >>= (LENGTH - high);
    // x1x2...00...xn
    n1 ^= n;

    // x1'x2'...A'...xn'
    n2 = ~n;
    // 00...x1'x2'...A'
    n2 >>= (low - 1);
    // A'...00.00
    n2 <<= ( (low - 1) + (LENGTH - high) );
    // 00...A'...00
    n2 >>= (LENGTH - high);

    // x1x2...A'...xn
    n3 = n1 + n2;

    return n3;
}


unsigned int flip2( unsigned int n, unsigned int high, unsigned int low )
{
    if ( high == 0 || high > LENGTH || low == 0 || low > LENGTH || high < low )
        return n;

    return (n ^ ( (1 << high) - (1 << (low - 1)) ) );
}


int main()
{
    unsigned int n, high, low;
    while ( cin >> n >> low >> high )
    {   
        if ( high == 0 || low == 0 )
            break;
        print_binary(n);
        print_binary(flip1( n, high, low ));
        print_binary(flip2( n, high, low ));
    }

    return 0;
}