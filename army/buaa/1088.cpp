#include <iostream>
using namespace std;

int digitCnt(int a)
{
	if (a < 10)
		return 1;
	else if (a < 100)
		return 2;
	else if (a < 1000)
		return 3;
	else if (a < 10000)
		return 4;
	else
		return 5;
}

void solve(int a, int b)
{
	int prod = a * b;
	int aLen = digitCnt(a);
	int bLen = digitCnt(b);
	int prodLen = digitCnt(prod);
	int maxLen = max(prodLen, bLen + 1);
	
	for (int i = aLen; i < maxLen; ++i)
		cout << " ";
	cout << a << endl;
	
	for (int i = bLen + 1; i < maxLen; ++i)
		cout << " ";
	cout << "x" << b << endl;
	
	for (int i = 0; i < maxLen; ++i)
		cout << "-";
	cout << endl;
	
	for (int i = 0; i < bLen; ++i)
	{
		int v = (b % 10) * a;
		b /= 10;
		if (v == 0)
		{
			for (int j = aLen + i; j < maxLen; ++j)
				cout << " ";
			for (int j = 0; j < aLen; ++j)
				cout << 0;
			cout << endl;
		}
		else
		{
			int dcnt = digitCnt(v);
			for (int j = dcnt + i; j < maxLen; ++j)
				cout << " ";
			cout << v << endl;	
		}
	}
	
	if (bLen > 1)
	{
		for (int i = 0; i < maxLen; ++i)
			cout << "-";
		cout << endl;
		
		for (int i = prodLen; i < maxLen; ++i)
			cout << " ";
		cout << prod << endl;
	}
	cout << endl;
}

int main()
{
	for (;;)
	{
		int a, b;
		cin >> a >> b;
		if (a == 0 && b == 0)
			break;
		solve(a, b);
	}
}
