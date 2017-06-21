#include<iostream>
#include<cstdio>
#include<cmath>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
static const double PI = acos(-1);
#define EPS 0.0000001
double getArea( double c, double A, double B ){
    return c*c*sin(A)*sin(B)/(2*sin(A+B));
}

bool eq( double a, double b ){
    return fabs(a-b)<EPS;
}

void compute(set<double> angle ){
    vector<double> v;
    for ( set<double>::iterator it = angle.begin(); it != angle.end(); it++ ){
	double x = *it;
	if ( v.size() == 0 ) v.push_back(x);
	else if ( fabs(v[v.size()-1]-x) > EPS ) v.push_back(x);
    }

    double r = 0.5/cos(30*PI/180);
    int n = v.size();
    double d = (v[1] - v[0])/2;
    double area = 2*getArea(r, d*PI/180, 30*PI/180);
    printf("%.16lf\n", area*n);
}

void insertP( set<double> &p, double a ){
    if ( a > 360.0 || eq(a, 360)) p.insert(a - 360.0);
    else p.insert(a);
}

main(){
    int n;
    while( cin >> n && n ){
	set<double> p;
	for ( int i = 0; i < 3; i++ ) p.insert(i*120.0);
	double cur = 0.0;
	for ( int t = 1; t < n; t++ ){
	    cur += 360.0/n;
	    for ( int i = 0; i < 3; i++ ) insertP(p, cur+i*120.0);
	}
	compute(p);
    }
}
