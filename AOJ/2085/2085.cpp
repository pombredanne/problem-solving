#include<iostream>
#include<string>
#include<map>
#include<queue>
#include<vector>
#include<cassert>
using namespace std;
#define rep(i, n) for ( int i = 0; i < n; i++ )
#define MAX 1000
#define INFTY (1<<25)

class Point{
    public:
    int x, y, adj[4];
    Point(int x = 0, int y = 0):x(x), y(y){ rep(d, 4) adj[d] = -1; }
};

class State{
    public:
    int pos, dir, dist, turn;
    State(int pos=0, int dir=0, int dist=0, int turn=0):pos(pos), dir(dir), dist(dist), turn(turn){}
    bool operator < ( const State &s ) const {
	if ( dist == s.dist ) return turn > s.turn;
	return dist > s.dist;
    }
};

int getDistance(int i, int j, Point P[MAX]){
    return max(P[i].x, P[j].x ) - min(P[i].x, P[j].x) +
	max(P[i].y, P[j].y ) - min(P[i].y, P[j].y);
}

int dijkstra(int n, int source, int target, Point P[MAX]){
    priority_queue<State> PQ;
    int D[MAX][4], T[MAX][4];

    rep(i, n) rep(j, 4) { D[i][j] = T[i][j] = INFTY; }
    
    rep(d, 4){
	PQ.push(State(source, d, 0, 1));
	D[source][d] = 0;
	T[source][d] = 1;
    }

    State u, v;

    while( !PQ.empty() ){
	u = PQ.top(); PQ.pop();
	int pos = u.pos;
	int dir = u.dir;
	if ( pos == target ) return T[pos][dir];
	for ( int d = 0; d < 4; d++ ){
	    if ( P[pos].adj[d] == -1 ) continue;
	    if ( !( d == dir || d == (dir+1)%4 ) ) continue;
	    v = State( P[pos].adj[d], d, 0, 0 );
	    
	    int cost = getDistance(pos, P[pos].adj[d], P);
	    if ( (D[pos][dir] + cost ==  D[v.pos][v.dir] && T[pos][dir] + 1 < T[v.pos][v.dir]) ||
		 D[pos][dir] + cost <  D[v.pos][v.dir]){
		v.dist = D[v.pos][v.dir] = D[pos][dir] + cost;
		v.turn = T[v.pos][v.dir] = T[pos][dir] + 1;
		PQ.push(v);
	    }
	}
    }
    return -1;
}

int getDirection(int s, int t, Point P[MAX]){
    if ( P[s].x < P[t].x ) return 0;
    else if ( P[s].x > P[t].x ) return 2;
    else if ( P[s].y < P[t].y ) return 1;
    else if ( P[s].y > P[t].y ) return 3;
}

main(){
    int m, n, x, y, s, t;
    string name, p, q;
    Point P[MAX];

    while( cin >> m >> n && m && n ){
	map<string, int> M;
	for ( int i = 0; i < m; i++ ){
	    cin >> name >> x >> y;
	    P[i] = Point(x, y);
	    M[name] = i;
	}
	for ( int i = 0; i < n; i++ ){
	    cin >> p >> q; s = M[p]; t = M[q];
	    P[s].adj[getDirection(s, t, P)] = t;
	    P[t].adj[getDirection(t, s, P)] = s;
	}
	cin >> p >> q;
	int cost = dijkstra(m, M[p], M[q], P);
	if ( cost == -1 ) cout << "impossible" << endl;
	else cout << cost << endl;
    }
}
