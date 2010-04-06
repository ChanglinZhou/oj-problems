#include <iostream>
#include <string>
using namespace std;

string src;
string tgt;

void StackOperations(int pos, int deep, string op, string si, int iNext)
{
    int iPush = (pos + 1)- deep;
    for (int i = 0; i < iPush; i++)
        op += "i ";
    op += "o ";
    deep = pos;
    iNext ++;
    si.erase(pos, 1);
    
    if (si.size() == 0)
    {
    	cout<<op<<endl;
    }
    else {
    	for (int j = si.size() - 1; j >= pos; j--)
    	    if (si[j] == tgt[iNext]) {
    	    	StackOperations(j, deep, op, si, iNext);
    	    }
    	if (deep > 0 && si[deep - 1] == tgt[iNext])
    	    StackOperations(deep - 1, deep, op, si, iNext);
    }
    
}

int main()
{
    while(cin>>src>>tgt) {
       if (src.size() != tgt.size())
            cout<<"[\n"<<"]"<<endl;
       else {
           cout<<"["<<endl;
           for (int i = src.size(); i >= 0; i--)
               if (src[i] == tgt[0]) {
                   StackOperations(i, 0, "", src, 0);
               }
           cout<<"]"<<endl;
       }
    }	
    return 0;
}