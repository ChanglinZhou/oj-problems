#include <iostream>
#include <cmath>
using namespace std;


struct Point
{
	double x, y, z;

/*	
	void normalize()
	{
		double l = len();
		if (l == 0)
		{
			*(int*)0 = 0;
		}
		x /= l;
		y /= l;
		z /= l;
	}
*/	
	double len()
	{
		return sqrt(x * x + y * y + z * z);
	}

};

Point operator -(const Point& lh, const Point& rh)
{
	Point p;
	p.x = lh.x - rh.x;
	p.y = lh.y - rh.y;
	p.z = lh.z - rh.z;
	return p;
}
/*
double dot(const Point& lh, const Point& rh)
{
	return lh.x * rh.x + lh.y * rh.y + lh.z * rh.z;
}
*/
float solve()
{
	Point p;
	cin >> p.x >> p.y >> p.z;
	Point end1, end2;
	cin >> end1.x >> end1.y >> end1.z >> end2.x >> end2.y >> end2.z;

	Point p1 = p - end1;
	Point p2 = p - end2;
	Point p3 = end1 - end2;
	double l1 = p1.len();
	double l2 = p2.len();
	double l3 = p3.len();

	
	if (l1 == 0 || l2 == 0)
		return 0;
	if (l3 == 0)
		return l1;
	if (l3 == l1 + l2)
		return 0;		
	double ll_1 = l1 * l1;
	double ll_2 = l2 * l2;
	double ll_3 = l3 * l3;
	
	if (ll_1 > ll_2 + ll_3)
		return l2;
	if (ll_2 > ll_1 + ll_3)
		return l1;
/*	
		{
			Point p1 = p - end1;
			p1.normalize();
			Point p2 = end2 - end1;
			p2.normalize();
			if (dot(p1, p2) < 0) {
				return l1;
			}
		}
	
		{
			Point p1 = p - end2;
			p1.normalize();
			Point p2 = end1 - end2;
			p2.normalize();
			if (dot(p1, p2) < 0) {
				return l2;
			}
		}
*/
	double s = (l1 + l2 + l3) / 2;
	double dist = sqrt(s * (s - l1) * (s - l2) * (s - l3)) * 2 / l3;
	
	return dist;
}

int main()
{
	int cnt;
	cin >> cnt;
	int c = 0;
	while (cnt--) {
		float ret = solve();
		printf("Case %d: %.2f\n", ++c, ret);
	}
}

 
