#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int l, t;
vector<int> a;

void forward(vector<int>& v)
{
	vector<int> t(v);
	for (size_t i = 1; i < v.size(); ++i)
		t[i] = v[v[i]];
	v.swap(t);
}

bool issame(vector<int>& a, vector<int>& b)
{
	for (size_t i = 1; i < a.size(); ++i)
		if (a[i] != b[i])
			return false;
	return true;
}

void solve()
{
	vector<int> s(a);
	int loop = 0;
	do
	{
		loop++;
		forward(s);
		if (issame(a, s))
			break;
	} while (true);
	
	t = t % loop;
	t = loop - t;
	while (t--)
		forward(a);
}

int main()
{
	for (;;)
	{
		cin >> l >> t;
		if (l == 0)
			break;
		a.assign(1, 0);
		for (int i = l; i; --i)
		{
			int tmp;
			cin >> tmp;
			a.push_back(tmp);
		}
		solve();
		copy(a.begin() + 1, a.end(), ostream_iterator<int>(cout, " "));
		cout << endl;
	}
}
