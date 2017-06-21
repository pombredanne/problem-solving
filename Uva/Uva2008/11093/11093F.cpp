#include<stdio.h>
#include<algorithm>
using namespace std;

#define MAX 100001

int n, C[MAX], P[MAX], T[MAX], T2[MAX]; 

int pre(int p ){
    if ( p == 0 ) return n-1;
    else return p-1;
}

void readNum(int &x){
    x = 0;
    char ch;
    while(1){
	ch = getchar();
	if ( ch == ' ' || ch == '\n' ) break;
	x *= 10; x += (ch - '0');
    }
}

int compute(){
    int x;
    //    scanf("%d", &n);
    readNum(n);
    for ( int i = 0; i < n; i++ ) readNum(C[i]);
    for ( int i = 0; i < n; i++ ) {
	readNum(P[i]);
	T[i] = INT_MIN;
    }
    
    int len = 0;
    int pos = 0;
    T2[0] = C[0];
    int v, p;
    while(1){
	pos++;
	if ( pos == n ) pos = 0;
	p = pre(pos);
	v = T2[p] - P[p];
	if ( T[pos] >= v ) break;
	T[pos] = v;
	if ( v < 0 ){
	    T[pos] = v;
	    T2[pos] = C[pos];
	    len = 0;
	} else {
	    T2[pos] = T[pos] + C[pos];
	    len++;
	}

	if ( len == n ) return pos;
    }

    return -1;
	
}

int main(){
    int tcase; scanf("%d", &tcase);
    getchar();
    for ( int i = 1; i <= tcase; i++ ){
	printf("Case %d: ", i);
	int index = compute();
	if ( index == -1 ) printf("Not possible\n");
	else printf("Possible from station %d\n", index+1);
    }
    return 0;
}