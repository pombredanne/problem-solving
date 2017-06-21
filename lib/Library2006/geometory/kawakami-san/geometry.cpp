#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <cassert>

using namespace std;

#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define M_PI_4 0.78539816339744830962

#define EPS DBL_EPSILON
#define deq(a, b) ( fabs((a)-(b)) < EPS )
#define dle(a, b) ( deq(a, b) || a < b )

// direction �᥽�å���
#define PARALLEL 0
#define CLOCKWISE (-1)
#define ANTI_CLOCKWISE 1

// intersect �᥽�å���
#define NOINTERSECT 0
#define ONPOINT 1
#define ONLINE 2

#define NIL (-1)

class Point {
public:

	double x, y;

	Point( double Xpos=0.0, double Ypos=0.0 ) {
		x = Xpos, y = Ypos;
	}

	bool operator == ( const Point &p ) const {
		return ( deq(x, p.x) && deq(y, p.y) );
	}

	bool operator < ( const Point &p ) const {
		if ( x < p.x ) return true;
		if ( x > p.x ) return false;
		return (y < p.y);
	}

	// �� p �Ȥε�Υ���֤�.
	double distance( const Point &p ) const {
		return sqrt((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y));
	}

	// ���� (0, 0) ����ε�Υ���֤�.
	double distance() const {
		return sqrt(x*x + y*y);
	}

	// �� o �����Ȥ������, X �������Ⱦ���ײ�������γ��٤��֤�.
	// 0 <= angle < 2pi
	double angle( const Point &o ) const {
		const double polar = atan2(y-o.y, x-o.x);

		// atan2 �η���ϰϤ� -pi ���� pi �ޤǤʤΤ�
		// ����� 0 �ʾ�, 2pi ̤���ޤǤ��ϰϤˤ����֤�.
		return (dle(0, polar))? polar : 2 * M_PI + polar;
	}

	// ������ (0, 0) �˼����� angle �᥽�åɤ�Ʊ��.
	double angle() const {
		const Point o = Point(0, 0);
		return angle(o);
	}

	// �� p �Ȥ���ʬ����, �� q �Ȥ���ʬ�ؤβ�ž�������֤�.
	// �������� p ���̤�ľ������� q ���ΤäƤ���
	// �� PARALLEL �Ȥʤ�. (���Ȥ�ȿ�������Ǥ�)
	int direction( const Point &p, const Point &q ) const {
		const double r = (p.x-x) * (q.y-y) - (q.x-x) * (p.y-y);

		if ( deq(r, 0) )
			return PARALLEL;
		else
			return (r > 0)? ANTI_CLOCKWISE : CLOCKWISE;
	}

	// �� p �Ȥ���ʬ��Ⱦ���ײ��ˤɤ������ž�����, �� q �Ȥ���ʬ��
	// �Ťʤ뤫�׻�����. 0 <= dangle < 2pi
	double dangle( const Point &p, const Point &q ) const {
		const double d = q.angle(*this) - p.angle(*this);
		return (d < 0)? d + 2 * M_PI : d;
	}

	// �� o �����Ȥ��� rad ����Ⱦ���ײ��˲�ž���������ѹ�����.
	void rotate( const Point &o, const double rad ) {
		const double dx = x - o.x, dy = y - o.y;
		x = dx*cos(rad) - dy*sin(rad) + o.x;
		y = dx*sin(rad) + dy*cos(rad) + o.y;
	}

	// ������ (0, 0) �˼����� rotate �᥽�åɤ�Ʊ��.
	void rotate( const double rad ) {
		Point o = Point(0, 0);
		rotate(o, rad);
	}

	// �� o �Ȥε�Υ�� magnitude �ܤ���褦�˰�ư����.
	void scale( const Point &o, const double magnitude ) {
		x = magnitude * (x - o.x) + o.x;
		y = magnitude * (y - o.y) + o.y;
	}

	// ������ (0, 0) �˼����� scale �᥽�åɤ�Ʊ��.
	void scale( const double magnitude ) {
		Point o = Point(0, 0);
		scale(o, magnitude);
	}

	// �� o �򼴤Ȥ������оΰ�ư����.
	void symmetry( const Point &o ) {
		x -= 2 * (x - o.x);
		y -= 2 * (y - o.y);
	}

	// 0 �˶ᤤ��ɸ�� 0 ����Ȥ�.
	void revise() {
		if ( deq(x, 0) ) x = 0;
		if ( deq(y, 0) ) y = 0;
	}

};


class Segment {
public:

	Point begin, end;

	Segment( Point p=Point(0, 0), Point q=Point(0, 0) ) {
		begin = p, end = q;
	}

	bool operator < ( const Segment &s ) const {
		if ( begin < s.begin ) return true;
		if ( begin == s.begin ) return (end < s.end);
		return false;
	}

	bool operator == ( const Segment &s ) const {
		return ( begin == s.begin && end == s.end );
	}

	// ��ʬĹ���֤�.
	double length() const {
		return begin.distance(end);
	}

	// ��ʬ�η������֤�. begin �����Ȥ��� end �� angle ��Ȥ�.
	double angle() const {
		return end.angle(begin);
	}

	// ������ʬ�����Ĺ�������¸�ߤ��뤫Ƚ�ꤹ��.
	bool inbox( const Point &p ) const {
		if ( min(begin.x, end.x) > p.x || max(begin.x, end.x) < p.x ) return false;
		if ( min(begin.y, end.y) > p.y || max(begin.y, end.y) < p.y ) return false;
		return true;
	}

	// ���������Ƚ�����ޤ���ʬ���¸�ߤ��뤫Ƚ�ꤹ��.
	bool contain( const Point &p ) const {
		return (inbox(p) && begin.direction(end, p) == PARALLEL);
	}

	// ��ʬ s �ȥ��󥹥��󥹼��Ȥ�ľ���ȸ��ʤ�������
	// �����˽Ťʤ뤫Ƚ�ꤹ��.
	bool overlap( const Segment &s ) const {
		if ( !deq(distance(s.begin), 0) ) return false;
		if ( !deq(distance(s.end), 0) ) return false;
		return true;
	}

	// �������齪�������Ǥκ�¦, ��ʬ�ο�ľ����������¸�ߤ��뤫Ƚ�ꤹ��.
	bool onleft( const Point &p ) const {
		if ( begin.dangle(end, p) > M_PI/2 ) return false;
		if ( end.dangle(p, begin) > M_PI/2 ) return false;
		return true;
	}

	// ��ʬ�ο�ľ����������¸�ߤ��뤫Ƚ�ꤹ��.
	bool above( const Point &p ) const {
		Point q = end, r = p;
		
		q.rotate(begin, -end.angle(begin));
		r.rotate(begin, -end.angle(begin));

		return ( r.x >= begin.x && r.x <= q.x );
	}

	// �����Ƚ�����򴹤���. (����������Ȥ��� 180 �ٲ�ž��Ʊ������)
	void flip() {
		swap(begin, end);
	}

	// ����������Ȥ�����ʬ�� rad ����Ⱦ���ײ��˲�ž����.
	// �����Τߤ��ѹ������.
	void rotate( const double rad ) {
		end.rotate(begin, rad);
	}

	// ������ p �ޤǰ�ư����. ������Ŭ�ڤ˰�ư�����.
	void move( const Point &p ) {
		end.x += p.x - begin.x;
		end.y += p.y - begin.y;
		begin = p;
	}

	// �����Ƚ����ε�Υ�� magnitude �ܤˤ���褦�˽������ѹ�����.
	void scale( const double magnitude ) {
		end.scale(begin, magnitude);
	}

	// �������齪�������Ǥκ�¦�� d ����ʿ�԰�ư����.
	// d ����ˤ��뤳�ȤǱ�¦��ʿ�԰�ư���뤳�Ȥ���ǽ. ���ϰ�ư�Ǥ��ʤ�.
	void translate( const double d ) {
		Point p = end;

		p.rotate(begin, M_PI/2);
		p.scale(begin, d / length());
		move(p);
	}

	// ����ľ�� (��ʬ��ޤ�ľ��) �ε�Υ.
	// ��ʬ�����ˤʤäƤ��ʤ�����. ���ˤʤäƤ������ abort ����.
	double distance( const Point &p ) const {
		Segment r = Segment(begin, end);

		// ��ʬ�����ˤʤäƤ������ abort ����.
		assert( !(begin == end) );

		// ��ʬ���Ф��ƿ�ľ���� p ������Ȥ�����ʬ����.
		r.rotate(M_PI_2);
		r.move(p);

		return intersection(r).distance(p);
	}

	// ������ʬ�κ�û��Υ.
	// ������ʬ�Τɤ��餫��¦�̤ˤ���ʤ��, ����ľ���ε�Υ.
	// �����Ǥʤ��ʤ��, ��ʬ��ξü������ε�Υ��û�����.
	double shortest( const Point &p ) const {
		if ( above(p) ) return distance(p);
		return min(begin.distance(p), end.distance(p));
	}

	// ��ʬ����ʬ�κ�û��Υ.
	// ���줾���ξü������, ��ʬ�ؤε�Υ����, �Ǥ�û�����
	// ����û��Υ�Ȥʤ�.
	double shortest( const Segment &s ) const {
		double result = shortest(s.begin);
		result = min(result, shortest(s.end));
		result = min(result, s.shortest(begin));
		result = min(result, s.shortest(end));
		return result;
	}

	// ��ʬ���������֤�.
	Point center() const {
		return Point((begin.x+end.x)/2, (begin.y+end.y)/2);
	}

	// ��ľ 2 ��ʬ�����֤�.  ��������ʬ�������ˤ��, ľ�򤹤�
	// ��ʬ�򤽤�Ȥߤʤ��Ƥ���.  �ä�Ĺ���ʤɤϼ�����, ����
	// ��ʬ��Ʊ���Ǥ��뤬, ���������ˤ������Ѥ򤷤ʤ�����.
	Segment bisector() const {
		Segment result = Segment(begin, end);

		result.move(center());
		result.rotate(M_PI_2);

		return result;
	}

	// ��������ʬ��˿�������Ȥ�. ������, ľ���Ȥ��Ƹ��ʤ��ƿ�����
	// ��Ȥ��Ƥ���Τ�, ɬ��������ʬ��Ȥϸ¤�ʤ�.
	Segment perpendicular( const Point &p ) const {
		Segment r = Segment(begin, end);

		assert( !(begin == end) );

		r.rotate(M_PI_2);
		r.move(p);
	
		return Segment(p, intersection(r));
	}

	// ���󥹥��󥹼��Ȥ�ľ���ȸ��ʤ��������� p �����о�
	// ��ư���������֤�.
	Point symmetry( const Point &p ) const {
		if ( contain(p) ) return p;

		Segment r = Segment(begin, end);

		r.rotate(M_PI_2);
		r.move(p);
		const Point q = intersection(r);

		Point result = p;
		result.rotate(q, M_PI);		

		return result;
	}

	// ��ʬ s �ȸ򺹤��Ƥ��뤫Ƚ�ꤹ��.
	int intersect( const Segment &s ) const {
		const int d1 = begin.direction(end, s.begin);
		const int d2 = begin.direction(end, s.end);
		const int d3 = s.begin.direction(s.end, begin);
		const int d4 = s.begin.direction(s.end, end);
		
		if ( d1 == PARALLEL && inbox(s.begin) ) return ONPOINT;
		if ( d2 == PARALLEL && inbox(s.end) ) return ONPOINT;
		if ( d3 == PARALLEL && s.inbox(begin) ) return ONPOINT;
		if ( d4 == PARALLEL && s.inbox(end) ) return ONPOINT;

		return ( d1 != d2 && d3 != d4 )? ONLINE : NOINTERSECT;
	}

	// ��ʬ s ��ʿ�Ԥ�Ƚ�ꤹ��.
	// �����׻����Ѥ���ʬ�줬 0 �ξ���ʿ��.
	// Computational Geometry in C
	bool parallel( const Segment &s ) const {
		double denom;

		// ʸ���Υ����ɤǤϼ���Ÿ�����Ƥ���. ���٤��ɤ��Τ�?
		denom = (end.x - begin.x) * (s.end.y - s.begin.y)
			- (end.y - begin.y) * (s.end.x - s.begin.x);
		return deq(denom, 0);
	}

	// ��ʬ s �Ȥθ������֤�.
	// ��ʬ s �ȸ���, ʿ�ԤǤʤ����Ȥ�Τ���Ƽ¹Ԥ��뤳��.
	// ���äƤ��ʤ������Ĺ����θ������֤���, �����
	// �ݾڤǤϤʤ��Τǳ�������ϻȤ��٤��ǤϤʤ�.
	// Computational Geometry in C
	Point intersection( const Segment &s ) const {
		double num, denom, r;
		
		num = (begin.y - s.begin.y) * (s.end.x - s.begin.x)
			- (begin.x - s.begin.x) * (s.end.y - s.begin.y);
		denom = (end.x - begin.x) * (s.end.y - s.begin.y)
			- (end.y - begin.y) * (s.end.x - s.begin.x);

		assert( ! deq(denom, 0) );
		r = num / denom;

		return Point(begin.x + r*(end.x - begin.x), begin.y + r*(end.y - begin.y));
	}

};


class Circle {
public:

	Point center;
	double radius;

	Circle( Point c=Point(0, 0), double r=0 ) {
		center = c, radius = r;
	}

	// �����������ޤޤʤ������¸�ߤ��뤫Ƚ�ꤹ��.
	bool inside( const Point &p ) const {
		return (center.distance(p) < radius);
	}

	// �����������¸�ߤ��뤫Ƚ�ꤹ��.
	bool onframe( const Point &p ) const {
		return deq(center.distance(p), radius);
	}

	// �߼�Ĺ.
	double perimeter() const {
		return M_PI * 2 * radius;
	}

	// �ߤ�����.
	double area() const {
		return M_PI * radius * radius;
	}

	// ��������ߤ��Ф��ư��������������֤�.
	// ������ߤ������˴ޤޤʤ�����.  �߼���ʤ�����ʤ�.
	// ����줿��ʬ�� 2*asin(radius / result.length()) ��ž���뤳�Ȥ�
	// ȿ���ײ��������������������.
	Segment tangent() const {
		Segment result;

		const Point o = Point(0, 0);
		assert( !inside(o) );

		result = Segment(o, center);
		result.rotate(-asin(radius / result.length()));
	
		return result;
	}

};


class Triangle {
public:

	Point a, b, c;

	Triangle( Point p=Point(0, 0), Point q=Point(0, 0), Point r=Point(0, 0) ) {
		a = p, b = q, c = r;
	}

	// �Ĥ֤�Ƥ��ʤ����ѷ����ɤ���Ƚ�ꤹ��.
	bool valid() const {
		// �Ĥ֤�Ƥ��ʤ��Ȥ� 3 ĺ������ľ����ˤʤ�Фʤ�����.
		return (a.direction(b, c) != PARALLEL);
	}

	// ���ѷ�������.
	double area() const {
		// ���Ѥ����Ѥ��Ƶ���.
		return fabs(((b.x-a.x) * (c.y-a.y) - (c.x-a.x) * (b.y-a.y)) / 2);
	}

	// �������ޤޤʤ����ѷ��������¸�ߤ��뤫Ƚ�ꤹ��.
	bool inside( const Point &p ) const {
		// �Ĥ֤줿���ѷ�����¦�Ϥʤ�.
		if ( !valid() ) return false;

		if ( a.direction(b, c) != a.direction(b, p) ) return false;
		if ( b.direction(c, a) != b.direction(c, p) ) return false;
		if ( c.direction(a, b) != c.direction(a, p) ) return false;
		return true;
	}

	// �����������¸�ߤ��뤫Ƚ�ꤹ��.
	bool onframe( const Point &p ) const {
		if ( Segment(a, b).contain(p) ) return true;
		if ( Segment(b, c).contain(p) ) return true;
		if ( Segment(c, a).contain(p) ) return true;
		return false;
	}

	// ���ܱߤ�Ⱦ�¤Τߤ�׻�.
	// ���Ѥ�����Ǥ���Ĥ֤�Ƥ��ʤ����ѷ��Ǥ��뤳��.
	double circumscribe() const {
		// �������� (a/sin(A) = 2R) �����Ѥ��Ƶ���.
		double bac = a.dangle(b, c);

		if ( bac > M_PI ) bac = 2*M_PI - bac;

		assert(sin(bac) != 0);
		return (b.distance(c) / sin(bac)) / 2;
	}

	// ���ܱߤ�Ⱦ�¤��濴��׻���, Circle �Υ��󥹥��󥹤�
	// ������������. ���Ѥ�����Ǥ���Ĥ֤�Ƥ��ʤ����ѷ��Ǥ��뤳��.
	Circle circumscribed() const {
		// ���ܱߤ��濴�� 2 �դο�ľ����ʬ���θ����Ȥ���Ϳ�����뤳�Ȥ����Ѥ���.
		Segment ab = Segment(a, b).bisector();
		Segment bc = Segment(b, c).bisector();

		assert( !ab.parallel(bc) );
		Point o = ab.intersection(bc);

		return Circle(o, o.distance(a));
	}

};


// �����ݻ�����Τ�, �դ��ݻ�����Τ�, ������ϸ��ꤹ�� (constant)
// �Τ��ʤɸ�Ƥ���뤳��.
//
// UNDER DEVELOPMENT!!
class Polygon {
public:

	// ĺ���ν����Ϳ����¿�ѷ����������.
	// ���������ϥ�ˡ����ˤ���. �����Ǥʤ�����դ����ˤ��ʤ��褦���ѹ�����
	// ɬ�פ�����.  ���Ѥʤɤ�����ʤ���, �⳰Ƚ�꤬Ư���ʤ��ʤ�.
	void build( vector<Point> &v ) {
		pts = v;

		// �դ�������������.  �դ���������������Ʊ�������뤿���,
		// ����夫���ɲä��뤳�Ȥ�ػߤ���.
		frame.clear();
		for ( int n = 1; n < pts.size(); n++ )
			frame.push_back(Segment(pts[n-1], pts[n]));
		frame.push_back(Segment(pts.back(), pts.front()));
	}

	const Point &operator [] ( int n ) const {
		return pts[n];
	}

	const int size() const {
		return pts.size();
	}

	// ¿�ѷ������Ѥ����. ���ײ��˳�Ǽ���Ƥ�Ⱦ���ײ��˳�Ǽ
	// ���Ƥ������ͤ���Τ����ѷ׻��˺��Ϥʤ�.  ɬ��������ͤˤʤ�.
	double area() const {
		double result = 0.0;

		for ( int n = 0; n < frame.size(); n++ )
			result += frame[n].begin.x * frame[n].end.y - frame[n].end.x * frame[n].begin.y;
		return fabs(result) / 2;
	}

	// ¿�ѷ������������Ƥ���������̤������եȤ���. ¿�ѷ���ʿ�԰�ư
	// �Ȥʤ�.
	void translate( double dx, double dy ) {
		for ( int n = 0; n < pts.size(); n++ )
			pts[n].x += dx, pts[n].y += dy;

		for ( int m = 0; m < frame.size(); m++ ) {
			frame[n].begin.x += dx, frame[n].begin.y += dy;
			frame[n].end.x += dx, frame[n].end.y += dy;
		}
	}

	// �������ޤޤʤ�¿�ѷ������ p ��¸�ߤ��뤫Ƚ�ꤹ��.
	// ĺ����ξ����θ����ʤ����Ȥ����. ������ޤߤ������ˤ�
	// onframe ��ʻ�Ѥ��뤳��.  inside �������Ǥ϶�����ˤ��뤫Ƚ�ꤷ��
	// ���Ѥ��Ƥ���.
	bool inside( const Point &p ) const {
		if ( onframe(p) ) return false;

		// ������ˤʤ����Ȥ��ݾڤ��줿.  ���������Ѥ��륢�르�ꥺ���
		// ��������¦�ޤ��ϳ�¦�ˤ������μ¤�Ƚ�ꤷ, ������ξ��
		// ��ۣ��ʷ�̤���Ϳ�����ʤ���ΤǤ���.  ������, �����Ǥ϶�����
		// �ˤϤʤ����ݾڤ��Ƥ���ΤǸ�̩�˷��ꤹ��.  ʸ����Ƚ�ꥢ�르�ꥺ��
		// ��ۣ�椵���ӽ��Ǥ��Ƥ��뤬Ĺ���Τ�, onframe �Ȥ��Ȥ߹�碌�Ǵ�ά��.
		// ���르�ꥺ��Υ����ǥ������� p ���̤� X ����ʿ�Ԥ�ľ���α�¦��
		// ¿�ѷ��ȸ򺹤�������Ƚ�ꤹ����.
		// Computational Geometry in C
		bool outside = true;

		for ( int n = 0; n < frame.size(); n++ ) {
			const Point &begin = frame[n].begin;
			const Point &end = frame[n].end;

			if ( !(begin.y > p.y && dle(end.y, p.y))
				&& !(end.y > p.y && dle(begin.y, p.y)) ) continue;

			if ( p.x < (end.x - begin.x) * (p.y - begin.y) / (end.y - begin.y) + begin.x )
				outside = !outside;
		}
		return !outside;
	}

	// ¿�ѷ��ζ�������� p ��¸�ߤ��뤫Ƚ�ꤹ��.
	bool onframe( const Point &p ) const {
		for ( int n = 0; n < frame.size(); n++ )
			if ( frame[n].contain(p) ) return true;
		return false;
	}

private:

	vector<Point> pts;
	vector<Segment> frame;

};


class AngleSortLess {
public:

	AngleSortLess( Point &o ) {
		base = o;
	}

	bool operator () ( const Point &p, const Point &q ) const {
		double pa = p.angle(base);
		double qa = q.angle(base);

		if ( pa < qa ) return true;
		if ( pa > qa ) return false;
		return ( p.distance(base) < q.distance(base) );
	}

private:

	Point base;

};


class ConvexHull {
public:

	void clear() {
		cvx.clear();
		pts.clear();
	}

	void push( Point &p ) {
		pts.push_back(p);
	}

	int size() {
		return cvx.size();
	}

	Point &operator [] ( int n ) {
		return cvx[n];
	}

	// Convex Hull ���르�ꥺ���¹Ԥ�, pts ����
	// �ȤĿ޷� cvx ����������. ɬ�פ��ʤ����
	// ��Ϣ�Υ����ɤ�����������ʤ�.
	void compute() {
		assert( pts.size() >= 3 );
		grahamScan();
	}

	// ���Ѥ�׻�����.
	double area() const {
		double result = 0.0;

		// �ȤĿ޷���������ޤ໰�ѷ���ʬ�䤷�Ʒ׻�����.
		for ( int i = 2; i < (int)cvx.size() - 1; i++ )
			result += fabs((cvx[i-1].x-cvx[0].x)*(cvx[i].y-cvx[0].y) - (cvx[i].x-cvx[0].x)*(cvx[i-1].y-cvx[0].y));
		return result / 2;
	}

	// �ȤĿ޷��δ�����Ū�ſ������.
	Point gravity() const {
		Point result = Point(0.0, 0.0);
		double denom = 0.0;

		for ( int i = 2; i < (int)cvx.size() - 1; i++ ) {
			const double s = Triangle(cvx[0], cvx[i-1], cvx[i]).area();
			result.x += s * (cvx[i-1].x + cvx[i].x - 2 * cvx[0].x) / 3;
			result.y += s * (cvx[i-1].y + cvx[i].y - 2 * cvx[0].y) / 3;
			denom += s;
		}
		
		result.x = result.x / denom + cvx[0].x;
		result.y = result.y / denom + cvx[0].y;
		return result;
	}

	// �����ޤ����¦�ˤ��뤫Ƚ�ꤹ��.
	bool inside( const Point &p ) const {
		// ���Ƥ��դ��Ф���Ⱦ���׼��������ޤ���ʿ�Ԥʤ���ɤ� (���ײ��ǤϤʤ����Ȥ�Ʊ��).
		// O(logn) �Υ��르�ꥺ��˲��ɤ���;�Ϥ����� (��ʬõ��).
		for ( int i = 1; i < cvx.size(); i++ )
			if ( cvx[i-1].direction(cvx[i], p) == CLOCKWISE ) return false;
		return true;
	}

	// ������Ĺ��׻�����.
	double perimeter() const {
		double result = 0.0;

		for ( int i = 1; i < cvx.size(); i++ )
			result += cvx[i].distance(cvx[i-1]);
		return result;
	}

private:

	vector<Point> pts, cvx;

	void grahamScan() {
		// ��ü�Ȥ��ƻ�����Ǹ���ɲä��Ƥ���.
		grahamSort();
		pts.push_back(pts[0]);

		// ����ϥ���������
		cvx.push_back(pts[0]);
		cvx.push_back(pts[1]);

		for ( int i = 2; i < pts.size(); i++ ) {
			// ���ξ��� 0 �������ȼ����ľ���˴ޤޤ������������Ȥ��Ǥ���.
			while ( cvx[cvx.size()-2].direction(cvx.back(), pts[i]) < 0 )
				cvx.pop_back();
			cvx.push_back(pts[i]);
		}
	}

	void grahamSort() {
		// Ʊ������ʤ�, Graham Scan �򳫻Ϥ����������Ƭ�ˤ���.
		sort(pts.begin(), pts.end(), grahamLess);
		pts.erase(unique(pts.begin(), pts.end()), pts.end());

		sort(pts.begin(), pts.end(), AngleSortLess(pts.front()));
	}

	static bool grahamLess( const Point &p, const Point &q ) {
		if ( p.y < q.y ) return true;
		if ( p.y > q.y ) return false;
		return ( p.x < q.x );
	}

};


class SmallestEnclosingDisc {
public:

	void compute( vector<Point> &pts ) {
		assert(pts.size() >= 2);

		if ( pts.size() == 2 )
			smallest = Circle(Segment(pts[0], pts[1]).center(), pts[0].distance(pts[1]) / 2);
		else
			smallest = computeMiniDisc(pts);
	}

	Circle getSmallestDisc() const {
		return smallest;
	}

private:

	Circle smallest;

	Circle computeMiniDisc( vector<Point> pts ) {
		// random_shuffle �򥵥ݡ��Ȥ��Ƥ��ʤ��Ķ�����դ���. (online ��̤�б�)
		// �äˤ����¹Ԥ��ʤ��Ƥ��Ψ�����꤬����������Ǽ¹Ԥϲ�ǽ.
		random_shuffle(pts.begin(), pts.end());

		Circle D = Circle(Segment(pts[0], pts[1]).center(), pts[0].distance(pts[1]) / 2);
		for ( int n = 2; n < pts.size(); n++ )
			if ( !(D.inside(pts[n]) || D.onframe(pts[n])) )
				D = computeMiniDisc2(pts, n, pts[n]);
		return D;
	}

	Circle computeMiniDisc2( vector<Point> &pts, int npoint, Point &p ) {
		// random_shuffle �򥵥ݡ��Ȥ��Ƥ��ʤ��Ķ�����դ���. (online ��̤�б�)
		random_shuffle(pts.begin(), pts.begin()+npoint);

		Circle D = Circle(Segment(pts[0], p).center(), pts[0].distance(p) / 2);
		for ( int n = 1; n < npoint; n++ )
			if ( !(D.inside(pts[n]) || D.onframe(pts[n])) )
				D = computeMiniDisc3(pts, n, p, pts[n]);
		return D;
	}

	Circle computeMiniDisc3( vector<Point> &pts, int npoint, Point &p, Point &q ) {
		Circle D = Circle(Segment(p, q).center(), p.distance(q) / 2);
		for ( int n = 0; n < npoint; n++ )
			if ( !(D.inside(pts[n]) || D.onframe(pts[n])) )
				D = Triangle(p, q, pts[n]).circumscribed();
		return D;
	}

};

int main() {
	Circle C = Circle(Point(5, 5), 1);
	Segment tangent = C.tangent();
	Point house = Point(12, 12);

	cout << tangent.distance(house) << endl;

	return 0;
}
