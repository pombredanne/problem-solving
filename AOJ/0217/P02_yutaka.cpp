#include<iostream>
using namespace std;

int main(){
    int n, p, maxp, maxv, d1, d2;

    while( cin >> n && n ){
	maxv = -1;
	for ( int i = 0; i < n; i++ ){
	    cin >> p >> d1 >> d2;
	    if ( maxv < d1 + d2 ){
		maxp = p;
		maxv = d1 + d2;
	    }
	}
	cout << maxp << " " << maxv << endl;
    }

    return 0;
}

/*
n $B?M$N45<T$,$=$l$>$l(B d1i + d2i $B$@$1Jb$$$?$H$-$K!":G$bD9$$5wN%$rJb$$$?45<T$NHV9f(Bpi $B$r5a$a$kLdBj$G$9!#(B

$BM?$($i$l$?%j%9%H$K$D$$$F:GBgCM$r5a$a$k%W%m%0%i%`$r5-=R$G$-$k$+$,Ld$o$l$F$$$^$9!#(B

$B8=:_$N:GBg$N5wN%$r(B maxv, $B$=$N:GBg$N5wN%$rJb$$$?45<T$NHV9f$r(B maxp $B$H$7$^$9!#:G=i$K(B maxv $B$r(B -1 $B$K=i4|2=$7!"$=$l$>$l$N45<T$N>pJs(B p, d1, d2 $B$rFI$_9~$_!"(Bd1 + d2 $B$,(B maxv $B$h$j$bBg$-$1$l$P(B maxv $B$r(B d1 + d2 $B$K!"(Bmaxp $B$r(B p $B$KCV$-49$($^$9!#%G!<%?%;%C%H$K$D$$$FA4$F$N45<T$N>pJs$rD4$Y$?8e$N(B maxp $B5Z$S(B maxv $B$r=PNO$7$^$9!#(B 

*/
