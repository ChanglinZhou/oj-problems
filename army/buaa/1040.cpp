#include <iostream>
#include <map>
using namespace std;

int mat[] = 
{
1,
2,
3,
4,
5,
6,
7,
8,
9,
2,
3,
4,
5,
6,
7,
8,
9,
10,
3,
5,
7,
9,
11,
13,
15,
17,
19,
5,
13,
29,
61,
125,
253,
509,
1021,
2045,
};

int main()
{
	int cnt;
	cin >> cnt;
	while (cnt--) {
		int a, b;
		cin >> a >> b;
		cout << mat[a * 9 + b] << endl;
	}

	return 0;
}

/*
map<pair<int, int>, long long> a;

long long solve(int m, int n)
{
	if (m == 0)
		return n + 1;

	map<pair<int, int>, long long>::iterator iter = a.find(make_pair(m, n));
	if (iter != a.end())
		return iter->second;

	if (n == 0) {
		long long v = solve(m - 1, 1);
		a[make_pair(m, n)] = v;
		return v;
	}
	
	long long s = solve(m, n - 1);
	s = solve(m - 1, s);
	a[make_pair(m, n)] = s;
	return s;
}

int main()
{
	for (int m = 0; m < 4; m++)
		for (int n = 0; n < 9; n++)
			cout << solve(m, n) << "," << endl;

	int cnt;
	cin >> cnt;
	while (cnt--) {
		int a, b;
		cin >> a >> b;
		cout << solve(a, b) << endl;
	}

	return 0;
}
*/
