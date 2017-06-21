#include<iostream>
using namespace std;
#define MAX 100
#define INFTY (1<<21)

int n, G[MAX][MAX];

int prim(){
    bool visited[MAX];
    int cost[MAX];
    int p[MAX];

    for ( int i = 0; i < n; i++ ){
	visited[i] = false;
	cost[i] = INFTY;
	p[i] = -1;
    }

    cost[0] = 0;

    int minv, u;

    while(1){
	// cost ���Ǿ��ΥΡ��� u ��õ��
	minv = INFTY;
	for ( int i = 0; i < n; i++ ){
	    if ( !visited[i] && cost[i] < minv ){
		minv = cost[i];
		u = i;
	    }
	}
	
	if ( minv == INFTY ) break;

	// u �� MST ���ɲ�
	visited[u] = true;

	// u �����ܤ���Ρ��� v �� cost �򹹿�����
	for ( int v = 0; v < n; v++ ){
	    if ( visited[v] ) continue;
	    if ( G[u][v] < cost[v] ){
		cost[v] = G[u][v];
		p[v] = u; // MST�ˤ����� v �οƤ� u �Ȥʤ�
	    }
	}
    }

    // MST �Υ��å��νŤߤ����¤�׻�
    int ans = 0;
    for ( int i = 0; i < n; i++ ){
	if ( p[i] == -1 ) continue;
	ans += G[i][p[i]];
    }

    return ans;
}

main(){
    char ch;
    int s, t, d, m;
    while(1){
	cin >> n;
	if ( n == 0 ) break;
	cin >> m;
	for ( int i = 0; i < n; i++ ){
	    for ( int j = 0; j < n; j++ ){
		G[i][j] = INFTY;
	    }
	}

	for ( int i = 0; i < m; i++ ){
	    cin >> s >> ch >> t >> ch >> d;
	    G[s][t] = G[t][s] = d/100 - 1;
	}
	cout << prim() << endl;
    }
}
