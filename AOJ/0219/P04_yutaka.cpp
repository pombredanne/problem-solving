#include<iostream>
using namespace std;

int main(){
    int n, T[10], x;
    while( cin >> n && n ){
	for ( int i = 0; i < 10; i++ ) T[i] = 0;
	for ( int i = 0; i < n; i++ ){ cin >> x; T[x]++; }
	for ( int i = 0; i < 10; i++ ){
	    if (T[i] == 0 ) cout << "-" << endl;
	    else {
		for ( int j = 0; j < T[i]; j++ ) cout << "*";
		cout << endl;
	    }
	}
    }
    return 0;
}

/*
$BF~NO$H$7$FM?$($i$l$k?t;z$,$=$l$>$l2?2s8=$o$l$?$+?t$(!"7k2L$rK@%0%i%U$H$7$F2hLL>e$K=PNO$9$kLdBj$G$9!#(B

$BM?$($i$l$k?t;z$O(B0$B!A(B9$B$H>.$5$$?t$G$"$k$?$a!"4JC1$JG[Ns$NA`:n$r9T$&%W%m%0%i%`$,:n@.$G$-$k$+$,Ld$o$l$F$$$^$9!#(B

$B$=$l$>$l$N?t;z$r%+%&%s%H$9$k$?$a$N@0?t7?G[Ns(B T[10] $B$rMQ0U$7$^$9!#(BT[x] $B$K?t;z(B x $B$N=P8=2s?t$r5-O?$7$^$9!#(B
 */
