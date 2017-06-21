#include<iostream>
#include<string>
#include<vector>
using namespace std;

bool judge(int x, string y){
    if ( x % 3 == 0 && x % 5 == 0 ) return y == "FizzBuzz";
    if ( x % 3 == 0 ) return y == "Fizz";
    if ( x % 5 == 0 ) return y == "Buzz";
    if ( !isdigit(y[0]) ) return false;
    return x == atoi(y.c_str());
}

int main(){
    int m, n;
    string num;
    while( cin >> m >> n && m ){
	vector<int> P;
	int cur = 0, w = -1;
	for ( int i = 1; i <= m; i++ ) P.push_back(i);

	for ( int i = 1; i <= n; i++ ){
	    cin >> num;
	    if ( w != -1 ) continue;
	    if ( judge(i, num) ) cur++;
	    else P.erase(P.begin() + cur);
	    cur = cur%P.size();
	    if ( P.size() == 1 ) w = P[0];
	}

	if ( w != -1 ) cout << w << endl;
	else {
	    for ( int i = 0; i < P.size(); i++ ) 
		cout << ((i)?" ":"") << P[i];
	    cout << endl;
	}
    }
    return 0;
}

/*
Fizz Buzz$B$N%7%_%e%l!<%7%g%s$r9T$&LdBj$G$9!#%W%l%$%d!<$NH/8@$,=gHV$KM?$($i$l$?$H$-$N!"ESCf7P2a$"$k$$$O:G8e$^$G;D$C$F$$$?%W%l%$%d!<$r=PNO$7$J$1$l$P$J$j$^$;$s!#(B

$B4JC1$J%7%_%e%l!<%7%g%s$r9T$&%W%m%0%i%`$,5-=R$G$-$k$+$,Ld$o$l$F$$$^$9!#(B

$B2DJQD9$NG[Ns$H$7$F07$($k(B vector<int> $B$r;H$C$F!";D$C$F$$$k%W%l%$%d!<$r4IM}$7%7%_%e%l!<%7%g%s$r9T$$$^$9!#$^$:!"H/8@$N=gHV(B x $B$HH/8@$5$l$?8@MU(B y $B$r0z?t$K$H$j!"H/8@$,@5Ez$+$I$&$+$rH=Dj$9$k4X?t(B judge() $B$rDj5A$7$^$9!#$3$N4X?t$G$OLdBj$KDj5A$5$l$?$h$&$K!"(B3$B$NG\?t$+$D(B5$B$NG\?tHVL\$G$OH/8@$,(B"FizzBuzz"$B$G$"$k$+!"(B3$B$NG\?tHVL\$G$OH/8@$,(B"Fizz"$B$G$"$k$+!"(B5$B$NG\?tHVL\$G$OH/8@$,(B"Buzz"$B$G$"$k$+!"$=$l0J30$G$O=gHV(B x $B$,(B y $B$KEy$7$$$+$I$&$+$rH=Dj$7$^$9!#(B

$B%7%_%e%l!<%7%g%sK\BN$G$O!"8=:_$NH/8@<T$r%+!<%=%k(B cur $B$G<($7!"#1$D$:$DH/8@(B num $B$rFI$_9~$_!"H/8@$,@5Ez$G$"$l$P(B cur $B$r#1$D?J$a!"$=$&$G$J$1$l$P(B cur $B$N0LCV$N%W%l%$%d!<$r:o=|$7$^$9!#%+!<%=%k$O;D$C$F$$$k%W%l%$%d!<$r=[4D$9$k$h$&$K(B cur = cur%P.size() $B$H$7!"ESCf$G%W%l%$%d!<$,0l?M$K$J$C$?>l9g$O!"FI$_9~$_=hM}$r=|$$$F%7%_%e%l!<%7%g%s=hM}$r=*N;$7$^$9!#(B

 */
