#include <iostream>
#include <vector>
using namespace std;

int nodeCnt, edgeCnt;

int dis[11][11];

/*
void addCandidate(int i, vector<bool>& visited, vector<int>& mindis, vector<int>& candidates)
{
	for (int j = 1; j <= nodeCnt; ++j)
	{
		if (visited[j] == false && dis[i][j] != -1)
		{
			int newMindis = mindis[i] + dis[i][j];
			if (mindis[j] == -1)
			{
				mindis[j] = newMindis;
				candidates.push_back(j);
			}
			else if (mindis[j] > newMindis)
				mindis[j] = newMindis;
		}
	}
}

int solve()
{
	vector<int> mindis(nodeCnt + 1, -1);
	vector<bool> visited(nodeCnt + 1, false);
	vector<int> candidates;
	
	visited[1] = true;
	mindis[1] = 0;
	addCandidate(1, visited, mindis, candidates);
	
	while (candidates.empty() == false)
	{
		int mini = 0;
		for (int i = 1; i < candidates.size(); ++i)
		{
			if (mindis[candidates[i]] < mindis[candidates[mini]])
				mini = i;
		}
		int nodeIndex = candidates[mini];
		
		if (nodeIndex == nodeCnt)
			break;
		visited[nodeIndex] = true;
		candidates.erase(candidates.begin() + mini);
		addCandidate(nodeIndex, visited, mindis, candidates);
	}
	return mindis[nodeCnt];
}
*/

void solve()
{
	int mat[11][11];
	memcpy(mat, dis, sizeof(int)*11*11);
	
	for (int i = 1; i < nodeCnt; ++i)
	{
		int tmp[11][11];
		for (int a = 1; a <= nodeCnt; ++a)
		{
			for (int b = 1; b <= nodeCnt; ++b)
			{
				int m = mat[a][b];
				for (int c = 1; c <= nodeCnt; ++c)
				{
					if (mat[a][c] > 0 && dis[c][b] > 0)
					{
						int k = mat[a][c] + dis[c][b];
						if (m == -1 || k < m)
							m = k;
					}
				}
				tmp[a][b] = tmp[b][a] = m;
			}
		}
		memcpy(mat, tmp, sizeof(int)*11*11);
	}
	memcpy(dis, mat, sizeof(int)*11*11);
}

int main()
{
	cin >> nodeCnt >> edgeCnt;
	for (int i = 1; i <= nodeCnt; ++i)
		for (int j = 1; j <= nodeCnt; ++j)
			if (i == j)
				dis[i][j] = 0;
			else
				dis[i][j] = -1;
	for (int i = 0; i < edgeCnt; ++i)
	{
		int a, b, d;
		cin >> a >> b >> d;
		dis[a][b] = d;
		dis[b][a] = d;
	}
	
	solve();
	
	for (;;)
	{
		int a, b;
		cin >> a >> b;
		if (a == 0 && b == 0)
			break;
		cout << dis[a][b] << endl;
	}
}
