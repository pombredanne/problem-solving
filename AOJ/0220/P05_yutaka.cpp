#include<iostream>
#include<vector>
using namespace std;

void convert1(int x, vector<int> &v){
    if ( x == 0 ) return;
    convert1(x/2, v);
    v.push_back(x%2);
}

void convert2(double x, vector<int> &v){
    if ( x == 0 ) return;
    v.push_back(x >= 1.0);
    convert2((x >= 1.0) ? (x-1)*2 : x*2, v);
}

int main(){
    for( double x; cin >> x && x >= 0; ){
	int a = (int)x;    // $B@0?tIt(B
	double b = x - a;  // $B>.?tE@0J2<(B
	vector<int> A, B;

	convert1(a, A);
	convert2(b*2, B);

	while( A.size() < 8 ) A.insert(A.begin(), 0);
	while( B.size() < 4 ) B.push_back(0);

	if ( A.size() > 8 || B.size() > 4 ) cout << "NA" << endl;
	else {
	    for ( int i = 0; i < A.size(); i++ ) cout << A[i];
	    cout << ".";
	    for ( int i = 0; i < B.size(); i++ ) cout << B[i];
	    cout << endl;
	}
    }

    return 0;
}

/*
#include<iostream>
using namespace std;

void convert(int x, int p){
    if ( p == 12 ) return;
    convert(x/2, p+1);
    if ( p == 3 ) cout << ".";
    cout << x%2;
}

int main(){
    for ( double x; cin >> x && x >= 0; ){
	int shift = (int)(x*16);
	if ( x == shift/16.0 && shift < 4096 ){
	    convert(shift, 0);
	    cout << endl;
	} else {
	    cout << "NA" << endl;
	}
    }
    return 0;
}

*/

/*
$B#1#0?J?t$N<B?t$r#2?J?t$KJQ49$7=PNO$9$kLdBj$G$9!#@0?tIt$,#87e0JFb!">.?tIt$,#47e0JFb$K<}$^$i$J$$>l9g$O(B NA $B$H=PNO$7$J$1$l$P$J$j$^$;$s!#(B

$B<B?t(B($BIbF0>.?tE@?t(B)$B$N4p?tJQ49$r9T$&%W%m%0%i%`$,5-=R$G$-$k$+$,Ld$o$l$F$$$^$9!#(B


[$B2rK!#1(B]
$BM?$($i$l$?<B?t$r@0?t$K%7%U%H$7$F4p?tJQ49$r9T$$$^$9!#$^$:M?$($l$??t$K(B16$B$r3]$1#2?J?t$G(B4$B7eJ,%7%U%H$7$^$9!#%7%U%H$7$?CM$r(B16.0$B$G3d$C$?$b$N$,(B x $B$H0[$J$k!"$^$?$O%7%U%H$7$?CM$,(B 4096 $B0J>e(B($B#2?J?t$G(B13$B7e0J>e(B)$B$G$"$l$P!"@)8B7e?t$K<}$^$i$J$$$HH=CG$G$-$k$N$G(B NA $B$H=PNO$7$^$9!#7e?t$K<}$^$k>l9g$O4p?tJQ49$r9T$$E,@Z$J0LCV$K(B.$B$r4^$a7k2L=PNO$7$^$9!#(B

[$B2rK!#2(B]
$BM?$($i$l$?<B?t$r@0?tItJ,$H>.?tItJ,$KJ,$1$F4p?tJQ49$r9T$$$^$9!#>.?tItJ,$N4p?tJQ49$O!"$^$:>.?tIt$r#2G\$7$??t(B x $B$+$i;O$a!"(Bx$B$,(B1$B0J>e$N>l9g$O(B1$B$r(B1$B$h$j>.$5$$>l9g$O(B0$B$r%S%C%HNs$KDI2C$7!"(Bx$B$,(B1$B0J>e$N>l9g$O(B x $B$+$i(B1$B$r0z$$$F(B2$BG\$7$?CM!"(B1$B$h$j>.$5$$>l9g$O(B x $B$r(B2$BG\$7$?CM$r<!$N(B x $B$H$7$FJQ49=hM}$r7+$jJV$7$^$9!#(B

 */
