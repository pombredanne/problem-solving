#include<iostream>
#include<vector>
#include<algorithm>
#define MAX 10000
using namespace std;


class Graph{
public:
    int n;
    vector<int> adj[MAX];
    Graph(int n = 0):n(n){
	
    }
    void connect(int i, int j){ adj[i].push_back(j); }
    void transpose(){
	vector<int> nadj[MAX];
	for ( int i = 0; i < n; i++ ){
	    for ( int j = 0; j < adj[i].size(); j++ ){
		nadj[adj[i][j]].push_back(i);
	    }
	}
	for ( int i = 0; i < n; i++ ) adj[i] = nadj[i];
    }
};

Graph g;
int visited[MAX], finish[MAX], t, id[MAX];

vector<int> com;

void dfs(int u){
    visited[u] = t++;
    for ( int i = 0; i < g.adj[u].size(); i++ ){
	int v = g.adj[u][i];
	if ( visited[v] == -1 ) dfs(v);
    }
    finish[u] = t++;
}

void dfsT(int u){
    com.push_back(u);
    visited[u] = 1;
    for ( int i = 0; i < g.adj[u].size(); i++ ){
	int v = g.adj[u][i];
	if ( visited[v] == 0 ) dfsT(v);
    }
}

int compute(){
    int n, m, s, d;
    cin >> n >> m;
    g = Graph(n); 
    
    for ( int i = 0; i < m; i++ ){
	cin >> s >> d;
	s--; d--;// zero base
	g.connect(s, d);
    }

    for ( int i = 0; i < n; i++ ) visited[i] = finish[i] = -1;
    t = 0;
    for ( int i = 0; i < n; i++ ){
	if ( visited[i] == -1 ) dfs(i);
    }

    g.transpose();

    vector<pair<int, int> > order;
    for ( int i = 0; i < n; i++ ){
	order.push_back(make_pair(finish[i], i));
    }
    sort(order.begin(), order.end());

    for ( int i =  0; i < n; i++ ) visited[i] = 0;

    int ncom = 0;

    for ( int i = n-1; i >= 0; i-- ){
	int u = order[i].second;
	com.clear();
	if ( visited[u] == 0 ) {
	    dfsT(u);
	    for ( int c = 0; c < com.size(); c++ ){
		id[com[c]] = ncom;
	    }
	    ncom++;
	}
    }

    int cnt = 0;
    bool indeg[MAX];
    g.transpose();

    for ( int i = 0; i < ncom; i++ ) indeg[i] = false;
    for ( int u = 0; u < n; u++ ){
	for ( int i = 0; i < g.adj[u].size(); i++ ){
	    int v = g.adj[u][i];
	    if ( id[v] != id[u] ) indeg[id[v]] = true;
	}
    }
    /*
    cout << endl;
    for ( int i = 0; i < n; i++ ){
	cout << i+1 << " : " << id[i] << endl;
	}*/
	

    for ( int i = 0; i < ncom; i++ ) if (!indeg[i]) cnt++;

    return cnt;
}


main(){
    int tcase; cin >> tcase;
    for ( int t = 1; t <= tcase; t++ ){
	cout << "Case " << t << ": " << compute() << endl;
    }
}

  
