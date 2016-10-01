#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <cstdio>
#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
#define INF (1e300)
#define eps (1e-9)
using namespace std;

ifstream fin("378_input.txt");
#define cin fin

struct Point
{
	Point() {

	}

	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}

	bool isSamePoint(Point p) {
		return (this->x == p.x && this->y == p.y);
	}

	bool isSameDir(Point d) {
		return (this->xProduct(d) == 0);
	}

	double xProduct(Point other) {
		return (this->x * other.y - this->y*other.x);
	}

	double x;
	double y;
};

typedef Point Direction;

struct Line
{
	Line(Point p1, Point p2) {
		this->p = p1;
		this->dir = Direction(p2.x - p1.x, p2.y - p1.y);
	}

	bool containsPoint(Point p) {
		Direction d = Direction(p.x - this->p.x, p.y - this->p.y);
		if (d.isSameDir(this->dir)) {
			return true;
		}
		return false;
	}

	Point intersectLine(Line other) {
		Point p1 = this->p;
		Point p2 = other.p;
		Direction v1 = this->dir;
		Direction v2 = other.dir;
		double a = v1.xProduct(p2);
		double b = p1.xProduct(v1);
		double c = v2.xProduct(v1);
		double t2 = (a + b) / c;
		return Point(p2.x + t2 * v2.x, p2.y + t2 * v2.y);
	}

	Point p;
	Direction dir;
};

int main()
{
	int N;
	cin >> N;
	cout << "INTERSECTING LINES OUTPUT" << endl;
	while (N--)
	{
		Point a1, a2, b1, b2;
		long long x, y;
		cin >> x >> y;
		a1 = Point(x, y);
		cin >> x >> y;
		a2 = Point(x, y);
		cin >> x >> y;
		b1 = Point(x, y);
		cin >> x >> y;
		b2 = Point(x, y);

		Line l1 = Line(a1, a2);
		Line l2 = Line(b1, b2);

		if (l1.containsPoint(b1) && l1.containsPoint(b2)) { // if same line
			cout << "LINE" << endl;
		}
		else if (l1.dir.isSameDir(l2.dir)) {
			cout << "NONE" << endl;
		}
		else {
			Point r = l1.intersectLine(l2);
			printf("POINT %.2f %.2f\n", r.x, r.y);
		}
	}
	cout << "END OF OUTPUT" << endl;
}
