#include <iostream>
#include <vector>
#include <list>
using namespace std;

struct Node
{
	int index;
	int cnt;
	int pos;
	Node* parent;
};

vector<Node> ships(30001);
//vector<vector<int> > regions(30001);
//vector<int> pos(30001, 0);
//vector<int> tsize(30001, 0);

void init()
{
	for (int i = 1; i <= 30000; ++i)
	{
		ships[i].index = i;
		ships[i].cnt = 1;
		ships[i].pos = 1;
		ships[i].parent = NULL;
		//tsize[i] = 1;
		//ships[i].index = i;
		//ships[i].cnt = 1;
		//ships[i].parent = NULL;
		//ships[i].children.clear();
	}
}

void uninit()
{
}


Node* head(Node* n)
{
	while (n->parent)
	{
		n = n->parent;
	}
	return n;
}

Node* head(Node* n, int& pos)
{
	pos = 1;
	while (n->parent)
	{
		pos += n->pos;
		n = n->parent;
	}
	return n;
}

void move(int s, int t)
{
	Node* shead = head(&ships[s]);
	Node* thead = head(&ships[t]);
	shead->parent = thead;
	shead->pos = thead->cnt;
	thead->cnt += shead->cnt;
/*
	int s_region = ships[s];
	int t_region = ships[t];
	if (s_region == t_region)
		return;
	size_t ts = regions[t_region].size();
	regions[t_region].resize(regions[t_region].size() + regions[s_region].size());
	copy(regions[s_region].begin(), regions[s_region].end(), regions[t_region].begin() + ts);
	vector<int>::iterator endIter = regions[s_region].end();
	//for (vector<int>::iterator iter = regions[s_region].begin(); iter != endIter; ++iter)
	//{
	//	ships[*iter] = t_region;
	//	pos[*iter] += ts;
	//}
	vector<int>().swap(regions[s_region]);
	
*/
/*
	Node* s_head = head(&ships[s]);	
	//Node* s_tail = tail(&ships[s]);
	Node* t_head = head(&ships[t]);
	//Node* t_tail = tail(&ships[t]);
	if (s_head == t_head)
	{
		*(int*)0 = 1;
		return;
	}
	s_head->parent = t_head;
	t_head->children.push_back(s_head);
	t_head->cnt += s_head->cnt;
*/
}

void query(int s, int t)
{
	int spos;
	Node* shead = head(&ships[s], spos);
	int tpos;
	Node* thead = head(&ships[t], tpos);
	//if (shead != thead)
	//	cout << -1 << endl;
	//else
	//	cout << abs(spos - tpos) - 1 << endl;
	//cout << -1 << endl;
	//int s_region = ships[s];
	//int t_region = ships[t];
	//if (s_region != t_region)
	//	cout << -1 << endl;
	//else
	//{
	//	cout << abs(pos[s] - pos[t]) - 1 << endl;
	//}
/*
	int s_pos;
	Node* s_head = head(&ships[s]);
	int t_pos;
	Node* t_head = NULL;//head_with_cnt(&ships[t], t_pos);
	if (s_head != t_head)
		cout << -1 << endl;
	else
		cout << abs(t_pos - s_pos) - 1 << endl;
*/
}

int main()
{
	for (;;)
	{
		char buf[100];
		cin.getline(buf, 100);
		int cnt;
		sscanf(buf, "%d", &cnt);
		if (cnt == 0)
			break;
		init();
		while (cnt--) 
		{
			cin.getline(buf, 100);
			if (buf[0] == 'M')
			{
				int s, t;
				sscanf(buf + 1, "%d%d", &s, &t);
				move(s, t);
			}
			else
			{
				int s, t;
				sscanf(buf + 1, "%d%d", &s, &t);
				query(s, t);
			}
		}
		uninit();
	}
	return 0;
}

/*
struct Node
{
	Node(int _index)
	{
		index = _index;
		next = prev = NULL;
	}
	
	int index;
	Node* next;
	Node* prev
};

vector<int> ships(30001, 0);
vector<pair<Node*, Node*> > regions(30001, pair<Node*, Node*>(NULL, NULL));
vector<int> pos(30001, 0);
vector<int> tsize(30001, 0);

void init()
{
	for (int i = 1; i <= 30000; ++i)
	{
		ships[i] = i;
		pos[i] = 1;
		Node* p = new Node(i);
		regions[i].first = p;
		regions[i].second = p;
		tsize[i] = 1;
	}
}

void uninit()
{
	for (int i = 1; i <= 30000; ++i)
	{
		delete regions[i].first;
	}
}

void move(int s, int t)
{
	int s_region = ships[s];	
	int t_region = ships[t];
	regions[t_region].second->next = regions[s_region].first;
	regions[t_region].second = regions[s_region].second;
	Node* p = regions[s_region].first;
	while (p)
	{
		pos[p->index] += tsize[t_region];
		ships[p->index] = t_region;
		p = p->next;
	}
	tsize[t_region] += tsize[s_region];
	tsize[s_region] = 0;
	regions[s_region].first = regions[s_region].second = NULL;
}

void query(int s, int t)
{
	int s_region = ships[s];
	int t_region = ships[t];
	if (s_region != t_region)
		cout << -1 << endl;
	else
		cout << abs(pos[s] - pos[t]) - 1 << endl;
}
*/
