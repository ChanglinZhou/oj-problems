#include <iostream>
#include <vector>
using namespace std;

vector<int> a;

void extend(int val)
{
	int k = a.size();
	for (; k <= val; ++k) {
		int v = 0;
		for (int i = 2; i < k; ++i) 
		{
			v += a[i] * a[k + 1 - i];
		}
		a.push_back(v);
	}
}

int solve(int val)
{
	if (a.size() <= val)
		extend(val);

	cout << a[val] << endl;		
}

int main()
{
	a.reserve(100);
	a.push_back(1);
	a.push_back(1);
	a.push_back(1);
	a.push_back(1);
	
	char buf[100];
	for (;;) {
		cin.getline(buf, 100);
		if (strlen(buf) == 0)
			break;
		int a;
		sscanf(buf, "%d", &a);
		solve(a);
	}
	return 0;
}
