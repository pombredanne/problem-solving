#include<iostream>
#include<algorithm>
using namespace std;

struct Point{int x, y;};

class Cube{
public:
  char C[3];
  Cube(){ C[0] = 'W'; C[1] = 'R'; C[2] = 'B';}
  void setEmpty(){ C[0] = 'E';}
  void rotate(int d){
    if ( d % 2 == 0 ) swap(C[0], C[2]);
    else swap(C[0], C[1]);
  }
};

char target[3][3];

class Puzzle{
public:
  Cube cubes[3][3];
  Point empty;
  int manhattanDist;

  Puzzle(){
    for ( int y = 0; y < 3; y++ ){
      for ( int x = 0; x < 3; x++ ) cubes[y][x] = Cube();
    }
  }

  void setEmpty( int y, int x ){
    empty.x = x; empty.y = y;
    cubes[y][x].setEmpty();
  }

  void setmanhattanDist(){
    manhattanDist = 0;
    for ( int y = 0; y < 3; y++ ){
      for ( int x = 0; x < 3; x++ ){
	if ( cubes[y][x].C[0] != target[y][x] ) manhattanDist++;
      }
    }
  }

  void upDate( int y, int x, int d ){
    if ( target[y][x] != cubes[y][x].C[0] ) manhattanDist += d;
  }
};

int ix, iy, tx, ty, limit;
Puzzle u;
static const int dy[4] = {0, -1, 0, 1};
static const int dx[4] = {1, 0, -1, 0};


bool dfs( int depth, int pre, int seq ){
  if ( depth + u.manhattanDist-1 > limit ) return false;
  if ( u.manhattanDist == 0 ) return true;

  int x, y, nx, ny;

  y = u.empty.y;
  x = u.empty.x;

  Puzzle tmp = u;

  for ( int d = 0; d < 4; d++ ){
    if ( pre != -1 && d == (pre+2)%4 ) continue;
    ny = y + dy[d];
    nx = x + dx[d];
    if ( ny < 0 || nx < 0 || 3 <= nx || 3 <= ny ) continue;
    
    u = tmp;

    u.upDate(ny, nx, -1);
    u.upDate(y, x, -1);

    u.cubes[ny][nx].rotate(d);
    u.cubes[y][x] = u.cubes[ny][nx];
    u.setEmpty(ny, nx);

    u.upDate(ny, nx, 1);
    u.upDate(y, x, 1);

    if ( dfs( depth+1, d, seq) ) return true;
  }

  return false;
}

void compute(){
  Puzzle initial = Puzzle();
  initial.setEmpty(iy, ix);
  initial.setmanhattanDist();
  int start = initial.manhattanDist -1;
  while( start % 3 != 0 ) start--;
  for ( limit = start; limit <= 30; limit+=3 ){
    u = initial;
    if ( dfs(  0, -1, 0 ) ) {
      if ( limit == 0 ) {cout << 0 << endl; return;}
      limit -= 2;
      u = initial;
      if ( dfs(0, -1, 0 ) ) {
	cout << limit << endl;
      } else {
	limit++;
	u = initial;
	if ( dfs(0, -1, 0) ) cout << limit << endl;
	else cout << limit + 1 << endl;
      }
      return;
    }
  }
  cout << -1 << endl;
}

bool input(){
  cin >> ix >> iy;
  if ( ix == 0 && iy == 0 ) return false;
  ix--; iy--;
  for ( int y = 0; y < 3; y++ ){
    for ( int x = 0; x < 3; x++ ){
      cin >> target[y][x];
      if ( target[y][x] == 'E' ){ tx = x; ty = y; }
    }
  }
  return true;
}

main(){
  while(input()) compute();
}
