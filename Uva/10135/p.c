// @JUDGE_ID:  17051CA  10135  C++
// @begin_of_source_code
/* Geometory Convex Hull */
#include<stdio.h>
#include<iostream>
#include<string>
#include<stl.h>
#include<math.h>
#include<float.h>
#define INCLUDE_POINT
#define EPS DBL_EPSILON
#define M_PI 3.14159265358979323846
#define deq(a, b) (fabs(a-b) < EPS)
#define dlt(a, b) (!deq(a, b) && a<b)
#define dle(a, b) (deq(a, b) || a<b)

class point{
 public:
  double x, y;
  point(){}
  point(double x, double y): x(x), y(y){}
  point operator+(const point &p) const{ return point(x+p.x, y+p.y); }
  point operator-(const point &p) const{ return point(x-p.x, y-p.y); }
  point operator*(double a) const{ return point(a*x, a*y); }
  double operator*(const point &p) const{ return x*p.y - y*p.x; }
};

/*
 * ¿�ѷ����֥�������
 */
class polygon {
 public:
  vector<point> v;
  point l, u;

  polygon(){}
  polygon(const polygon &p): v(p.v){}
  void push_back(const point &p){
    v.push_back(p);
    find_most();
  }
  void clear(){ v.clear(); }
  void resize(int n){ v.resize(n); }
  int size(){ return v.size(); }
  /* i >= -size()�Ǥ��뤳�ȡ� */
  point &operator[](int i){ return v[(i+size())%size()]; }
  void find_most(){
    if(size()==0) return;

    u = l = v[0];
    for(int i=1; i<size(); i++){
      if(deq(v[i].y, l.y) && v[i].x<l.x || v[i].y<l.y)
	l = v[i];
      if(deq(v[i].y, u.y) && v[i].x<u.x || v[i].y>u.y)
	u = v[i];
    }
  }
};

/*
 * p1��p2�ε�Υ��
 */
double dist(const point &p1, const point &p2){
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

/*
 * ��ʬ(p, o)���� y=o.y �ȤΡ�ȿ���ײ��Ρ˳��١�
 * ���: �֤��ͤ� [0, 2*M_PI)�Ǥ��롣
 */
double angle(const point &p, point o=point(0, 0)){
  double a = atan2(p.y-o.y, p.x-o.x);
  
  if(dle(0, a)) return a;
  return 2*M_PI+a;
}

/*
 * ��ʬ(p1, o)������ʬ(p2, o)�ؤΡ�ȿ���ײ��Ρ˳��١�
 * �׷�: �ؿ� angle(const point&, point)
 */
double angle(const point &p1, const point &p2, const point &o){
  double a = angle(p2, o)-angle(p1, o);
  
  if(dle(0, a)) return a;
  return 2*M_PI+a;
}

/*
 * p0p2��p0p1�κ�(ȿ���ײ��)�ˤ��뤫�ɤ�����
 * ��ա� �֤��� -1 �� p0, p1, p2����ľ����ˤ���Ȥ���
 */
int is_left(const point &p0, const point &p1, const point &p2){
  double tmp = (p2-p0)*(p1-p0);

  if(deq(tmp, 0)) return -1;
  return tmp<0;
}

/*
 * ����o �����Ȥ�����ɸ�Ǥ�x������Ρ�ȿ���ײ��Ρ˳��٤���Ӥ��롣
 * �׷�: �ؿ� angle(const point&, point)��dist
 */
class cmp_by_angle: binary_function<int, int, bool> {
 public:
  point o;
  vector<point> *l;

  cmp_by_angle(vector<point> &v, const point o=point(0, 0)): l(&v), o(o){}
  bool operator()(int i, int j) const {
    vector<point> &v = *l;

    double a = angle(v[j], o)-angle(v[i], o);
    
    if(fabs(a)<EPS){
      return dist(v[i], o)<dist(v[j], o);
    }
    return a>0;
  }
};

/*
 * s �� ��¿�ѷ��ˤ��� t �˰ܤ���
 * �׷�: �ؿ� is_left�����饹 cmp_by_angle
 * ���: s ��Ʊ������ޤޤʤ���С��ɤ������ޤߡ��ɤ�ʽ���Ǥ�褤��
 *       �¹Ը�� t �ϡ�s ����κǤ��㤤������İʾ�ΤȤ��Ϥ�����κǤ⺸��
 *       ������ȿ���ײ����������äƤ��롣t �Τʤ��ǡ���ľ����ˣ���
 *       �ʾ���¤Фʤ���
 */
void convex(polygon &s, vector<int> &t){
  vector<int> v(s.size());
  
  s.find_most();
  iota(v.begin(), v.end(), 0);
  sort(v.begin(), v.end(), cmp_by_angle(s.v, s.l));

  t.clear();
  for(int i=0; i<3; i++) t.push_back(v[i]);
  for(int i=3; i<v.size(); i++){
    while(is_left(s[t[t.size()-2]], s[t.back()], s[v[i]])!=1 && t.size()>1)
      t.pop_back();
    t.push_back(v[i]);
  }
}

polygon pl;

int read(){
  pl = polygon();

  int k;
  double a, b;
  cin >> k;
  for(int i=0; i<k; i++){
    cin >> a >> b;
    pl.push_back(point(a, b));
  }

}

void work(){
  vector<int> cvx;
  convex(pl, cvx);
  
  int p1, p2;
  double sub = 1000000;
  double seg0, seg1, seg2;
  double silk = 0;
  double subDist = 0;
  double d = 0;
  pair<int, int> p;

  for(int i=0; i<cvx.size(); i++){
    p1 = i;
    p2 = i+1;
    if(i==cvx.size()-1) p2 = 0;
    
    seg0 = dist(pl[cvx[p1]], pl[cvx[p2]]);
    seg1 = dist(pl[cvx[p1]], point(0, 0));
    seg2 = dist(pl[cvx[p2]], point(0, 0));

    if(seg1+seg2-seg0 < sub){
      sub = seg1 + seg2 - seg0;
      p = pair<int, int>(p1, p2);
      silk = seg1 + seg2;
      subDist = seg0;
    }
    d += seg0;
  }

  d -= subDist;
  d += silk;

  printf("%.2lf\n", d + 2);
}

main(){
  int t;
  cin >> t;
  for(int i=0; i<t; i++){
    if(i) cout << endl;
    read();
    work();
  }
}
// @end_of_source_code




