#include<iostream>
using namespace std;
#define N 10000000

bool P[N + 1];

void eratos(){
    for ( int i = 0; i <= N; i++ ) P[i] = true;
    P[0] = P[1] = false;
    for ( int i = 2; i*i <= N; i++ )
	if ( P[i] )
	    for ( int j = 2; i*j <= N; j++ ) P[i*j] = false;
}

int getQuads(int n){
    for ( int i = n; i >= 13; i--)
	if ( P[i] && P[i-2] && P[i-6] && P[i-8] ) return i;
}

main(){
    eratos();
    int n;
    while( cin >> n && n ) cout << getQuads(n) << endl;
}

/*
$BBg$-$5$,(Bn$B0J2<$K$J$k$h$&$J;M$D;RAG?t$N$&$A!":GBg$H$J$k$b$N$NBg$-$5$r5a$a$kLdBj$G$9!#(B

$BAG?tI=$r:n@.$7!"9bB.$JAG?tH=Dj$r9T$&%W%m%0%i%`$,:n@.$G$-$k$+$,Ld$o$l$F$$$^$9!#(B

$B$^$:%(%i%H%9%F%M%9$NdA$K$h$C$FF~NOCM$N:GBgCM$G$"$k(B10,000,000$B0J2<$N?t$K$D$$$F$NAG?tI=$r:n@.$7$^$9!#$3$NAG?tI=$r;H$$;M$D;RAG?t$N0LCV$r$r(B n $B$+$i;O$a$k@~7AC5:w$K$h$C$FC5$7=P$7$^$9!#(B
 */
