// @JUDGE_ID:  17051CA  297  C++
// @begin_of_source_code
#include<stdio.h>
#include<iostream>
#include<string>
#define MAX 35

void work();
void rec(int, int, int);

string line;
int index;
int sum;
int A[MAX][MAX], B[MAX][MAX];
char sig;

void fill(int, int, int);
void init();

void init(){
  for(int i=1; i<=32; i++){
    for(int j=1; j<=32; j++){
      A[i][j] = 0; B[i][j] = 0;
    }
  }
}

void work(){
  init();
  sum = 0;

  cin >> line; sig = 'a';
  index = 0;
  if(line[index]=='p')  rec(1, 32, 32);
  else if(line[index]=='f') fill(32, 32, 32);

  cin >> line; sig = 'b';
  index = 0;
  if(line[index]=='p')  rec(1, 32, 32);
  else if(line[index]=='f') fill(32, 32, 32);

  int sum = 0;
  for(int i=1; i<=32; i++){
    for(int j=1; j<=32; j++){
      A[i][j] = (A[i][j]|B[i][j]);
      if(A[i][j]) sum++;
    }
  }

  cout << "There are " << sum << " black pixels." << endl;
}

void rec(int depth, int i, int j){
  int pow = 1;
  for(int a=0; a<depth; a++){
    pow *= 2;
  }
  int base = 32/pow;
  for(int d=1; d<=4; d++){
    index++;
    char c = line[index];
    if(c =='p'){
      if(d==1) rec(depth+1, i-base, j);
      if(d==2) rec(depth+1, i-base, j-base);
      if(d==3) rec(depth+1, i, j-base);
      if(d==4) rec(depth+1, i, j);
    }else if(c=='f'){
      if(d==1) fill(base, i-base, j);
      if(d==2) fill(base, i-base, j-base);
      if(d==3) fill(base, i, j-base);
      if(d==4) fill(base, i, j);
    }
  }
}

void fill(int base, int i, int j){
  /*cout << "fill " << "i " << i  << " j " << j << " base " << base << endl;*/
  if(sig=='a'){
    for(int a=i; a>=i-base+1; a--){
      for(int b=j; b>=j-base+1; b--){
	A[a][b] = 1;
      }
    }
  }else if(sig=='b'){
    for(int a=i; a>=i-base+1; a--){
      for(int b=j; b>=j-base+1; b--){
	B[a][b] = 1;
      }
    }
  }
}

main(){
  int n;
  cin >> n;
  for(int i=0; i<n; i++){
    work();
  }
}
// @end_of_source_code