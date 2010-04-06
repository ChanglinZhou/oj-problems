#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Point
{
	Point(float a = 0, float b = 0)
	{
		x = a;
		y = b;
	}
	float x, y;
};

class Graph
{
public:
	virtual bool isCircle() = 0;
	virtual bool hitTest(const Point& pt) = 0;
};

class Rect : public Graph
{
public:
	Rect(const Point& lt, const Point& rb)
		: mini(lt), maxi(rb)
	{
	}
	
	virtual bool isCircle()
	{
		return false;
	}
	
	virtual bool hitTest(const Point& pt)
	{
		return pt.x > mini.x && pt.x < maxi.x && pt.y > mini.y && pt.y < maxi.y;
	}
	
	Point mini, maxi;
};

class Circle : public Graph
{
public:
	Circle(const Point& c, float r)
		: center(c), radius(r)
	{
	}
	
	virtual bool isCircle()
	{
		return true;
	}
	
	virtual bool hitTest(const Point& pt)
	{
		float xx = center.x - pt.x;
		float yy = center.y - pt.y;
		float dist = sqrt(xx * xx + yy * yy);
		return radius > dist;
	}
	
	Rect getRect()
	{
		return Rect(Point(center.x - radius, center.y - radius), Point(center.x + radius, center.y + radius));
	}
	
private:
	Point center;
	float radius;
};



vector<Circle> circles;
vector<Rect> rects;
vector<Point> pts;

class Node
{
public:
	~Node()
	{
		for (size_t i = 0; i < subnodes.size(); ++i)
			delete subnodes[i];
	}
	vector<Graph*> graphs;
	vector<Node*> subnodes;
	Point mini, maxi;
};

void subdivideNode(Node* node, int depth)
{
	if (depth == 0)
		return;
	node->subnodes.push_back(new Node);
	node->subnodes.push_back(new Node);	
	node->subnodes.push_back(new Node);
	node->subnodes.push_back(new Node);
	
	float mid_x = (node->mini.x + node->maxi.x) / 2;
	float mid_y = (node->maxi.y + node->maxi.y) / 2;
	
	node->subnodes[0]->mini = node->mini;
	node->subnodes[0]->maxi = Point(mid_x, mid_y);
	node->subnodes[1]->mini = Point(mid_x, node->mini.y);
	node->subnodes[1]->maxi = Point(node->maxi.x, mid_y);
	node->subnodes[2]->mini = Point(node->mini.x, mid_y);
	node->subnodes[2]->maxi = Point(mid_x, node->maxi.y);
	node->subnodes[3]->mini = Point(mid_x, mid_y);
	node->subnodes[3]->maxi = node->maxi;
	
	for (size_t i = 0; i < node->graphs.size(); ++i) {
		Rect tmp = node->graphs[i]->isCircle() ? dynamic_cast<Circle*>(node->graphs[i])->getRect() : *(dynamic_cast<Rect*>(node->graphs[i]));
		//cout << tmp.mini.x << " " << tmp.mini.y << " " << tmp.maxi.x << " " << tmp.maxi.y << endl;
		if (tmp.mini.x <= mid_x && tmp.mini.y <= mid_y)
			node->subnodes[0]->graphs.push_back(node->graphs[i]);
		if (tmp.maxi.x >= mid_x && tmp.mini.y <= mid_y)
			node->subnodes[1]->graphs.push_back(node->graphs[i]);
		if (tmp.mini.x <= mid_x && tmp.maxi.y >= mid_y)
			node->subnodes[2]->graphs.push_back(node->graphs[i]);
		if (tmp.maxi.x >= mid_x && tmp.maxi.y >= mid_y)
			node->subnodes[3]->graphs.push_back(node->graphs[i]); 
	}

	for (int i = 0; i < 4; i++) {
		//cout << node->subnodes[i]->graphs.size() << endl;
		if (node->subnodes[i]->graphs.size() > 4)
			subdivideNode(node->subnodes[i], depth - 1);
	}
	node->graphs.clear();	
}

Node* constructTree()
{
	Node* root = new Node;
	for (size_t i = 0; i < circles.size(); ++i)
		root->graphs.push_back(&circles[i]);
	for (size_t i = 0; i < rects.size(); ++i)
		root->graphs.push_back(&rects[i]);
	
	Rect r = root->graphs[0]->isCircle() ? dynamic_cast<Circle*>(root->graphs[0])->getRect() : *(dynamic_cast<Rect*>(root->graphs[0]));
	for (size_t i = 1; i < root->graphs.size(); ++i) {
		Rect tmp = root->graphs[i]->isCircle() ? dynamic_cast<Circle*>(root->graphs[i])->getRect() : *(dynamic_cast<Rect*>(root->graphs[i]));
		r.mini.x = min(r.mini.x, tmp.mini.x);
		r.mini.y = min(r.mini.y, tmp.mini.y);
		r.maxi.x = max(r.maxi.x, tmp.maxi.x);
		r.maxi.y = max(r.maxi.y, tmp.maxi.y);
	}
	
	root->mini = r.mini;
	root->maxi = r.maxi;
	
	subdivideNode(root, 7);
	
	return root;
}

int solve(Node* root, const Point& p)
{
	while (root->subnodes.empty() == false) {
		float mid_x = (root->mini.x + root->maxi.x) / 2;
		float mid_y = (root->mini.y + root->maxi.y) / 2;
		if (p.x <= mid_x && p.y <= mid_y)
			root = root->subnodes[0];
		else if (p.x >= mid_x && p.y <= mid_y)
			root = root->subnodes[1];
		else if (p.x <= mid_x && p.y >= mid_y)
			root = root->subnodes[2];
		else
			root = root->subnodes[3];
	}
	
	int cnt = 0;
	for (size_t i = 0; i < root->graphs.size(); ++i) {
		if (root->graphs[i]->hitTest(p))
			++cnt;
	}
	return cnt;
}

int main()
{
	char buf[200];
	for (;;) {
		int graphCnt, pointCnt;
		cin.getline(buf, 200);
		sscanf(buf, "%d%d", &graphCnt, &pointCnt);
		if (graphCnt == 0 && pointCnt == 0)
			break;
		circles.clear();
		rects.clear();
		pts.clear();
		while (graphCnt--) {
			cin.getline(buf, 200);
			if (buf[0] == 'c') {
				Point c;
				float r;
				sscanf(buf + 1, "%f%f%f", &c.x, &c.y, &r);
				circles.push_back(Circle(c, r));
			}
			else {
				Point a, b;
				sscanf(buf + 1, "%f%f%f%f", &a.x, &a.y, &b.x, &b.y);
				rects.push_back(Rect(Point(min(a.x, b.x), min(a.y, b.y)), Point(max(a.x, b.x), max(a.y, b.y))));
			}
		}
		
		while (pointCnt--) {
			cin.getline(buf, 200);
			Point p;
			sscanf(buf, "%f%f", &p.x, &p.y);
			pts.push_back(p);
		}
		
		Node* pRoot = constructTree();
		for (size_t i = 0; i < pts.size(); ++i) {
			cout << solve(pRoot, pts[i]) << endl;
		}
		delete pRoot;
	}
	return 0;
}

