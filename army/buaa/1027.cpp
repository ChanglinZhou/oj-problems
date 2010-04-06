#include <iostream>
using namespace std;

bool solve(const string& str)
{
	string::const_iterator iter = str.begin();
	while (iter != str.end() && *iter != 'I')
		++iter;
	while (iter != str.end() && *iter != 'C')
		++iter;
	while (iter != str.end() && *iter != 'P')
		++iter;
	while (iter != str.end() && *iter != 'C')
		++iter;
	if (iter == str.end())
		return false;
	else
		return true;
}

int main()
{
	int cnt;
	cin >> cnt;
	char buf[100];
	cin.getline(buf, 100);
	int c = 0;
	while (cnt--)
	{
		cin.getline(buf, 100);
		if (solve(buf))
			printf("Case %d: Yes\n", ++c);
		else
			printf("Case %d: No\n", ++c);
	}
}
