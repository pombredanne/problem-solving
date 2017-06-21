#include<iostream>
#include<queue>
#include<map>
using namespace std;
#define MAX 50
#define INFTY (1<<10)

class State{
    public:
    int ty, tx, ky, kx, t;
    State(int ty=0, int tx=0, int ky=0, int kx=0, int t=0):
	ty(ty), tx(tx), ky(ky), kx(kx), t(t){}

    bool operator < ( const State &s) const{
	if ( ty != s.ty ) return ty < s.ty;
	if ( tx != s.tx ) return tx < s.tx;
	if ( ky != s.ky ) return ky < s.ky;
	if ( kx != s.kx ) return kx < s.kx;
	return false;
    }
};

int H, W, G[MAX][MAX];

bool isBlock(int y, int x){
    if ( 0 > y || 0 > x || y >= H || x >= W ) return true;
    return G[y][x];
}

int bfs(int ty, int tx, int ky, int kx){
    queue<State> Q;
    map<State, bool> V;
    State start = State(ty, tx, ky, kx, 0);
    V[start] = true;
    Q.push(start);

    State u, v;
    const int dy[4] = {0, -1, 0, 1};
    const int dx[4] = {1, 0, -1, 0};
    int nty, ntx, nky, nkx;

    while(!Q.empty()){
	u = Q.front(); Q.pop();
	if ( u.tx == u.kx && u.ty == u.ky ) return u.t; 
	for ( int r = 0; r < 4; r++ ){
	    nty = u.ty + dy[r];
	    ntx = u.tx + dx[r];
	    nky = u.ky + dy[r]*(-1);
	    nkx = u.kx + dx[r]*(-1);
	    if ( isBlock(nty, ntx) ){ nty = u.ty; ntx = u.tx; }
	    if ( isBlock(nky, nkx) ){ nky = u.ky; nkx = u.kx; }
	    v = State(nty, ntx, nky, nkx);
	    if ( !V[v] ){
		v.t = u.t + 1;
		V[v] = true;
		Q.push(v);
	    }
	}
    }
    return INFTY;
}

int main(){
    int tx, ty, kx, ky;
    while( cin >> W >> H && W ) {
	cin >> tx >> ty >> kx >> ky;
        for ( int i = 0; i < H; i++ )
	    for ( int j = 0; j < W; j++ ) cin >> G[i][j];
	int t = bfs(ty-1, tx-1, ky-1, kx-1);
	if ( t == INFTY ) cout << "NA" << endl;
	else cout << t << endl;
    }
    return 0;
}

/*
$B%0%j%C%I>e$rAP;R$,??5U$K0\F0$9$k$H$-!"Fs?M$,=P2q$&$^$G$N:GC;$N;~4V$r5a$a$kLdBj$G$9!#JI$r4^$s$@%0%j%C%I$N>#L\$H!"Fs?M$N=i4|0LCV$,M?$($i$l$^$9!#(B

$B>uBVA+0\$K$h$kI}M%@hC5:w$r<BAu$9$k%W%m%0%i%`$,5-=R$G$-$k$+$I$&$+$,Ld$o$l$F$$$^$9!#(B

$B>uBV$rI=$9$?$a$K%/%i%9(B State $B$rDj5A$7$^$9!##1$D$N>uBV$OFs?M$N0LCV(B(ty, tx)$B5Z$S(B(ky, kx)$B$GI=$7$^$9!#$=$N>uBV$K0\$C$?;~4V$rJ];}$7$F$*$/$?$a$K(B t $B$b@k8@$7$^$9!##1EYK,Ld$7$?>uBV$r(B map $B$G4IM}$9$k$?$a!"(BState$B%/%i%9$K$OHf3S1i;;;R$rDj5A$9$kI,MW$,$"$j$^$9!#$3$3$G$O!"Fs?M$N0LCV4X78$G0[$J$k>uBV$NBg>.4X78$rDj5A$7$F$$$^$9!#$3$N>uBV6u4V$NCf$GI}M%@hC5:w$r9T$$:GC;$N;~4V$r5a$a$^$9!#(B
 */
