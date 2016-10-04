#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <cstdio>
#include <cmath>

#define INT_MIN (1<<31)
#define INT_MAX (~INT_MIN)
#define UNREACHABLE (INT_MAX>>2)
#define INF (1e300)
#define EPS (1e-9)
#define PI 3.1415926535897932384626

using namespace std;

ifstream fin("109_input.txt");
#define cin fin

struct point {
	double x, y; // only used if more precision is needed
	point() { x = y = 0.0; } // default constructor
	point(double _x, double _y) : x(_x), y(_y) {}

	bool operator==(const point & b) {
		return (this->x == b.x && this->y == b.y);
	}
}; // user-defined

struct vec {
	double x, y; // name: ¡®vec¡¯ is different from STL vector
	vec(double _x, double _y) : x(_x), y(_y) {}
};

vec toVec(point a, point b) { // convert 2 points to vector a->b
	return vec(b.x - a.x, b.y - a.y);
}

vec toVector(point a, point b) { // convert 2 points to vector a->b
	return toVec(a, b);
}

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }
double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }
double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

double dist(point p1, point p2) { // Euclidean distance
								  // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
	return hypot(p1.x - p2.x, p1.y - p2.y);
} // return double

// note: to accept collinear points, we have to change the ¡®> 0¡¯
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
	return cross(toVec(p, q), toVec(p, r)) > 0;
}

double angle(point a, point o, point b) { // returns angle aob in rad
	vec oa = toVector(o, a), ob = toVector(o, b);
	return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
	return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

// returns true if point p is in either convex/concave polygon P
bool inPolygon(point pt, const vector<point> &P) {
	if ((int)P.size() == 0) return false;
	double sum = 0; // assume the first vertex is equal to the last vertex
	for (int i = 0; i < (int)P.size() - 1; i++) {
		if (ccw(pt, P[i], P[i + 1]))
			sum += angle(P[i], pt, P[i + 1]); // left turn/ccw
		else sum -= angle(P[i], pt, P[i + 1]);
	} // right turn/cw
	return fabs(fabs(sum) - 2 * PI) < EPS;
}

point pivot(0, 0);
bool angleCmp(point a, point b) { // angle-sorting function
	if (collinear(pivot, a, b)) // special case
		return dist(pivot, a) < dist(pivot, b); // check which one is closer
	double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
	double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
	return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
} // compare two angles

vector<point> CH(vector<point> P) { // the content of P may be reshuffled
	int i, j, n = (int)P.size();
	if (n <= 3) {
		if (!(P[0] == P[n - 1])) P.push_back(P[0]); // safeguard from corner case
		return P;
	} // special case, the CH is P itself
	  // first, find P0 = point with lowest Y and if tie: rightmost X
	int P0 = 0;
	for (i = 1; i < n; i++)
		if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
			P0 = i;
	point temp = P[0]; P[0] = P[P0]; P[P0] = temp; // swap P[P0] with P[0]
												   // second, sort points by angle w.r.t. pivot P0
	pivot = P[0]; // use this global variable as reference
	sort(++P.begin(), P.end(), angleCmp); // we do not sort P[0]
										  // third, the ccw tests
	vector<point> S;
	S.push_back(P[n - 1]); S.push_back(P[0]); S.push_back(P[1]); // initial S
	i = 2; // then, we check the rest
	while (i < n) { // note: N must be >= 3 for this method to work
		j = (int)S.size() - 1;
		if (ccw(S[j - 1], S[j], P[i])) S.push_back(P[i++]); // left turn, accept
		else S.pop_back();
	} // or pop the top of S until we have a left turn
	return S;
} // return the result

  // returns the area, which is half the determinant
double area(const vector<point> &P) {
	double result = 0.0, x1, y1, x2, y2;
	for (int i = 0; i < (int)P.size() - 1; i++) {
		x1 = P[i].x; x2 = P[i + 1].x;
		y1 = P[i].y; y2 = P[i + 1].y;
		result += (x1 * y2 - x2 * y1);
	}
	return fabs(result) / 2.0;
}

int main() {
	int N;
	cin >> N;
	vector< vector<point> > kds;
	vector< bool > has_power;
	while (N != -1) {
		vector<point> tv(N, point(0,0));
		for (int i = 0; i < N; i++) {
			cin >> tv[i].x >> tv[i].y;
		}
		kds.push_back(CH(tv));
		has_power.push_back(true);
		cin >> N;
	}
	point p;
	while (cin >> p.x >> p.y) {
		for (int i = 0; i < kds.size(); i++)
			if (has_power[i] && inPolygon(p, kds[i])) {
				has_power[i] = false;
				break;
			}
	}
	double result = 0;
	for (int i = 0; i < kds.size(); i++)
		if (!has_power[i]) {
			result += area(kds[i]);
		}
	printf("%.2f\n", result);
}
