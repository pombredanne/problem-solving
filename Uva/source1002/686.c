// @JUDGE_ID:  17051CA  686  C++
// @begin_of_source_code
#include<stdio.h>
#include<vector>
#include<math.h>
#include<iostream.h>

typedef unsigned long ulong;
int read();
void work();
void eratos(ulong x, vector<bool> &primes); 
void eratos(ulong a, ulong b, vector<ulong> &p);

/*
 * ����ȥ��ƥͥ����� version 2 (The sieve of Eratosthenes)
 * �Ķ��[min(a, b), max(a, b)], a, b>0, ����ǿ���vector<ulong>������롣
 * �׷�: �ؿ� eratos (version 1)
 */
void eratos(ulong a, ulong b, vector<ulong> &p){
  vector<bool> v;
  ulong i;
  if(a>b) swap(a, b);
  if(b<2) return;
  if(b==2){ p = vector<ulong>(1, 2); return; }
  eratos(b, v);
  if(a<=2){ p.push_back(2); a = 2; }
  for(i=(a-2)/2; i<=(b-3)/2; i++)
    if(v[i]) p.push_back(2*i+3);
}

/* 
 * ����ȥ��ƥͥ����� version 1 (The sieve of Eratosthenes)
 * �Ķ��[3, x], x>=3, ��δ�����ǿ����ɤ�����vector<bool>������롣
 * primes[i] == true �� 2*i+3 ���ǿ��Ǥ��뤳�Ȥ�ɽ����
 * �׷�: �ʤ�
 */
void eratos(ulong x, vector<bool> &primes){
  ulong i, j;
  primes = vector<bool>((x-1)/2, 1);
  for(i=3; i<=sqrt(x); i+=2)
    for(j=3; i*j<=x; j+=2)
      primes[(i*j-3)/2] = 0;
}

vector<ulong> p;
ulong n;

int read(){
  cin >> n;
  if( n==0 ) return 0;
  else return 1;
}

void work(){
  int count = 0;
  for(int i=0; p[i] <= n && i<p.size(); i++){
    for(int j=i; p[i]+p[j]<=n && j<p.size(); j++){
      if( n == p[i]+p[j] ) count++;
    }
  }
  cout << count << endl;
}

main(){
  p.clear();
  eratos(1, pow(2,16), p );
  while(read()){
    work();
  }
}
// @end_of_source_code
