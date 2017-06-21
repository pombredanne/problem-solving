#include<iostream>
#include<map>
#include<set>
#include<queue>
#include<cassert>
#define MAX_SIZE 10
#define MAX_ROCK 105
#define LIMIT 20

using namespace std;

class Point{
    public:
    int x, y;
    Point(){}
    Point( int x, int y ): x(x), y(y){}
    
    int getDist( const Point &p ){
	return max(x, p.x)-min(x, p.x) + max(y, p.y)-min(y, p.y);
    }

    bool isAdj( const Point &p ){
	int dx = max( x, p.x ) - min( x, p.x );
	int dy = max( y, p.y ) - min( y, p.y );
	if ( dx == 1 && dy == 0 || dx == 0 && dy == 1 ) return true;
	if ( dx == 1 && dy == 1 && ( x - p.x ) != (y - p.y ) ) return true;
	return false;
    }

    bool operator == ( const Point &p ) const{
	return (x == p.x && y == p.y);
    }

    bool operator < ( const Point &p ) const {
	if ( x == p.x ) return y < p.y;
	else return x < p.x;
    }
};

class Snake{
    public:
    int size, cost;
    Point bodies[MAX_SIZE];

    Snake(){}
    Snake( int size ): size( size ){}

    void print(){
	cout << "snake" << endl;
	for  ( int i = 0; i < size; i++ ){
	    cout << bodies[i].x << "," << bodies[i].y << endl;
	}
    }
    
    bool operator < ( const Snake &s ) const{
	for ( int i = 0; i < size; i++ ){
	    if ( bodies[i] == s.bodies[i] ) continue;
	    return (bodies[i] < s.bodies[i]);
	}
	return false;
    }
};

int nBody, nRock;
Snake initial;
Point rocks[MAX_ROCK], goal;

bool onRock( Point target ){
    for ( int i = 0; i < nRock; i++ ){
	if ( rocks[i] == target ) return true;
    }
    return false;
}

void tryMove( int pos, Snake current, set<Snake> &nexts, bool moved ){
    //    current.print();
    nexts.insert( current );

    if ( pos == nBody ) return;

    Snake next;

    // do not move
    tryMove ( pos + 1, current, nexts, false );

    if ( moved ) return;
    // move
    static const int dx[6] = {1, 0, -1, -1, 0, 1};
    static const int dy[6] = {-1, -1, 0, 1, 1, 0};
    for ( int r = 0; r < 6; r++ ){
	Point target = current.bodies[pos];
	target.x += dx[r];
	target.y += dy[r];
	
	if ( onRock( target ) ) continue;

	vector<int> adjList;
	for ( int j = 0; j < current.size; j++ ){
	    if ( j != pos && target.isAdj( current.bodies[j] )) adjList.push_back(j);
	}

	int valid = false;
	if ( pos == 0 ){
	    if ( adjList.size() == 1 && adjList[0] == 1 ) valid = true;
	} else if ( pos == nBody - 1 ){
	    if ( adjList.size() == 1 && adjList[0] == nBody-2 ) valid = true;
	} else {
	    if ( adjList.size() ==2 &&
		 ( adjList[0] == pos - 1 && adjList[1] == pos + 1 ||
		   adjList[0] == pos + 1 && adjList[1] == pos - 1 ) ) valid = true;
	}

	if ( valid ){
	    next = current;
	    next.bodies[pos] = target;
	    tryMove( pos + 1, next, nexts, true );
	}
    }
}

int bfs(){
    queue<Snake> Q;
    map<Snake, int> D;
    
    Q.push( initial );
    D[initial] = 0;
    
    while ( !Q.empty() ){
	Snake current = Q.front(); Q.pop();
	int cost = D[current];

	if ( current.bodies[0] == goal ) return cost;

	set<Snake> nexts;
	tryMove( 0, current, nexts, false );
	//	cout << "size = " << nexts.size() << endl;
	for ( set<Snake>::iterator it = nexts.begin(); it != nexts.end(); it++ ){
	    if ( D.count(*it) == 0 && current.bodies[0].getDist(goal) + cost <= LIMIT ){
		D[*it] = cost + 1;
		Q.push(*it);
	    }
	}
    }
    return -1;
    assert( false );
}

void compute(){
    cout << bfs() << endl;
}

bool input(){
    cin >> nBody;
    if ( nBody == 0 ) return false;

    initial = Snake( nBody );

    for ( int i = 0; i < nBody; i++ ){
	cin >> initial.bodies[i].x >> initial.bodies[i].y;
    }

    cin >> nRock;
    for ( int i = 0; i < nRock; i++ ){
	cin >> rocks[i].x >> rocks[i].y;
    }

    cin >> goal.x >> goal.y;

    return true;
}

main(){
    while ( input() ) compute();
}