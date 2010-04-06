#include <iostream>
#include <vector>
#include <iterator>
#include <map>
using namespace std;


void multiply(vector<int>& l, const vector<int>& r)
{
	vector<int> ret(l.size(), 0);
	for (vector<int>::const_reverse_iterator ri = r.rbegin(); ri != r.rend(); ++ri)
	{
		vector<int>::const_reverse_iterator lastIter = l.rbegin() + (l.size() - (ri - r.rbegin()));
		for (vector<int>::const_reverse_iterator li = l.rbegin(); li != lastIter; ++li)
		{
			int v = *ri * *li;
			*(ret.rbegin() + (ri - r.rbegin()) + (li - l.rbegin())) += v;
		}
	}
	
	for (vector<int>::reverse_iterator iter = ret.rbegin(); iter != ret.rend() - 1; ++iter)
	{
		*(iter + 1) += *iter / 10;
		*iter %= 10;
	}
	ret[0] %= 10;
	l.swap(ret);
}

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


void trim(vector<int>& l, int k)
{
	if (l.size() > k)
		l.erase(l.begin(), l.begin() + l.size() - k);
	else
	{
		while (l.size() < k)
			l.insert(l.begin(), 0);
	}	
}

bool issame(const vector<int>& l, const vector<int>& r, int& k)
{
	vector<int>::const_reverse_iterator li = l.rbegin(), ri = r.rbegin();
	k = 0;
	for (; li != l.rend() && ri != r.rend(); ++li, ++ri, ++k)
		if (*li != *ri)
			return false;
	return true;
}

void print(const vector<int>& l)
{
	copy(l.begin(), l.end(), ostream_iterator<int>(cout, ""));
	cout << endl;
}

void add_map(multimap<unsigned int, vector<int> >& m, const vector<int>& l)
{
	int key = 0;
	int i = 0;
	for (vector<int>::const_reverse_iterator iter = l.rbegin(); iter != l.rend() && i < 6; ++iter)
	{
		key = key * 10 + *iter;
		i++;
	}
	m.insert(make_pair(key, l));
}

bool find_map(multimap<unsigned int, vector<int> >& m, const vector<int>& l)
{
	int key = 0;
	int i = 0;
	for (vector<int>::const_reverse_iterator iter = l.rbegin(); iter != l.rend() && i < 6; ++iter)
	{
		key = key * 10 + *iter;
		i++;
	}
	int cnt = m.count(key);
	multimap<unsigned int, vector<int> >::iterator iter = m.find(key);
	while (cnt--)
	{
		int k;
		issame(l, iter->second, k);
		if (k == l.size())
			return true;
		++iter;
	}
	return false;
}

vector<int> solve(const vector<int>& l, int k)
{
	int incr_k = 0;

	vector<int> ref = l;
	trim(ref, k);
	vector<int> ref1 = ref;
	//vector<int> ref2 = ref;
	//multiply(ref2, ref1);
	//trim(ref2, k);
	
	vector<int> incr_ref1 = ref1;
	//vector<int> incr_ref2 = ref2;
	multimap<unsigned int, vector<int> > store;
	//vector<int> v2 = ref;
	
	vector<int> n(1, 1);
	vector<int> step(1, 1);
	for (;;)
	{
		vector<int> v1(ref);
		//vector<int> v2(ref);
		multiply(v1, incr_ref1);
		//multiply(v2, incr_ref2);
		//trim(v1, k);
		//trim(v2, k);
		int tmp_k;
		issame(v1, ref, tmp_k);
		if (tmp_k == k)
		{
			break;
		}
		if (tmp_k > incr_k)
		{
			incr_k = tmp_k;
			ref1 = incr_ref1;
			//ref2 = incr_ref2;
			step = n;
		}
		if (find_map(store, v1))
		{
			n.clear();
			n.push_back(-1);
			break;
		}
		add_map(store, v1);
		//int tmp_k2;
		//issame(v1, v2, tmp_k2);
		//if (tmp_k2 > tmp_k)
		//{
		//	n.clear();
		//	n.push_back(-1);
		//	break;
		//}
		multiply(incr_ref1, ref1);
		//multiply(incr_ref2, ref2);
		my_add(n, step);
	}
	
	return n;
}


int main()
{
	char buf[250];
	for (;;)
	{
		cin.getline(buf, 250);
		vector<int> l;
		char* p = buf;
		while (isdigit(*p))
		{
			l.push_back(*p - '0');
			++p;
		}
		int k;
		sscanf(p, "%d", &k);		
		if (k == 0)
			break;
		vector<int> ret = solve(l, k);
		print(ret);
	}
}
