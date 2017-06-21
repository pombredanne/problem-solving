#include<iostream>
#include<string>
using namespace std;
#define rep(i, n) for ( int i = 0; i < n; i++)

int n, in[26], out[26], G[26][26];
bool visited[26];

bool check(){
    rep(i, 26) if ( in[i] != out[i] ) return false;
    return true;
}

void dfs(int u){
    visited[u] = true;
    rep(v, 26) if ( !visited[v] && G[u][v] ) dfs(v);
}

int getNComponent(){
    int nc = 0;
    rep(i, 26){
	if ( in[i] == 0 && out[i] == 0 ) continue;
	if ( !visited[i] ){ nc++; dfs(i); }
    }
    return nc;
}

int main(){
    while( cin >> n && n ){
	rep(i, 26){
	    in[i] = out[i] = 0;
	    visited[i] = false;
	    rep(j, 26) G[i][j] = 0;
	}
	
	string str;
	rep(i, n){
	    cin >> str;
	    in[str[0]-'a']++;
	    out[str[str.size()-1]-'a']++;
	    G[str[0]-'a'][str[str.size()-1]-'a'] = 1;
	    G[str[str.size()-1]-'a'][str[0]-'a'] = 1;
	}
	
	cout << (( check() && getNComponent() == 1 )?"OK":"NG") << endl;
    }
    return 0;
}

/*
$BM?$($i$l$?C18l$rA4$F;HMQ$7!"=[4D$9$k$7$j$H$j$,9T$($k$+$I$&$+$rH=Dj$9$kLdBj$G$9!#(B

$B%0%i%U$N%*%$%i!<JDO)$NM-L5$rH=Dj$9$k%W%m%0%i%`$r:n@.$G$-$k$+$,Ld$o$l$F$$$^$9!#(B

$B$3$N2r@b$G$O%9%Z!<%9$N@aLs$N$?$a$K0J2<$N%^%/%m$rMxMQ$7$F$$$^$9!#(B
#define rep(i, n) for ( int i = 0; i < n; i++)

$B$^$:!"M?$($i$l$?C18l$G%0%i%U$r:n@.$7$^$9!#%0%i%U$O%"%k%U%!%Y%C%H$N?t$G$"$k(B26$B8D$N%N!<%I$r;}$A!"M?$($i$l$?3FC18l$K$D$$$F:G=i$NJ8;z$,;kE@!":G8e$NJ8;z$,=*E@$H$J$k$h$&$K%(%C%8$rDI2C$7$^$9!#M-8~$-%0%i%U$,%*%$%i!<JDO)$r;}$D>r7o$O!"$3$N%0%i%U$K$NA4$F$N%N!<%I$K$D$$$F!"F~NO%(%C%8$H=PNO%(%C%8$N?t$,Ey$7$$$3$H$G$9!#$?$@$7!"%0%i%U$,O"7k$GL5$$>l9g$b$9$Y$F$NC18l$G=[4D$7$j$H$j$r9T$&$3$H$bIT2DG=$K$J$k$N$GCm0U$,I,MW$G$9!#(B

 */
