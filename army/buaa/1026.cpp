#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

struct Node
{
	vector<vector<int> > ways;
	vector<vector<int> > smalls;
};

typedef vector<vector<int> > IntMat;
typedef vector<vector<Node> > NodeMat;

vector<vector<int> > mat(10, vector<int>(10, 0));
int r, c, s, k;
vector<int> ways;
vector<int> smallest;

void clear0(vector<int>& l)
{
	vector<int>::iterator iter = l.begin();
	while (iter != l.end() && *iter == 0)
		++iter;
	l.erase(l.begin(), iter);
	if (l.empty())
		l.push_back(0);
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

bool isBigger(const vector<int>& l, const vector<int>& r)
{
	for (size_t i = 0; i < l.size(); ++i)
	{
		if (l[i] > r[i])
			return true;
		if (l[i] < r[i])
			return false;
	}
	return false;
}

bool isBigger(const vector<int>& l, const vector<int>& r, int k)
{
	for (size_t i = 0; i < k; ++i)
	{
		if (l[i] > r[i])
			return true;
		if (l[i] < r[i])
			return false;
	}
	return false;
}

bool isEqual(const vector<int>& l, const vector<int>& r)
{
	for (size_t i = 0; i < l.size(); ++i)
	{
		if (l[i] != r[i])
			return false;
	}
	return true;
}

void compute(IntMat& oldways, IntMat& oldsmalls, IntMat& newways, IntMat& newsmalls, int val)
{
	static int sss = 0;
	for (int i = 0; i < k; ++i)
	{
		if (oldways[i].empty())
			continue;
		int newmod = (i * 10 + val) % k;
		/*
					cout << "old:" << endl;
					copy(oldsmalls[i].begin(), oldsmalls[i].end(), ostream_iterator<int>(cout, ""));
					cout << " ";
					copy(oldways[i].begin(), oldways[i].end(), ostream_iterator<int>(cout, ""));
					cout << endl;	
					*/
		if (newways[newmod].empty() || isBigger(newsmalls[newmod], oldsmalls[i]))
		{
			newways[newmod] = oldways[i];
			newsmalls[newmod] = oldsmalls[i];
			/*
					cout << "new:" << endl;
					copy(newsmalls[newmod].begin(), newsmalls[newmod].end(), ostream_iterator<int>(cout, ""));
					cout << " ";
					copy(newways[newmod].begin(), newways[newmod].end(), ostream_iterator<int>(cout, ""));
					cout << endl;	
				*/
		}
		else if (isEqual(newsmalls[newmod], oldsmalls[i]))
		{
			my_add(newways[newmod], oldways[i]);
			/*
					cout << "new:add" << endl;
					copy(newsmalls[newmod].begin(), newsmalls[newmod].end(), ostream_iterator<int>(cout, ""));
					cout << " ";
					copy(newways[newmod].begin(), newways[newmod].end(), ostream_iterator<int>(cout, ""));
					cout << endl;	
				*/
		}
	}
}

void solve()
{
	NodeMat oldnm(r, vector<Node>(c));
	for (int i = 0; i < r; i++) 
	{
		for (int j = 0; j < c; j++)
		{
			oldnm[i][j].ways.assign(k, vector<int>());
			oldnm[i][j].smalls.assign(k, vector<int>());
			int mod = mat[i][j] % k;
			oldnm[i][j].ways[mod].push_back(1);
			oldnm[i][j].smalls[mod].push_back(mat[i][j]);
		}
	}
	
	
	for (int step = 1; step < s; ++step)
	{
		NodeMat newnm(r, vector<Node>(c));
		for (int i = 0; i < r; i++) 
		{
			for (int j = 0; j < c; j++)
			{
				newnm[i][j].ways.assign(k, vector<int>());
				newnm[i][j].smalls.assign(k, vector<int>());
			}
		}
		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < c; ++j)
			{
				//cout << "I:" << i << " "<< j << endl;
			
				if (i != 0)
					compute(oldnm[i - 1][j].ways, oldnm[i - 1][j].smalls, newnm[i][j].ways, newnm[i][j].smalls, mat[i][j]);
				if (i != r - 1)
					compute(oldnm[i + 1][j].ways, oldnm[i + 1][j].smalls, newnm[i][j].ways, newnm[i][j].smalls, mat[i][j]);
				if (j != 0)
					compute(oldnm[i][j - 1].ways, oldnm[i][j - 1].smalls, newnm[i][j].ways, newnm[i][j].smalls, mat[i][j]);
				if (j != c - 1)
					compute(oldnm[i][j + 1].ways, oldnm[i][j + 1].smalls, newnm[i][j].ways, newnm[i][j].smalls, mat[i][j]);
					
				for (int b = 0; b < k; b++)
				{
					if (newnm[i][j].ways[b].empty() == false)
						newnm[i][j].smalls[b].push_back(mat[i][j]);
			/*		cout << "I:" << i << j << b << endl;
					copy(newnm[i][j].smalls[b].begin(), newnm[i][j].smalls[b].end(), ostream_iterator<int>(cout, ""));
					cout << " ";
					copy(newnm[i][j].ways[b].begin(), newnm[i][j].ways[b].end(), ostream_iterator<int>(cout, ""));
					cout << endl;				
					*/
				}
			}
		}
		
		oldnm.swap(newnm);
	}
	
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			if (oldnm[i][j].ways[0].empty() == false)
			{
				if (ways.empty() || isBigger(smallest, oldnm[i][j].smalls[0]))
				{
					ways = oldnm[i][j].ways[0];
					smallest = oldnm[i][j].smalls[0];
				}
				else if (isEqual(smallest, oldnm[i][j].smalls[0]))
				{
					my_add(ways, oldnm[i][j].ways[0]);
				}
			}
		}
	}
}

int main()
{
	int cnt;
	cin >> cnt;
	int index = 0;
	while (cnt--)
	{
		cin >> r >> c >> s >> k;
	
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				cin >> mat[i][j];
		
		ways.clear();
		smallest.clear();

		solve();
		clear0(smallest);
		cout << "Case " << ++index << ": ";
		if (ways.empty())
			cout << -1 << " " << -1 << endl;
		else
		{
			copy(smallest.begin(), smallest.end(), ostream_iterator<int>(cout, ""));
			cout << " ";
			copy(ways.begin(), ways.end(), ostream_iterator<int>(cout, ""));
			cout << endl;
		}
	}
}


/*
void f(vector<int>& val, int& step, int& mod, int prev_i, int prev_j);
void go(vector<int>& val, int& step, int& mod, int i, int j)
{
	val.push_back(mat[i][j]);
	if (smallest.empty() || !isBigger(val, smallest, val.size()))
	{
		++step;
		int oldMod = mod;
		mod = mod * 10 + mat[i][j];
		mod %= k;
		
		f(val, step, mod, i, j);
		
		mod = oldMod;
		--step;
	}
	val.pop_back();
}

void f(vector<int>& val, int& step, int& mod, int prev_i, int prev_j)
{
	if (step == s)
	{
		if (mod == 0)
		{
			if (smallest.empty() || isBigger(smallest, val))
			{
				
				smallest = val;
				ways = 1;
			}
			else if (isEqual(smallest, val))
				++ways;
		}
		return;
	}

	if (prev_i != 0)
		go(val, step, mod, prev_i - 1, prev_j);
	if (prev_i != r - 1)
		go(val, step, mod, prev_i + 1, prev_j);
	if (prev_j != 0)
		go(val, step, mod, prev_i, prev_j - 1);
	if (prev_j != c - 1)
		go(val, step, mod, prev_i, prev_j + 1);
}

void solve()
{
	vector<int> val;
	int step = 0;
	int mod = 0;
	
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j)
			go(val, step, mod, i, j);
}
*/

