#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool isDigit( const char& c )
{
    return ('0' <= c && c <= '9');
}

bool isAlpha( const char& c )
{
    return ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z');
}

vector<string> divideText( const string& str )
{
    vector<string> units;

    for ( int i = 0; i < str.size(); )
    {
        int n;
        if ( str[i] < 0 )
        {
            n = 2;
        }
        else
        {
            n = 0;
            while ( isDigit(str[i + n]) || isAlpha(str[i + n]) )
            {
                ++n;
                if ( i + n >= str.size() )
                    break;
            }
            n = ( n == 0 ) ? 1 : n;
        }
        units.push_back(str.substr(i, n));
        i += n;
    }

    return units;
}

int lzw( const string& str1, const string& str2 )
{
    int weight = 0;
    vector<string> units1 = divideText(str1);
    vector<string> units2 = divideText(str2);
    
    for ( int i = 0; i < units1.size(); ++i )
        for ( int j = 0; j < units2.size(); ++j )
        {
            int l = 0;
            while (units1[i + l] == units2[j + l])
            {
                ++l;
                if ( (i + l) >= units1.size() || (j + l) >= units2.size() )
                    break;
            }
            if ( l > 0 )
            {
                weight += l*l;
                i += l;
                break;
            }
        }

    return weight;
}

int main()
{
    string str1, str2;
    
    cin >> str1 >> str2;

    cout << lzw(str1, str2) << endl;

    return 0;
}