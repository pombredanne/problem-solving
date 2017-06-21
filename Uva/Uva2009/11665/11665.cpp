#include<iostream>
#include<cfloat>
#include<cassert>
#include<cmath>
#include<vector>
#include<string>
#include<sstream>

using namespace std;
#define rep(i, n) for ( int i = 0; i < n; i++ )
#define EPS (1e-10)
#define equals(a, b) (fabs((a) - (b)) < EPS )
#define dle(a, b) (equals(a, b) || a < b )
static const double PI = acos(-1);

class Point{
    public:
    double x, y;
    
    Point ( double x = 0, double y = 0): x(x), y(y){}
    
    Point operator + ( Point p ){ return Point(x + p.x, y + p.y); }
    Point operator - ( Point p ){ return Point(x - p.x, y - p.y); }
    Point operator * ( double a ){ return Point(x*a, y*a); }
    Point operator / ( double a ){ return Point(x/a, y/a); }

    double abs() { return sqrt(norm());}
    double norm() { return x*x + y*y; }

    bool operator < ( const Point &p ) const {
	return x != p.x ? x < p.x : y < p.y;
    }

    bool operator == ( const Point &p ) const {
	return fabs(x-p.x) < EPS && fabs(y-p.y) < EPS;
    }
};

typedef Point Vector;

class Segment{
    public:
    Point p1, p2;
    Segment(Point s = Point(), Point t = Point()): p1(s), p2(t){}
};

typedef Segment Line;

typedef vector<Point> Polygon;

double norm( Vector a ){ return a.x*a.x + a.y*a.y; }
double abs( Vector a ){ return sqrt(norm(a)); }
Point polar( double a, double r ){ return Point(cos(r)*a, sin(r)*a);}
double getDistance( Vector a, Vector b ){ return abs(a - b); }
double dot( Vector a, Vector b ){ return a.x*b.x + a.y*b.y; }
double cross( Vector a, Vector b ){ return a.x*b.y - a.y*b.x; }

bool isOnSegment( Point a, Point b, Point c){
    if ( a == c || b == c ) return true;
    return (abs(a-c) + abs(c-b) < abs(a-b) + EPS );
}

bool isOrthogonal( Vector a, Vector b ){
     return equals( dot(a, b), 0.0 );
}

bool isOrthogonal( Point a1, Point a2, Point b1, Point b2 ){
    return isOrthogonal( a1 - a2, b1 - b2 );
}

bool isOrthogonal( Segment s1, Segment s2 ){
    return equals( dot(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0 );
}

bool isParallel( Vector a, Vector b ){
    return equals( cross(a, b), 0.0 );
}

bool isParallel( Point a1, Point a2, Point b1, Point b2){
    return isParallel( a1 - a2, b1 - b2 );
}

bool isParallel( Segment s1, Segment s2 ){
    return equals( cross(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0 );
}

static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;

// EPS can be 0
// need to check for 920, 833, 866
int ccw( Point p0, Point p1, Point p2 ){
    Vector a = p1 - p0;
    Vector b = p2 - p0;
    if ( cross(a, b) > EPS ) return COUNTER_CLOCKWISE;
    if ( cross(a, b) < -EPS ) return CLOCKWISE;
    if ( dot(a, b) < -EPS ) return ONLINE_BACK;
    if ( norm(a) < norm(b) ) return ONLINE_FRONT;
    return ON_SEGMENT;
}

// intersect Segment p1-p2 and Segment p3-p4 ?
bool isIntersect(Point p1, Point p2, Point p3, Point p4){
    return ( ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 &&
	     ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0 );
}

// intersect Segment s1 and Segment s2 ?
// verified by 920, 833, 866, uoa2062
bool isIntersect(Segment s1, Segment s2){
    return isIntersect(s1.p1, s1.p2, s2.p1, s2.p2);
}

// verified by 920, 833, uoa2062
Point getCrossPoint(Segment s1, Segment s2){
    assert( isIntersect(s1, s2) );
    Vector base = s2.p2 - s2.p1;
    double d1 = abs(cross(base, s1.p1 - s2.p1));
    double d2 = abs(cross(base, s1.p2 - s2.p1));
    double t = d1/(d1 + d2);
    return s1.p1 + (s1.p2 - s1.p1)*t;
}

Point getCrossPointLines( Line s1, Line s2){
    Vector a = s1.p2 - s1.p1;
    Vector base = s2.p2 - s2.p1;
    return s1.p1 + a * cross(base, s2.p1 - s1.p1)/cross(base, a);
}

bool isContain( Polygon g, Point p ){
    
}

bool isOverlap( Polygon g1, Polygon g2 ){
    for ( int i = 0; i < g1.size(); i++ ){
	Segment s1 = Segment(P[i], P[(i+1)%g1.size()]);
	for ( int j = 0; j < g2.size()-1; j++ ){
	    Segment s2 = Segment(P[j], P[(j+1)%g2.size()]);
	    if ( isIntersect(s1, s2) ) return true;
	}
    }
    for ( int i = 0; i < g1.size(); i++ )
	if ( isContain(g2, g1[i]) ) return true;
    for ( int i = 0; i < g2.size(); i++ )
	if ( isContain(g1, g2[i]) ) return true;
    return false;
}

#define MAX 40

Polygon P[MAX];
bool G[MAX][MAX], visited[MAX];
int n, ncomponent;

void dfs(int u ){
    visited[u] = true;
    for ( int v = 0; v < n; v++ ){
	if ( visited[v] || !G[u][v] ) continue;
	dfs(v);
    }
}

void compute(){
    rep(i, n) rep(j, n) G[i][j] = false;
    for ( int i = 0; i < n-1; i++ ){
	for ( int j = i+1; j < n; j++ ){
	    if ( isOverlap(P[i], P[j])) G[i][j] = G[j][i] = true;
	}
    }
    ncomponent = 0;
    rep(i, n) visited[i] = false;
    rep(i, n){
	if ( !visited[i] ){
	    ncomponent++;
	    dfs(i);
	}
    }
}

int main(){
    string line;
    double x, y;
    while(1){
	getline(cin, line);
	n = atoi(line.c_str());
	if ( n == 0 ) break;
	for ( int i = 0; i < n; i++ ){
	    getline(cin, line);
	    stringstream sin(line);
	    Polygon pol;
	    while( sin >> x >> y ){
		pol.push_back(Point(x, y));
	    }
	}
	compute();
    }
}

