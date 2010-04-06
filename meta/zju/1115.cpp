#include <iostream>
#include <string>
using namespace std;

int digitalRoot(string s)
{
    int result = 0;
    int temp;
    
    for (int i=0; i<s.length(); i++)
        result += s[i] - '0';
        
    while (result >= 10) {
        temp = result;
        result = 0;
        while (temp) {
            result += temp%10;
            temp /= 10;
        }
    }
    
    return result;
}

int main()
{
    string number;
    
    while (cin>>number) {
        if("0" == number) break;
        cout<<digitalRoot(number)<<endl;
    }
    
    return 0;
}