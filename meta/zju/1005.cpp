#include <iostream>
using namespace std;

int main()
{
    int Ca,Cb,N,x,y;
    
    while (cin>>Ca>>Cb>>N)
    {
    	x = y = 0;
        while(1)
        {
            cout<<"fill A"<<endl;
            x = Ca;
            if (x == N) 
            {
                cout<<"success"<<endl;
                break;
            }
            while (x > 0)
            {
                if (x <= (Cb - y))
                {
                    cout<<"pour A B"<<endl;
                    y += x;
                    x = 0;
                }
                else
                {
                    cout<<"pour A B"<<endl;
                    x -= (Cb - y);
                    y = Cb;
                }
                if (x == N) {
                    cout<<"success"<<endl;
                    break;
                }
                if (y == N)
                    break;
                if (y == Cb) {
                    cout<<"empty B"<<endl;
                    y = 0;
                }
            }
            if (x == N)
                break;
            if (y == N) {
                cout<<"success"<<endl;
                break;
            }
        }
    }
    return 0;
}