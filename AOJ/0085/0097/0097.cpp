#include<iostream>
#include<cstdio>
using namespace std;
#define L 100
long long dp[L+1][11][1001];

main(){
  for ( int i = 0; i <= L; i++ )
    for ( int j = 0; j <= 10; j++ )
      for ( int k = 0; k <= 100; k++ ) dp[i][j][k] = 0;
  
  dp[0][0][0] = dp[0][1][0] = 1;

  for ( int i = 1; i <= L; i++ ){
    for ( int j = 0; j <= 10; j++ ){
      for ( int k = 0; k <= 1000; k++ ){
	dp[i][j][k] = dp[i-1][j][k];
	if ( k - i >= 0 && j > 0 ){
	  dp[i][j][k] += dp[i-1][j-1][k-i];
	}
      }
    }
  }

  int n, s;
  int tcase = 0;
  while(1){
    cin >> n >> s;
    if ( n == 0 && s == 0 ) break;
    tcase++;
    cout << dp[L][n][s] << endl;
  }
}
