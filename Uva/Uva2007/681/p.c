// @JUDGE_ID:  17051CA  681  C++
// @begin_of_source_code
#include<stdio.h>
#include<iostream>
#include<string>
#include<stl.h>
#include<math.h>
#include<float.h>
#define INCLUDE_POINT
#define EPS FLT_EPSILON
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
  bool operator==(const point &p) const {
    return deq(x, p.x) && deq(y, p.y);
  }
};

/*
 * $BB?3Q7A%*%V%8%'%/%H(B
 */
class polygon {
 public:
  vector<point> v;
  point l, u;

  polygon(){}
  polygon(const polygon &p): v(p.v){}
  void push_back(const point &p){
    v.push_back(p);
  }
  void clear(){ v.clear(); }
  void resize(int n){ v.resize(n); }
  int size(){ return v.size(); }
  /* i >= -size()$B$G$"$k$3$H!#(B */
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
 * p1$B$H(Bp2$B$N5wN%!#(B
 */
double dist(const point &p1, const point &p2){
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

/*
 * $B@~J,(B(p, o)$B$H@~(B y=o.y $B$H$N!JH?;~7W2s$j$N!K3QEY!#(B
 * $BCm0U(B: $BJV$jCM$O(B [0, 2*M_PI)$B$G$"$k!#(B
 */
double angle(const point &p, point o=point(0, 0)){
  double a = atan2(p.y-o.y, p.x-o.x);
  
  if(dle(0, a)) return a;
  return 2*M_PI+a;
}

/*
 * $B@~J,(B(p1, o)$B$+$i@~J,(B(p2, o)$B$X$N!JH?;~7W2s$j$N!K3QEY!#(B
 * $BMW7o(B: $B4X?t(B angle(const point&, point)
 */
double angle(const point &p1, const point &p2, const point &o){
  double a = angle(p2, o)-angle(p1, o);
  
  if(dle(0, a)) return a;
  return 2*M_PI+a;
}

/*
 * p0p2$B$,(Bp0p1$B$N:8(B($BH?;~7W2s$j(B)$B$K$"$k$+$I$&$+!#(B
 * $BCm0U!'(B $BJV$jCM(B -1 $B$O(B p0, p1, p2$B$,0lD>@~>e$K$"$k$H$-!#(B
 */
int is_left(const point &p0, const point &p1, const point &p2){
  double tmp = (p2-p0)*(p1-p0);

  if(deq(tmp, 0)) return -1;

  //  retrun tmp < 0;
  //  return tmp>=0;
    return (tmp < 0) ? 0 : 1; /* 0 = unti cloclwise */
}

int is_left_turn(const point &p0, const point &p1, const point &p2){
  double tmp = (p2-p0)*(p1-p0);

  if(fabs(tmp)<EPS) return -1;
  return tmp<0;
}

class cmp_by_angle: binary_function<const point&, const point&, bool>{
 public:
  point o;

  cmp_by_angle(const point o=point(0, 0)): o(o){}
  bool operator()(const point &p1, const point &p2) const {
    double a = angle(p2, o)-angle(p1, o);

    if(fabs(a)<EPS){
      return dist(p1, o)<dist(p2, o);
    }
    return a>0;
  }
};

/**
 * create convex hull
 * Solved 218, 10135, 109
 */
void convex(polygon &s, polygon &t){
  vector<point> v(s.v);

  s.find_most();
  sort(v.begin(), v.end(), cmp_by_angle(s.l));
  
  t.clear();
  for(int i=0; i<2; i++) t.push_back(v[i]);
  for(int i=2; i<v.size(); i++){
    /*
    while(is_left(t[t.size()-2], t.v.back(), v[i])==0 && t.size()>1)
      t.v.pop_back();
    t.push_back(v[i]);
    */
     while ( true ) {
        const int top = t.size() - 1;
        const int nextTop = t.size() - 2;
        if ( nextTop < 0 )
          break;
        if ( is_left(t[nextTop], t[top], v[i]) == 0 )
          break;
        t.v.pop_back();
      }
      t.push_back(v[i]);

  }
  t.find_most();
}

int n;
polygon P, CVX;

void read(){
  cin >> n;
  P.clear(); CVX.clear();
  double x, y;
  for ( int i = 0; i < n; i++ ){
    cin >> x >> y;
    P.push_back( point( x, y ) );
  }
}

void work(){

  convex( P, CVX );
  
  cout << CVX.size()+1 << endl;

  for ( int i = 0; i < CVX.size(); i++ ){
    cout << CVX[i].x << " " << CVX[i].y << endl;
  }
  cout << CVX[0].x << " " << CVX[0].y << endl;

}

main(){
  int tcase, kasu;
  cin >> tcase; cout << tcase << endl;
  for ( int i = 0; i < tcase; i++ ){
    read();
    if ( i != tcase -1 ){
      cin >> kasu;
      assert( kasu == -1 );
    }
    work();
    if ( i != tcase -1 ) cout << -1 << endl;
  }
}

// @end_of_source_code


