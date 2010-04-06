#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

vector<vector<int> > tree;
vector<int> p;
vector<bool> infect;
vector<bool> separate;
int nodeCnt, edgeCnt;
int infectcnt;

void constructTree()
{
	tree.clear();
	tree.assign(nodeCnt + 1, vector<int>());
	infect.clear();
	infect.assign(nodeCnt + 1, false);
	separate.clear();
	separate.assign(nodeCnt + 1, false);
	p.clear();
	p.assign(nodeCnt + 1, 0);
	infect[1] = true;
	infectcnt = 0;
	
	while (edgeCnt--) {
		int parent, son;
		cin >> parent >> son;
		p[son] = parent;
		tree[parent].push_back(son);
	}
}

void separateTree(int i)
{
	separate[i] = true;
	for (size_t j = 0; j < tree[i].size(); ++j)
		separateTree(tree[i][j]);
}

void unseparateTree(int i)
{
	separate[i] = false;
	for (size_t j = 0; j < tree[i].size(); ++j)
		unseparateTree(tree[i][j]);
}

void infectTree(vector<int>& nodes)
{
	for (int i = 1; i <= nodeCnt; ++i)
	{
		if (infect[i] == false && separate[i] == false && infect[p[i]] == true)
		{
			nodes.push_back(i);
		}
	}
	for (size_t i = 0; i < nodes.size(); ++i)
		infect[nodes[i]] = true;
}

void uninfectTree(vector<int>& nodes)
{
	for (int i = 0; i < nodes.size(); ++i)
	{
		infect[nodes[i]] = false;
	}
}

void solve(int& cnt)
{
	bool f = false;
	for (size_t i = 1; i <= nodeCnt; ++i)
	{
		if (infect[i] == false && separate[i] == false && infect[p[i]] == true)
		{
			f = true;
			separateTree(i);
			vector<int> nodes;
			infectTree(nodes);
			cnt += nodes.size();
			solve(cnt);
			cnt -= nodes.size();
			uninfectTree(nodes);
			unseparateTree(i);
		}
	}
	if (f == false)
	{
		if (infectcnt == 0 || cnt < infectcnt)
		{
			//cout << cnt << ": ";
			//copy(infect.begin(), infect.end(), ostream_iterator<bool>(cout, " "));
			//cout << endl;
			infectcnt = cnt;
		}
	}
}

/*
int solve(const vector<int>& root)
{
	int min_v = 0;
	for (size_t i = 0; i < root.size(); ++i) {
		vector<int> subRoot;
		for (size_t j = 0; j < root.size(); ++j) {
			if (i == j)
				continue;
			int childNode = root[j];
			copy(tree[childNode].begin(), tree[childNode].end(), back_inserter(subRoot));
		}
		if (subRoot.empty() == false) {
			int v = solve(subRoot);
			if (min_v == 0 || v < min_v)
				min_v = v;
/*			cout << root[i] << " : ";
			copy(subRoot.begin(), subRoot.end(), ostream_iterator<int>(cout, " "));
			cout << endl;
			cout << v << endl;

		}
		else {
			min_v = 0;
			break;
		}
	}
	return min_v + root.size() - 1;	
}
*/



int main()
{
	for (;;)
	{
		cin >> nodeCnt >> edgeCnt;
		if (nodeCnt == 0)
			break;
		constructTree();
		int cnt = 1;
		solve(cnt);
		cout << infectcnt << endl;
	}
}
