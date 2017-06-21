#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

#define NIL (-1)
#define INF INT_MAX

class Edge {

  int begin, end, weight;

public:

  Edge( int b = 0, int e = 0, int w = 0 ) {

    begin = b, end = e, weight = w;

  }

  int getBegin() {

    return begin;

  }

  int getEnd() {

    return end;

  }

  int getWeight() {

    return weight;

  }

  bool operator <( const Edge &re ) const {

    return (weight < re.weight);

  }

};

class Graph {

  vector<vector<Edge> > vertexes;

public:

  Graph( int size = 0 ) {

    vertexes.assign(size, vector<Edge>());

  }

  int vSize() {

    return vertexes.size();

  }

  vector<Edge> &operator []( int index ) {

    return vertexes[index];

  }

  void connect( int begin, int end, int weight ) {

    vertexes[begin].push_back(Edge(begin, end, weight));

  }

};

class Dijkstra {

  vector<int> estimate, parent;     // ��ûϩ�������ͤ����ĺ��

  queue<Edge> visiting;

  // ����ˡ(����ޤǤ�ȯ������Ƥ����ûϩ��current���̤뤳�Ȥǲ���
  // �Ǥ���ʤ��ûϩ�����ͤ����ĺ���򹹿�����)
  void relax( Edge &cur, Graph &G ) {

    int begin = cur.getBegin(), end = cur.getEnd();
    int weight = cur.getWeight();

    if ( estimate[begin]+weight < estimate[end] ) {
      visiting.push(Edge(end, end, 0));
      estimate[end] = estimate[begin]+weight, parent[end] = begin;
    }

  }

public:

  void search( int begin, Graph &G ) {

    estimate.assign(G.vSize(), INF);
    parent.assign(G.vSize(), NIL);

    visiting.push(Edge(begin, begin, 0));
    estimate[begin] = 0;
    while ( !visiting.empty() ) {
      Edge current = visiting.front();
      visiting.pop();
      for ( int i = 0; i < G[current.getEnd()].size(); i++ )
        relax(G[current.getEnd()][i], G);
    }

  }

  bool isPossibletoArrive( int destination ) {

    return (estimate[destination] != INF );

  }

  int getTime( int destination ) {

    assert(estimate[destination] != INF);

    return estimate[destination];

  }

  // destination �ޤǤκ�û��ϩ�����
  vector<int> getPath( int destination ) {

    assert(estimate[destination] != INF);

    // ��ϩ�ϵս�ǳ�Ǽ�����
    vector<int> path;

    for ( int i = destination; i != NIL; i = parent[i] )
      path.push_back(i);

    return path;

  }

};

class fireStation {

  int number, time;

public:

  fireStation( int n ) {

    number = n, time = 0;

  }

  void setTime( int t ) {

    time = t;

  }

  int getNum() {

    return number;

  }

  int getTime() {

    return time;

  }

  bool operator <( const fireStation &rf ) const {

    return (time < rf.time);

  }

};

class TFDNYtotheRescue {

  Graph G;

  Dijkstra D;

  int fireLocation;

  vector<vector<int> > paths;

  vector<fireStation> fireStations;

  void split( string &line ) {

    int digit;
    int cur = -1;

    line += ' ';

    for ( int i = 0; i < line.size(); i++ ) {
      if ( !isspace(line[i]) )
	continue;
      if ( cur+1 != i ) {
	digit = atoi(line.substr(cur+1, i-cur-1).c_str());
	fireStations.push_back(fireStation(digit));
      }
      cur = i;
    }

  }

public:

  void input() {

    int nIntersections, minutes;
    string line;

    cin >> nIntersections;

    G = Graph(nIntersections+1);
    paths.assign(nIntersections+1, vector<int>());
    for ( int i = 1; i < nIntersections+1; i++ ) {
      for ( int j = 1; j < nIntersections+1; j++ ) {
	cin >> minutes;
	if ( i != j && minutes != -1 )
	  // �л����줫��õ���Ǥ���褦�˵ո����Υ���դˤ���
	  G.connect(j, i, minutes);
      }
    }

    cin >> fireLocation;
    getline(cin, line);
    
    split(line);

  }

  void work() {

    // ����դ��ո����ʤΤǲл����줫���õ���������Ƥξ��ɽ𤫤��
    // ��û��ϩ���狼��
    D.search(fireLocation, G);

    for ( int i = 0; i < fireStations.size(); i++ ) {
      fireStations[i].setTime(D.getTime(fireStations[i].getNum()));
      paths[fireStations[i].getNum()] = D.getPath(fireStations[i].getNum());
    }

    sort(fireStations.begin(), fireStations.end());

  }

  void output() {

    cout << "Org\tDest\tTime\tPath" << endl;

    for ( int i = 0; i < fireStations.size(); i++ ) {
      cout << fireStations[i].getNum() << '\t' << fireLocation << '\t'
	   << fireStations[i].getTime() << '\t';
      for ( int j = 0; j < paths[fireStations[i].getNum()].size(); j++ ) {
	if ( j != 0 )
	  cout << '\t';
	cout << paths[fireStations[i].getNum()][j];
      }
      cout << endl;
    }

  }

  void clear() {

    fireStations.clear();

  }

};


int main()
{

  int nCases;
  TFDNYtotheRescue Tfr;

  cin >> nCases;
  for ( int i = 0; i < nCases; i++ ) {
    Tfr.input();
    Tfr.work();
    if ( i != 0 )
      cout << endl;
    Tfr.output();
    Tfr.clear();
  }

  return 0;

}
