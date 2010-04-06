#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
using namespace std;

int self_trans[][4] =
{
	/* 0 */ {6, 9, -1},
	/* 1 */ {-1},
	/* 2 */ {3, -1},
	/* 3 */ {2, 5, -1},
	/* 4 */ {-1},
	/* 5 */ {3, -1},
	/* 6 */ {0, 9, -1},
	/* 7 */ {-1},
	/* 8 */ {-1},
	/* 9 */ {0, 6, -1},
};

int minus_trans[][4] = 
{
	/* 0 */ {-1},
	/* 1 */ {-1},
	/* 2 */ {-1},
	/* 3 */ {-1},
	/* 4 */ {-1},
	/* 5 */ {-1},
	/* 6 */ {5, -1},
	/* 7 */ {1, -1},
	/* 8 */ {0,6,9, -1},
	/* 9 */ {3, 5, -1},
};

int add_trans[][4] =
{
	/* 0 */ {8, -1},
	/* 1 */ {7, -1},
	/* 2 */ {-1},
	/* 3 */ {9, -1},
	/* 4 */ {-1},
	/* 5 */ {6,9, -1},
	/* 6 */ {8, -1},
	/* 7 */ {-1},
	/* 8 */ {-1},
	/* 9 */ {8, -1},
};



void my_minus(vector<int>& l, const vector<int>& r)
{
	for (size_t i = 0; i < r.size(); ++i)
	{
		if (l[i] < r[i])
		{
			l[i + 1]--;
			l[i] += 10;
		}
		l[i] -= r[i];
	}
	while (l.back() == 0)
		l.pop_back();
}

bool isBigger(const vector<int>& l, const vector<int>& r)
{
	if (l.size() > r.size())
	{
		for (size_t i = l.size() - 1; i >= r.size(); --i)
			if (l[i] > 0)
				return true;
	}
	else if (r.size() > l.size())
	{
		for (size_t i = r.size() - 1; i >= l.size(); --i)
			if (r[i] > 0)
				return false;
	}
	for (int i = min(l.size(), r.size()) - 1; i >= 0; --i)
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
	if (l.size() > r.size())
	{
		for (size_t i = l.size() - 1; i >= r.size(); --i)
			if (l[i] > 0)
				return false;
	}
	else if (r.size() > l.size())
	{
		for (size_t i = r.size() - 1; i >= l.size(); --i)
			if (r[i] > 0)
				return false;
	}
	for (int i = min(l.size(), r.size()) - 1; i >= 0; --i)
	{
		if (l[i] != r[i])
			return false;
	}
	return true;
}

void my_add(vector<int>& l, const vector<int>& r)
{
	while (l.size() < r.size())
		l.push_back(0);
	l.push_back(0);
	for (size_t i = 0; i < r.size(); ++i)
	{
		l[i] += r[i];
		if (l[i] > 9)
		{
			++l[i + 1];
			l[i] -= 10;
		}
	}
	while (l.back() == 0)
		l.pop_back();
}

struct Node
{
	bool add;
	vector<int> number;
	
	bool operator< (const Node& r) const
	{
		if (add)
		{
			if (r.add)
			{
				return isBigger(r.number, number);
			}
			else
				return false;
		}
		else
		{
			if (r.add)
				return true;
			else
				return isBigger(number, r.number);
		}
	}
};

void my_add(Node& l, Node& r)
{
	if (l.add != r.add)
	{
		vector<int> tmp;
		if (isEqual(l.number, r.number))
		{
			l.add = true;
			l.number.clear();
			l.number.push_back(0);
		}
		else if (isBigger(l.number, r.number))
		{
			my_minus(l.number, r.number);
		}
		else
		{
			l.add = r.add;
			tmp = r.number;
			my_minus(tmp, l.number);
			tmp.swap(l.number);
		}
	}
	else
	{
		my_add(l.number, r.number);
	}
}

void my_minus(Node& l, Node& r)
{
	r.add = !r.add;
	my_add(l, r);
	r.add = !r.add;
}

vector<Node> val(const string& str)
{
	vector<Node> ret;
	for (size_t i = 0; i < str.length(); ) {
		Node n;
		n.add = true;
		if (str[i] == '+') {
			++i;
		}
		else if (str[i] == '-') {
			n.add = false;
			++i;
		}

		while (i < str.length() && isdigit(str[i])) {
			n.number.push_back(str[i] - '0');
			++i;
		}
		reverse(n.number.begin(), n.number.end());
		ret.push_back(n);
	}
	return ret;
}

bool compare(Node left, Node& newVal, Node& oldVal, Node& right)
{
	my_add(left, newVal);
	oldVal.add = !oldVal.add;
	my_add(left, oldVal);
	oldVal.add = !oldVal.add;
	if (left.add == right.add && !isBigger(left.number, right.number) && !isBigger(right.number, left.number))
		return true;
	else
		return false;
}

/*
vector<int> compute(const string& str)
{
	vector<int> v;
	for (string::reverse_iterator iter = str.rbegin(); iter != str.rend(); ++iter)
		v.push_back(*iter - '0');
	return v;
}
*/
void output(const vector<Node>& left, const vector<Node>& right)
{
	for (size_t i = 0; i < left.size(); ++i)
	{
		if (i != 0 || left[i].add == false)
		{
			if (left[i].add)
				cout << "+";
			else
				cout << "-";
		}
		for (int j = left[i].number.size() - 1; j >= 0; --j)
			cout << char('0' + left[i].number[j]);
	}
	cout << "=";
	for (size_t i = 0; i < right.size(); ++i)
	{
		if (i != 0 || right[i].add == false)
		{
			if (right[i].add)
				cout << "+";
			else
				cout << "-";
		}
		for (int j = right[i].number.size() - 1; j >= 0; --j)
			cout << char('0' + right[i].number[j]);
	}
	cout << "#" << endl;
/*
	copy(left.begin(), left.end(), ostream_iterator<string>(cout, ""));
	cout << "=";
	copy(right.begin(), right.end(), ostream_iterator<string>(cout, ""));
	cout << "#";
	cout << endl;
	*/
}

struct NewSet
{
	int strIndex;
	int charIndex;
	char newChar;
};

bool solve(string ori)
{
	int find = 0;
	int i = ori.find('=');
	int j = ori.find('#');
	string left = ori.substr(0, i);
	string right = ori.substr(i + 1, j - i - 1);
	vector<Node> leftVal = val(left);
	vector<Node> rightVal = val(right);

	Node leftTotal;
	leftTotal.add = true;
	leftTotal.number.push_back(0);
	for (vector<Node>::iterator iter = leftVal.begin(); iter != leftVal.end(); ++iter) 
	{
		my_add(leftTotal, *iter);
	}

	Node rightTotal;
	rightTotal.add = true;
	rightTotal.number.push_back(0);
	for (vector<Node>::iterator iter = rightVal.begin(); iter != rightVal.end(); ++iter) 
	{
		my_add(rightTotal, *iter);
	}
	
	map<Node, NewSet> leftmap, rightmap;

	for (vector<Node>::iterator iter = leftVal.begin(); iter != leftVal.end(); ++iter) {
		Node oldVal = *iter;
		for (int i = 0; i < iter->number.size(); i++) {
			for (int j = 0; j < 4; j++) {
				int newChar = self_trans[iter->number[i]][j];
				if (newChar == -1)
					break;
				int backup = iter->number[i];
				iter->number[i] = newChar;
				if (compare(leftTotal, *iter, oldVal, rightTotal)) 
				{
					output(leftVal, rightVal);
					find++;
					return true;
				}
				iter->number[i] = backup;
			}
			for (int j = 0; j < 4; ++j) {
				char newChar = add_trans[iter->number[i]][j];
				if (newChar == -1)
					break;
				int backup = iter->number[i];
				iter->number[i] = newChar;
				NewSet ns;
				ns.strIndex = iter - leftVal.begin();
				ns.charIndex = i;
				ns.newChar = newChar;
				Node n = *iter;
				my_minus(n, oldVal);
				//cout << "add: " << (n.add ? '+' : '-');
				//copy(n.number.rbegin(), n.number.rend(), ostream_iterator<int>(cout, ""));
				//cout << endl;
				leftmap[n] = ns;
				iter->number[i] = backup;
			}
		}
	}

	for (vector<Node>::iterator iter = rightVal.begin(); iter != rightVal.end(); ++iter) {
		Node oldVal = *iter;
		for (int i = 0; i < iter->number.size(); i++) {
			for (int j = 0; j < 4; j++) {
				int newChar = self_trans[iter->number[i]][j];
				if (newChar == -1)
					break;
				int backup = iter->number[i];
				iter->number[i] = newChar;
				if (compare(rightTotal, *iter, oldVal, leftTotal)) 
				{
					output(leftVal, rightVal);
					return true;
				}
				iter->number[i] = backup;
			}

			for (int j = 0; j < 4; ++j) {
				int newChar = add_trans[iter->number[i]][j];
				if (newChar == -1)
					break;
				int backup = iter->number[i];
				iter->number[i] = newChar;
				NewSet ns;
				ns.strIndex = iter - rightVal.begin();
				ns.charIndex = i;
				ns.newChar = newChar;
				Node n = *iter;
				my_minus(n, oldVal);
				rightmap[n] = ns;
				iter->number[i] = backup;
			}
		}
	}

	for (vector<Node>::iterator iter = leftVal.begin(); iter != leftVal.end(); ++iter) {
		Node oldVal = *iter;
		for (int i = 0; i < iter->number.size(); i++) {
			for (int j = 0; j < 4; ++j) {
				int newChar = minus_trans[iter->number[i]][j];
				if (newChar == -1)
					break;
				int backup = iter->number[i];
				iter->number[i] = newChar;	
				
				Node ln = leftTotal;
				my_minus(ln, oldVal);
				my_add(ln, *iter);
				{
					Node leftDesire = rightTotal;
					my_minus(leftDesire, ln);
					map<Node, NewSet>::iterator a = leftmap.find(leftDesire);
					if (a != leftmap.end()) {
						if (a->second.strIndex != iter - leftVal.begin() || a->second.charIndex != i) {
							leftVal[a->second.strIndex].number[a->second.charIndex] = a->second.newChar;
							output(leftVal, rightVal);
							return true;
						}	
					}
				}

				{
					my_minus(ln, rightTotal);
					map<Node, NewSet>::iterator a = rightmap.find(ln);
					if (a != rightmap.end()) {
						rightVal[a->second.strIndex].number[a->second.charIndex] = a->second.newChar;
						output(leftVal, rightVal);
						return true;
					}
				}
				
				iter->number[i] = backup;
			}
		}
	}
	
	for (vector<Node>::iterator iter = rightVal.begin(); iter != rightVal.end(); ++iter) {
		Node oldVal = *iter;
		for (int i = 0; i < iter->number.size(); i++) {
			for (int j = 0; j < 4; ++j) {
				int newChar = minus_trans[iter->number[i]][j];
				if (newChar == -1)
					break;
				int backup = iter->number[i];
				iter->number[i] = newChar;
				
				Node rn = rightTotal;
				//copy(rn.number.rbegin(), rn.number.rend(), ostream_iterator<int>(cout, ""));
				//cout << endl;
				my_minus(rn, oldVal);
				//copy(rn.number.rbegin(), rn.number.rend(), ostream_iterator<int>(cout, ""));
				//cout << endl;
				my_add(rn, *iter);
				//copy(rn.number.rbegin(), rn.number.rend(), ostream_iterator<int>(cout, ""));
				//cout << endl;

				{
					Node rightDesire = leftTotal;
					my_minus(rightDesire, rn);
					map<Node, NewSet>::iterator a = rightmap.find(rightDesire);
					if (a != rightmap.end()) {
						if (a->second.strIndex != iter - leftVal.begin() || a->second.charIndex != i) {
							rightVal[a->second.strIndex].number[a->second.charIndex] = a->second.newChar;
							output(leftVal, rightVal);
							return true;
						}
					}
				}

				{
				//copy(leftTotal.number.rbegin(), leftTotal.number.rend(), ostream_iterator<int>(cout, ""));
				//cout << endl;
					my_minus(rn, leftTotal);
				//cout << "query: " << (rn.add ? '+' : '-');
				//copy(rn.number.rbegin(), rn.number.rend(), ostream_iterator<int>(cout, ""));
				//cout << endl;
					map<Node, NewSet>::iterator a = leftmap.find(rn);
					if (a != leftmap.end()) {
						leftVal[a->second.strIndex].number[a->second.charIndex] = a->second.newChar;
						output(leftVal, rightVal);
						return true;
					}
				}
				
				iter->number[i] = backup;
			}
		}
	}

	return false;
}

int main()
{
	char buf[1001];
	for (;;) {
		cin.getline(buf, 1001);
		if (strlen(buf) == 0)
			break;
		if (solve(buf) == false)
			cout << "No" << endl;
	}
	return 0;
}

