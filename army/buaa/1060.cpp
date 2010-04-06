#include <iostream>
#include <vector>
using namespace std;

vector<int> mat(26, 0);
int total;
int cnt;

vector<int> ch(26, 0);
int finalResult;

int jiecheng(int a)
{
	int s = 1;
	for (int i = 2; i <= a; ++i)
		s *= i;
	return s;
}

void calc()
{
	int all = jiecheng(total);
	for (int i = 0; i < 26; ++i)
	{
		if (ch[i] != 0)
		{
			all /= jiecheng(ch[i]);
		}
	}
	finalResult += all;
}

void compute(int alph)
{
	if (cnt == 0)
	{
		calc();
		return;
	}
	
	if (alph == 26)
		return;
	
	int aCnt = min(cnt, mat[alph]);
	for (int i = 0; i <= aCnt; ++i)
	{
		cnt -= i;
		ch[alph] = i;
		compute(alph + 1);
		ch[alph] = 0;
		cnt += i;
	}
}

void solve()
{
	ch.clear();
	ch.assign(26, 0);
	finalResult = 0;
	compute(0);
	cout << finalResult << endl;
}

int main()
{
	char buf[200];
	for (;;)
	{
		cin.getline(buf, 200);
		if (buf[0] == '-')
			break;
		char* p = buf;
		while (*p != ' ')
			++p;
		*p = 0;
		string str(buf);
		sscanf(p + 1, "%d", &cnt);
		total = cnt;

		mat.clear();
		mat.assign(26, 0);
		for (size_t i = 0; i < str.length(); ++i)
			++mat[str[i] - 'a']; 
		solve();
	}
}
