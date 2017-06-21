#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
#define REP(i, a, b) for ( int i = a; i < b; i++ )
#define rep(i, n) REP(i, 0, n)
#define INFTY (1<<21)

int m, n, k, d, C[7], G[110][110], N, D[110][64];

int getID(string str){
    if ( str == "H" ) return 0;
    if ( str == "D" ) return N - 1;
    string num = str.substr(1, str.size()-1);
    if ( str[0] == 'C' ) return atoi(num.c_str());
    return atoi(num.c_str()) + m;
}

bool isC(int x){ return 1 <= x && x <= m; }

int bellman(){
    rep(i, N) rep(j, (1<<m)) D[i][j] = INFTY;
    D[0][0] = 0;
    rep(o, N*(1<<m)) rep(u, N) rep(v, N){
	if ( u == v || G[u][v] == INFTY ) continue;
	rep(b, (1<<m)){
	    if (isC(v) && (b&(1<<(v-1))) != 0 ) continue; 
	    if ( isC(v) ) D[v][b|(1<<(v-1))] = min(D[v][b|(1<<(v-1))], D[u][b] + G[u][v] - C[v]);
	    else D[v][b] = min(D[v][b], D[u][b] + G[u][v]);
	}
    }
    int minv = INFTY;
    rep(i, (1<<m)) minv = min(minv, D[N-1][i]);
    return minv;
}

int main(){
    string source, target;
    int cost;
    while(cin >> m >> n >> k >> d && m ){
	N = 2 + n + m;
	REP(i, 1, m+1) cin >> C[i];
	rep(i, N) rep(j, N) G[i][j] = INFTY;
	rep(i, d){
	    cin >> source >> target >> cost;
	    int s = getID(source);
	    int t = getID(target);
	    G[t][s] = G[s][t] = min(G[s][t], cost * k);
	}
	cout << bellman() << endl;
    }
    return 0;
}

/*

$B3HD%%0%i%U$K$*$$$F:GC;7PO)(B($B5wN%(B)$B$r5a$a$k%W%m%0%i%`$,:n@.$G$-$k$+$,Ld$o$l$F$$$^$9!#$?$@$7!"Ii$N%3%9%H$r4^$`$?$a%@%$%/%9%H%i$N%"%k%4%j%:%`$rE,MQ$9$k$3$H$O$G$-$^$;$s!#(B

$B$3$N2r@b$G$O%9%Z!<%9@aLs$N$?$a0J2<$N%^%/%m$rMQ$$$F$$$^$9!#(B
#define REP(i, a, b) for ( int i = a; i < b; i++ )
#define rep(i, n) REP(i, 0, n)

$B3HD%%0%i%U$K$*$$$F%Y%k%^%s%U%)!<%I$N%"%k%4%j%:%`$rE,MQ$7$^$9!#3F%1!<%-20$5$s$KN)$A4s$C$?$+$N>pJs$O(B5$B%S%C%HJ,$N@0?t$H$7$F4IM}$7$^$9!#(B




 */
