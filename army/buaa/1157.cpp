#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

void print(const vector<int>& l)
{
	copy(l.begin(), l.end(), ostream_iterator<int>(cout, ""));
	cout << endl;
}

void clear0(vector<int>& l)
{
	vector<int>::iterator iter = l.begin();
	while (iter != l.end() && *iter == 0)
		++iter;
	l.erase(l.begin(), iter);
	if (l.empty())
		l.push_back(0);
}

void my_minus(int* l_begin, int* l_end, int* r_begin, int* r_end)
{
	int* li = l_end;
	int* ri = r_end;
	for (; ri >= r_begin; --li, --ri)
	{
		int v;
		if (*li < *ri)
		{
			*li += 10;
			*(li - 1) -= 1;
		}
		*li -= *ri;
	}
}

/*
void my_add(vector<int>& l, const vector<int>& r)
{
	vector<int> tmp;
	vector<int>::reverse_iterator li = l.rbegin();
	vector<int>::const_reverse_iterator ri = r.rbegin();
	int flag = 0;
	for (; li != l.rend() || ri != r.rend();)
	{
		int v;
		if (li == l.rend())
		{
			v = *ri + flag;
			if (v > 9)
			{
				v %= 10;
				flag = 1;
			}
			else
				flag = 0;
			++ri;
		}
		else if (ri == r.rend())
		{
			v = *li + flag;
			if (v > 9)
			{
				v %= 10;
				flag = 1;
			}
			else
				flag = 0;
			++li;
		}
		else
		{
			v = *li + *ri + flag;
			if (v > 9)
			{
				v %= 10;
				flag = 1;
			}
			else
				flag = 0;
			++li;
			++ri;
		}
		tmp.push_back(v);
	}
	if (flag)
		tmp.push_back(flag);
	l.clear();
	copy(tmp.rbegin(), tmp.rend(), back_inserter(l));
}
*/
bool isBigger(int* l_begin, int* l_end, int* r_begin, int* r_end)
{
	if (l_end - l_begin > r_end - r_begin)
		return true;
	if (l_end - l_begin < r_end - r_begin)
		return false;
	for (int *p = l_begin, *q = r_begin; p <= l_end; ++p, ++q)
	{
		if (*p > *q)
			return true;
		if (*p < *q)
			return false;
	}
	return true;
}

vector<int> multiply(const vector<int>& l, const vector<int>& r)
{
	vector<int> ret(l.size() + r.size(), 0);
	for (int ri = r.size() - 1; ri >= 0; --ri)
	{
		for (int li = l.size() - 1; li >= 0; --li)
		{
			int v = r[ri] * l[li];
			int index = li + ri + 1;
			do
			{
				ret[index] += v;
				if (ret[index] < 10)
					break;
				else
				{
					v = ret[index] / 10;
					ret[index] %= 10;
					--index;
				}
			} while (true);
		}
	}
	clear0(ret);
	return ret;
}

void mod(vector<int>& l, vector<int>& r)
{
	int *l_begin = &l.front(), *l_end = &l[r.size() - 1], *r_begin = &r[0], *r_end = &r.back();
	do
	{
		while (isBigger(l_begin, l_end, r_begin, r_end))
		{
			my_minus(l_begin, l_end, r_begin, r_end);
			while (*l_begin == 0)
				++l_begin;
		}
		if (l_end == &l.back())
			break;
		else
			++l_end;
	} while (true);
	clear0(l);
}

vector<int> divide(vector<int>& l, vector<int>& r)
{
	vector<int> ret;
	int *l_begin = &l[0], *l_end = &l[r.size() - 1], *r_begin = &r[0], *r_end = &r.back();
	do
	{
		int v = 0;
		while (isBigger(l_begin, l_end, r_begin, r_end))
		{
			++v;
			my_minus(l_begin, l_end, r_begin, r_end);
			while (*l_begin == 0)
				++l_begin;
		}
		ret.push_back(v);
		if (l_end == &l.back())
			break;
		else
			++l_end;
	} while (true);
	clear0(l);
	clear0(ret);
	return ret;
}

void gcd(vector<int>& l, vector<int>& r)
{
	mod(l, r);
	l.swap(r);
	if (!(r.size() == 1 && r[0] == 0))
		gcd(l, r);
}

vector<int> solve(const vector<int>& l, const vector<int>& r)
{
	vector<int> lt(l), rt(r);
	if (!isBigger(&lt.front(), &lt.back(), &rt.front(), &rt.back()))
		lt.swap(rt);
	gcd(lt, rt);
	vector<int> a = multiply(l, r);
	return divide(a, lt);
}


int main()
{
	char buf[250];
	for (;;)
	{
		cin.getline(buf, 250);
		vector<int> l;
		vector<int> r;
		char* p = buf;
		while (isdigit(*p))
		{
			l.push_back(*p - '0');
			++p;
		}
		++p;
		while (isdigit(*p))
		{
			r.push_back(*p - '0');
			++p;
		}
		
		if (l[0] == 0 && r[0] == 0)
			break;
		vector<int> ret = solve(l, r);
		print(ret);
	}
}
