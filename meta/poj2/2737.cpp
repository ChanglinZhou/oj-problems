/**

 * author : meta

 * date : 2008-10-24

 * problem : high precision --- divide

 * algorithm : simple

 * input : two lines,

 * 1st line : a positive highprecision number

 * 2nd line : a positive low precicion number

 * output : times & rest of the two numbers

**/

#include <cstdio>

using namespace std;

int main()
{
    int n;
    string line;
    
    cin >> n;

    while ( n-- ) {
        cin >> line;
        vector<INT64> x = StringToInt( line );

        cin >> line;
        vector<INT64> y = StringToInt( line );

        vector<INT64> z = x / y;

        cout << z;
    }

    return 0;
}

