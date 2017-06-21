// @JUDGE_ID:  17051CA  10296  C++
// @begin_of_source_code
/* Chinese Postman Problem */
#include<stdio.h>
#include<iostream>
#include<climits>
#include<stl.h>
#define MAX 16

int n, nodd;
int M[MAX][MAX];
int D[MAX];
int ODD[MAX];
int C[MAX];
int totalCost;
int minAdd;

void floyd(){
  int inf = INT_MIN;
  for ( int i = 0; i < n; i++ ){
    for( int j = 0; j < n; j++ ){
      if ( i == j ) M[i][j] = 0;
      if ( i != j && M[i][j] == INT_MAX ) M[i][j] = inf;
    }
  }
  for ( int k = 0; k < n; k++ ){
    for ( int i = 0; i < n; i++ ){
      if ( M[i][k] == inf ) continue;
      for ( int j = 0; j < n; j++ ){
	if ( M[k][j] == inf ) continue;
	if ( M[i][j] == inf || M[i][k] + M[k][j] < M[i][j] ){
	  M[i][j] = M[i][k] + M[k][j];
	}
      }
    }
  }
}

void rec(int id){
  int start = -1;

  for ( int i = 0; i < nodd; i++ ){
    if ( C[i] == -1 ){ start = i; C[i] = id; break;}
  }

  if ( start == -1 ) {
    int sum = 0;
    for ( int i = 0; i < nodd-1; i++ ){
      for ( int j = i+1; j < nodd; j++ ){
	if ( C[i] == C[j] ){
	  int source = ODD[ i ];
	  int target = ODD[ j ];
	  sum += M[source][target];
	}
      }
    } 
    if ( sum < minAdd ) minAdd = sum;
    return;
  }
  
  for ( int i = 0; i < nodd; i++ ){
    if ( C[i] == -1){
      C[i] = id;
      rec(id+1);
      C[i] = -1;
    }
  }
  C[start] = -1;
}

void combination(){
  for ( int i = 0; i < nodd; i++ ) C[i] = -1;
  rec(0);
}

void work(){
  floyd();

  minAdd = INT_MAX;

  nodd = 0;
  for ( int i = 0; i < n; i++ ){
    if ( D[i] % 2 != 0 ){
      ODD[nodd++] = i;
    }
  }

  combination();

  printf("%d\n", minAdd + totalCost);
}

bool read(){
  int m, source, target, cost;
  scanf("%d", &n); if ( n == 0 ) return false;

  for ( int i = 0; i < n; i++  ){
    for ( int j = 0; j < n; j++ ){
      M[i][j] = INT_MAX;
    }
    D[i] = 0;
  }
  totalCost = 0;
  
  scanf("%d", &m);
  for ( int i = 0; i < m; i++ ){
    scanf("%d %d %d", &source, &target, &cost );
    source--; target--;
    M[source][target] = min(M[source][target], cost);
    M[target][source] = min(M[target][source], cost);
    D[source]++;
    D[target]++;
    totalCost += cost;
  }

  return true;
}

main(){
  while (read()){
    work();
  }
}
// @end_of_source_code