#include <iostream>
#include <vector>
#include <map>
#include <stack>

using namespace std;

class Node
{
public:
	Node()
	{
		val = 1;
		conn = 0;
		top = bottom = left = right = visited = false;
	}
	int val, conn;
	bool top, bottom, left, right, visited;
	
};

typedef vector<vector<Node> > matrix;
typedef pair<size_t, size_t> position;

bool isConnectable(matrix& m)
{
	position startPos;
	bool found = false;
	for (size_t i = 0; !found && i < m.size(); ++i)
		for (size_t j = 0; !found && j < m[i].size(); ++j)
			if (m[i][j].val == 0) {
				startPos.first = i;
				startPos.second = j;
				found = true;
			}
	if (!found)
		return true;
	
	stack<position> stk;
	stk.push(startPos);
	m[startPos.first][startPos.second].visited = true;

	while (stk.empty() == false) {
		position tmp = stk.top();
		Node& node = m[tmp.first][tmp.second];
		if (node.top && m[tmp.first - 1][tmp.second].visited == false) {
			m[tmp.first - 1][tmp.second].visited = true;
			stk.push(make_pair(tmp.first - 1, tmp.second));
		}
		else if (node.bottom && m[tmp.first + 1][tmp.second].visited == false) {
			m[tmp.first + 1][tmp.second].visited = true;
			stk.push(make_pair(tmp.first + 1, tmp.second));
		}
		else if (node.left && m[tmp.first][tmp.second - 1].visited == false) {
			m[tmp.first][tmp.second - 1].visited = true;
			stk.push(make_pair(tmp.first, tmp.second - 1));
		}
		else if (node.right && m[tmp.first][tmp.second + 1].visited == false) {
			m[tmp.first][tmp.second + 1].visited = true;
			stk.push(make_pair(tmp.first, tmp.second + 1));
		}
		else
			stk.pop();
	}
	
	found = false;
	for (size_t i = 0; i < m.size(); ++i)
		for (size_t j = 0; j < m[i].size(); ++j) {
			if (m[i][j].val == 0 && m[i][j].visited == false) {
				found = true;
			}
			m[i][j].visited = false;
		}
	
	return !found;
}

bool solve(int w, int h)
{
	matrix m(h, vector<Node>(h));
	
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			cin >> m[i][j].val;
			if (m[i][j].val == 1)
				continue;
			if (i > 0 && m[i - 1][j].val == 0) {
				m[i - 1][j].conn++;
				m[i - 1][j].bottom = true;
				m[i][j].conn++;
				m[i][j].top = true;
			}
			if (j > 0 && m[i][j - 1].val == 0) {
				m[i][j - 1].conn++;
				m[i][j - 1].right = true;
				m[i][j].conn++;
				m[i][j].left = true;
			}
		}
	}

	if (false == isConnectable(m))
		return false;
		
	
	
	return true;
}

int main()
{
	for (;;) {
		int w, h;
		cin >> h >> w;
		if (w == 0 && h == 0)
			break;
		if (solve(w, h))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	return 0;
}

