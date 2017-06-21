// @JUDGE_ID:  17051CA  10171  C++
// @begin_of_source_code
/* Graph  SSSP */
#include<stdio.h>
#include<iostream>
#include<string>
#include<stdio.h>
#include<stl.h> 
#include<vector>
#include<slist>

/**
 * class: graph
 * �׷�: #include <slist>
 */
class graph {
 public:
  vector<vector<int> > m;
  vector<slist<int> > adj;
  vector<slist<int>::iterator> pos;
  
  /**
   * Constructor
   * @param the number of nodes
   */
  graph(){}
  graph(int n){ resize(n); }

  /** 
   * @param the number of node
   */ 
  void resize(int n){
    m.resize(n), adj.resize(n), pos.resize(n); 
    for(int i=0; i<n; i++){
      m[i].resize(n);
      fill(m[i].begin(), m[i].end(), INT_MAX);
      adj[i].clear();
    }
  }
  
  /**
   * @return the number of node
   */
  int size(){ return m.size(); }

  /**
   * insert e between i and j;
   * @param i, j, e(weight)
   * if it is non-weighted graph, e should be 1.
   * if it is undirected graph, Do insert(i, j, e) and insert(j, i, e).
   */
  void insert(int i, int j, int e){
    m[i][j] = e;
    adj[i].push_front(j);
  }
  
  /**
   * refer to weight.
   * usage: using g[i][j], edge weight can be refered.
   */
  vector<int> & operator[](int i){ return m[i]; }

  /**
   * refere to adjacency list of node i, and move one.
   */
  int next(int i){ 
    if(pos[i]==adj[i].end()) return -1;
    return *pos[i]++; 
  }
  
  /**
   * begin again of adjacency list reference of node i.
   */
  void reset(int i){ pos[i] = adj[i].begin(); }

  /**
   * begin again of adjacency list reference of all node.
   * Before use graph, it must be called !!!.
   */
  void reset(){ for(int i=0; i<size(); i++) reset(i); }

  /* less used methods */
  void erase(int i, int j){
    m[i][j] = 0;
    for(slist<int>::iterator it=adj[i].begin(); it!=adj[i].end(); it++){
      if(*it==j){
	adj[i].erase(it);
	break;
      }
    }
  }

  /** clear all nodes */
  void clear(){ m.clear(), adj.clear(), pos.clear(); }

  graph & operator=(const graph &g){
    m = g.m;
    adj = g.adj;
    pos.resize(m.size());
    for(int i=0; i<m.size(); i++)
      pos[i] = adj[i].begin();
  }
};

/**
 * Dijkstra
 * @param 
 *   pi:   previous node
 *         -1 --> source and not visited node
 *   cost: distance from source
 *          0 --> source
 *         INT_MAX --> not visited node
 */ 
void dijkstra(graph &g, vector<int> &pi, vector<int> &cost, int s){
  cost.resize(g.size(), INT_MAX);
  pi.resize(g.size(), -1);
  vector<int> visited(g.size(), 0);
  
  cost[s] = 0;
  g.reset();
  while(1){
    int min = INT_MAX;
    int x;
    for(int i=0; i<g.size(); i++){
      if(visited[i]==0 && min > cost[i] ){
	min = cost[i];
	x = i;
      }
    }

    if( min == INT_MAX ) break;

    visited[x] = 1;

    int v;
    while((v=g.next(x))!=-1){
      if( !visited[v] && cost[x] + g.m[x][v] < cost[v] ){ /* Ƚ��ϡ���*/
	cost[v] = cost[x] + g.m[x][v];
	pi[v] = x;
      }
    }

  }
}

graph gY, gM;
int n;
int sY, sM;

int read(){
  cin >> n;
  if(n==0) return 0;

  gY = graph(26);
  gM = graph(26);

  char c1, c2, c3, c4;
  int e;
  int a, b;
  for(int i=0; i<n; i++){
    cin >> c1 >> c2 >> c3 >> c4 >> e;
    a = c3 - 'A';
    b = c4 - 'A';
    if(c1=='Y'){
      gY.insert(a, b, e);
      if(c2=='B') gY.insert(b, a, e);
    }else if(c1=='M'){
      gM.insert(a, b, e);
      if(c2=='B') gM.insert(b, a, e);
    }
  }

  cin >> c1 >> c2;
  sY = c1 - 'A';
  sM = c2 - 'A';
  return 1;
}

void work(){
  vector<int> costY, costM;
  vector<int> piY, piM;
  dijkstra(gY, piY, costY, sY);
  dijkstra(gM, piM, costM, sM);


  int minV = INT_MAX;
  for(int i=0; i<26; i++){
    if(costY[i]!=INT_MAX && costM[i]!=INT_MAX){
      minV = min(minV, costY[i]+costM[i]);
    }
  }

  if(minV == INT_MAX) {
    cout << "You will never meet." << endl;
    return;
  }
  
  cout << minV;
  for(int i=0; i<26; i++){
    if(costY[i]+costM[i]==minV){
      char ch = i+'A';
      cout << " " << ch;
    }
  }
  cout << endl;
}

main(){
  while(read()){
    work();
  }
}
// @end_of_source_code
