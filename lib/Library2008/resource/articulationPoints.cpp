// C++ @yutaka
// begin_of_library
#include<iostream>
#include<vector>
using namespace std;

class Graph{
    private:
    vector<vector<int> > adjList;
    vector<vector<int>::iterator> pos;

    public:
    static const int END = -1;
    Graph(){}
    Graph( int n ) { resize(n); }

    void resize( int n ){
	adjList.resize(n), pos.resize(n);
	for ( int i = 0; i < n; i++ ){
	    adjList[i].clear();
	}
    }
    
    int size(){ return adjList.size(); }

    void insert( int source, int target ){
	adjList[source].push_back( target );
    }
    
    int next( int source ){
	if ( pos[source] == adjList[source].end() ) return END;
	return *pos[source]++;
    }
    
    void reset( int i ){ pos[i] = adjList[i].begin(); }
    void reset(){ for ( int i = 0; i < size(); i++ ) reset(i); }
};
// end_of_library

// begin_of_source
#define SIZE 1000

Graph graph = Graph( SIZE ); // graph structure
bool visited[SIZE];

int prenum[SIZE]; int parent[SIZE]; int lowest[SIZE]; int timer;

void dfs( int current, int prev ){

    // �m�[�h current ��K�₵������̏���
    prenum[current] = timer; lowest[current] = timer;
    timer++;

    visited[current] = true;

    int next;

    while ( (next = graph.next( current )) != graph.END ){
        if ( !visited[next] ){
            // �m�[�h current ����m�[�h next �֖K�₷�钼�O�̏���
            parent[next] = current;

            dfs( next, current );

            // �m�[�h next �̒T�����I����������̏���
            lowest[current] = min( lowest[current], lowest[next] );
        } else if ( next != prev ){
            // �G�b�W current --> next �� Back-edge �̏ꍇ�̏���
            lowest[current] = min( lowest[current], prenum[next] );
        }
    }

    // �m�[�h current �̒T�����I����������̏���


}

void depthFirstSearchScheme(){
    for ( int i = 0; i < SIZE; i++ ) visited[ i ] = false;
    int root = 0;
    timer = 1;
      
    graph.reset();

    // lowest �̌v�Z
    dfs( root, -1 );
}

// end_of_source

void inputGraph(){

    int source, target;
    // input based on adjList
    cout << "input edges: ";
    while (1){
	cin >> source >> target;
	if ( source == -1 && target == -1 ) break;
	graph.insert( source, target );
	graph.insert( target, source );
    }
}

void output(){
    cout << endl;
    for ( int i = 0; i < SIZE; i++ ){
	cout << i << " ---> pre = " << prenum[i] << "  lowest = " << lowest[i] << endl;
    }
}

int main(){
    inputGraph();
    depthFirstSearchScheme();
    output();
    return 0;
}
