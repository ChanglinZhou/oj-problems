#include <iostream>
#include <string>
using namespace std;

void solve(const string& str)
{
	int val = 0;
	for (size_t i = 0; i < str.length(); ++i) {
		val <<= 1;
		if (str[i] == '1')
			++val;
	}
	cout << val << endl;
}

int main()
{
	char buf[100];
	int cnt;
	cin >> cnt;
	cin.getline(buf, 100);	
	while (cnt--) {
		cin.getline(buf, 100);
		solve(buf);
	}
	return 0;
}
