#include <iostream>
using namespace std;

typedef unsigned char int8;

bool IsPalindrom(int number, int basis)
{
    int8 a[16];
    int i = 0;
    int j = 0;
    int k;
    int Len;
    
    while (i < 16) {
        if (number) {          
            a[i++] = number % basis;
            number /= basis;
            if (!number) Len = i;
            continue;
        }
        a[i++] = 0;
    }
    
    k = Len/2;
    
    while (j < k) {
        if (a[j] != a[Len - 1 - j]) return false;
        j++;
    }
    return true;
}

int main()
{
    int number;
    bool Flag;
    while(cin >> number) {
        if (!number) break;
        
        Flag = false;
        
        for (int i = 2; i <= 16; i++) {
            if (IsPalindrom(number, i)) {
                if(!Flag) {
                    Flag = true;
                    cout << "Number " << number << " is palindrom in basis";
                }
                cout<<" "<<i;
            }
        }
        
        if (!Flag)
            cout << "Number " << number << " is not a palindrom";
            
        cout << endl;    
    }
    return 0;
}