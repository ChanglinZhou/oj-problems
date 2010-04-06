#include <iostream>
#include <string>
using namespace std;

int main()
{
    string text;
    int length = 0;
    int i;
    
    while (cin>>text) {
        if (text == "<br>") {
            cout<<endl;
            length = 0;
        }
        else if (text == "<hr>") {
            if (length) {
                length = 0;
                cout<<endl;
            }
            i = 0;
            while (i < 4){
                cout<<"--------------------";
                i++;
            }
            cout<<endl;
        }
        else {
            if (!length) { //if at the begin of a new-line
                cout<<text;
                length += text.length();
            }
            else {
                if ((text.length() + length) > 79) {
                    cout<<endl;
                    cout<<text;
                    length = text.length();
                }
                else {
                    cout<<" ";
                    cout<<text;
                    length += (text.length() +1);
                }
            }
        }
    }
    cout<<endl;// you must add end-line after you output all html elements
    return 0;
}